/**
 * File Request.php
 * @henter
 * Time: 2018-11-24 19:53
 *
 */
namespace Zim\Http;

use Zim\Contract\Request as RequestContract;

/**
 * Request represents an HTTP request.
 * @author Fabien Potencier <fabien@symfony.com>
 */
class Request implements RequestContract
{
    const METHOD_HEAD = "HEAD";
    const METHOD_GET = "GET";
    const METHOD_POST = "POST";
    const METHOD_PUT = "PUT";
    const METHOD_PATCH = "PATCH";
    const METHOD_DELETE = "DELETE";
    const METHOD_PURGE = "PURGE";
    const METHOD_OPTIONS = "OPTIONS";
    const METHOD_TRACE = "TRACE";
    const METHOD_CONNECT = "CONNECT";
    /**
     * Custom parameters.
     *
     * @var ParameterBag
     */
    public attributes;
    /**
     * Request body parameters ($_POST).
     *
     * @var ParameterBag
     */
    public request;
    /**
     * Query string parameters ($_GET).
     *
     * @var ParameterBag
     */
    public query;
    /**
     * Server and execution environment parameters ($_SERVER).
     *
     * @var ServerBag
     */
    public server;
    /**
     * Headers (taken from the $_SERVER).
     *
     * @var HeaderBag
     */
    public headers;
    /**
     * @var string|resource|false|null
     */
    protected content;
    /**
     * @var string
     */
    protected pathInfo;
    /**
     * @var string
     */
    protected requestUri;
    /**
     * @var string
     */
    protected method;
    /**
     * @var array
     */
    protected static formats;
    protected static forwardedHeaders = ["FORWARDED", "X_FORWARDED_FOR", "X_FORWARDED_HOST"];
    /**
     * @param array                $query      The GET parameters
     * @param array                $request    The POST parameters
     * @param array                $attributes The request attributes (parameters parsed from the PATH_INFO, ...)
     * @param array                $server     The SERVER parameters
     * @param string|resource|null $content    The raw body data
     */
    public function __construct(array query = [], array request = [], array attributes = [], array server = [], content = null) -> void
    {
        this->initialize(query, request, attributes, server, content);
    }
    
    /**
     * @return string
     */
    public function getForwardedFor() -> string
    {
        var key, host;
    
        for key in self::forwardedHeaders {
            let host =  this->headers->get(key);
            if host {
                return current(host);
            }
        }
        return "";
    }
    
    /**
     * Sets the parameters for this request.
     *
     * This method also re-initializes all properties.
     *
     * @param array                $query      The GET parameters
     * @param array                $request    The POST parameters
     * @param array                $attributes The request attributes (parameters parsed from the PATH_INFO, ...)
     * @param array                $server     The SERVER parameters
     * @param string|resource|null $content    The raw body data
     */
    public function initialize(array query = [], array request = [], array attributes = [], array server = [], content = null) -> void
    {
        let this->request =  new ParameterBag(request);
        let this->query =  new ParameterBag(query);
        let this->attributes =  new ParameterBag(attributes);
        let this->server =  new ServerBag(server);
        let this->headers =  new HeaderBag(this->server->getHeaders());
        let this->content = content;
        let this->pathInfo =  null;
        let this->requestUri =  null;
        let this->method =  null;
    }
    
    /**
     * Creates a new request with values from PHP's super globals.
     *
     * @return static
     */
    public static function createFromGlobals() -> <Request>
    {
        var request, methods, data;
    
        let request =  new static(_GET, _POST, [], _SERVER);
        let methods = ["PUT", "DELETE", "PATCH"];
        if 0 === strpos(request->headers->get("CONTENT_TYPE"), "application/x-www-form-urlencoded") &&
            in_array(strtoupper(request->server->get("REQUEST_METHOD", "GET")), methods)
        {
            parse_str(request->getContent(), data);
            let request->request =  new ParameterBag(data);
        }
        return request;
    }
    
