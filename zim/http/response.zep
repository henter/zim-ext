/**
 * File Response.php
 * @henter
 * Time: 2018-11-24 19:53
 *
 */
namespace Zim\Http;

/**
 * Response represents an HTTP response.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
class Response implements \Zim\Contract\Response
{
    const HTTP_CONTINUE = 100;
    const HTTP_SWITCHING_PROTOCOLS = 101;
    const HTTP_PROCESSING = 102;
    // RFC2518
    const HTTP_EARLY_HINTS = 103;
    // RFC8297
    const HTTP_OK = 200;
    const HTTP_CREATED = 201;
    const HTTP_ACCEPTED = 202;
    const HTTP_NON_AUTHORITATIVE_INFORMATION = 203;
    const HTTP_NO_CONTENT = 204;
    const HTTP_RESET_CONTENT = 205;
    const HTTP_PARTIAL_CONTENT = 206;
    const HTTP_MULTI_STATUS = 207;
    // RFC4918
    const HTTP_ALREADY_REPORTED = 208;
    // RFC5842
    const HTTP_IM_USED = 226;
    // RFC3229
    const HTTP_MULTIPLE_CHOICES = 300;
    const HTTP_MOVED_PERMANENTLY = 301;
    const HTTP_FOUND = 302;
    const HTTP_SEE_OTHER = 303;
    const HTTP_NOT_MODIFIED = 304;
    const HTTP_USE_PROXY = 305;
    const HTTP_RESERVED = 306;
    const HTTP_TEMPORARY_REDIRECT = 307;
    const HTTP_PERMANENTLY_REDIRECT = 308;
    // RFC7238
    const HTTP_BAD_REQUEST = 400;
    const HTTP_UNAUTHORIZED = 401;
    const HTTP_PAYMENT_REQUIRED = 402;
    const HTTP_FORBIDDEN = 403;
    const HTTP_NOT_FOUND = 404;
    const HTTP_METHOD_NOT_ALLOWED = 405;
    const HTTP_NOT_ACCEPTABLE = 406;
    const HTTP_PROXY_AUTHENTICATION_REQUIRED = 407;
    const HTTP_REQUEST_TIMEOUT = 408;
    const HTTP_CONFLICT = 409;
    const HTTP_GONE = 410;
    const HTTP_LENGTH_REQUIRED = 411;
    const HTTP_PRECONDITION_FAILED = 412;
    const HTTP_REQUEST_ENTITY_TOO_LARGE = 413;
    const HTTP_REQUEST_URI_TOO_LONG = 414;
    const HTTP_UNSUPPORTED_MEDIA_TYPE = 415;
    const HTTP_REQUESTED_RANGE_NOT_SATISFIABLE = 416;
    const HTTP_EXPECTATION_FAILED = 417;
    const HTTP_I_AM_A_TEAPOT = 418;
    // RFC2324
    const HTTP_MISDIRECTED_REQUEST = 421;
    // RFC7540
    const HTTP_UNPROCESSABLE_ENTITY = 422;
    // RFC4918
    const HTTP_LOCKED = 423;
    // RFC4918
    const HTTP_FAILED_DEPENDENCY = 424;
    // RFC4918
    /**
     * @var ResponseHeaderBag
     */
    public headers;
    /**
     * @var string
     */
    protected content;
    /**
     * @var string
     */
    protected version;
    /**
     * @var int
     */
    protected statusCode;
    /**
     * @var string
     */
    protected statusText;
    /**
     * @var string
     */
    protected charset;
    /**
     * Status codes translation table.
     *
     * The list of codes is complete according to the
     * {@link http://www.iana.org/assignments/http-status-codes/ Hypertext Transfer Protocol (HTTP) Status Code Registry}
     * (last updated 2016-03-01).
     *
     * Unless otherwise noted, the status code is defined in RFC2616.
     *
     * @var array
     */
    public static statusTexts = [100 : "Continue", 101 : "Switching Protocols", 102 : "Processing", 103 : "Early Hints", 200 : "OK", 201 : "Created", 202 : "Accepted", 203 : "Non-Authoritative Information", 204 : "No Content", 205 : "Reset Content", 206 : "Partial Content", 207 : "Multi-Status", 208 : "Already Reported", 226 : "IM Used", 300 : "Multiple Choices", 301 : "Moved Permanently", 302 : "Found", 303 : "See Other", 304 : "Not Modified", 305 : "Use Proxy", 307 : "Temporary Redirect", 308 : "Permanent Redirect", 400 : "Bad Request", 401 : "Unauthorized", 402 : "Payment Required", 403 : "Forbidden", 404 : "Not Found", 405 : "Method Not Allowed", 406 : "Not Acceptable", 407 : "Proxy Authentication Required", 408 : "Request Timeout", 409 : "Conflict", 410 : "Gone", 411 : "Length Required", 412 : "Precondition Failed", 413 : "Payload Too Large", 414 : "URI Too Long", 415 : "Unsupported Media Type", 416 : "Range Not Satisfiable", 417 : "Expectation Failed", 418 : "I'm a teapot", 421 : "Misdirected Request", 422 : "Unprocessable Entity", 423 : "Locked", 424 : "Failed Dependency", 425 : "Too Early", 426 : "Upgrade Required", 428 : "Precondition Required", 429 : "Too Many Requests", 431 : "Request Header Fields Too Large", 451 : "Unavailable For Legal Reasons", 500 : "Internal Server Error", 501 : "Not Implemented", 502 : "Bad Gateway", 503 : "Service Unavailable", 504 : "Gateway Timeout", 505 : "HTTP Version Not Supported", 506 : "Variant Also Negotiates", 507 : "Insufficient Storage", 508 : "Loop Detected", 510 : "Not Extended", 511 : "Network Authentication Required"];
    /**
     * Response constructor.
     * @param string $content
     * @param int $status
     * @param array $headers
     */
    public function __construct(string content = "", int status = 200, array headers = []) -> void
    {
        let this->headers =  new ResponseHeaderBag(headers);
        this->setContent(content);
        this->setStatusCode(status);
        this->setProtocolVersion("1.0");
    }
    
    /**
     * Factory method for chainability.
     *
     * Example:
     *
     *     return Response::create($body, 200)
     *         ->setSharedMaxAge(300);
     *
     * @param mixed $content The response content, see setContent()
     * @param int   $status  The response status code
     * @param array $headers An array of response headers
     *
     * @return static
     */
    public static function create(content = "", int status = 200, array headers = []) -> <Response>
    {
        return new static(content, status, headers);
    }
    
    /**
     * Returns the Response as an HTTP string.
     *
     * The string representation of the Response is the same as the
     * one that will be sent to the client only if the prepare() method
     * has been called before.
     *
     * @return string The Response as an HTTP string
     *
     * @see prepare()
     */
    public function __toString() -> string
    {
        return sprintf("HTTP/%s %s %s", this->version, this->statusCode, this->statusText) . "
" . this->headers . "
" . this->getContent();
    }
    
    /**
     * Clones the current Response instance.
     */
    public function __clone() -> void
    {
        let this->headers =  clone this->headers;
    }
    
    /**
     * Prepares the Response before it is sent to the client.
     *
     * This method tweaks the Response to ensure that it is
     * compliant with RFC 2616. Most of the changes are based on
     * the Request that is "associated" with this Response.
     *
     * @return $this
     */
    public function prepare(<Zim\Contract\Request> request)
    {
        var headers, format, mimeType, charset, length;
    
        let headers =  this->headers;
        if this->isInformational() || this->isEmpty() {
            this->setContent(null);
            headers->remove("Content-Type");
            headers->remove("Content-Length");
        } else {
            // Content-type based on the Request
            if !(headers->has("Content-Type")) {
                let format =  request->getRequestFormat();
                let mimeType =  request->getMimeType(format);
                if format !== null && mimeType {
                    headers->set("Content-Type", mimeType);
                }
            }
            // Fix Content-Type
            let charset =  this->charset ? this->charset : "UTF-8";
            if !(headers->has("Content-Type")) {
                headers->set("Content-Type", "text/html; charset=" . charset);
            } elseif 0 === stripos(headers->get("Content-Type"), "text/") && false === stripos(headers->get("Content-Type"), "charset") {
                // add the charset
                headers->set("Content-Type", headers->get("Content-Type") . "; charset=" . charset);
            }
            // Fix Content-Length
            if headers->has("Transfer-Encoding") {
                headers->remove("Content-Length");
            }
            if request->isMethod("HEAD") {
                // cf. RFC2616 14.13
                let length =  headers->get("Content-Length");
                this->setContent(null);
                if length {
                    headers->set("Content-Length", length);
                }
            }
        }
        // Fix protocol
        if request->server->get("SERVER_PROTOCOL") != "HTTP/1.0" {
            this->setProtocolVersion("1.1");
        }
        // Check if we need to send extra expire info headers
        if this->getProtocolVersion() == "1.0" && strpos(this->headers->get("Cache-Control"), "no-cache") !== false {
            this->headers->set("pragma", "no-cache");
            this->headers->set("expires", -1);
        }
        return this;
    }
    
    /**
     * Sends HTTP headers.
     *
     * @return $this
     */
    public function sendHeaders()
    {
        var name, values, value;
    
        // headers have already been sent by the developer
        if headers_sent() {
            return this;
        }
        // headers
        for name, values in this->headers->allPreserveCase() {
            for value in values {
                header(name . ": " . value, false, this->statusCode);
            }
        }
        // status
        header(sprintf("HTTP/%s %s %s", this->version, this->statusCode, this->statusText), true, this->statusCode);
        return this;
    }
    
    /**
     * Sends content for the current web response.
     *
     * @return $this
     */
    public function sendContent()
    {
        echo this->content;
        return this;
    }
    
    /**
     * Sends HTTP headers and content.
     *
     * @return $this
     */
    public function send()
    {
        this->sendHeaders();
        this->sendContent();
        if function_exists("fastcgi_finish_request") {
            fastcgi_finish_request();
        }
        return this;
    }
    
    /**
     * Sets the response content.
     *
     * Valid types are strings, numbers, null, and objects that implement a __toString() method.
     *
     * @param mixed $content Content that can be cast to string
     *
     * @return $this
     *
     * @throws \UnexpectedValueException
     */
    public function setContent(content)
    {
        var tmpArray0f67bfd40374ca906cbbc56c42cdae7c;
    
        let tmpArray0f67bfd40374ca906cbbc56c42cdae7c = [content, "__toString"];
        if content !== null && !(is_string(content)) && !(is_numeric(content)) && !(is_callable(tmpArray0f67bfd40374ca906cbbc56c42cdae7c)) {
            throw new \UnexpectedValueException(sprintf("The Response content must be a string or object implementing __toString(), \"%s\" given.", gettype(content)));
        }
        let this->content =  (string) content;
        return this;
    }
    
    /**
     * Gets the current response content.
     *
     * @return string Content
     */
    public function getContent() -> string
    {
        return this->content;
    }
    
    /**
     * Sets the HTTP protocol version (1.0 or 1.1).
     *
     * @return $this
     *
     * @final
     */
    public function setProtocolVersion(string version)
    {
        let this->version = version;
        return this;
    }
    
    /**
     * Gets the HTTP protocol version.
     *
     * @final
     */
    public function getProtocolVersion()
    {
        return this->version;
    }
    
    /**
     * Sets the response status code.
     *
     * If the status text is null it will be automatically populated for the known
     * status codes and left empty otherwise.
     *
     * @return $this
     *
     * @throws \InvalidArgumentException When the HTTP status code is not valid
     *
     * @final
     */
    public function setStatusCode(int code, text = null)
    {
        let this->statusCode = code;
        if this->isInvalid() {
            throw new \InvalidArgumentException(sprintf("The HTTP status code \"%s\" is not valid.", code));
        }
        if text === null {
            let this->statusText =  isset self::statusTexts[code] ? self::statusTexts[code]  : "unknown status";
            return this;
        }
        if text === false {
            let this->statusText = "";
            return this;
        }
        let this->statusText = text;
        return this;
    }
    
    /**
     * Retrieves the status code for the current web response.
     *
     * @final
     */
    public function getStatusCode()
    {
        return this->statusCode;
    }
    
    /**
     * Sets the response charset.
     *
     * @return $this
     *
     * @final
     */
    public function setCharset(string charset)
    {
        let this->charset = charset;
        return this;
    }
    
    /**
     * Retrieves the response charset.
     *
     * @final
     */
    public function getCharset()
    {
        return this->charset;
    }
    
    /**
     * Is response invalid?
     *
     * @see http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
     *
     * @final
     */
    public function isInvalid()
    {
        return this->statusCode < 100 || this->statusCode >= 600;
    }
    
    /**
     * Is response informative?
     *
     * @final
     */
    public function isInformational()
    {
        return this->statusCode >= 100 && this->statusCode < 200;
    }
    
    /**
     * Is response successful?
     *
     * @final
     */
    public function isSuccessful()
    {
        return this->statusCode >= 200 && this->statusCode < 300;
    }
    
    /**
     * Is the response a redirect?
     *
     * @final
     */
    public function isRedirection()
    {
        return this->statusCode >= 300 && this->statusCode < 400;
    }
    
    /**
     * Is there a client error?
     *
     * @final
     */
    public function isClientError()
    {
        return this->statusCode >= 400 && this->statusCode < 500;
    }
    
    /**
     * Was there a server side error?
     *
     * @final
     */
    public function isServerError()
    {
        return this->statusCode >= 500 && this->statusCode < 600;
    }
    
    /**
     * Is the response OK?
     *
     * @final
     */
    public function isOk()
    {
        return 200 === this->statusCode;
    }
    
    /**
     * Is the response forbidden?
     *
     * @final
     */
    public function isForbidden()
    {
        return 403 === this->statusCode;
    }
    
    /**
     * Is the response a not found error?
     *
     * @final
     */
    public function isNotFound()
    {
        return 404 === this->statusCode;
    }
    
    /**
     * Is the response a redirect of some form?
     *
     * @final
     */
    public function isRedirect(string location = null)
    {
        return in_array(this->statusCode, [201, 301, 302, 303, 307, 308]) && ( location === null ? location === null : location == this->headers->get("Location"));
    }
    
    /**
     * Is the response empty?
     *
     * @final
     */
    public function isEmpty()
    {
        return in_array(this->statusCode, [204, 304]);
    }
}