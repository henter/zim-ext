/*
 * This file is part of the Symfony package.
 *
 * (c) Fabien Potencier <fabien@symfony.com>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */
namespace Zim\Http;

use Zim\Contract\Arrayble;
use Zim\Contract\Jsonable;

/**
 * Response represents an HTTP response in JSON format.
 *
 * Note that this class does not force the returned JSON content to be an
 * object. It is however recommended that you do return an object as it
 * protects yourself against XSSI and JSON-JavaScript Hijacking.
 *
 * @see https://www.owasp.org/index.php/OWASP_AJAX_Security_Guidelines#Always_return_JSON_with_an_Object_on_the_outside
 *
 * @author Igor Wiedler <igor@wiedler.ch>
 */
class JsonResponse extends Response
{
    protected data;
    protected callback;
    protected encodingOptions = self::DEFAULT_ENCODING_OPTIONS;

    // Encode <, >, ', &, and " characters in the JSON, making it also safe to be embedded into HTML.
    // 15 === JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_AMP | JSON_HEX_QUOT
    const DEFAULT_ENCODING_OPTIONS = 15;

    const JSON_PARTIAL_OUTPUT_ON_ERROR = 512;
    const JSON_ERROR_RECURSION = 6;
    const JSON_ERROR_INF_OR_NAN = 7;
    const JSON_ERROR_UNSUPPORTED_TYPE = 8;

    /**
     * @param mixed $data    The response data
     * @param int   $status  The response status code
     * @param array $headers An array of response headers
     * @param bool  $json    If the data is already a JSON string
     */
    public function __construct(var data = null, int status = 200, array headers = [], bool json = false) -> void
    {
        parent::__construct("", status, headers);
        if data === null {
            let data = new \ArrayObject();
        }
        if json {
            this->setJson(data);
        } else {
            this->setData(data);
        }
    }
    
    /**
     * Factory method for chainability.
     *
     * Example:
     *
     *     return JsonResponse::create($data, 200)
     *         ->setSharedMaxAge(300);
     *
     * @param mixed $data    The json response data
     * @param int   $status  The response status code
     * @param array $headers An array of response headers
     *
     * @return static
     */
    public static function create(var data = null, int status = 200, array headers = [])
    {
        return new static(data, status, headers);
    }
    
    /**
     * Make easier the creation of JsonResponse from raw json.
     */
    public static function fromJsonString(data = null, status = 200, headers = [])
    {
        return new static(data, status, headers, true);
    }
    
    /**
     * Sets the JSONP callback.
     *
     * @param string|null $callback The JSONP callback or null to use none
     *
     * @return $this
     *
     * @throws \InvalidArgumentException When the callback name is not valid
     */
    public function setCallback(callback = null)
    {
        var pattern, reserved, parts, part;
    
        if callback !== null {
            // partially taken from http://www.geekality.net/2011/08/03/valid-javascript-identifier/
            // partially taken from https://github.com/willdurand/JsonpCallbackValidator
            //      JsonpCallbackValidator is released under the MIT License. See https://github.com/willdurand/JsonpCallbackValidator/blob/v1.1.0/LICENSE for details.
            //      (c) William Durand <william.durand1@gmail.com>
            let pattern = "/^[$_\\p{L}][$_\\p{L}\\p{Mn}\\p{Mc}\\p{Nd}\\p{Pc}\\x{200C}\\x{200D}]*(?:\\[(?:\"(?:\\\\.|[^\"\\\\])*\"|'(?:\\\\.|[^'\\\\])*'|\\d+)\\])*?$/u";
            let reserved = ["break", "do", "instanceof", "typeof", "case", "else", "new", "var", "catch", "finally", "return", "void", "continue", "for", "switch", "while", "debugger", "function", "this", "with", "default", "if", "throw", "delete", "in", "try", "class", "enum", "extends", "super", "const", "export", "import", "implements", "let", "private", "public", "yield", "interface", "package", "protected", "static", "null", "true", "false"];
            let parts = explode(".", callback);
            for part in parts {
                if !(preg_match(pattern, part)) || in_array(part, reserved, true) {
                    throw new \InvalidArgumentException("The callback name is not valid.");
                }
            }
        }
        let this->callback = callback;
        return this->update();
    }
    
    /**
     * Sets a raw string containing a JSON document to be sent.
     *
     * @param string $json
     *
     * @return $this
     *
     * @throws \InvalidArgumentException
     */
    public function setJson(string json)
    {
        let this->data = json;
        return this->update();
    }

    /**
     * Get the json_decoded data from the response.
     *
     * @param  bool  $assoc
     * @param  int  $depth
     * @return mixed
     */
    public function getData(bool assoc = true, int depth = 512)
    {
        return json_decode(this->data, assoc, depth);
    }

    /**
     * @param array $data
     * @return self
     */
    public function setData(var data = [])
    {
        let this->original = data;

        if typeof data == "object" {
            if (data instanceof Jsonable) {
                let this->data = data->toJson(this->encodingOptions);
            } elseif (data instanceof \JsonSerializable) {
                let this->data = json_encode(data->jsonSerialize(), this->encodingOptions);
            } elseif (data instanceof Arrayable) {
                let this->data = json_encode(data->toArray(), this->encodingOptions);
            }
        } else {
            let this->data = json_encode(data, this->encodingOptions);
        }

        if !(this->hasValidJson(json_last_error())) {
            throw new \InvalidArgumentException(json_last_error_msg());
        }

        return this->update();
    }

    /**
     * Determine if an error occurred during JSON encoding.
     *
     * @param  int  $jsonError
     * @return bool
     */
    protected function hasValidJson(int jsonError)
    {
        if (jsonError === JSON_ERROR_NONE) {
            return true;
        }

        return this->hasEncodingOption(self::JSON_PARTIAL_OUTPUT_ON_ERROR) &&
            in_array(jsonError, [
                self::JSON_ERROR_RECURSION,
                self::JSON_ERROR_INF_OR_NAN,
                self::JSON_ERROR_UNSUPPORTED_TYPE
            ]);
    }

    /**
     * Determine if a JSON encoding option is set.
     *
     * @param  int  $option
     * @return bool
     */
    public function hasEncodingOption(int option)
    {
        return (bool) (this->encodingOptions & option);
    }

    /**
     * Returns options used while encoding data to JSON.
     *
     * @return int
     */
    public function getEncodingOptions() -> int
    {
        return this->encodingOptions;
    }
    
    /**
     * Sets options used while encoding data to JSON.
     *
     * @param int $encodingOptions
     *
     * @return $this
     */
    public function setEncodingOptions(int encodingOptions)
    {
        let this->encodingOptions = (int) encodingOptions;
        return this->setData(json_decode(this->data));
    }
    
    /**
     * Updates the content and headers according to the JSON data and callback.
     *
     * @return $this
     */
    protected function update()
    {
        if this->callback !== null {
            // Not using application/javascript for compatibility reasons with older browsers.
            this->headers->set("Content-Type", "text/javascript");
            return this->setContent(sprintf("/**/%s(%s);", this->callback, this->data));
        }
        // Only set the header when there is none or when it equals 'text/javascript' (from a previous update with callback)
        // in order to not overwrite a custom definition.
        if !(this->headers->has("Content-Type")) || this->headers->get("Content-Type") === "text/javascript" {
            this->headers->set("Content-Type", "application/json");
        }
        return this->setContent(this->data);
    }

}