    /**
     * Gets the request format.
     *
     * Here is the process to determine the format:
     *
     *  * _format request attribute
     *  * $default
     *
     * @param string|null $default The default format
     *
     * @return string The request format
     */
    public function getRequestFormat(deft = "html") -> string
    {
        return this->attributes->get("_format", deft);
    }
    
    /**
     * Gets the mime type associated with the format.
     *
     * @param string $format The format
     *
     * @return string|null The associated mime type (null if not found)
     */
    public function getMimeType(string format)
    {
        if self::formats === null {
            static::initializeFormats();
        }
        return  isset self::formats[format] ? self::formats[format][0]  : null;
    }
    
    /**
     * Gets the mime types associated with the format.
     *
     * @param string $format The format
     *
     * @return array The associated mime types
     */
    public static function getMimeTypes(string format) -> array
    {
        if self::formats === null {
            static::initializeFormats();
        }
        return  isset self::formats[format] ? self::formats[format]  : [];
    }
    
    /**
     * Initializes HTTP request formats.
     */
    protected static function initializeFormats() -> void
    {
        let self::formats =  ["html" : ["text/html", "application/xhtml+xml"], "txt" : ["text/plain"], "js" : ["application/javascript", "application/x-javascript", "text/javascript"], "css" : ["text/css"], "json" : ["application/json", "application/x-json"], "jsonld" : ["application/ld+json"], "xml" : ["text/xml", "application/xml", "application/x-xml"], "rdf" : ["application/rdf+xml"], "atom" : ["application/atom+xml"], "rss" : ["application/rss+xml"], "form" : ["application/x-www-form-urlencoded"]];
    }
    
    /**
     * Clones the current request.
     *
     * Note that the session is not cloned as duplicated requests
     * are most of the time sub-requests of the main one.
     */
    public function __clone() -> void
    {
        let this->query =  clone this->query;
        let this->request =  clone this->request;
        let this->attributes =  clone this->attributes;
        let this->server =  clone this->server;
        let this->headers =  clone this->headers;
    }
    
    /**
     * Returns the request as a string.
     *
     * @return string The request
     */
    public function __toString() -> string
    {
        var content, e;
    
        try {
            let content =  this->getContent();
        } catch \LogicException, e {
            return trigger_error(e, E_USER_ERROR);
        }
        return sprintf("%s %s %s", this->getMethod(), this->getRequestUri(), this->server->get("SERVER_PROTOCOL")) . "
" . this->headers . content;
    }
    
    /**
     * Normalizes a query string.
     *
     * It builds a normalized query string, where keys/value pairs are alphabetized,
     * have consistent escaping and unneeded delimiters are removed.
     *
     * @param string $qs Query string
     *
     * @return string A normalized query string for the Request
     */
    public static function normalizeQueryString(string qs) -> string
    {
        if qs == "" {
            return "";
        }
        parse_str(qs, qs);
        ksort(qs);
        return http_build_query(qs, "", "&", PHP_QUERY_RFC3986);
    }

    /**
     * Gets a "parameter" value from any bag.
     *
     * This method is mainly useful for libraries that want to provide some flexibility. If you don't need the
     * flexibility in controllers, it is better to explicitly get request parameters from the appropriate
     * public property instead (attributes, query, request).
     *
     * Order of precedence: PATH (routing placeholders or custom attributes), GET, BODY
     *
     * @param string $key     The key
     * @param mixed  $default The default value if the parameter key does not exist
     *
     * @return mixed
     */
    public function get(string key, deft = null)
    {
        var result;
    
        let result =  this->attributes->get(key, this);
        if this !== result {
            return result;
        }
        let result =  this->query->get(key, this);
        if this !== result {
            return result;
        }
        let result =  this->request->get(key, this);
        if this !== result {
            return result;
        }
        return deft;
    }
    
