namespace Zim\Routing;

/**
 * A Route describes a route and its parameters.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 * @author Tobias Schultze <http://tobion.de>
 *
 *
 * static method for route definition
 *
 * @method static get(string $uri, \Closure|array|string|null $info = null)
 * @method static post(string $uri, \Closure|array|string|null $info = null)
 * @method static put(string $uri, \Closure|array|string|null $info = null)
 * @method static delete(string $uri, \Closure|array|string|null $info = null)
 * @method static patch(string $uri, \Closure|array|string|null $info = null)
 * @method static options(string $uri, \Closure|array|string|null $info = null)
 * @method static match(array|string $method, string $uri, \Closure|array|string|null $info = null)
 * @method static any(string $uri, \Closure|array|string|null $info = null)
 * @method static name(string $value)
 * @method static where(array  $where)
 */
class Route
{
    /**
     * @var Registrar
     */
    protected static registrar;
    protected path = "/";
    protected methods = [];
    protected defaults = [];
    protected requirements = [];
    protected options = [];
    protected parameters = [];
    /**
     * @var CompiledRoute|null
     */
    protected compiled;
    /**
     * Constructor.
     *
     * Available options:
     *  * utf8:           Whether UTF-8 matching is enforced ot not
     *
     * @param string          $path         The path pattern to match
     * @param array           $defaults     An array of default parameter values
     * @param array           $requirements An array of requirements for parameters (regexes)
     * @param string|string[] $methods      A required HTTP method or an array of restricted methods
     * @param array           $options      An array of options
     */
    public function __construct(string path, array defaults = [], array requirements = [], var methods = [], array options = []) -> void
    {
        this->setPath(path);
        this->addDefaults(defaults);
        this->addRequirements(requirements);
        this->setMethods(methods);
        this->addOptions(options);
    }
    
    /**
     * @param array $parameters
     * @return $this
     */
    public function setParameters(array parameters)
    {
        let this->parameters = this->mergeDefaults(parameters);
        //TODO
        unset this->parameters["_controller"];
        unset this->parameters["_action"];
        
        return this;
    }
    
    public function getParameters()
    {
        return this->parameters;
    }
    
    /**
     * Get merged default parameters.
     *
     * @param array $params   The parameters
     *
     * @return array Merged default parameters
     */
    protected function mergeDefaults(array params) -> array
    {
        var defaults, key, value;
    
        let defaults = this->getDefaults();
        for key, value in params {
            if !(is_int(key)) && value !== null {
                let defaults[key] = value;
            }
        }
        return defaults;
    }
    
    /**
     * Returns the pattern for the path.
     *
     * @return string The path pattern
     */
    public function getPath() -> string
    {
        return this->path;
    }
    
    /**
     * Sets the pattern for the path.
     *
     * This method implements a fluent interface.
     *
     * @param string $pattern The path pattern
     *
     * @return $this
     */
    public function setPath(string pattern)
    {
        if strpbrk(pattern, "?<") !== false {
            let pattern = preg_replace_callback("#\\{(\\w++)(<.*?>)?(\\?[^\\}]*+)?\\}#", [this, "setPathCallback"], pattern);
        }
        let this->path = "/" . ltrim(trim(pattern), "/");
        let this->compiled = null;
        return this;
    }

    private function setPathCallback(array m)
    {
        if strlen(m[3]) > 0 {
            this->setDefault(m[1],  m[3] !== "?" ? substr(m[3], 1) : null);
        }

        if strlen(m[2]) > 0 {
            this->setRequirement(m[1], substr(m[2], 1, -1));
        }
        return "{" . m[1] . "}";
    }
    
    /**
     * Returns the uppercased HTTP methods this route is restricted to.
     * So an empty array means that any method is allowed.
     *
     * @return string[] The methods
     */
    public function getMethods() -> array
    {
        return this->methods;
    }
    
    /**
     * Sets the HTTP methods (e.g. 'POST') this route is restricted to.
     * So an empty array means that any method is allowed.
     *
     * This method implements a fluent interface.
     *
     * @param string[] $methods The method or an array of methods
     *
     * @return $this
     */
    public function setMethods(array methods)
    {
        let this->methods = array_map("strtoupper", methods);
        let this->compiled = null;
        return this;
    }
    
    /**
     * Returns the options.
     *
     * @return array The options
     */
    public function getOptions() -> array
    {
        return this->options;
    }
    
    /**
     * Adds options.
     *
     * This method implements a fluent interface.
     *
     * @param array $options The options
     *
     * @return $this
     */
    public function addOptions(array options)
    {
        var name, option;
    
        for name, option in options {
            let this->options[name] = option;
        }
        let this->compiled = null;
        return this;
    }
    
    /**
     * Sets an option value.
     *
     * This method implements a fluent interface.
     *
     * @param string $name  An option name
     * @param mixed  $value The option value
     *
     * @return $this
     */
    public function setOption(string name, value)
    {
        let this->options[name] = value;
        let this->compiled = null;
        return this;
    }
    
