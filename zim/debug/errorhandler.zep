/*
 * This file is part of the Symfony package.
 *
 * (c) Fabien Potencier <fabien@symfony.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
namespace Zim\Debug;

/**
 * A generic ErrorHandler for the PHP engine.
 *
 * Provides five bit fields that control how errors are handled:
 * - thrownErrors: errors thrown as \ErrorException
 * - loggedErrors: logged errors, when not @-silenced
 * - scopedErrors: errors thrown or logged with their local context
 * - tracedErrors: errors logged with their stack trace
 * - screamedErrors: never @-silenced errors
 *
 * Each error level can be logged by a dedicated PSR-3 logger object.
 * Screaming only applies to logging.
 * Throwing takes precedence over logging.
 * Uncaught exceptions are logged as E_ERROR.
 * E_DEPRECATED and E_USER_DEPRECATED levels never throw.
 * E_RECOVERABLE_ERROR and E_USER_ERROR levels always throw.
 * Non catchable errors that can be detected at shutdown time are logged when the scream bit field allows so.
 * As errors have a performance cost, repeated errors are all logged, so that the developer
 * can see them and weight them as more important to fix than others of the same level.
 *
 * @author Nicolas Grekas <p@tchwork.com>
 * @author Grégoire Pineau <lyrixx@lyrixx.info>
 */
class ErrorHandler
{
    protected levels = [
        8192: "Deprecated",
        16384: "User Deprecated",
        8: "Notice",
        1024: "User Notice",
        2048: "Runtime Notice",
        2: "Warning",
        512: "User Warning",
        128: "Compile Warning",
        32: "Core Warning",
        256: "User Error",
        4096: "Catchable Fatal Error",
        64: "Compile Error",
        4: "Parse Error",
        1: "Error",
        16: "Core Error"
    ];
    protected thrownErrors = 0x1FFF;
    // E_ALL - E_DEPRECATED - E_USER_DEPRECATED
    protected screamedErrors = 0x55;
    // E_ERROR + E_CORE_ERROR + E_COMPILE_ERROR + E_PARSE
    protected traceReflector;
    protected exceptionHandler;
    /**
     * Registers the error handler.
     *
     * @param self|null $handler The handler to register
     *
     * @return self The registered error handler
     */
    public static function register(<self> handler = null)
    {
        var prev;
    
        if handler === null {
            let handler = new static();
        }
        let prev = set_error_handler([handler, "handleError"]);
        if prev === null {
            restore_error_handler();
            set_error_handler([handler, "handleError"], handler->thrownErrors);
        }
        let prev = set_exception_handler([handler, "handleException"]);
        handler->setExceptionHandler(prev);
        return handler;
    }
    
    public function __construct() -> void
    {
        let this->traceReflector = new \ReflectionProperty("Exception", "trace");
        this->traceReflector->setAccessible(true);
    }
    
    /**
     * Sets a user exception handler.
     *
     * @param callable $handler A handler that will be called on Exception
     *
     * @return callable|null The previous exception handler
     */
    public function setExceptionHandler(var handler = null)
    {
        var prev;
    
        let prev = this->exceptionHandler;
        let this->exceptionHandler = handler;
        return prev;
    }
    
    /**
     * Handles errors by filtering then logging them according to the configured bit fields.
     *
     * @param int    $type    One of the E_* constants
     * @param string $message
     * @param string $file
     * @param int    $line
     *
     * @throws \ErrorException When $this->thrownErrors requests so
     *
     * @internal
     */
    public function handleError(int type, string message, string file, int line) -> void
    {
        var level, msg, errorAsException;
    
        let level = error_reporting();
        let level = level | (E_RECOVERABLE_ERROR | E_USER_ERROR | E_DEPRECATED | E_USER_DEPRECATED);
        let type = level & (level | this->screamedErrors);
        let msg = this->levels[type] . ": " . message;
        let errorAsException = new \ErrorException(msg, 0, type, file, line);
        this->traceReflector->setValue(errorAsException, errorAsException->getTrace());
        throw errorAsException;
    }
    
    /**
     * @param $exception
     * @return mixed
     * @throws FatalErrorException
     * @throws \Throwable
     */
    public function handleException(var exception)
    {
        var handlerException, exceptionHandler;
        if typeof exception == "object" && !(exception instanceof \Exception) {
            let exception = new FatalErrorException(exception);
        }
        let handlerException = null;
        let exceptionHandler = this->exceptionHandler;
        let this->exceptionHandler = null;
        try {
            if exceptionHandler !== null {
                return call_user_func(exceptionHandler, exception);
            }
            let handlerException = handlerException ?: exception;
        } catch \Throwable, handlerException {
        }
        if exception === handlerException {
            throw exception;
        }
        this->handleException(handlerException);
    }

}