
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * File RequestInterface.php
 * @henter
 * Time: 2018-11-24 19:52
 *
 */
ZEPHIR_INIT_CLASS(Zim_Contract_Request) {

	ZEPHIR_REGISTER_INTERFACE(Zim\\Contract, Request, zim, contract_request, zim_contract_request_method_entry);

	return SUCCESS;

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
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getRequestFormat);

/**
 * Gets the mime type associated with the format.
 *
 * @param string $format The format
 *
 * @return string|null The associated mime type (null if not found)
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getMimeType);

/**
 * Gets the mime types associated with the format.
 *
 * @param string $format The format
 *
 * @return array The associated mime types
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getMimeTypes);

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
ZEPHIR_DOC_METHOD(Zim_Contract_Request, get);

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
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getPathInfo);

/**
 * Gets the request's scheme.
 *
 * @return string
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getScheme);

ZEPHIR_DOC_METHOD(Zim_Contract_Request, isSecure);

/**
 * Returns the requested URI (path and query string).
 *
 * @return string The raw URI (i.e. not URI decoded)
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getRequestUri);

/**
 * Generates a normalized URI (URL) for the Request.
 *
 * @return string A normalized URI (URL) for the Request
 *
 * @see getQueryString()
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getUri);

/**
 * Generates the normalized query string for the Request.
 *
 * It builds a normalized query string, where keys/value pairs are alphabetized
 * and have consistent escaping.
 *
 * @return string|null A normalized query string for the Request
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getQueryString);

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
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getHost);

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
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getMethod);

/**
 * Checks if the request method is of specified type.
 *
 * @param string $method Uppercase request method (GET, POST etc)
 *
 * @return bool
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Request, isMethod);

/**
 * Returns the request body content.
 *
 * @param bool $asResource If true, a resource will be returned
 *
 * @return string|resource The request body content or a resource to read the body stream
 *
 * @throws \LogicException
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Request, getContent);

