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
     * Determine if the given abstract type has been bound.
     *
     * @param  string  $abstract
     * @return bool
     */
    public function bound(var abstractt) -> bool
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
    public function resolved(var abstractt) -> bool
    {
        if this->isAlias(abstractt) {
            let abstractt = this->getAlias(abstractt);
        }
        return isset this->resolved[abstractt] || isset this->instances[abstractt];
    }

    /**
     * Determine if a given type is shared.
     *
     * @param  string  $abstract
     * @return bool
     */
    public function isShared(var abstractt) -> bool
    {
        return isset this->instances[abstractt] || isset this->bindings[abstractt]["shared"] && this->bindings[abstractt]["shared"] === true;
    }

    /**
     * Determine if a given string is an alias.
     *
     * @param  string  $name
     * @return bool
     */
    public function isAlias(var name) -> bool
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
    public function bind(var abstractt, var concrete = null, bool shared = false)
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
            let concrete = this->getClosure(abstractt, concrete);
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
    protected function getClosure(var abstractt, var concrete) -> <ContainergetClosureClosureZero>
    {
        return new ContainergetClosureClosureZero(abstractt, concrete);
    }

    /**
     * Register a shared binding in the container.
     *
     * @param  string  $abstract
     * @param  \Closure|string|null  $concrete
     * @return void
     */
    public function singleton(var abstractt, var concrete = null)
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
    public function extend(var abstractt, <Closure> closure)
    {
        let abstractt = this->getAlias(abstractt);
        if isset this->instances[abstractt] {
            let this->instances[abstractt] = {closure}(this->instances[abstractt], this);
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
    public function instance(var abstractt, instance)
    {
        unset this->aliases[abstractt];

        let this->instances[abstractt] = instance;
        return instance;
    }

    /**
     * Alias a type to a different name.
     *
     * @param  string  $abstract
     * @param  string  $alias
     * @return void
     */
    public function alias(var abstractt, var alias)
    {
        let this->aliases[alias] = abstractt;
    }

    /**
     * Call the given Closure / callable and inject its dependencies.
     *
     * @param  callable $callback
     * @param  array  $parameters
     * @return mixed
     */
    public function call(var callback, array parameters = [])
    {
        return BoundMethod::call(this, callback, parameters);
    }

    /**
     * Resolve the given type from the container.
     *
     * @param  string  $abstract
     * @param  array  $parameters
     * @return mixed
     */
    public function make(var abstractt, array parameters = [])
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
    protected function resolve(var abstractt, array parameters = [])
    {
        var concrete, obj, extender;

        let abstractt = this->getAlias(abstractt);
        if isset this->instances[abstractt] {
            return this->instances[abstractt];
        }

        let this->with[] = parameters;

        let concrete = this->getConcrete(abstractt);
        if this->isBuildable(concrete, abstractt) {
            let obj = this->build(concrete);
        } else {
            let obj = this->make(concrete);
        }

        for extender in this->getExtenders(abstractt) {
            let obj = {extender}(obj, this);
        }

        if this->isShared(abstractt) {
            let this->instances[abstractt] = obj;
        }

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
    protected function getConcrete(var abstractt)
    {
        var concrete;

        if isset this->bindings[abstractt] {
            return this->bindings[abstractt]["concrete"];
        }
        return abstractt;
    }

    /**
     * Determine if the given concrete is buildable.
     *
     * @param  mixed   $concrete
     * @param  string  $abstract
     * @return bool
     */
    protected function isBuildable(var concrete, var abstractt) -> bool
    {
        return concrete === abstractt ||
            (typeof concrete == "object" && (concrete instanceof Closure || concrete instanceof ContainergetClosureClosureZero));
    }

    /**
     * Instantiate a concrete instance of the given type.
     *
     * @param  string $concrete
     * @return mixed
     *
     * @throws \Zim\Container\BindingResolutionException
     */
    public function build(var concrete)
    {
        var reflector, constructor, dependencies, instances;

        if typeof concrete == "object" &&
            (concrete instanceof ContainergetClosureClosureZero || concrete instanceof Closure) {
            return {concrete}(this, this->getLastParameterOverride());
        }

        let reflector = new ReflectionClass(concrete);
        if !(reflector->isInstantiable()) {
            return this->notInstantiable(concrete);
        }

        let this->buildStack[] = concrete;

        let constructor = reflector->getConstructor();
        if is_null(constructor) {
            array_pop(this->buildStack);
            return new {concrete}();
        }

        let dependencies = constructor->getParameters();
        let instances = this->resolveDependencies(dependencies);
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

        let results = [];
        for dependency in dependencies {
            if this->hasParameterOverride(dependency) {
                let results[] = this->getParameterOverride(dependency);
                continue;
            }

            let results[] = is_null(dependency->getClass()) ? this->resolvePrimitive(dependency) : this->resolveClass(dependency);
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
        return  count(this->with) ? end(this->with) : [];
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
     * @param  string $concrete
     * @return void
     *
     * @throws \Zim\Container\BindingResolutionException
     */
    protected function notInstantiable(var concrete)
    {
        var previous, message;

        if !(empty(this->buildStack)) {
            let previous = implode(", ", this->buildStack);
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
        let message = "Unresolvable dependency resolving [{".parameter."}] in class {".parameter->getDeclaringClass()->getName()."}";
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
    public function getAlias(var abstractt)
    {
        if ! isset this->aliases[abstractt] {
            return abstractt;
        }
        if this->aliases[abstractt] === abstractt {
            throw new LogicException("[{".abstractt."}] is aliased to itself.");
        }
        return this->getAlias(this->aliases[abstractt]);
    }

    /**
     * Get the extender callbacks for a given type.
     *
     * @param  string  $abstract
     * @return array
     */
    protected function getExtenders(var abstractt) -> array
    {
        let abstractt = this->getAlias(abstractt);
        if isset this->extenders[abstractt] {
            return this->extenders[abstractt];
        }
        return [];
    }

    /**
     * Remove all of the extender callbacks for a given type.
     *
     * @param  string  $abstract
     * @return void
     */
    public function forgetExtenders(var abstractt)
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
    protected function dropStaleInstances(var abstractt)
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
    public function forgetInstance(var abstractt)
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
        let this->instances = [];
    }
    
    /**
     * Flush the container of all bindings and resolved instances.
     *
     * @return void
     */
    public function flush()
    {
        let this->aliases = [];
        let this->resolved = [];
        let this->bindings = [];
        let this->instances = [];
    }

    /**
     * Set the globally available instance of the container.
     *
     * @return static
     */
    public static function getInstance() -> <Container>
    {
        if is_null(self::instance) {
            let self::instance = new static();
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
    public function set(var key, value)
    {
        this->bind(key, (typeof value == "object" && value instanceof Closure) ? value : new ContainersetClosureOne(value));
    }
    
    /**
     * Unset the value at a given key.
     *
     * @param  string  $key
     * @return void
     */
    public function remove(var key)
    {
        unset this->bindings[key];
        unset this->instances[key];
        unset this->resolved[key];
    }

}