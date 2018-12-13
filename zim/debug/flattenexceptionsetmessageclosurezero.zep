namespace Zim\Debug;

class FlattenExceptionsetMessageClosureZero
{

    public function __construct()
    {
        
    }

    public function __invoke(m)
    {
    return  \class_exists(m[0], false) ? get_parent_class(m[0]) . "@anonymous"  : m[0];
    }
}
    