    /**
     * Returns the path being requested relative to the executed script.
     *
     * The path info always starts with a /.
     *
     * Suppose this request is instantiated from /mysite on localhost:
     *
     *  * http://localhost/mysite              returns an empty string
     *  * http://localhost/mysite/about        returns '/about'
     *  * http://localhost/mysite/enco%20ded   returns '/enco%20ded'
     *  * http://localhost/mysite/about?var=1  returns '/about'
     *
     * @return string The raw path (i.e. not urldecoded)
     */
    public function getPathInfo() -> string
    {
        if this->pathInfo === null {
            let this->pathInfo =  this->preparePathInfo();
        }
        return this->pathInfo;
    }
    
    /**
     * Gets the request's scheme.
     *
     * @return string
     */
    public function getScheme() -> string
    {
        return  this->isSecure() ? "https"  : "http";
    }
    
    public function isSecure()
    {
        var https;
    
        let https =  this->server->get("HTTPS");
        return !(empty(https)) && strtolower(https) !== "off";
    }
    
    /**
     * Returns the port on which the request is made.
     *
     * This method can read the client port from the "X-Forwarded-Port" header
     * when trusted proxies were set via "setTrustedProxies()".
     *
     * The "X-Forwarded-Port" header must contain the client port.
     *
     * @return int|string can be a string if fetched from the server bag
     */
    public function getPort()
    {
        var host, pos;
    
        let host =  this->getForwardedFor();
        if host {
            //nothing
            let host = host;
        } else {
        let host =  this->headers->get("HOST");
        if !(host) {
            return this->server->get("SERVER_PORT");
        }
        }
        if host[0] === "[" {
            let pos =  strpos(host, ":", strrpos(host, "]"));
        } else {
            let pos =  strrpos(host, ":");
        }
        if pos !== false {
            return (int) substr(host, pos + 1);
        }
        return  this->getScheme() === "https" ? 443  : 80;
    }
    
    /**
     * Returns the HTTP host being requested.
     *
     * The port name will be appended to the host if it's non-standard.
     *
     * @return string
     */
    public function getHttpHost() -> string
    {
        var scheme, port;
    
        let scheme =  this->getScheme();
        let port =  this->getPort();
        if scheme == "http" && 80 == port || scheme == "https" && 443 == port {
            return this->getHost();
        }
        return this->getHost() . ":" . port;
    }
    
    /**
     * Returns the requested URI (path and query string).
     *
     * @return string The raw URI (i.e. not URI decoded)
     */
    public function getRequestUri() -> string
    {
        if this->requestUri === null {
            let this->requestUri =  this->prepareRequestUri();
        }
        return this->requestUri;
    }
    
    /**
     * Gets the scheme and HTTP host.
     *
     * If the URL was called with basic authentication, the user
     * and the password are not added to the generated string.
     *
     * @return string The scheme and HTTP host
     */
    public function getSchemeAndHttpHost() -> string
    {
        return this->getScheme() . "://" . this->getHttpHost();
    }
    
    /**
     * Generates a normalized URI (URL) for the Request.
     *
     * @return string A normalized URI (URL) for the Request
     *
     * @see getQueryString()
     */
    public function getUri() -> string
    {
        var qs;
    
        let qs =  this->getQueryString();
        if qs !== null {
            let qs =  "?" . qs;
        }
        return this->getSchemeAndHttpHost() . this->getPathInfo() . qs;
    }
    
    /**
     * Generates the normalized query string for the Request.
     *
     * It builds a normalized query string, where keys/value pairs are alphabetized
     * and have consistent escaping.
     *
     * @return string|null A normalized query string for the Request
     */
    public function getQueryString()
    {
        var qs;
    
        let qs =  static::normalizeQueryString(this->server->get("QUERY_STRING"));
        return  qs === "" ? null  : qs;
    }
    
