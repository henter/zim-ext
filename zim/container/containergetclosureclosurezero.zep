namespace Zim\Container;

class ContainergetClosureClosureZero
{
    private abstractt;
    private concrete;

    public function __construct(abstractt, concrete)
    {
        let this->abstractt = abstractt;
        let this->concrete = concrete;
    }

    public function __invoke(container, parameters = [])
    {
        if this->abstractt == this->concrete {
            return container->build(this->concrete);
        }
        return container->make(this->concrete, parameters);
    }
}
    