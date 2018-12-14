namespace Zim\Container;

use Closure;
use Exception;
use LogicException;
use ReflectionClass;
use ReflectionParameter;
class Container
{
    /**
     * The current globally available container (if any).
     *
     * @var static
     */
    protected static instance;
    /**
     * An array of the types that have been resolved.
     *
     * @var array
     */
    protected resolved = [];
    /**
     * The container's bindings.
     *
     * @var array
     */
    protected bindings = [];
    /**
     * The container's method bindings.
     *
     * @var array
     */
    protected methodBindings = [];
    /**
     * The container's shared instances.
     *
     * @var array
     */
    protected instances = [];
    /**
     * The registered type aliases.
     *
     * @var array
     */
    protected aliases = [];
    /**
     * The registered aliases keyed by the abstract name.
     *
     * @var array
     */
    protected abstractAliases = [];
    /**
     * The extension closures for services.
     *
     * @var array
     */
    protected extenders = [];
    /**
     * The stack of concretions currently being built.
     *
     * @var array
     */
    protected buildStack = [];
    /**
     * The parameter override stack.
     *
     * @var array
     */
    protected with = [];
    /**
     * The contextual binding map.
     *
     * @var array
     */
    public contextual = [];
    /**
     * Define a contextual binding.
     *
     * @param  array|string  $concrete
     * @return \Zim\Container\ContextualBindingBuilder
     */
    public function when(concrete) -> <\Zim\Container\ContextualBindingBuilder>
    {
        var aliases, concretes, c;
    
        let aliases =  [];
        let concretes =  is_array(concrete) ? concrete  : [concrete];
        for c in concretes {
            let aliases[] =  this->getAlias(c);
        }
        return new ContextualBindingBuilder(this, aliases);
    }
    
    /**
     * Determine if the given abstract type has been bound.
     *
     * @param  string  $abstract
     * @return bool
     */
    public function bound(string abstractt) -> bool
    {
        return isset this->bindings[abstractt] || isset this->instances[abstractt] || this->isAlias(abstractt);
    }
    
    /**
     *  {@inheritdoc}
     */
    public function has(id)
    {
        return this->bound(id);
    }
    
    /**
     * Determine if the given abstract type has been resolved.
     *
     * @param  string  $abstract
     * @return bool
     */
    public function resolved(string abstractt) -> bool
    {
        if this->isAlias(abstractt) {
            let abstractt =  this->getAlias(abstractt);
        }
        return isset this->resolved[abstractt] || isset this->instances[abstractt];
    }
    
    /**
     * Determine if a given type is shared.
     *
     * @param  string  $abstract
     * @return bool
     */
    public function isShared(string abstractt) -> bool
    {
        return isset this->instances[abstractt] || isset this->bindings[abstractt]["shared"] && this->bindings[abstractt]["shared"] === true;
    }
    
    /**
     * Determine if a given string is an alias.
     *
     * @param  string  $name
     * @return bool
     */
    public function isAlias(string name) -> bool
    {
        return isset this->aliases[name];
    }
    
    /**
     * Register a binding with the container.
     *
     * @param  string  $abstract
     * @param  \Closure|string|null  $concrete
     * @param  bool  $shared
     * @return void
     */
    public function bind(string abstractt, concrete = null, bool shared = false)
    {
        // If no concrete type was given, we will simply set the concrete type to the
        // abstract type. After that, the concrete type to be registered as shared
        // without being forced to state their classes in both of the parameters.
        this->dropStaleInstances(abstractt);
        if is_null(concrete) {
            let concrete = abstractt;
        }
        // If the factory is not a Closure, it means it is just a class name which is
        // bound into this container to the abstract type and we will just wrap it
        // up inside its own Closure to give us more convenience when extending.
        if !(typeof concrete == "object" && concrete instanceof Closure) {
            let concrete =  this->getClosure(abstractt, concrete);
        }
        let this->bindings[abstractt] = [
            "concrete": concrete,
            "shared": shared
        ];
    }
    
    /**
     * Get the Closure to be used when building a type.
     *
     * @param  string  $abstract
     * @param  string  $concrete
     * @return \Closure
     */
    protected function getClosure(string abstractt, string concrete) -> <ContainergetClosureClosureZero>
    {
        return new ContainergetClosureClosureZero(abstractt, concrete);
    }
    