    /**
     * Returns the host name.
     *
     * This method can read the client host name from the "X-Forwarded-Host" header
     * when trusted proxies were set via "setTrustedProxies()".
     *
     * The "X-Forwarded-Host" header must contain the client host name.
     *
     * @return string
     */
    public function getHost() -> string
    {
        var host;
    
        let host =  this->getForwardedFor();
        if host {
            //nothing
            let host = host;
        } else {
        let host =  this->headers->get("HOST");
        if !(host) {
            let host =  this->server->get("SERVER_NAME");
            if !(host) {
                let host =  this->server->get("SERVER_ADDR", "");
            }
        }
        }
        return strtolower(preg_replace("/:\\d+$/", "", trim(host)));
    }
    
    /**
     * Gets the request "intended" method.
     *
     * If the X-HTTP-Method-Override header is set, and if the method is a POST,
     * then it is used to determine the "real" intended HTTP method.
     *
     * The _method request parameter can also be used to determine the HTTP method,
     * but only if enableHttpMethodParameterOverride() has been called.
     *
     * The method is always an uppercased string.
     *
     * @return string The request method
     *
     * @see getRealMethod()
     */
    public function getMethod() -> string
    {
        var method;
    
        if this->method === null {
            let this->method =  strtoupper(this->server->get("REQUEST_METHOD", "GET"));
            if this->method === "POST" {
                let method =  this->headers->get("X-HTTP-METHOD-OVERRIDE");
                if method {
                    let this->method =  strtoupper(method);
                }
            }
        }
        return this->method;
    }
    
    /**
     * Gets the "real" request method.
     *
     * @return string The request method
     *
     * @see getMethod()
     */
    public function getRealMethod() -> string
    {
        return strtoupper(this->server->get("REQUEST_METHOD", "GET"));
    }
    
    /**
     * Checks if the request method is of specified type.
     *
     * @param string $method Uppercase request method (GET, POST etc)
     *
     * @return bool
     */
    public function isMethod(string method) -> bool
    {
        return this->getMethod() === strtoupper(method);
    }
    
    /**
     * Returns the request body content.
     *
     * @param bool $asResource If true, a resource will be returned
     *
     * @return string|resource The request body content or a resource to read the body stream
     *
     * @throws \LogicException
     */
    public function getContent(bool asResource = false)
    {
        var currentContentIsResource, resourcee;
    
        let currentContentIsResource =  is_resource(this->content);
        if asResource === true {
            if currentContentIsResource {
                rewind(this->content);
                return this->content;
            }
            // Content passed in parameter (test)
            if is_string(this->content) {
                let resourcee =  fopen("php://temp", "r+");
                fwrite(resourcee, this->content);
                rewind(resourcee);
                return resourcee;
            }
            let this->content =  false;
            return fopen("php://input", "rb");
        }
        if currentContentIsResource {
            rewind(this->content);
            return stream_get_contents(this->content);
        }
        if this->content === null || this->content === false {
            let this->content =  file_get_contents("php://input");
        }
        return this->content;
    }
    
    /**
     * @return string
     */
    protected function prepareRequestUri() -> string
    {
        var requestUri, schemeAndHttpHost;
    
        let requestUri =  this->server->get("REQUEST_URI");
        // HTTP proxy reqs setup request URI with scheme and host [and port] + the URL path, only use URL path
        let schemeAndHttpHost =  this->getSchemeAndHttpHost();
        if 0 === strpos(requestUri, schemeAndHttpHost) {
            let requestUri =  substr(requestUri, strlen(schemeAndHttpHost));
        }
        return requestUri;
    }
    
    /**
     * Prepares the path info.
     *
     * @return string path info
     */
    protected function preparePathInfo() -> string
    {
        var requestUri, pos;
    
        let requestUri =  this->getRequestUri();
        if requestUri === null {
            return "/";
        }
        // Remove the query string from REQUEST_URI
        let pos =  strpos(requestUri, "?");
        if pos !== false {
            let requestUri =  substr(requestUri, 0, pos);
        }
        if requestUri !== "" && substr(requestUri, 0, 1) !== "/" {
            let requestUri =  "/" . requestUri;
        }
        return requestUri;
    }

}