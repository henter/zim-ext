namespace Zim\Container;

class BoundMethodcallClosureZero
{
    private container;
    private callback;
    private parameters;

    public function __construct(container, callback, parameters)
    {
                let this->container = container;
        let this->callback = callback;
        let this->parameters = parameters;

    }

    public function __invoke()
    {
    return call_user_func_array(this->callback, BoundMethod::getMethodDependencies(this->container, this->callback, this->parameters));
    }
}
    