    /**
     * Determine if the container has a method binding.
     *
     * @param  string  $method
     * @return bool
     */
    public function hasMethodBinding(string method) -> bool
    {
        return isset this->methodBindings[method];
    }
    
    /**
     * Bind a callback to resolve with Container::call.
     *
     * @param  array|string  $method
     * @param  \Closure  $callback
     * @return void
     */
    public function bindMethod(method, <\Closure> callback)
    {
        var tmpThis1;
    
        
        this->parseBindMethod(method);
        let tmpThis1 = this;
        
        let this->methodBindings[tmpThis1] = callback;
    }
    
    /**
     * Get the method to be bound in class@method format.
     *
     * @param  array|string $method
     * @return string
     */
    protected function parseBindMethod(method) -> string
    {
        if is_array(method) {
            return method[0] . "@" . method[1];
        }
        return method;
    }
    
    /**
     * Get the method binding for the given method.
     *
     * @param  string  $method
     * @param  mixed  $instance
     * @return mixed
     */
    public function callMethodBinding(string method, instance)
    {
        return call_user_func(this->methodBindings[method], instance, this);
    }
    
    /**
     * Add a contextual binding to the container.
     *
     * @param  string  $concrete
     * @param  string  $abstract
     * @param  \Closure|string  $implementation
     * @return void
     */
    public function addContextualBinding(string concrete, string abstractt, implementation)
    {
        var tmpThis1;
    
        
        this->getAlias(abstractt);
        let tmpThis1 = this;
        
        let this->contextual[concrete][tmpThis1] = implementation;
    }
    
    /**
     * Register a shared binding in the container.
     *
     * @param  string  $abstract
     * @param  \Closure|string|null  $concrete
     * @return void
     */
    public function singleton(string abstractt, concrete = null)
    {
        this->bind(abstractt, concrete, true);
    }
    
    /**
     * "Extend" an abstract type in the container.
     *
     * @param  string    $abstract
     * @param  \Closure  $closure
     * @return void
     *
     * @throws \InvalidArgumentException
     */
    public function extend(string abstractt, <Closure> closure)
    {
        let abstractt =  this->getAlias(abstractt);
        if isset this->instances[abstractt] {
            let this->instances[abstractt] =  {closure}(this->instances[abstractt], this);
        } else {
            let this->extenders[abstractt][] = closure;
        }
    }
    
    /**
     * Register an existing instance as shared in the container.
     *
     * @param  string  $abstract
     * @param  mixed   $instance
     * @return mixed
     */
    public function instance(string abstractt, instance)
    {
        this->removeAbstractAlias(abstractt);
        unset this->aliases[abstractt];
        
        let this->instances[abstractt] = instance;
        return instance;
    }
    
    /**
     * Remove an alias from the contextual binding alias cache.
     *
     * @param  string  $searched
     * @return void
     */
    protected function removeAbstractAlias(string searched)
    {
        var abstractt, aliases, index, alias;
    
        if !(isset this->aliases[searched]) {
            return;
        }
        for abstractt, aliases in this->abstractAliases {
            for index, alias in aliases {
                if alias == searched {
                    unset this->abstractAliases[abstractt][index];
                
                }
            }
        }
    }
    
    /**
     * Alias a type to a different name.
     *
     * @param  string  $abstract
     * @param  string  $alias
     * @return void
     */
    public function alias(string abstractt, string alias)
    {
        let this->aliases[alias] = abstractt;
        let this->abstractAliases[abstractt][] = alias;
    }
    
    /**
     * Call the given Closure / class@method and inject its dependencies.
     *
     * @param  callable|string  $callback
     * @param  array  $parameters
     * @param  string|null  $defaultMethod
     * @return mixed
     */
    public function call(callback, array parameters = [], defaultMethod = null)
    {
        return BoundMethod::call(this, callback, parameters, defaultMethod);
    }
    
    /**
     * Resolve the given type from the container.
     *
     * @param  string  $abstract
     * @param  array  $parameters
     * @return mixed
     */
    public function make(string abstractt, array parameters = [])
    {
        return this->resolve(abstractt, parameters);
    }
    
    /**
     * get service
     */
    public function get(id)
    {
        var e;
    
        try {
            return this->resolve(id);
        } catch Exception, e {
            if this->has(id) {
                throw e;
            }
            throw new EntryNotFoundException();
        }
    }
    
