namespace Zim\Contract;

interface Config
{
    /**
     * Determine if the given configuration value exists.
     *
     * @param  string  $key
     * @return bool
     */
    public function has(string key) -> bool;
    
    /**
     * Get the specified configuration value.
     *
     * @param  array|string  $key
     * @param  mixed   $deft
     * @return mixed
     */
    public function get(key, deft = null);
    
    /**
     * Get all of the configuration items for the application.
     *
     * @return array
     */
    public function all() -> array;
    
    /**
     * Set a given configuration value.
     *
     * @param  array|string  $key
     * @param  mixed   $value
     * @return void
     */
    public function set(key, value = null);
    
    /**
     * Prepend a value onto an array configuration value.
     *
     * @param  string  $key
     * @param  mixed  $value
     * @return void
     */
    public function prepend(string key, value);
    
    /**
     * Push a value onto an array configuration value.
     *
     * @param  string  $key
     * @param  mixed  $value
     * @return void
     */
    public function push(string key, value);

}