    /**
     * Get an option value.
     *
     * @param string $name An option name
     *
     * @return mixed The option value or null when not given
     */
    public function getOption(string name)
    {
        return  isset this->options[name] ? this->options[name] : null;
    }
    
    /**
     * Checks if an option has been set.
     *
     * @param string $name An option name
     *
     * @return bool true if the option is set, false otherwise
     */
    public function hasOption(string name) -> bool
    {
        return array_key_exists(name, this->options);
    }
    
    /**
     * Returns the defaults.
     *
     * @return array The defaults
     */
    public function getDefaults() -> array
    {
        return this->defaults;
    }
    
    /**
     * Sets the defaults.
     *
     * This method implements a fluent interface.
     *
     * @param array $defaults The defaults
     *
     * @return $this
     */
    public function setDefaults(array defaults)
    {
        let this->defaults = [];
        return this->addDefaults(defaults);
    }
    
    /**
     * Adds defaults.
     *
     * This method implements a fluent interface.
     *
     * @param array $defaults The defaults
     *
     * @return $this
     */
    public function addDefaults(array defaults)
    {
        var name, deft;
    
        for name, deft in defaults {
            let this->defaults[name] = deft;
        }
        let this->compiled = null;
        return this;
    }
    
    /**
     * Gets a default value.
     *
     * @param string $name A variable name
     *
     * @return mixed The default value or null when not given
     */
    public function getDefault(string name)
    {
        return  isset this->defaults[name] ? this->defaults[name] : null;
    }
    
    /**
     * Checks if a default value is set for the given variable.
     *
     * @param string $name A variable name
     *
     * @return bool true if the default value is set, false otherwise
     */
    public function hasDefault(string name) -> bool
    {
        return array_key_exists(name, this->defaults);
    }
    
    /**
     * Sets a default value.
     *
     * @param string $name    A variable name
     * @param mixed  $default The default value
     *
     * @return $this
     */
    public function setDefault(string name, deft)
    {
        let this->defaults[name] = deft;
        let this->compiled = null;
        return this;
    }
    
    /**
     * Returns the requirements.
     *
     * @return array The requirements
     */
    public function getRequirements() -> array
    {
        return this->requirements;
    }
    
    /**
     * Sets the requirements.
     *
     * This method implements a fluent interface.
     *
     * @param array $requirements The requirements
     *
     * @return $this
     */
    public function setRequirements(array requirements)
    {
        let this->requirements = [];
        return this->addRequirements(requirements);
    }
    
    /**
     * Adds requirements.
     *
     * This method implements a fluent interface.
     *
     * @param array $requirements The requirements
     *
     * @return $this
     */
    public function addRequirements(array requirements)
    {
        var key, regex;
    
        for key, regex in requirements {
            let this->requirements[key] = this->sanitizeRequirement(key, regex);
        }
        let this->compiled = null;
        return this;
    }
    
    /**
     * Returns the requirement for the given key.
     *
     * @param string $key The key
     *
     * @return string|null The regex or null when not given
     */
    public function getRequirement(string key)
    {
        return  isset this->requirements[key] ? this->requirements[key] : null;
    }
    
    /**
     * Checks if a requirement is set for the given key.
     *
     * @param string $key A variable name
     *
     * @return bool true if a requirement is specified, false otherwise
     */
    public function hasRequirement(string key) -> bool
    {
        return array_key_exists(key, this->requirements);
    }
    
    /**
     * Sets a requirement for the given key.
     *
     * @param string $key   The key
     * @param string $regex The regex
     *
     * @return $this
     */
    public function setRequirement(string key, string regex)
    {
        let this->requirements[key] = this->sanitizeRequirement(key, regex);
        let this->compiled = null;
        return this;
    }
    
    /**
     * Compiles the route.
     *
     * @return CompiledRoute A CompiledRoute instance
     *
     * @throws \LogicException If the Route cannot be compiled because the
     *                         path or host pattern is invalid
     *
     * @see RouteCompiler which is responsible for the compilation process
     */
    public function compile() -> <CompiledRoute>
    {
        if this->compiled !== null {
            return this->compiled;
        }
        let this->compiled = RouteCompiler::compile(this);
        return this->compiled;
    }
    
    protected function sanitizeRequirement(string key, string regex)
    {
        if regex !== "" && substr(regex, 0, 1) === "^" {
            let regex = (string) substr(regex, 1);
        }
        if substr(regex, -1) === "$" {
            let regex = substr(regex, 0, -1);
        }
        if regex === "" {
            throw new \InvalidArgumentException(sprintf("Routing requirement for \"%s\" cannot be empty.", key));
        }
        return regex;
    }
    
    /**
     * Dynamically handle calls into the route registrar.
     *
     * @param  string  $method
     * @param  array  $parameters
     * @return Route|$this
     *
     * @throws \BadMethodCallException
     */
    public static function __callStatic(string method, array parameters)
    {
        var call;

        if !(self::registrar) {
            let self::registrar = new Registrar(\Zim\Zim::app("router"));
        }
        let call = [self::registrar, method];
        return call_user_func_array(call, parameters);
    }

}