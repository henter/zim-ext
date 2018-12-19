namespace Zim\Container;

use Closure;
use InvalidArgumentException;
use ReflectionFunctionAbstract;

class BoundMethod
{
    /**
     * Call the given Closure / callable and inject its dependencies.
     *
     * @param  Container  $container
     * @param  callable $callback
     * @param  array  $parameters
     * @return mixed
     */
    public static function call(<Container> container, var callback, array parameters = [])
    {
        if typeof callback != "array" {
            return call_user_func_array(
                callback, self::getMethodDependencies(container, callback, parameters)
            );
        }

        var method;
        let method = static::normalizeMethod(callback);
        if container->hasMethodBinding(method) {
            return container->callMethodBinding(method, callback[0]);
        }
        return call_user_func_array(
            callback, self::getMethodDependencies(container, callback, parameters)
        );
    }

    /**
     * Normalize the given callback into a Class@method string.
     *
     * @param  callable  $callback
     * @return string
     */
    protected static function normalizeMethod(array callback) -> string
    {
        var classs;
    
        let classs = is_string(callback[0]) ? callback[0] : get_class(callback[0]);
        return "{classs}@{callback[1]}";
    }
    
    /**
     * Get all dependencies for a given method.
     *
     * @param  Container  $container
     * @param  callable|string  $callback
     * @param  array  $parameters
     * @return array
     */
    public static function getMethodDependencies(<Container> container, var callback, array parameters = []) -> array
    {
        var dependencies, parameter, tmpListParametersDependencies, tmpparams, tmpdeps;

        let dependencies = [];
        for parameter in self::getCallReflector(callback)->getParameters() {
            let tmpListParametersDependencies = self::addDependencyForCallParameter(container, parameter, parameters, dependencies);
            if isset tmpListParametersDependencies[1] {
                let tmpparams = tmpListParametersDependencies[0];
                let tmpdeps = tmpListParametersDependencies[1];
                let parameters = tmpparams;
                let dependencies = tmpdeps;
            }
        }
        return array_merge(dependencies, parameters);
    }
    
    /**
     * Get the proper reflection instance for the given callback.
     *
     * @param  callable|string $callback
     * @return \ReflectionFunctionAbstract
     *
     * @throws \ReflectionException
     */
    public static function getCallReflector(var callback) -> <ReflectionFunctionAbstract>
    {
        if is_string(callback) && strpos(callback, "::") !== false {
            let callback = explode("::", callback);
        }
        return typeof callback == "array" ? new \ReflectionMethod(callback[0], callback[1]) : new \ReflectionFunction(callback);
    }
    
    /**
     * Get the dependency for the given call parameter.
     *
     * @param  Container  $container
     * @param  \ReflectionParameter  $parameter
     * @param  array  $parameters
     * @param  array  $dependencies
     * @return mixed
     */
    protected static function addDependencyForCallParameter(<Container> container, <\ReflectionParameter> parameter, array parameters, array dependencies)
    {
        if array_key_exists(parameter->name, parameters) {
            let dependencies[] = parameters[parameter->name];
            unset parameters[parameter->name];
        
        } elseif parameter->getClass() && array_key_exists(parameter->getClass()->name, parameters) {
            let dependencies[] = parameters[parameter->getClass()->name];
            unset parameters[parameter->getClass()->name];
        
        } elseif parameter->getClass() {
            let dependencies[] = container->make(parameter->getClass()->name);
        } elseif parameter->isDefaultValueAvailable() {
            let dependencies[] = parameter->getDefaultValue();
        }
        return [parameters, dependencies];
    }

}