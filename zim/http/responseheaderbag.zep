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
 * ResponseHeaderBag is a container for Response HTTP headers.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
class ResponseHeaderBag extends HeaderBag
{
    protected computedCacheControl = [];
    protected headerNames = [];
    public function __construct(array headers = []) -> void
    {
        parent::__construct(headers);
        this->set("Cache-Control", "");
        /* RFC2616 - 14.18 says all Responses need to have a Date */
        if !(isset this->headers["date"]) {
            this->initDate();
        }
    }
    
    /**
     * Returns the headers, with original capitalizations.
     *
     * @return array An array of headers
     */
    public function allPreserveCase() -> array
    {
        var headers, name, value;
    
        let headers =  [];
        for name, value in this->all() {
            let headers[isset this->headerNames[name] ? this->headerNames[name]  : name] = value;
        }
        return headers;
    }
    
    /**
     * {@inheritdoc}
     */
    public function replace(array headers = []) -> void
    {
        let this->headerNames =  [];
        parent::replace(headers);
        if !(isset this->headers["cache-control"]) {
            this->set("Cache-Control", "");
        }
        if !(isset this->headers["date"]) {
            this->initDate();
        }
    }
    
    /**
     * {@inheritdoc}
     */
    public function set(key, values, replace = true) -> void
    {
        var uniqueKey, tmpArrayd0d6087f950982817b4a268511aa1623, computed;
    
        let uniqueKey =  str_replace("_", "-", strtolower(key));
        let this->headerNames[uniqueKey] = key;
        parent::set(key, values, replace);
        // ensure the cache-control header has sensible defaults
        let tmpArrayd0d6087f950982817b4a268511aa1623 = ["cache-control", "etag", "last-modified", "expires"];
        if in_array(uniqueKey, tmpArrayd0d6087f950982817b4a268511aa1623, true) {
            let computed =  this->computeCacheControlValue();
            let this->headers["cache-control"] =  [computed];
            let this->headerNames["cache-control"] = "Cache-Control";
            let this->computedCacheControl =  this->parseCacheControl(computed);
        }
    }
    
    /**
     * {@inheritdoc}
     */
    public function remove(key) -> void
    {
        var uniqueKey;
    
        let uniqueKey =  str_replace("_", "-", strtolower(key));
        unset this->headerNames[uniqueKey];
        
        parent::remove(key);
        if uniqueKey === "cache-control" {
            let this->computedCacheControl =  [];
        }
        if uniqueKey === "date" {
            this->initDate();
        }
    }
    
    /**
     * Returns the calculated value of the cache-control header.
     *
     * This considers several other headers and calculates or modifies the
     * cache-control header to a sensible, conservative value.
     *
     * @return string
     */
    protected function computeCacheControlValue() -> string
    {
        var header;
    
        if !(this->cacheControl) && !(this->has("ETag")) && !(this->has("Last-Modified")) && !(this->has("Expires")) {
            return "no-cache, private";
        }
        if !(this->cacheControl) {
            // conservative by default
            return "private, must-revalidate";
        }
        let header =  this->getCacheControlHeader();
        if isset this->cacheControl["public"] || isset this->cacheControl["private"] {
            return header;
        }
        // public if s-maxage is defined, private otherwise
        if !(isset this->cacheControl["s-maxage"]) {
            return header . ", private";
        }
        return header;
    }
    
    protected function initDate() -> void
    {
        var now;
    
        let now =  \DateTime::createFromFormat("U", time());
        now->setTimezone(new \DateTimeZone("UTC"));
        this->set("Date", now->format("D, d M Y H:i:s") . " GMT");
    }

}