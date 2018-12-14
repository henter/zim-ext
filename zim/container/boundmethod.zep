namespace Zim\Container;

use Closure;
use ReflectionMethod;
use ReflectionFunction;
use InvalidArgumentException;
class BoundMethod
{
    /**
     * Call the given Closure / class@method and inject its dependencies.
     *
     * @param  Container  $container
     * @param  callable|string  $callback
     * @param  array  $parameters
     * @param  string|null  $defaultMethod
     * @return mixed
     */
    public static function call(<Container> container, callback, array parameters = [], defaultMethod = null)
    {
        if static::isCallableWithAtSign(callback) || defaultMethod {
            return static::callClass(container, callback, parameters, defaultMethod);
        }
        return static::callBoundMethod(container, callback, new BoundMethodcallClosureZero(container, callback, parameters));
    }
    
    /**
     * Call a string reference to a class using Class@method syntax.
     *
     * @param  Container  $container
     * @param  string  $target
     * @param  array  $parameters
     * @param  string|null  $defaultMethod
     * @return mixed
     *
     * @throws \InvalidArgumentException
     */
    protected static function callClass(<Container> container, string target, array parameters = [], defaultMethod = null)
    {
        var segments, method, tmpArrayfc3097742aa3c3120f5545e8f51f1abf;
    
        let segments =  explode("@", target);
        // We will assume an @ sign is used to delimit the class name from the method
        // name. We will split on this @ sign and then build a callable array that
        // we can pass right back into the "call" method for dependency binding.
        let method =  count(segments) === 2 ? segments[1]  : defaultMethod;
        if is_null(method) {
            throw new InvalidArgumentException("Method not provided.");
        }
        let tmpArrayfc3097742aa3c3120f5545e8f51f1abf = [container->make(segments[0]), method];
        return static::call(container, tmpArrayfc3097742aa3c3120f5545e8f51f1abf, parameters);
    }
    
    /**
     * Call a method that has been bound to the container.
     *
     * @param  Container  $container
     * @param  callable  $callback
     * @param  mixed  $deft
     * @return mixed
     */
    protected static function callBoundMethod(<Container> container, callback, deft)
    {
        var method;
    
        if !(is_array(callback)) {
            return (typeof deft == "object" && deft instanceof Closure) ? {deft}() : deft;
        }
        // Here we need to turn the array callable into a Class@method string we can use to
        // examine the container and see if there are any method bindings for this given
        // method. If there are, we can call this method binding callback immediately.
        let method =  static::normalizeMethod(callback);
        if container->hasMethodBinding(method) {
            return container->callMethodBinding(method, callback[0]);
        }
        return  (typeof deft == "object" && deft instanceof Closure) ? {deft}() : deft;
    }
    
    /**
     * Normalize the given callback into a Class@method string.
     *
     * @param  callable  $callback
     * @return string
     */
    protected static function normalizeMethod(callback) -> string
    {
        var classs;
    
        let classs =  is_string(callback[0]) ? callback[0]  : get_class(callback[0]);
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
    protected static function getMethodDependencies(<Container> container, callback, array parameters = []) -> array
    {
        var dependencies, parameter, tmpListParametersDependencies, tmpparams, tmpdeps;
    
        let dependencies =  [];
        for parameter in static::getCallReflector(callback)->getParameters() {
            let tmpListParametersDependencies = static::addDependencyForCallParameter(container, parameter, parameters, dependencies);
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
    public static function getCallReflector(callback) -> <\ReflectionFunctionAbstract>
    {
        if is_string(callback) && strpos(callback, "::") !== false {
            let callback =  explode("::", callback);
        }
        return  is_array(callback) ? new ReflectionMethod(callback[0], callback[1])  : new ReflectionFunction(callback);
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
            let dependencies[] =  container->make(parameter->getClass()->name);
        } elseif parameter->isDefaultValueAvailable() {
            let dependencies[] =  parameter->getDefaultValue();
        }
        return [parameters, dependencies];
    }
    
    /**
     * Determine if the given string is in Class@method syntax.
     *
     * @param  mixed  $callback
     * @return bool
     */
    protected static function isCallableWithAtSign(callback) -> bool
    {
        return is_string(callback) && strpos(callback, "@") !== false;
    }

}