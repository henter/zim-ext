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
        let this->parameters = array_replace(this->parameters, parameters);
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
        return  array_key_exists(key, this->parameters) ? this->parameters[key] : deft;
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
     * Returns the alphabetic characters of the parameter value.
     *
     * @param string $key     The parameter key
     * @param string $default The default value if the parameter key does not exist
     *
     * @return string The filtered value
     */
    public function getAlpha(string key, var deft = "")
    {
        return preg_replace("/[^[:alpha:]]/", "", this->get(key, deft));
    }

    /**
     * Returns the alphabetic characters and digits of the parameter value.
     *
     * @param string $key     The parameter key
     * @param string $default The default value if the parameter key does not exist
     *
     * @return string The filtered value
     */
    public function getAlnum(string key, var deft = "")
    {
        return preg_replace("/[^[:alnum:]]/", "", this->get(key, deft));
    }

    /**
     * Returns the digits of the parameter value.
     *
     * @param string $key     The parameter key
     * @param string $default The default value if the parameter key does not exist
     *
     * @return string The filtered value
     */
    public function getDigits(string key, var deft = "")
    {
        // we need to remove - and + because they're allowed in the filter
        return str_replace(["-", "+"], "", this->filter(key, deft, FILTER_SANITIZE_NUMBER_INT));
    }

    /**
     * Returns the parameter value converted to integer.
     *
     * @param string $key     The parameter key
     * @param int    $default The default value if the parameter key does not exist
     *
     * @return int The filtered value
     */
    public function getInt(string key, var deft = 0)
    {
        return (int) this->get(key, deft);
    }

    /**
     * Returns the parameter value converted to boolean.
     *
     * @param string $key     The parameter key
     * @param bool   $default The default value if the parameter key does not exist
     *
     * @return bool The filtered value
     */
    public function getBoolean(string key, var deft = false)
    {
        return this->filter(key, deft, FILTER_VALIDATE_BOOLEAN);
    }

    /**
     * Filter key.
     *
     * @param string $key     Key
     * @param mixed  $default Default = null
     * @param int    $filter  FILTER_* constant
     * @param mixed  $options Filter options
     *
     * @see http://php.net/manual/en/function.filter-var.php
     *
     * @return mixed
     */
    public function filter(string key, var deft = null, int filter = -1, var options = [])
    {
        if filter == -1 {
            let filter = FILTER_DEFAULT;
        }

        var value, ops;
        let value = this->get(key, deft);

        // Always turn $options into an array - this allows filter_var option shortcuts.
        let ops = options;
        if !is_array(ops) && ops {
            var ops = ["flags": ops];
        }

        // Add a convenience check for arrays.
        if is_array(value) && !isset(ops["flags"]) {
            let ops["flags"] = FILTER_REQUIRE_ARRAY;
        }

        return filter_var(value, filter, ops);
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