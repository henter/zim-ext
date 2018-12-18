/*
 * This file is part of the Symfony package.
 *
 * (c) Fabien Potencier <fabien@symfony.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
namespace Zim\Routing;

/**
 * A RouteCollection represents a set of Route instances.
 *
 * When adding a route at the end of the collection, an existing route
 * with the same name is removed first. So there can only be one route
 * with a given name.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 * @author Tobias Schultze <http://tobion.de>
 */
class RouteCollection implements \IteratorAggregate, \Countable
{
    /**
     * @var Route[]
     */
    protected routes = [];

    public function __clone() -> void
    {
        var name, route;
        for name, route in this->routes {
            let this->routes[name] = clone route;
        }
    }
    
    /**
     * Gets the current RouteCollection as an Iterator that includes all routes.
     *
     * It implements \IteratorAggregate.
     *
     * @see all()
     *
     * @return \ArrayIterator|Route[] An \ArrayIterator object for iterating over routes
     */
    public function getIterator()
    {
        return new \ArrayIterator(this->routes);
    }
    
    /**
     * Gets the number of Routes in this collection.
     *
     * @return int The number of routes
     */
    public function count() -> int
    {
        return count(this->routes);
    }
    
    /**
     * Adds a route.
     *
     * @param string $name  The route name
     * @param Route  $route A Route instance
     */
    public function add(string name, <Route> route) -> void
    {
        unset this->routes[name];
        
        let this->routes[name] = route;
    }
    
    /**
     * Returns all routes in this collection.
     *
     * @return Route[] An array of routes
     */
    public function all() -> array
    {
        return this->routes;
    }
    
    /**
     * Gets a route by name.
     *
     * @param string $name The route name
     *
     * @return Route|null A Route instance or null when not found
     */
    public function get(string name)
    {
        return isset this->routes[name] ? this->routes[name] : null;
    }
    
    /**
     * Removes a route or an array of routes by name from the collection.
     *
     * @param string $name The route name or an array of route names
     */
    public function remove(string name) -> void
    {
        unset this->routes[name];
    }
    
    /**
     * Adds a route collection at the end of the current set by appending all
     * routes of the added collection.
     */
    public function addCollection(<RouteCollection> collection) -> void
    {
        var name, route;
    
        // we need to remove all routes with the same names first because just replacing them
        // would not place the new route at the end of the merged array
        for name, route in collection->all() {
            unset this->routes[name];
            
            let this->routes[name] = route;
        }
    }
    
    /**
     * Adds a prefix to the path of all child routes.
     *
     * @param string $prefix       An optional prefix to add before each pattern of the route collection
     * @param array  $defaults     An array of default values
     * @param array  $requirements An array of requirements
     */
    public function addPrefix(string prefix, array defaults = [], array requirements = [])
    {
        var route;
    
        let prefix = trim(trim(prefix), "/");
        if prefix === "" {
            return;
        }
        for route in this->routes {
            route->setPath("/" . prefix . route->getPath());
            route->addDefaults(defaults);
            route->addRequirements(requirements);
        }
    }
    
    /**
     * Adds a prefix to the name of all the routes within in the collection.
     */
    public function addNamePrefix(string prefix) -> void
    {
        var prefixedRoutes, name, route;
    
        let prefixedRoutes = [];
        for name, route in this->routes {
            let prefixedRoutes[prefix . name] = route;
            let name = route->getDefault("_canonical_route");
            if name !== null {
                route->setDefault("_canonical_route", prefix . name);
            }
        }
        let this->routes = prefixedRoutes;
    }
    
    /**
     * Adds defaults to all routes.
     *
     * An existing default value under the same name in a route will be overridden.
     *
     * @param array $defaults An array of default values
     */
    public function addDefaults(array defaults) -> void
    {
        var route;
    
        if count(defaults) > 0 {
            for route in this->routes {
                route->addDefaults(defaults);
            }
        }
    }
    
    /**
     * Adds requirements to all routes.
     *
     * An existing requirement under the same name in a route will be overridden.
     *
     * @param array $requirements An array of requirements
     */
    public function addRequirements(array requirements) -> void
    {
        var route;
    
        if count(requirements) > 0 {
            for route in this->routes {
                route->addRequirements(requirements);
            }
        }
    }
    
    /**
     * Adds options to all routes.
     *
     * An existing option value under the same name in a route will be overridden.
     *
     * @param array $options An array of options
     */
    public function addOptions(array options) -> void
    {
        var route;
    
        if count(options) > 0 {
            for route in this->routes {
                route->addOptions(options);
            }
        }
    }
    
    /**
     * Sets the HTTP methods (e.g. 'POST') all child routes are restricted to.
     *
     * @param string[] $methods The method or an array of methods
     */
    public function setMethods(array methods) -> void
    {
        var route;

        for route in this->routes {
            route->setMethods(methods);
        }
    }

}