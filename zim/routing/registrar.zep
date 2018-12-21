namespace Zim\Routing;

use BadMethodCallException;
use InvalidArgumentException;
/**
 * @method get(string $uri, \Closure|array|string|null $info = null)
 * @method post(string $uri, \Closure|array|string|null $info = null)
 * @method put(string $uri, \Closure|array|string|null $info = null)
 * @method delete(string $uri, \Closure|array|string|null $info = null)
 * @method patch(string $uri, \Closure|array|string|null $info = null)
 * @method options(string $uri, \Closure|array|string|null $info = null)
 * @method any(string $uri, \Closure|array|string|null $info = null)
 * @method name(string $value)
 * @method where(array  $where)
 */
class Registrar
{
    /**
     * The router instance.
     *
     * @var Router
     */
    protected router;
    /**
     * The attributes to pass on to the router.
     *
     * @var array
     */
    protected attributes = [];
    /**
     * The methods to dynamically pass through to the router.
     *
     * @var array
     */
    protected passthru = ["get", "post", "put", "patch", "delete", "options", "any"];
    /**
     * The attributes that can be set through this class.
     *
     * @var array
     */
    protected allowedAttributes = ["name", "where"];
    /**
     * Create a new route registrar instance.
     *
     * @param  Router  $router
     * @return void
     */
    public function __construct(<Router> router)
    {
        let this->router = router;
    }
    
    /**
     * Set the value for a given attribute.
     *
     * @param  string  $key
     * @param  mixed  $value
     * @return $this
     *
     * @throws \InvalidArgumentException
     */
    public function attribute(string key, value)
    {
        if !in_array(key, this->allowedAttributes) {
            throw new InvalidArgumentException("Attribute [{key}] does not exist.");
        }
        let this->attributes[key] = value;
        return this;
    }
    
    /**
     * Registrar a new route with the router.
     *
     * @param  string  $method
     * @param  string  $uri
     * @param  \Closure|array|string|null  $info
     * @return Route
     */
    protected function registrarRoute(string method, string uri, info = null) -> <Route>
    {
        if method == "any" {
            return this->router->addRoute([], uri, info);
        }
        return this->router->addRoute(method, uri, info);
    }
    
    /**
     * Register a new route with the given verbs.
     *
     * @param  array|string  $methods
     * @param  string  $uri
     * @param  \Closure|array|string|null  $info
     * @return Route
     */
    public function doMatch(methods, string uri, info = null) -> <Route>
    {
        return this->router->addRoute(methods, uri, info);
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
    public function __call(string method, array parameters)
    {
        var all;

        if in_array(method, this->passthru) {
            let all = parameters;
            array_unshift(all, method);
            //return this->registrarRoute(method, ...parameters);
            return call_user_func_array([this, "registrarRoute"], all);
        }
        if in_array(method, this->allowedAttributes) {
            return this->attribute(method, parameters[0]);
        }
        if method == "match" {
            //return this->doMatch(...parameters);
            return call_user_func_array([this, "doMatch"], parameters);
        }
        throw new BadMethodCallException(sprintf("Method %s::%s does not exist.", "Registrar", method));
    }

}