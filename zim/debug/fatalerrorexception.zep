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
 * Fatal Error Exception.
 *
 * @author Konstanton Myakshin <koc-dp@yandex.ru>
 */
class FatalErrorException extends \ErrorException
{
    protected originalClassName;
    public function __construct(<Throwable> e) -> void
    {
        var severity;

        let this->originalClassName =  get_class(e);
        if e instanceof \ParseError {
            let severity =  E_PARSE;
        } elseif e instanceof \TypeError {
            let severity =  E_RECOVERABLE_ERROR;
        } else {
            let severity =  E_ERROR;
        }
        parent::__construct(e->getMessage(), e->getCode(), severity, e->getFile(), e->getLine(), e->getPrevious());
        this->setTrace(e->getTrace());
    }
    
    public function getOriginalClassName()
    {
        return this->originalClassName;
    }
    
    protected function setTrace(trace) -> void
    {
        var traceReflector;
    
        let traceReflector =  new \ReflectionProperty("Exception", "trace");
        traceReflector->setAccessible(true);
        traceReflector->setValue(this, trace);
    }

}