    /**
     * Resolve the given type from the container.
     *
     * @param  string  $abstract
     * @param  array  $parameters
     * @return mixed
     */
    protected function resolve(string abstractt, array parameters = [])
    {
        var needsContextualBuild, concrete, obj, extender;
    
        let abstractt =  this->getAlias(abstractt);
        let needsContextualBuild =  !(empty(parameters)) || !(is_null(this->getContextualConcrete(abstractt)));
        // If an instance of the type is currently being managed as a singleton we'll
        // just return an existing instance instead of instantiating new instances
        // so the developer can keep using the same objects instance every time.
        if isset this->instances[abstractt] && !(needsContextualBuild) {
            return this->instances[abstractt];
        }
        let this->with[] = parameters;
        let concrete =  this->getConcrete(abstractt);
        // We're ready to instantiate an instance of the concrete type registered for
        // the binding. This will instantiate the types, as well as resolve any of
        // its "nested" dependencies recursively until all have gotten resolved.
        if this->isBuildable(concrete, abstractt) {
            let obj =  this->build(concrete);
        } else {
            let obj =  this->make(concrete);
        }
        // If we defined any extenders for this type, we'll need to spin through them
        // and apply them to the object being built. This allows for the extension
        // of services, such as changing configuration or decorating the object.
        for extender in this->getExtenders(abstractt) {
            let obj =  {extender}(obj, this);
        }
        // If the requested type is registered as a singleton we'll want to cache off
        // the instances in "memory" so we can return it later without creating an
        // entirely new instance of an object on each subsequent request for it.
        if this->isShared(abstractt) && !(needsContextualBuild) {
            let this->instances[abstractt] = obj;
        }
        // Before returning, we will also set the resolved flag to "true" and pop off
        // the parameter overrides for this build. After those two things are done
        // we will be ready to return back the fully constructed class instance.
        let this->resolved[abstractt] = true;
        array_pop(this->with);
        return obj;
    }
    
    /**
     * Get the concrete type for a given abstract.
     *
     * @param  string  $abstract
     * @return mixed   $concrete
     */
    protected function getConcrete(string abstractt)
    {
        var concrete;
    
        let concrete =  this->getContextualConcrete(abstractt);
        if !(is_null(concrete)) {
            return concrete;
        }
        // If we don't have a registered resolver or concrete for the type, we'll just
        // assume each type is a concrete name and will attempt to resolve it as is
        // since the container should be able to resolve concretes automatically.
        if isset this->bindings[abstractt] {
            return this->bindings[abstractt]["concrete"];
        }
        return abstractt;
    }
    
    /**
     * Get the contextual concrete binding for the given abstract.
     *
     * @param  string  $abstract
     * @return string|null
     */
    protected function getContextualConcrete(string abstractt)
    {
        var binding, alias;
    
        let binding =  this->findInContextualBindings(abstractt);
        if !(is_null(binding)) {
            return binding;
        }
        // Next we need to see if a contextual binding might be bound under an alias of the
        // given abstract type. So, we will need to check if any aliases exist with this
        // type and then spin through them and check for contextual bindings on these.
        //TODO check ? empty => !isset
        if !isset this->abstractAliases[abstractt] {
            return;
        }
        for alias in this->abstractAliases[abstractt] {
            let binding =  this->findInContextualBindings(alias);
            if !(is_null(binding)) {
                return binding;
            }
        }
    }
    
    /**
     * Find the concrete binding for the given abstract in the contextual binding array.
     *
     * @param  string  $abstract
     * @return string|null
     */
    protected function findInContextualBindings(string abstractt)
    {
        var end;
    
        if count(this->buildStack) == 0 {
            return null;
        }
        let end = this->buildStack[count(this->buildStack) - 1];
        if isset this->contextual[end][abstractt] {
            return this->contextual[end][abstractt];
        }
    }
    
    /**
     * Determine if the given concrete is buildable.
     *
     * @param  mixed   $concrete
     * @param  string  $abstract
     * @return bool
     */
    protected function isBuildable(concrete, string abstractt) -> bool
    {
        return concrete === abstractt || (typeof concrete == "object" && concrete instanceof Closure);
    }
    
