/*
 * This file is part of the Symfony package.
 *
 * (c) Fabien Potencier <fabien@symfony.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
namespace Zim\Http;

/**
 * HeaderBag is a container for HTTP headers.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
class HeaderBag implements \IteratorAggregate, \Countable
{
    protected headers = [];
    protected cacheControl = [];
    /**
     * @param array $headers An array of HTTP headers
     */
    public function __construct(array headers = []) -> void
    {
        var key, values;
    
        for key, values in headers {
            this->set(key, values);
        }
    }

    /**
     * Parses a Cache-Control HTTP header.
     *
     * @param string $header The value of the Cache-Control HTTP header
     *
     * @return array An array representing the attribute values
     */
    protected function parseCacheControl(string header) -> array
    {
        var parts;

        let parts =  HeaderUtils::split(header, ",=");
        return HeaderUtils::combine(parts);
    }
    
    protected function getCacheControlHeader()
    {
        ksort(this->cacheControl);
        return HeaderUtils::toString(this->cacheControl, ",");
    }
    
    /**
     * Returns the headers as a string.
     *
     * @return string The headers
     */
    public function __toString() -> string
    {
        var headers, content, name, values, value;
    
        let headers =  this->all();
        if !(headers) {
            return "";
        }
        ksort(headers);
        let content = "";
        for name, values in headers {
            let name =  ucwords(name, "-");
            for value in values {
                let content = content.name . ":". value . "\r\n";
            }
        }
        return content;
    }
    
    /**
     * Returns the headers.
     *
     * @return array An array of headers
     */
    public function all() -> array
    {
        return this->headers;
    }
    
    /**
     * Returns the parameter keys.
     *
     * @return array An array of parameter keys
     */
    public function keys() -> array
    {
        return array_keys(this->all());
    }
    
    /**
     * Replaces the current HTTP headers by a new set.
     *
     * @param array $headers An array of HTTP headers
     */
    public function replace(array headers = []) -> void
    {
        let this->headers =  [];
        this->add(headers);
    }
    
    /**
     * Adds new headers the current HTTP headers set.
     *
     * @param array $headers An array of HTTP headers
     */
    public function add(array headers) -> void
    {
        var key, values;
    
        for key, values in headers {
            this->set(key, values);
        }
    }
    
    /**
     * Returns a header value by name.
     *
     * @param string               $key     The header name
     * @param string|string[]|null $default The default value
     * @param bool                 $first   Whether to return the first value or all header values
     *
     * @return string|string[]|null The first header value or default value if $first is true, an array of values otherwise
     */
    public function get(string key, deft = null, bool first = true)
    {
        var headers;
    
        let key =  str_replace("_", "-", strtolower(key));
        let headers =  this->all();
        if !(array_key_exists(key, headers)) {
            if deft === null {
                return  first ? null  : [];
            }
            return  first ? deft  : [deft];
        }
        if first {
            return count(headers[key]) ? headers[key][0]  : deft;
        }
        return headers[key];
    }
    
    /**
     * Sets a header by name.
     *
     * @param string          $key     The key
     * @param string|string[] $values  The value or an array of values
     * @param bool            $replace Whether to replace the actual value or not (true by default)
     */
    public function set(string key, values, bool replace = true) -> void
    {
        let key =  str_replace("_", "-", strtolower(key));
        if is_array(values) {
            let values =  array_values(values);
            if replace === true || !(isset this->headers[key]) {
                let this->headers[key] = values;
            } else {
                let this->headers[key] =  array_merge(this->headers[key], values);
            }
        } else {
            if replace === true || !(isset this->headers[key]) {
                let this->headers[key] =  [values];
            } else {
                let this->headers[key][] = values;
            }
        }
    }
    
    /**
     * Returns true if the HTTP header is defined.
     *
     * @param string $key The HTTP header
     *
     * @return bool true if the parameter exists, false otherwise
     */
    public function has(string key) -> bool
    {
        return array_key_exists(str_replace("_", "-", strtolower(key)), this->all());
    }
    
    /**
     * Returns true if the given HTTP header contains the given value.
     *
     * @param string $key   The HTTP header name
     * @param string $value The HTTP value
     *
     * @return bool true if the value is contained in the header, false otherwise
     */
    public function contains(string key, string value) -> bool
    {
        return in_array(value, this->get(key, null, false));
    }
    
    /**
     * Removes a header.
     *
     * @param string $key The HTTP header name
     */
    public function remove(string key) -> void
    {
        let key =  str_replace("_", "-", strtolower(key));
        unset this->headers[key];
    
    }
    
    /**
     * Returns an iterator for headers.
     *
     * @return \ArrayIterator An \ArrayIterator instance
     */
    public function getIterator() -> <\ArrayIterator>
    {
        return new \ArrayIterator(this->headers);
    }
    
    /**
     * Returns the number of headers.
     *
     * @return int The number of headers
     */
    public function count() -> int
    {
        return count(this->headers);
    }

}