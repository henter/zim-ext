namespace Zim\Container;

class ContainersetClosureOne
{
    private value;

    public function __construct(value)
    {
                let this->value = value;

    }

    public function __invoke()
    {
    return this->value;
    }
}
    