    /**
     * Instantiate a concrete instance of the given type.
     *
     * @param  string  $concrete
     * @return mixed
     *
     * @throws \Zim\Container\BindingResolutionException
     */
    public function build(string concrete)
    {
        var reflector, constructor, dependencies, instances;
    
        // If the concrete type is actually a Closure, we will just execute it and
        // hand back the results of the functions, which allows functions to be
        // used as resolvers for more fine-tuned resolution of these objects.
        //if concrete instanceof Closure {
        if typeof concrete != "string" && is_callable(concrete) {
            //return {concrete}(this, this->getLastParameterOverride());
            return call_user_func_array(concrete, [this, this->getLastParameterOverride()]);
        }
        let reflector =  new ReflectionClass(concrete);
        // If the type is not instantiable, the developer is attempting to resolve
        // an abstract type such as an Interface of Abstract Class and there is
        // no binding registered for the abstractions so we need to bail out.
        if !(reflector->isInstantiable()) {
            return this->notInstantiable(concrete);
        }
        let this->buildStack[] = concrete;
        let constructor =  reflector->getConstructor();
        // If there are no constructors, that means there are no dependencies then
        // we can just resolve the instances of the objects right away, without
        // resolving any other types or dependencies out of these containers.
        if is_null(constructor) {
            array_pop(this->buildStack);
            return new {concrete}();
        }
        let dependencies =  constructor->getParameters();
        // Once we have all the constructor's parameters we can create each of the
        // dependency instances and then use the reflection instances to make a
        // new instance of this class, injecting the created dependencies in.
        let instances =  this->resolveDependencies(dependencies);
        array_pop(this->buildStack);
        return reflector->newInstanceArgs(instances);
    }
    
    /**
     * Resolve all of the dependencies from the ReflectionParameters.
     *
     * @param  array  $dependencies
     * @return array
     */
    protected function resolveDependencies(array dependencies) -> array
    {
        var results, dependency;
    
        let results =  [];
        for dependency in dependencies {
            // If this dependency has a override for this particular build we will use
            // that instead as the value. Otherwise, we will continue with this run
            // of resolutions and let reflection attempt to determine the result.
            if this->hasParameterOverride(dependency) {
                let results[] =  this->getParameterOverride(dependency);
                continue;
            }
            // If the class is null, it means the dependency is a string or some other
            // primitive type which we can not resolve since it is not a class and
            // we will just bomb out with an error since we have no-where to go.
            let results[] =  is_null(dependency->getClass()) ? this->resolvePrimitive(dependency)  : this->resolveClass(dependency);
        }
        return results;
    }
    
    /**
     * Determine if the given dependency has a parameter override.
     *
     * @param  \ReflectionParameter  $dependency
     * @return bool
     */
    protected function hasParameterOverride(<\ReflectionParameter> dependency) -> bool
    {
        return array_key_exists(dependency->name, this->getLastParameterOverride());
    }
    
    /**
     * Get a parameter override for a dependency.
     *
     * @param  \ReflectionParameter  $dependency
     * @return mixed
     */
    protected function getParameterOverride(<\ReflectionParameter> dependency)
    {
        return this->getLastParameterOverride()[dependency->name];
    }
    
    /**
     * Get the last parameter override.
     *
     * @return array
     */
    protected function getLastParameterOverride() -> array
    {
        return  count(this->with) ? end(this->with)  : [];
    }
    
    /**
     * Resolve a non-class hinted primitive dependency.
     *
     * @param  \ReflectionParameter  $parameter
     * @return mixed
     *
     * @throws \Zim\Container\BindingResolutionException
     */
    protected function resolvePrimitive(<ReflectionParameter> parameter)
    {
        var concrete;
    
        let concrete =  this->getContextualConcrete("$" . parameter->name);
        if !(is_null(concrete)) {
            return (typeof concrete == "object" && concrete instanceof Closure) ? {concrete}(this) : concrete;
        }
        if parameter->isDefaultValueAvailable() {
            return parameter->getDefaultValue();
        }
        this->unresolvablePrimitive(parameter);
    }
    
    /**
     * Resolve a class based dependency from the container.
     *
     * @param  \ReflectionParameter  $parameter
     * @return mixed
     *
     * @throws \Zim\Container\BindingResolutionException
     */
    protected function resolveClass(<ReflectionParameter> parameter)
    {
        var e;
    
        try {
            return this->make(parameter->getClass()->name);
        } catch BindingResolutionException, e {
            if parameter->isOptional() {
                return parameter->getDefaultValue();
            }
            throw e;
        }
    }
    
