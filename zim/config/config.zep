/**
 * File Config.php
 * @henter
 * Time: 2018-11-26 16:50
 *
 */
namespace Zim\Config;

use ArrayAccess;
use Zim\Support\Arr;
class Config implements ArrayAccess, \Zim\Contract\Config
{
    /**
     * All of the configuration items.
     *
     * @var array
     */
    protected items = [];
    /**
     * Create a new configuration repository.
     *
     * @param  array  $items
     * @return void
     */
    public function __construct(array items = [])
    {
        let this->items = items;
    }
    
    /**
     * Determine if the given configuration value exists.
     *
     * @param  string  $key
     * @return bool
     */
    public function has(string key) -> bool
    {
        return Arr::has(this->items, key);
    }
    
    /**
     * Get the specified configuration value.
     *
     * @param  array|string  $key
     * @param  mixed   $deft
     * @return mixed
     */
    public function get(key, deft = null)
    {
        if is_array(key) {
            return this->getMany(key);
        }
        return Arr::get(this->items, key, deft);
    }
    
    /**
     * Get many configuration values.
     *
     * @param  array  $keys
     * @return array
     */
    public function getMany(array keys) -> array
    {
        var config, key, deft;
    
        let config =  [];
        for key, deft in keys {
            if is_numeric(key) {
                //php-to-zephir error
                //list($key, $deft) = [$deft, null];
                let key = deft;
                let deft =  null;
            }
            let config[key] = Arr::get(this->items, key, deft);
        }
        return config;
    }
    
    /**
     * Set a given configuration value.
     *
     * @param  array|string  $key
     * @param  mixed   $value
     * @return void
     */
    public function set(key, value = null)
    {
        var keys;
    
        let keys =  is_array(key) ? key  : [key : value];
        for key, value in keys {
            let this->items =  Arr::set(this->items, key, value);
        }
    }
    
    /**
     * Prepend a value onto an array configuration value.
     *
     * @param  string  $key
     * @param  mixed  $value
     * @return void
     */
    public function prepend(string key, value)
    {
        var myArray;
    
        let myArray =  this->get(key);
        array_unshift(myArray, value);
        this->set(key, myArray);
    }
    
    /**
     * Push a value onto an array configuration value.
     *
     * @param  string  $key
     * @param  mixed  $value
     * @return void
     */
    public function push(string key, value)
    {
        var myArray;
    
        let myArray =  this->get(key);
        let myArray[] = value;
        this->set(key, myArray);
    }
    
    /**
     * Get all of the configuration items for the application.
     *
     * @return array
     */
    public function all() -> array
    {
        return this->items;
    }
    
    /**
     * Determine if the given configuration option exists.
     *
     * @param  string  $key
     * @return bool
     */
    public function offsetExists(key) -> bool
    {
        return this->has(key);
    }
    
    /**
     * Get a configuration option.
     *
     * @param  string  $key
     * @return mixed
     */
    public function offsetGet(key)
    {
        return this->get(key);
    }
    
    /**
     * Set a configuration option.
     *
     * @param  string  $key
     * @param  mixed  $value
     * @return void
     */
    public function offsetSet(key, value)
    {
        this->set(key, value);
    }
    
    /**
     * Unset a configuration option.
     *
     * @param  string  $key
     * @return void
     */
    public function offsetUnset(key)
    {
        this->set(key, null);
    }

}