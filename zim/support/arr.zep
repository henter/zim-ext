namespace Zim\Support;

use ArrayAccess;

class Arr
{
    /**
     * Determine whether the given value is array accessible.
     *
     * @param  mixed  $value
     * @return bool
     */
    public static function accessible(value) -> bool
    {
        return is_array(value) || (typeof value == "object" && value instanceof ArrayAccess);
    }
    
    /**
     * Determine if the given key exists in the provided array.
     *
     * @param  \ArrayAccess|array  $array
     * @param  string|int  $key
     * @return bool
     */
    public static function exists(myArray, key) -> bool
    {
        if typeof myArray == "object" && myArray instanceof ArrayAccess {
            return myArray->offsetExists(key);
        }
        return array_key_exists(key, myArray);
    }
    
    /**
     * Get an item from an array using "dot" notation.
     *
     * @param  \ArrayAccess|array  $array
     * @param  string  $key
     * @param  mixed   $deft
     * @return mixed
     */
    public static function get(myArray, string key, deft = null)
    {
        var segment;
    
        if !(static::accessible(myArray)) {
            return deft;
        }
        if is_null(key) {
            return myArray;
        }
        if static::exists(myArray, key) {
            return myArray[key];
        }
        if strpos(key, ".") === false {
            return  isset myArray[key] ? myArray[key]  : deft;
        }
        for segment in explode(".", key) {
            if static::accessible(myArray) && static::exists(myArray, segment) {
                let myArray = myArray[segment];
            } else {
                return deft;
            }
        }
        return myArray;
    }
    
    /**
     * Check if an item or items exist in an array using "dot" notation.
     *
     * @param  \ArrayAccess|array  $array
     * @param  string|array  $keys
     * @return bool
     */
    public static function has(myArray, keys) -> bool
    {
        var key, subKeyArray, segment;
    
        if is_null(keys) {
            return false;
        }
        let keys = typeof keys == "array" ? keys : [keys];
        if !myArray {
            return false;
        }
        if count(keys) === 0 {
            return false;
        }
        for key in keys {
            let subKeyArray = myArray;
            if static::exists(myArray, key) {
                continue;
            }
            for segment in explode(".", key) {
                if static::accessible(subKeyArray) && static::exists(subKeyArray, segment) {
                    let subKeyArray = subKeyArray[segment];
                } else {
                    return false;
                }
            }
        }
        return true;
    }
    
    /**
     * Set an array item to a given value using "dot" notation.
     *
     * If no key is given to the method, the entire array will be replaced.
     *
     * @param  array   $array
     * @param  string  $key
     * @param  mixed   $value
     * @return array
     */
    public static function set(array myArray, string key, value) -> array
    {
        var ret;
    
        if is_null(key) {
            let myArray = value;
            return myArray;
        }
        let ret =  static::_parseIniString(key, value);
        return array_merge_recursive(myArray, ret);
    }
    
    protected static function _parseIniString(string path, value)
    {
        var pos, key;
    
        let value =  static::_cast(value);
        let pos =  strpos(path, ".");
        if pos === false {
            return [path : value];
        }
        let key =  substr(path, 0, pos);
        let path =  substr(path, pos + 1);
        return [key : static::_parseIniString(path, value)];
    }
    
    protected static function _cast(ini)
    {
        var key, val;
    
        if is_array(ini) {
            for key, val in ini {
                let ini[key] = static::_cast(val);
            }
        }
        return ini;
    }

}