    /**
     * Throw an exception that the concrete is not instantiable.
     *
     * @param  string  $concrete
     * @return void
     *
     * @throws \Zim\Container\BindingResolutionException
     */
    protected function notInstantiable(string concrete)
    {
        var previous, message;
    
        if !(empty(this->buildStack)) {
            let previous =  implode(", ", this->buildStack);
            let message = "Target [{concrete}] is not instantiable while building [{previous}].";
        } else {
            let message = "Target [{concrete}] is not instantiable.";
        }
        throw new BindingResolutionException(message);
    }
    
    /**
     * Throw an exception for an unresolvable primitive.
     *
     * @param  \ReflectionParameter  $parameter
     * @return void
     *
     * @throws \Zim\Container\BindingResolutionException
     */
    protected function unresolvablePrimitive(<ReflectionParameter> parameter)
    {
        var message;
    
        let message = "Unresolvable dependency resolving [{parameter}] in class {parameter->getDeclaringClass()->getName()}";
        throw new BindingResolutionException(message);
    }

    /**
     * Get the container's bindings.
     *
     * @return array
     */
    public function getBindings() -> array
    {
        return this->bindings;
    }
    
    /**
     * Get the alias for an abstract if available.
     *
     * @param  string  $abstract
     * @return string
     *
     * @throws \LogicException
     */
    public function getAlias(string abstractt) -> string
    {
        if !(isset this->aliases[abstractt]) {
            return abstractt;
        }
        if this->aliases[abstractt] === abstractt {
            throw new LogicException("[{abstractt}] is aliased to itself.");
        }
        return this->getAlias(this->aliases[abstractt]);
    }
    
    /**
     * Get the extender callbacks for a given type.
     *
     * @param  string  $abstract
     * @return array
     */
    protected function getExtenders(string abstractt) -> array
    {
        var tmpArray40cd750bba9870f18aada2478b24840a;
    
        let abstractt =  this->getAlias(abstractt);
        if isset this->extenders[abstractt] {
            return this->extenders[abstractt];
        }
        let tmpArray40cd750bba9870f18aada2478b24840a = [];
        return tmpArray40cd750bba9870f18aada2478b24840a;
    }
    
    /**
     * Remove all of the extender callbacks for a given type.
     *
     * @param  string  $abstract
     * @return void
     */
    public function forgetExtenders(string abstractt)
    {
        var ext;
        let ext = this->getAlias(abstractt);
        unset this->extenders[ext];
    }
    
    /**
     * Drop all of the stale instances and aliases.
     *
     * @param  string  $abstract
     * @return void
     */
    protected function dropStaleInstances(string abstractt)
    {
        unset this->instances[abstractt];
        unset this->aliases[abstractt];
    
    }
    
    /**
     * Remove a resolved instance from the instance cache.
     *
     * @param  string  $abstract
     * @return void
     */
    public function forgetInstance(string abstractt)
    {
        unset this->instances[abstractt];
    
    }
    
    /**
     * Clear all of the instances from the container.
     *
     * @return void
     */
    public function forgetInstances()
    {
        let this->instances =  [];
    }
    
    /**
     * Flush the container of all bindings and resolved instances.
     *
     * @return void
     */
    public function flush()
    {
        let this->aliases =  [];
        let this->resolved =  [];
        let this->bindings =  [];
        let this->instances =  [];
        let this->abstractAliases =  [];
    }
    
    /**
     * Set the globally available instance of the container.
     *
     * @return static
     */
    public static function getInstance() -> <Container>
    {
        if is_null(self::instance) {
            let self::instance =  new static();
        }
        return self::instance;
    }
    
    /**
     * Set the shared instance of the container.
     *
     * @param  Container|null  $container
     * @return Container|static
     */
    public static function setInstance(<Container> container = null)
    {
        let self::instance = container;
        return self::instance;
    }
    
    /**
     * Set the value at a given key.
     *
     * @param  string  $key
     * @param  mixed   $value
     * @return void
     */
    public function set(string key, value)
    {
        this->bind(key, (typeof value == "object" && value instanceof Closure) ? value  : new ContainersetClosureOne(value));
    }
    
    /**
     * Unset the value at a given key.
     *
     * @param  string  $key
     * @return void
     */
    public function remove(string key)
    {
        unset this->bindings[key];
        unset this->instances[key];
        unset this->resolved[key];
    
    }

}