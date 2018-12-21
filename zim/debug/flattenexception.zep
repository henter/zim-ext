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
 * FlattenException wraps a PHP Error or Exception to be able to serialize it.
 *
 * Basically, this class removes all objects from the trace.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
class FlattenException
{
    protected message;
    protected code;
    protected previous;
    protected trace;
    protected classs;
    protected statusCode;
    protected headers;
    protected file;
    protected line;
    public static function create(<Exception> exception, statusCode = null, array headers = [])
    {
        return static::createFromThrowable(exception, statusCode, headers);
    }
    
    public static function createFromThrowable(<Throwable> exception, int _statusCode = 0, array headers = [])
    {
        var e, previous, statusCode;
        let statusCode = _statusCode;
    
        let e = new static();
        e->setMessage(exception->getMessage());
        e->setCode(exception->getCode());
        if exception instanceof \Zim\Http\Exception\ExceptionInterface {
            let statusCode = exception->getStatusCode();
            let headers = array_merge(headers, exception->getHeaders());
        }
        if !statusCode {
            let statusCode = 500;
        }
        e->setStatusCode(statusCode);
        e->setHeaders(headers);
        e->setTraceFromThrowable(exception);
        e->setClass( exception instanceof FatalErrorException ? exception->getOriginalClassName() : get_class(exception));
        e->setFile(exception->getFile());
        e->setLine(exception->getLine());
        let previous = exception->getPrevious();
        if previous instanceof \Throwable {
            e->setPrevious(static::createFromThrowable(previous));
        }
        return e;
    }
    
    public function toArray()
    {
        var exceptions, exception;
    
        let exceptions = [];
        let exceptions[] = ["message" : this->getMessage(), "class" : this->getClass(), "trace" : this->getTrace()];

        for exception in this->getAllPrevious() {
            let exceptions[] = ["message" : exception->getMessage(), "class" : exception->getClass(), "trace" : exception->getTrace()];
        }
        return exceptions;
    }
    
    public function getStatusCode()
    {
        return this->statusCode;
    }
    
    /**
     * @return $this
     */
    public function setStatusCode(code)
    {
        let this->statusCode = code;
        return this;
    }
    
    public function getHeaders()
    {
        return this->headers;
    }
    
    /**
     * @return $this
     */
    public function setHeaders(array headers)
    {
        let this->headers = headers;
        return this;
    }
    
    public function getClass()
    {
        return this->classs;
    }
    
    /**
     * @return $this
     */
    public function setClass(var c)
    {
        if substr(c, 0, 1) === "c" && 0 === strpos(c, "class@anonymous\0") {
            let this->classs = get_parent_class(c);
        } else {
            let this->classs = c;
        }
        return this;
    }
    
    public function getFile()
    {
        return this->file;
    }
    
    /**
     * @return $this
     */
    public function setFile(file)
    {
        let this->file = file;
        return this;
    }
    
    public function getLine()
    {
        return this->line;
    }
    
    /**
     * @return $this
     */
    public function setLine(line)
    {
        let this->line = line;
        return this;
    }
    
    public function getMessage()
    {
        return this->message;
    }
    
    /**
     * @return $this
     */
    public function setMessage(message)
    {
        if strpos((string)message, "class@anonymous\0") !== false {
            let message = preg_replace_callback("/class@anonymous\\x00.*?\\.php0x?[0-9a-fA-F]++/", new FlattenExceptionsetMessageClosureOne(), message);
        }
        let this->message = message;
        return this;
    }
    
    public function getCode()
    {
        return this->code;
    }
    
    /**
     * @return $this
     */
    public function setCode(code)
    {
        let this->code = code;
        return this;
    }
    
    public function getPrevious()
    {
        return this->previous;
    }
    
    /**
     * @return $this
     */
    public function setPrevious(<self> previous)
    {
        let this->previous = previous;
        return this;
    }
    
    public function getAllPrevious()
    {
        var exceptions, e;
    
        let exceptions = [];
        let e = this;
        let e = e->getPrevious();
        while (e) {
            let exceptions[] = e;
        let e = e->getPrevious();
        }
        return exceptions;
    }
    
    public function getTrace()
    {
        return this->trace;
    }
    
    public function setTraceFromThrowable(<Throwable> throwable)
    {
        return this->setTrace(throwable->getTrace(), throwable->getFile(), throwable->getLine());
    }
    
    /**
     * @return $this
     */
    public function setTrace(trace, file, line)
    {
        var entry, classs, namespacee, parts;
    
        let this->trace = [];
        let this->trace[] = ["namespace" : "", "short_class" : "", "class" : "", "type" : "", "function" : "", "file" : file, "line" : line, "args" : []];
        for entry in trace {
            let classs = "";
            let namespacee = "";
            if isset entry["class"] {
                let parts = explode("\\", entry["class"]);
                let classs = array_pop(parts);
                let namespacee = implode("\\", parts);
            }
            let this->trace[] = [
                "namespace" : namespacee,
                "short_class" : classs,
                "class" :  isset entry["class"] ? entry["class"] : "",
                "type" :  isset entry["type"] ? entry["type"] : "",
                "function" :  isset entry["function"] ? entry["function"] : null,
                "file" :  isset entry["file"] ? entry["file"] : null,
                "line" :  isset entry["line"] ? entry["line"] : null,
                "args" :  isset entry["args"] ? this->flattenArgs(entry["args"]) : []
            ];
        }
        return this;
    }
    
    protected function flattenArgs(args, level = 0, count = 0)
    {
        var result, key, value;

        let result = [];
        for key, value in args {
            if count > 10000 {
                return ["array", "*SKIPPED over 10000 entries*"];
            }
            if typeof value == "object" && value instanceof \__PHP_Incomplete_Class {
                // is_object() returns false on PHP<=7.1
                let result[key] = ["incomplete-object", this->getClassNameFromIncomplete(value)];
            } elseif is_object(value) {
                let result[key] = ["object", get_class(value)];
            } elseif is_array(value) {
                if level > 10 {
                    let result[key] = ["array", "*DEEP NESTED ARRAY*"];
                } else {
                    let result[key] = ["array", this->flattenArgs(value, level + 1, count + 1)];
                }
            } elseif null === value {
                let result[key] = ["null", null];
            } elseif is_bool(value) {
                let result[key] = ["boolean", value];
            } elseif is_int(value) {
                let result[key] = ["integer", value];
            } elseif is_float(value) {
                let result[key] = ["float", value];
            } elseif is_resource(value) {
                let result[key] = ["resource", get_resource_type(value)];
            } else {
                let result[key] = ["string", (string) value];
            }
        }
        return result;
    }
    
    protected function getClassNameFromIncomplete(<__PHP_Incomplete_Class> value)
    {
        var myArray;
    
        let myArray = new \ArrayObject(value);
        return myArray["__PHP_Incomplete_Class_Name"];
    }

}