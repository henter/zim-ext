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

    protected static httpMethodParameterOverride = false;

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
    protected baseUrl;

    /**
     * @var string
     */
    protected basePath;

    /**
     * @var string
     */
    protected method;

    /**
     * @var string
     */
    protected format;
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
            let host = this->headers->get(key);
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
        let this->request = new ParameterBag(request);
        let this->query = new ParameterBag(query);
        let this->attributes = new ParameterBag(attributes);
        let this->server = new ServerBag(server);
        let this->headers = new HeaderBag(this->server->getHeaders());
        let this->content = content;
        let this->pathInfo = null;
        let this->requestUri = null;
        let this->baseUrl = null;
        let this->basePath = null;
        let this->method = null;
        let this->format = null;
    }
    
    /**
     * Creates a new request with values from PHP's super globals.
     *
     * @return static
     */
    public static function createFromGlobals() -> <Request>
    {
        var request, data;
        /*
         * With the php's bug #66606, the php's built-in web server
         * stores the Content-Type and Content-Length header values in
         * HTTP_CONTENT_TYPE and HTTP_CONTENT_LENGTH fields.
         */
        var server = _SERVER;

        if PHP_SAPI === "cli-server" {
            if array_key_exists("HTTP_CONTENT_LENGTH", _SERVER) {
                let server["CONTENT_LENGTH"] = _SERVER["HTTP_CONTENT_LENGTH"];
            }
            if array_key_exists("HTTP_CONTENT_TYPE", _SERVER) {
                let server["CONTENT_TYPE"] = _SERVER["HTTP_CONTENT_TYPE"];
            }
        }

        let request = new static(_GET, _POST, [], server);

        if strpos(request->headers->get("CONTENT_TYPE"), "application/x-www-form-urlencoded") === 0 &&
            in_array(strtoupper(request->server->get("REQUEST_METHOD", "GET")), ["PUT", "DELETE", "PATCH"]) {
            parse_str(request->getContent(), data);
            let request->request = new ParameterBag(data);
        }
        return request;
    }

    /**
     * Creates a Request based on a given URI and configuration.
     *
     * The information contained in the URI always take precedence
     * over the other information (server and parameters).
     *
     * @param string               $uri        The URI
     * @param string               $method     The HTTP method
     * @param array                $parameters The query (GET) or request (POST) parameters
     * @param array                $server     The server parameters ($_SERVER)
     * @param string|resource|null $content    The raw body data
     *
     * @return static
     */
    public static function create(string uri, string method = "GET",
                        array parameters = [], array server = [],
                        var content = null) -> <Request>
    {
        var components, request, query, queryString, qs;
        let server = array_replace([
            "SERVER_NAME": "localhost",
            "SERVER_PORT": 80,
            "HTTP_HOST": "localhost",
            "HTTP_USER_AGENT": "ZimPHP",
            "HTTP_ACCEPT": "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
            "HTTP_ACCEPT_LANGUAGE": "en-us,en;q=0.5",
            "HTTP_ACCEPT_CHARSET": "ISO-8859-1,utf-8;q=0.7,*;q=0.7",
            "REMOTE_ADDR": "127.0.0.1",
            "SCRIPT_NAME": "",
            "SCRIPT_FILENAME": "",
            "SERVER_PROTOCOL": "HTTP/1.1",
            "REQUEST_TIME": time()
        ], server);

        let server["PATH_INFO"] = "";
        let server["REQUEST_METHOD"] = strtoupper(method);

        let components = parse_url(uri);
        if isset(components["host"]) {
            let server["SERVER_NAME"] = components["host"];
            let server["HTTP_HOST"] = components["host"];
        }

        if isset(components["scheme"]) {
            if "https" === components["scheme"] {
                let server["HTTPS"] = "on";
                let server["SERVER_PORT"] = 443;
            } else {
                unset server["HTTPS"];
                let server["SERVER_PORT"] = 80;
            }
        }

        if isset(components["port"]) {
            let server["SERVER_PORT"] = components["port"];
            let server["HTTP_HOST"] = server["HTTP_HOST"] . ":" . components["port"];
        }

        if isset components["user"] {
            let server["PHP_AUTH_USER"] = components["user"];
        }

        if isset components["pass"] {
            let server["PHP_AUTH_PW"] = components["pass"];
        }

        if !isset(components["path"]) {
            let components["path"] = "/";
        }

        switch (strtoupper(method)) {
            case "POST":
            case "PUT":
            case "DELETE":
                if !isset(server["CONTENT_TYPE"]) {
                    let server["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
                }
            // no break
            case "PATCH":
                let request = parameters;
                let query = [];
                break;
            default:
                let request = [];
                let query = parameters;
                break;
        }

        let queryString = "";
        if isset(components["query"]) {
            parse_str(html_entity_decode(components["query"]), qs);

            if query {
                let query = array_replace(qs, query);
                let queryString = http_build_query(query, "", "&");
            } else {
                let query = qs;
                let queryString = components["query"];
            }
        } elseif query {
            let queryString = http_build_query(query, "", "&");
        }

        let server["REQUEST_URI"] = components["path"].(queryString !== "" ? "?".queryString : "");
        let server["QUERY_STRING"] = queryString;

        return new static(query, request, [], server, content);
    }

    /**
     * Clones a request and overrides some of its parameters.
     *
     * @param array $query      The GET parameters
     * @param array $request    The POST parameters
     * @param array $attributes The request attributes (parameters parsed from the PATH_INFO, ...)
     * @param array $server     The SERVER parameters
     *
     * @return static
     */
    public function duplicate(array query = [], array request = [], array attributes = [], array server = []) -> <Request>
    {
        var dup;
        let dup = clone this;
        if count(query) {
            let dup->query = new ParameterBag(query);
        }
        if count(request) {
            let dup->request = new ParameterBag(request);
        }
        if count(attributes) {
            let dup->attributes = new ParameterBag(attributes);
        }
        if count(server) {
            let dup->server = new ServerBag(server);
            let dup->headers = new HeaderBag(dup->server->getHeaders());
        }
        let dup->pathInfo = null;
        let dup->requestUri = null;
        let dup->baseUrl = null;
        let dup->basePath = null;
        let dup->method = null;
        let dup->format = null;

        if !dup->get("_format") && this->get("_format") {
            dup->attributes->set("_format", this->get("_format"));
        }

        if !dup->getRequestFormat(null) {
            dup->setRequestFormat(this->getRequestFormat(null));
        }

        return dup;
    }

    /**
     * Returns the user.
     *
     * @return string|null
     */
    public function getUser()
    {
        return this->headers->get("PHP_AUTH_USER");
    }

    /**
     * Returns the password.
     *
     * @return string|null
     */
    public function getPassword()
    {
        return this->headers->get("PHP_AUTH_PW");
    }

    /**
     * Gets the user info.
     *
     * @return string A user name and, optionally, scheme-specific information about how to gain authorization to access the server
     */
    public function getUserInfo()
    {
        var userinfo, pass;
        let userinfo = this->getUser();
        let pass = this->getPassword();
        if (pass != "") {
            let userinfo .= ":".pass;
        }

        return userinfo;
    }

    /**
     * @return bool
     */
    public function isNoCache()
    {
        return this->headers->hasCacheControlDirective("no-cache") || "no-cache" == $this->headers->get("Pragma");
    }

    /**
     * Associates a format with mime types.
     *
     * @param string       $format    The format
     * @param string|array $mimeTypes The associated mime types (the preferred one must be the first as it will be used as the content type)
     */
    public function setFormat(var format, var mimeTypes)
    {
        if null === self::formats {
            static::initializeFormats();
        }

        let self::formats[format] = is_array(mimeTypes) ? mimeTypes : [mimeTypes];
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
    public function getRequestFormat(var deft = "html") -> string
    {
       if this->format === null {
           let this->format = this->attributes->get("_format");
       }

       return this->format === null ? deft : this->format;
    }

    /**
     * Sets the request format.
     *
     * @param string $format The request format
     */
    public function setRequestFormat(string format)
    {
        let this->format = format;
    }

    /**
     * Gets the format associated with the request.
     *
     * @return string|null The format (null if no content type is present)
     */
    public function getContentType()
    {
        return this->getFormat((string)this->headers->get("CONTENT_TYPE"));
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
        return  isset self::formats[format] ? self::formats[format][0] : null;
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
        return  isset self::formats[format] ? self::formats[format] : [];
    }

    /**
     * Gets the format associated with the mime type.
     *
     * @param string $mimeType The associated mime type
     *
     * @return string|null The format (null if not found)
     */
    public function getFormat(string mimeType)
    {
        var canonicalMimeType, pos;
        let canonicalMimeType = null;
        let pos = strpos(mimeType, ";");

        if pos !== false {
            let canonicalMimeType = trim(substr(mimeType, 0, pos));
        }

        if (self::formats === null) {
            static::initializeFormats();
        }

        var format, mimeTypes;
        for format, mimeTypes in self::formats {
            if in_array(mimeType, (array) mimeTypes) {
                return format;
            }
            if canonicalMimeType !== null &&
                in_array(canonicalMimeType, (array) mimeTypes) {
                return format;
            }
        }
    }

    /**
     * Initializes HTTP request formats.
     */
    protected static function initializeFormats() -> void
    {
        let self::formats = [
            "html" : ["text/html", "application/xhtml+xml"],
            "txt" : ["text/plain"],
            "js" : ["application/javascript", "application/x-javascript", "text/javascript"],
            "css" : ["text/css"],
            "json" : ["application/json", "application/x-json"],
            "jsonld" : ["application/ld+json"],
            "xml" : ["text/xml", "application/xml", "application/x-xml"],
            "rdf" : ["application/rdf+xml"],
            "atom" : ["application/atom+xml"],
            "rss" : ["application/rss+xml"],
            "form" : ["application/x-www-form-urlencoded"]
        ];
    }
    
    /**
     * Clones the current request.
     *
     * Note that the session is not cloned as duplicated requests
     * are most of the time sub-requests of the main one.
     */
    public function __clone() -> void
    {
        let this->query = clone this->query;
        let this->request = clone this->request;
        let this->attributes = clone this->attributes;
        let this->server = clone this->server;
        let this->headers = clone this->headers;
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
            let content = this->getContent();
        } catch \LogicException, e {
            return trigger_error(e, E_USER_ERROR);
        }
        return sprintf("%s %s %s", this->getMethod(), this->getRequestUri(), this->server->get("SERVER_PROTOCOL")) . "
" . this->headers . content;
    }

    /**
     * Overrides the PHP global variables according to this request instance.
     *
     * It overrides $_GET, $_POST, $_REQUEST, $_SERVER, $_COOKIE.
     * $_FILES is never overridden, see rfc1867
     */
    public function overrideGlobals()
    {
        this->server->set("QUERY_STRING", static::normalizeQueryString(http_build_query(this->query->all(), "", "&")));

        let _GET = this->query->all();
        let _POST = this->request->all();
        let _SERVER = this->server->all();

        var key, value;
        for key, value in this->headers->all() {
            let key = strtoupper(str_replace("-", "_", key));
            if in_array(key, ["CONTENT_TYPE", "CONTENT_LENGTH"]) {
                let _SERVER[key] = implode(", ", value);
            } else {
                let _SERVER["HTTP_".key] = implode(", ", value);
            }
        }

        var request, requestOrder;
        let request = ["g": _GET, "p": _POST];
        let requestOrder = ini_get("request_order") ?: ini_get("variables_order");
        let requestOrder = preg_replace("#[^cgp]#", "", strtolower($requestOrder)) ?: "gp";

        let _REQUEST = [[]];

        var order;
        for order in str_split(requestOrder) {
            let _REQUEST = array_merge(_REQUEST, request[order]);
        }
    }

    /**
     * Enables support for the _method request parameter to determine the intended HTTP method.
     *
     * Be warned that enabling this feature might lead to CSRF issues in your code.
     * Check that you are using CSRF tokens when required.
     * If the HTTP method parameter override is enabled, an html-form with method "POST" can be altered
     * and used to send a "PUT" or "DELETE" request via the _method request parameter.
     * If these methods are not protected against CSRF, this presents a possible vulnerability.
     *
     * The HTTP method can only be overridden when the real HTTP method is POST.
     */
    public static function enableHttpMethodParameterOverride() -> void
    {
        let self::httpMethodParameterOverride = true;
    }

    /**
     * Checks whether support for the _method request parameter is enabled.
     *
     * @return bool True when the _method request parameter is enabled, false otherwise
     */
    public static function getHttpMethodParameterOverride()
    {
        return self::httpMethodParameterOverride;
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
    
        let result = this->attributes->get(key, this);
        if this !== result {
            return result;
        }
        let result = this->query->get(key, this);
        if this !== result {
            return result;
        }
        let result = this->request->get(key, this);
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
            let this->pathInfo = this->preparePathInfo();
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
        return  this->isSecure() ? "https" : "http";
    }
    
    public function isSecure()
    {
        var https;
    
        let https = this->server->get("HTTPS");
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
        var host, port, pos;

        let host = this->getForwardedFor();
        if !host {
            let port = this->server->get("SERVER_PORT");
            if port {
                return port;
            }
        }

        let host = this->headers->get("HOST");
        if host[0] === '[' {
            let pos = strpos(host, ":", strrpos(host, "]"));
        } else {
            let pos = strrpos(host, ":");
        }
        if pos !== false {
            return (int) substr(host, pos + 1);
        }
        return  this->getScheme() === "https" ? 443 : 80;
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
    
        let scheme = this->getScheme();
        let port = this->getPort();
        if (scheme == "http" && 80 == port) || (scheme == "https" && 443 == port) {
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
            let this->requestUri = this->prepareRequestUri();
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
    
        let qs = this->getQueryString();
        if qs !== null {
            let qs = "?" . qs;
        }
        return this->getSchemeAndHttpHost() . this->getBaseUrl() . this->getPathInfo() . qs;
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
    
        let qs = static::normalizeQueryString(this->server->get("QUERY_STRING"));
        return  qs === "" ? null : qs;
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

        let host = this->getForwardedFor();
        if !host {
            let host = this->headers->get("HOST");
            if !host {
                let host = this->server->get("SERVER_NAME");
                if !host {
                    let host = this->server->get("SERVER_ADDR", "");
                }
            }
        }
        return strtolower(preg_replace("/:\d+$/", "", trim(host)));
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
            let this->method = strtoupper(this->server->get("REQUEST_METHOD", "GET"));
            if this->method === "POST" {
                let method = this->headers->get("X-HTTP-METHOD-OVERRIDE");
                if method {
                    let this->method = strtoupper(method);
                } elseif self::httpMethodParameterOverride {
                    let method = this->request->get("_method", this->query->get("_method", "POST"));
                    if is_string(method) {
                        let this->method = strtoupper(method);
                    }
                }
            }
        }
        return this->method;
    }

    /**
     * Sets the request method.
     *
     * @param string $method
     */
    public function setMethod(method) -> void
    {
        let this->method = null;
        this->server->set("REQUEST_METHOD", method);
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
    
        let currentContentIsResource = is_resource(this->content);
        if asResource === true {
            if currentContentIsResource {
                rewind(this->content);
                return this->content;
            }
            // Content passed in parameter (test)
            if is_string(this->content) {
                let resourcee = fopen("php://temp", "r+");
                fwrite(resourcee, this->content);
                rewind(resourcee);
                return resourcee;
            }
            let this->content = false;
            return fopen("php://input", "rb");
        }
        if currentContentIsResource {
            rewind(this->content);
            return stream_get_contents(this->content);
        }
        if this->content === null || this->content === false {
            let this->content = file_get_contents("php://input");
        }
        return this->content;
    }
    
   /**
     * @return string
     */
    protected function prepareRequestUri()
    {
        var requestUri = "", uriComponents;

        if this->server->has("REQUEST_URI") {
            let requestUri = this->server->get("REQUEST_URI");

            // HTTP proxy reqs setup request URI with scheme and host [and port] + the URL path, only use URL path
            let uriComponents = parse_url(requestUri);

            if isset(uriComponents["path"]) {
                let requestUri = uriComponents["path"];
            }

            if isset(uriComponents["query"]) {
                let requestUri .= "?".uriComponents["query"];
            }
        } elseif this->server->has("ORIG_PATH_INFO") {
            // IIS 5.0, PHP as CGI
            let requestUri = this->server->get("ORIG_PATH_INFO");
            if this->server->get("QUERY_STRING") != "" {
                let requestUri .= "?".this->server->get("QUERY_STRING");
            }
            this->server->remove("ORIG_PATH_INFO");
        } elseif this->server->get("IIS_WasUrlRewritten") == "1" && this->server->get("UNENCODED_URL") != "" {
            // IIS7 with URL Rewrite: make sure we get the unencoded URL (double slash problem)
            let requestUri = this->server->get("UNENCODED_URL");
            this->server->remove("UNENCODED_URL");
            this->server->remove("IIS_WasUrlRewritten");
        }

        // normalize the request URI to ease creating sub-requests from this request
        this->server->set("REQUEST_URI", requestUri);

        return requestUri;
    }

    /**
     * Prepares the path info.
     *
     * @return string path info
     */
    protected function preparePathInfo() -> string
    {
        var requestUri, pos, baseUrl, pathInfo;
    
        let requestUri = this->getRequestUri();
        if requestUri === null {
            return "/";
        }
        // Remove the query string from REQUEST_URI
        let pos = strpos(requestUri, "?");
        if pos !== false {
            let requestUri = substr(requestUri, 0, pos);
        }
        if requestUri !== "" && substr(requestUri, 0, 1) !== "/" {
            let requestUri = "/" . requestUri;
        }

        let baseUrl = this->getBaseUrl();
        if baseUrl === null {
            return requestUri;
        }

        let pathInfo = substr(requestUri, strlen(baseUrl));
        if pathInfo === false || pathInfo === "" {
            // If substr() returns false then PATH_INFO is set to an empty string
            return "/";
        }

        return (string)pathInfo;
    }

    /**
     * Returns the root path from which this request is executed.
     *
     * Suppose that an index.php file instantiates this request object:
     *
     *  * http://localhost/index.php         returns an empty string
     *  * http://localhost/index.php/page    returns an empty string
     *  * http://localhost/web/index.php     returns '/web'
     *  * http://localhost/we%20b/index.php  returns '/we%20b'
     *
     * @return string The raw path (i.e. not urldecoded)
     */
    public function getBasePath()
    {
        if this->basePath === null {
            let this->basePath = this->prepareBasePath();
        }

        return this->basePath;
    }
    /**
     * Prepares the base path.
     *
     * @return string base path
     */
    protected function prepareBasePath()
    {
        var baseUrl;
        let baseUrl = this->getBaseUrl();
        if empty(baseUrl) {
            return "";
        }

        var filename, basePath;
        let filename = basename(this->server->get("SCRIPT_FILENAME"));
        if basename(baseUrl) === filename {
            let basePath = dirname(baseUrl);
        } else {
            let basePath = baseUrl;
        }

        if ("\\" === DIRECTORY_SEPARATOR) {
            let basePath = str_replace("\\", "/", basePath);
        }

        return rtrim(basePath, "/");
    }

    /**
     * Returns the root URL from which this request is executed.
     *
     * The base URL never ends with a /.
     *
     * This is similar to getBasePath(), except that it also includes the
     * script filename (e.g. index.php) if one exists.
     *
     * @return string The raw URL (i.e. not urldecoded)
     */
    public function getBaseUrl()
    {
        if this->baseUrl === null {
            let this->baseUrl = this->prepareBaseUrl();
        }

        return this->baseUrl;
    }

    /**
     * Prepares the base URL.
     *
     * @return string
     */
    protected function prepareBaseUrl()
    {
        var filename, baseUrl, requestUri, pos;
        let filename = basename(this->server->get("SCRIPT_FILENAME"));

        if (basename(this->server->get("SCRIPT_NAME")) === filename) {
            let baseUrl = this->server->get("SCRIPT_NAME");
        } elseif (basename($this->server->get("PHP_SELF")) === filename) {
            let baseUrl = this->server->get("PHP_SELF");
        } elseif (basename($this->server->get("ORIG_SCRIPT_NAME")) === filename) {
            let baseUrl = this->server->get("ORIG_SCRIPT_NAME"); // 1and1 shared hosting compatibility
        } else {
            // Backtrack up the script_filename to find the portion matching
            // php_self
            var path, file, segs, index, last, seg;
            let path = this->server->get("PHP_SELF", "");
            let file = this->server->get("SCRIPT_FILENAME", "");
            let segs = explode("/", trim(file, "/"));
            let segs = array_reverse(segs);
            let index = 0;
            let last = count(segs);
            let baseUrl = "";

            loop {
                let seg = segs[index];
                let baseUrl = "/" . seg . baseUrl;
                let index++;
                let pos = strpos(path, baseUrl);
                if last > index && pos !== false && pos != 0 {
                    break;
                }
            }
        }

        // Does the baseUrl have anything in common with the request_uri?
        let requestUri = this->getRequestUri();
        if requestUri !== "" {
            let requestUri = "/".ltrim(requestUri, "/");
        }

        var prefix;
        let prefix = this->getUrlencodedPrefix(requestUri, baseUrl);
        if baseUrl && prefix !== false {
            // full $baseUrl matches
            return prefix;
        }

        let prefix = this->getUrlencodedPrefix(requestUri, rtrim(dirname(baseUrl), "/".DIRECTORY_SEPARATOR)."/");
        if baseUrl && prefix !== false {
            // directory portion of $baseUrl matches
            return rtrim(prefix, "/".DIRECTORY_SEPARATOR);
        }

        var truncatedRequestUri;
        let truncatedRequestUri = requestUri;
        let pos = strpos(requestUri, "?");
        if pos !== false {
            let truncatedRequestUri = substr(requestUri, 0, pos);
        }

        var basename;
        let basename = basename(baseUrl);
        if empty(basename) || !strpos(rawurldecode(truncatedRequestUri), basename) {
            // no match whatsoever; set it blank
            return "";
        }

        // If using mod_rewrite or ISAPI_Rewrite strip the script filename
        // out of baseUrl. $pos !== 0 makes sure it is not matching a value
        // from PATH_INFO or QUERY_STRING
        let pos = strpos(requestUri, baseUrl);
        if strlen(requestUri) >= strlen(baseUrl) && pos !== false && pos !== 0 {
            let baseUrl = substr(requestUri, 0, pos + strlen(baseUrl));
        }

        return rtrim(baseUrl, "/".DIRECTORY_SEPARATOR);
    }

    /*
     * Returns the prefix as encoded in the string when the string starts with
     * the given prefix, false otherwise.
     *
     * @return string|false The prefix as it is encoded in $string, or false
     */
    private function getUrlencodedPrefix(string str, string prefix)
    {
        if strpos(rawurldecode(str), prefix) !== 0 {
            return false;
        }

        var len, match;
        let len = strlen(prefix);

        if preg_match(sprintf("#^(%%[[:xdigit:]]{2}|.){%d}#", len), str, match) {
            return match[0];
        }

        return false;
    }
}