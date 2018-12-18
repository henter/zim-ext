namespace Zim\Http;

/**
 * ParameterBag is a container for key/value pairs.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
class ParameterBag implements \IteratorAggregate, \Countable
{
    /**
     * Parameter storage.
     */
    protected parameters = [];
    /**
     * @param array $parameters An array of parameters
     */
    public function __construct(array parameters = []) -> void
    {
        let this->parameters = parameters;
    }
    
    /**
     * Returns the parameters.
     *
     * @return array An array of parameters
     */
    public function all() -> array
    {
        return this->parameters;
    }
    
    /**
     * Returns the parameter keys.
     *
     * @return array An array of parameter keys
     */
    public function keys() -> array
    {
        return array_keys(this->parameters);
    }
    
    /**
     * Replaces the current parameters by a new set.
     *
     * @param array $parameters An array of parameters
     */
    public function replace(array parameters = []) -> void
    {
        let this->parameters = parameters;
    }
    
    /**
     * Adds parameters.
     *
     * @param array $parameters An array of parameters
     */
    public function add(array parameters = []) -> void
    {
        let this->parameters =  array_replace(this->parameters, parameters);
    }
    
    /**
     * Returns a parameter by name.
     *
     * @param string $key     The key
     * @param mixed  $default The default value if the parameter key does not exist
     *
     * @return mixed
     */
    public function get(string key, deft = null)
    {
        return  array_key_exists(key, this->parameters) ? this->parameters[key]  : deft;
    }
    
    /**
     * Sets a parameter by name.
     *
     * @param string $key   The key
     * @param mixed  $value The value
     */
    public function set(string key, value) -> void
    {
        let this->parameters[key] = value;
    }
    
    /**
     * Returns true if the parameter is defined.
     *
     * @param string $key The key
     *
     * @return bool true if the parameter exists, false otherwise
     */
    public function has(string key) -> bool
    {
        return array_key_exists(key, this->parameters);
    }
    
    /**
     * Removes a parameter.
     *
     * @param string $key The key
     */
    public function remove(string key) -> void
    {
        unset this->parameters[key];
    
    }
    
    /**
     * Returns an iterator for parameters.
     *
     * @return \ArrayIterator An \ArrayIterator instance
     */
    public function getIterator() -> <\ArrayIterator>
    {
        return new \ArrayIterator(this->parameters);
    }
    
    /**
     * Returns the number of parameters.
     *
     * @return int The number of parameters
     */
    public function count() -> int
    {
        return count(this->parameters);
    }

}