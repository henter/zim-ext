
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"
#include "kernel/file.h"


/**
 * File Request.php
 * @henter
 * Time: 2018-11-24 19:53
 *
 */
/**
 * Request represents an HTTP request.
 * @author Fabien Potencier <fabien@symfony.com>
 */
ZEPHIR_INIT_CLASS(Zim_Http_Request) {

	ZEPHIR_REGISTER_CLASS(Zim\\Http, Request, zim, http_request, zim_http_request_method_entry, 0);

	/**
	 * Custom parameters.
	 *
	 * @var ParameterBag
	 */
	zend_declare_property_null(zim_http_request_ce, SL("attributes"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * Request body parameters ($_POST).
	 *
	 * @var ParameterBag
	 */
	zend_declare_property_null(zim_http_request_ce, SL("request"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * Query string parameters ($_GET).
	 *
	 * @var ParameterBag
	 */
	zend_declare_property_null(zim_http_request_ce, SL("query"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * Server and execution environment parameters ($_SERVER).
	 *
	 * @var ServerBag
	 */
	zend_declare_property_null(zim_http_request_ce, SL("server"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * Headers (taken from the $_SERVER).
	 *
	 * @var HeaderBag
	 */
	zend_declare_property_null(zim_http_request_ce, SL("headers"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var string|resource|false|null
	 */
	zend_declare_property_null(zim_http_request_ce, SL("content"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(zim_http_request_ce, SL("pathInfo"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(zim_http_request_ce, SL("requestUri"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(zim_http_request_ce, SL("method"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var array
	 */
	zend_declare_property_null(zim_http_request_ce, SL("formats"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(zim_http_request_ce, SL("forwardedHeaders"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zephir_declare_class_constant_string(zim_http_request_ce, SL("METHOD_HEAD"), "HEAD");

	zephir_declare_class_constant_string(zim_http_request_ce, SL("METHOD_GET"), "GET");

	zephir_declare_class_constant_string(zim_http_request_ce, SL("METHOD_POST"), "POST");

	zephir_declare_class_constant_string(zim_http_request_ce, SL("METHOD_PUT"), "PUT");

	zephir_declare_class_constant_string(zim_http_request_ce, SL("METHOD_PATCH"), "PATCH");

	zephir_declare_class_constant_string(zim_http_request_ce, SL("METHOD_DELETE"), "DELETE");

	zephir_declare_class_constant_string(zim_http_request_ce, SL("METHOD_PURGE"), "PURGE");

	zephir_declare_class_constant_string(zim_http_request_ce, SL("METHOD_OPTIONS"), "OPTIONS");

	zephir_declare_class_constant_string(zim_http_request_ce, SL("METHOD_TRACE"), "TRACE");

	zephir_declare_class_constant_string(zim_http_request_ce, SL("METHOD_CONNECT"), "CONNECT");

	zend_class_implements(zim_http_request_ce TSRMLS_CC, 1, zim_contract_request_ce);
	return SUCCESS;

}

/**
 * @param array                $query      The GET parameters
 * @param array                $request    The POST parameters
 * @param array                $attributes The request attributes (parameters parsed from the PATH_INFO, ...)
 * @param array                $server     The SERVER parameters
 * @param string|resource|null $content    The raw body data
 */
PHP_METHOD(Zim_Http_Request, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *query_param = NULL, *request_param = NULL, *attributes_param = NULL, *server_param = NULL, *content = NULL, content_sub, __$null;
	zval query, request, attributes, server;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&request);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&server);
	ZVAL_UNDEF(&content_sub);
	ZVAL_NULL(&__$null);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 5, &query_param, &request_param, &attributes_param, &server_param, &content);

	if (!query_param) {
		ZEPHIR_INIT_VAR(&query);
		array_init(&query);
	} else {
		zephir_get_arrval(&query, query_param);
	}
	if (!request_param) {
		ZEPHIR_INIT_VAR(&request);
		array_init(&request);
	} else {
		zephir_get_arrval(&request, request_param);
	}
	if (!attributes_param) {
		ZEPHIR_INIT_VAR(&attributes);
		array_init(&attributes);
	} else {
		zephir_get_arrval(&attributes, attributes_param);
	}
	if (!server_param) {
		ZEPHIR_INIT_VAR(&server);
		array_init(&server);
	} else {
		zephir_get_arrval(&server, server_param);
	}
	if (!content) {
		content = &content_sub;
		content = &__$null;
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "initialize", NULL, 0, &query, &request, &attributes, &server, content);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * @return string
 */
PHP_METHOD(Zim_Http_Request, getForwardedFor) {

	zval key, host, _0, *_1, _2$$3;
	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&host);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();

	zephir_read_static_property_ce(&_0, zim_http_request_ce, SL("forwardedHeaders"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "zim/http/request.zep", 103);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
	{
		ZEPHIR_INIT_NVAR(&key);
		ZVAL_COPY(&key, _1);
		zephir_read_property(&_2$$3, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&host, &_2$$3, "get", NULL, 0, &key);
		zephir_check_call_status();
		if (zephir_is_true(&host)) {
			ZEPHIR_RETURN_CALL_FUNCTION("current", &_3, 72, &host);
			zephir_check_call_status();
			RETURN_MM();
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&key);
	RETURN_MM_STRING("");

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
PHP_METHOD(Zim_Http_Request, initialize) {

	zephir_fcall_cache_entry *_1 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *query_param = NULL, *request_param = NULL, *attributes_param = NULL, *server_param = NULL, *content = NULL, content_sub, __$null, _0, _2, _3, _4, _5, _6, _7;
	zval query, request, attributes, server;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&request);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&server);
	ZVAL_UNDEF(&content_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 5, &query_param, &request_param, &attributes_param, &server_param, &content);

	if (!query_param) {
		ZEPHIR_INIT_VAR(&query);
		array_init(&query);
	} else {
		zephir_get_arrval(&query, query_param);
	}
	if (!request_param) {
		ZEPHIR_INIT_VAR(&request);
		array_init(&request);
	} else {
		zephir_get_arrval(&request, request_param);
	}
	if (!attributes_param) {
		ZEPHIR_INIT_VAR(&attributes);
		array_init(&attributes);
	} else {
		zephir_get_arrval(&attributes, attributes_param);
	}
	if (!server_param) {
		ZEPHIR_INIT_VAR(&server);
		array_init(&server);
	} else {
		zephir_get_arrval(&server, server_param);
	}
	if (!content) {
		content = &content_sub;
		content = &__$null;
	}


	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, zim_http_parameterbag_ce);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", &_1, 88, &request);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("request"), &_0);
	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, zim_http_parameterbag_ce);
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", &_1, 88, &query);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("query"), &_2);
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, zim_http_parameterbag_ce);
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", &_1, 88, &attributes);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("attributes"), &_3);
	ZEPHIR_INIT_VAR(&_4);
	object_init_ex(&_4, zim_http_serverbag_ce);
	ZEPHIR_CALL_METHOD(NULL, &_4, "__construct", &_1, 88, &server);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("server"), &_4);
	ZEPHIR_INIT_VAR(&_5);
	object_init_ex(&_5, zim_http_headerbag_ce);
	zephir_read_property(&_6, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_7, &_6, "getheaders", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_5, "__construct", NULL, 89, &_7);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("headers"), &_5);
	zephir_update_property_zval(this_ptr, SL("content"), content);
	zephir_update_property_zval(this_ptr, SL("pathInfo"), &__$null);
	zephir_update_property_zval(this_ptr, SL("requestUri"), &__$null);
	zephir_update_property_zval(this_ptr, SL("method"), &__$null);
	ZEPHIR_MM_RESTORE();

}

/**
 * Creates a new request with values from PHP's super globals.
 *
 * @return static
 */
PHP_METHOD(Zim_Http_Request, createFromGlobals) {

	zend_bool _5;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *_GET, *_POST, *_SERVER, request, methods, data, _0, _1, _2, _3, _4, _6, _7, _8, _9, _10, _11$$3, _12$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&request);
	ZVAL_UNDEF(&methods);
	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$3);

	ZEPHIR_MM_GROW();
	zephir_get_global(&_SERVER, SL("_SERVER"));
	zephir_get_global(&_POST, SL("_POST"));
	zephir_get_global(&_GET, SL("_GET"));

	ZEPHIR_INIT_VAR(&request);
	object_init_ex(&request, zim_http_request_ce);
	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	ZEPHIR_CALL_METHOD(NULL, &request, "__construct", NULL, 90, _GET, _POST, &_0, _SERVER);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&methods);
	zephir_create_array(&methods, 3, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "PUT");
	zephir_array_fast_append(&methods, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "DELETE");
	zephir_array_fast_append(&methods, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "PATCH");
	zephir_array_fast_append(&methods, &_1);
	zephir_read_property(&_2, &request, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "CONTENT_TYPE");
	ZEPHIR_CALL_METHOD(&_3, &_2, "get", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "application/x-www-form-urlencoded");
	ZEPHIR_INIT_VAR(&_4);
	zephir_fast_strpos(&_4, &_3, &_1, 0 );
	_5 = ZEPHIR_IS_LONG_IDENTICAL(&_4, 0);
	if (_5) {
		ZEPHIR_INIT_VAR(&_6);
		zephir_read_property(&_7, &request, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_9);
		ZVAL_STRING(&_9, "REQUEST_METHOD");
		ZEPHIR_INIT_VAR(&_10);
		ZVAL_STRING(&_10, "GET");
		ZEPHIR_CALL_METHOD(&_8, &_7, "get", NULL, 0, &_9, &_10);
		zephir_check_call_status();
		zephir_fast_strtoupper(&_6, &_8);
		_5 = zephir_fast_in_array(&_6, &methods TSRMLS_CC);
	}
	if (_5) {
		ZEPHIR_CALL_METHOD(&_11$$3, &request, "getcontent", NULL, 91);
		zephir_check_call_status();
		ZEPHIR_MAKE_REF(&data);
		ZEPHIR_CALL_FUNCTION(NULL, "parse_str", NULL, 92, &_11$$3, &data);
		ZEPHIR_UNREF(&data);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_12$$3);
		object_init_ex(&_12$$3, zim_http_parameterbag_ce);
		ZEPHIR_CALL_METHOD(NULL, &_12$$3, "__construct", NULL, 88, &data);
		zephir_check_call_status();
		zephir_update_property_zval(&request, SL("request"), &_12$$3);
	}
	RETURN_CCTOR(&request);

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
PHP_METHOD(Zim_Http_Request, getRequestFormat) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *deft = NULL, deft_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&deft_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &deft);

	if (!deft) {
		deft = &deft_sub;
		ZEPHIR_INIT_VAR(deft);
		ZVAL_STRING(deft, "html");
	}


	zephir_read_property(&_0, this_ptr, SL("attributes"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "_format");
	ZEPHIR_RETURN_CALL_METHOD(&_0, "get", NULL, 0, &_1, deft);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Gets the mime type associated with the format.
 *
 * @param string $format The format
 *
 * @return string|null The associated mime type (null if not found)
 */
PHP_METHOD(Zim_Http_Request, getMimeType) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *format_param = NULL, _0, _1, _2, _3, _4;
	zval format;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&format);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &format_param);

	zephir_get_strval(&format, format_param);


	zephir_read_static_property_ce(&_0, zim_http_request_ce, SL("formats"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_CALL_STATIC(NULL, "initializeformats", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_1);
	zephir_read_static_property_ce(&_2, zim_http_request_ce, SL("formats"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_2, &format)) {
		zephir_read_static_property_ce(&_3, zim_http_request_ce, SL("formats"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_4, &_3, &format, PH_NOISY | PH_READONLY, "zim/http/request.zep", 179 TSRMLS_CC);
		zephir_array_fetch_long(&_1, &_4, 0, PH_NOISY, "zim/http/request.zep", 179 TSRMLS_CC);
	} else {
		ZVAL_NULL(&_1);
	}
	RETURN_CCTOR(&_1);

}

/**
 * Gets the mime types associated with the format.
 *
 * @param string $format The format
 *
 * @return array The associated mime types
 */
PHP_METHOD(Zim_Http_Request, getMimeTypes) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *format_param = NULL, _0, _1, _2, _3;
	zval format;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&format);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &format_param);

	zephir_get_strval(&format, format_param);


	zephir_read_static_property_ce(&_0, zim_http_request_ce, SL("formats"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_CALL_STATIC(NULL, "initializeformats", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_1);
	zephir_read_static_property_ce(&_2, zim_http_request_ce, SL("formats"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_2, &format)) {
		zephir_read_static_property_ce(&_3, zim_http_request_ce, SL("formats"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_1, &_3, &format, PH_NOISY, "zim/http/request.zep", 194 TSRMLS_CC);
	} else {
		array_init(&_1);
	}
	RETURN_CCTOR(&_1);

}

/**
 * Initializes HTTP request formats.
 */
PHP_METHOD(Zim_Http_Request, initializeFormats) {

	zval _2;
	zval _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 11, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 2, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "text/html");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/xhtml+xml");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("html"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_create_array(&_1, 1, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "text/plain");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("txt"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_create_array(&_1, 3, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/javascript");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/x-javascript");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "text/javascript");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("js"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_create_array(&_1, 1, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "text/css");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("css"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_create_array(&_1, 2, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/json");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/x-json");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("json"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_create_array(&_1, 1, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/ld+json");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("jsonld"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_create_array(&_1, 3, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "text/xml");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/xml");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/x-xml");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("xml"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_create_array(&_1, 1, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/rdf+xml");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("rdf"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_create_array(&_1, 1, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/atom+xml");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("atom"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_create_array(&_1, 1, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/rss+xml");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("rss"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_1);
	zephir_create_array(&_1, 1, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "application/x-www-form-urlencoded");
	zephir_array_fast_append(&_1, &_2);
	zephir_array_update_string(&_0, SL("form"), &_1, PH_COPY | PH_SEPARATE);
	zend_update_static_property(zim_http_request_ce, ZEND_STRL("formats"), &_0);
	ZEPHIR_MM_RESTORE();

}

/**
 * Clones the current request.
 *
 * Note that the session is not cloned as duplicated requests
 * are most of the time sub-requests of the main one.
 */
PHP_METHOD(Zim_Http_Request, __clone) {

	zval _0, _1, _2, _3, _4, _5, _6, _7, _8, _9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("query"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	if (zephir_clone(&_1, &_0 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	zephir_update_property_zval(this_ptr, SL("query"), &_1);
	zephir_read_property(&_2, this_ptr, SL("request"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_3);
	if (zephir_clone(&_3, &_2 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	zephir_update_property_zval(this_ptr, SL("request"), &_3);
	zephir_read_property(&_4, this_ptr, SL("attributes"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_5);
	if (zephir_clone(&_5, &_4 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	zephir_update_property_zval(this_ptr, SL("attributes"), &_5);
	zephir_read_property(&_6, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_7);
	if (zephir_clone(&_7, &_6 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	zephir_update_property_zval(this_ptr, SL("server"), &_7);
	zephir_read_property(&_8, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_9);
	if (zephir_clone(&_9, &_8 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	zephir_update_property_zval(this_ptr, SL("headers"), &_9);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the request as a string.
 *
 * @return string The request
 */
PHP_METHOD(Zim_Http_Request, __toString) {

	zval content, e, _0, _2, _3, _4, _5, _6, _7, _8, _1$$4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$4);

	ZEPHIR_MM_GROW();


	/* try_start_1: */

		ZEPHIR_CALL_METHOD(&content, this_ptr, "getcontent", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_VAR(&_0);
		ZVAL_OBJ(&_0, EG(exception));
		Z_ADDREF_P(&_0);
		if (zephir_instance_of_ev(&_0, spl_ce_LogicException TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CPY_WRT(&e, &_0);
			ZVAL_LONG(&_1$$4, 256);
			ZEPHIR_RETURN_CALL_FUNCTION("trigger_error", NULL, 93, &e, &_1$$4);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getmethod", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getrequesturi", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_STRING(&_6, "SERVER_PROTOCOL");
	ZEPHIR_CALL_METHOD(&_5, &_4, "get", NULL, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_6);
	ZVAL_STRING(&_6, "%s %s %s");
	ZEPHIR_CALL_FUNCTION(&_7, "sprintf", NULL, 22, &_6, &_2, &_3, &_5);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CONCAT_VSVV(return_value, &_7, "\n", &_8, &content);
	RETURN_MM();

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
PHP_METHOD(Zim_Http_Request, normalizeQueryString) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *qs_param = NULL, _0, _1, _2;
	zval qs;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&qs);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &qs_param);

	zephir_get_strval(&qs, qs_param);


	if (ZEPHIR_IS_STRING(&qs, "")) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_MAKE_REF(&qs);
	ZEPHIR_CALL_FUNCTION(NULL, "parse_str", NULL, 92, &qs, &qs);
	ZEPHIR_UNREF(&qs);
	zephir_check_call_status();
	ZEPHIR_MAKE_REF(&qs);
	ZEPHIR_CALL_FUNCTION(NULL, "ksort", NULL, 15, &qs);
	ZEPHIR_UNREF(&qs);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "&");
	ZVAL_LONG(&_2, 2);
	ZEPHIR_RETURN_CALL_FUNCTION("http_build_query", NULL, 94, &qs, &_0, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM();

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
PHP_METHOD(Zim_Http_Request, get) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *deft = NULL, deft_sub, __$null, result, _0, _1, _2;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &key_param, &deft);

	zephir_get_strval(&key, key_param);
	if (!deft) {
		deft = &deft_sub;
		deft = &__$null;
	}


	zephir_read_property(&_0, this_ptr, SL("attributes"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&result, &_0, "get", NULL, 0, &key, this_ptr);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(this_ptr, &result)) {
		RETURN_CCTOR(&result);
	}
	zephir_read_property(&_1, this_ptr, SL("query"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&result, &_1, "get", NULL, 0, &key, this_ptr);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(this_ptr, &result)) {
		RETURN_CCTOR(&result);
	}
	zephir_read_property(&_2, this_ptr, SL("request"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&result, &_2, "get", NULL, 0, &key, this_ptr);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(this_ptr, &result)) {
		RETURN_CCTOR(&result);
	}
	RETVAL_ZVAL(deft, 1, 0);
	RETURN_MM();

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
PHP_METHOD(Zim_Http_Request, getPathInfo) {

	zval _0, _1$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("pathInfo"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "preparepathinfo", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("pathInfo"), &_1$$3);
	}
	RETURN_MM_MEMBER(getThis(), "pathInfo");

}

/**
 * Gets the request's scheme.
 *
 * @return string
 */
PHP_METHOD(Zim_Http_Request, getScheme) {

	zval _0, _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "issecure", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_1)) {
		ZVAL_STRING(&_0, "https");
	} else {
		ZVAL_STRING(&_0, "http");
	}
	RETURN_CCTOR(&_0);

}

PHP_METHOD(Zim_Http_Request, isSecure) {

	zend_bool _2;
	zval https, _0, _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&https);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "HTTPS");
	ZEPHIR_CALL_METHOD(&https, &_0, "get", NULL, 0, &_1);
	zephir_check_call_status();
	_2 = !(ZEPHIR_IS_EMPTY(&https));
	if (_2) {
		ZEPHIR_INIT_NVAR(&_1);
		zephir_fast_strtolower(&_1, &https);
		_2 = !ZEPHIR_IS_STRING_IDENTICAL(&_1, "off");
	}
	RETURN_MM_BOOL(_2);

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
PHP_METHOD(Zim_Http_Request, getPort) {

	zval host, pos, _4, _11, _12, _0$$4, _1$$4, _2$$5, _3$$5, _5$$6, _6$$6, _8$$7, _9$$8, _10$$8;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&host);
	ZVAL_UNDEF(&pos);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_10$$8);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&host, this_ptr, "getforwardedfor", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&host)) {
	} else {
		zephir_read_property(&_0$$4, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_1$$4);
		ZVAL_STRING(&_1$$4, "HOST");
		ZEPHIR_CALL_METHOD(&host, &_0$$4, "get", NULL, 0, &_1$$4);
		zephir_check_call_status();
		if (!(zephir_is_true(&host))) {
			zephir_read_property(&_2$$5, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_3$$5);
			ZVAL_STRING(&_3$$5, "SERVER_PORT");
			ZEPHIR_RETURN_CALL_METHOD(&_2$$5, "get", NULL, 0, &_3$$5);
			zephir_check_call_status();
			RETURN_MM();
		}
	}
	zephir_array_fetch_long(&_4, &host, 0, PH_NOISY | PH_READONLY, "zim/http/request.zep", 354 TSRMLS_CC);
	if (ZEPHIR_IS_STRING_IDENTICAL(&_4, "[")) {
		ZEPHIR_INIT_VAR(&_5$$6);
		ZVAL_STRING(&_5$$6, "]");
		ZEPHIR_CALL_FUNCTION(&_6$$6, "strrpos", &_7, 47, &host, &_5$$6);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_5$$6);
		ZVAL_STRING(&_5$$6, ":");
		ZEPHIR_INIT_VAR(&pos);
		zephir_fast_strpos(&pos, &host, &_5$$6, zephir_get_intval(&_6$$6) );
	} else {
		ZEPHIR_INIT_VAR(&_8$$7);
		ZVAL_STRING(&_8$$7, ":");
		ZEPHIR_CALL_FUNCTION(&pos, "strrpos", &_7, 47, &host, &_8$$7);
		zephir_check_call_status();
	}
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&pos)) {
		ZVAL_LONG(&_9$$8, (zephir_get_numberval(&pos) + 1));
		ZEPHIR_INIT_VAR(&_10$$8);
		zephir_substr(&_10$$8, &host, zephir_get_intval(&_9$$8), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		RETURN_MM_LONG(zephir_get_intval(&_10$$8));
	}
	ZEPHIR_INIT_VAR(&_11);
	ZEPHIR_CALL_METHOD(&_12, this_ptr, "getscheme", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING_IDENTICAL(&_12, "https")) {
		ZVAL_LONG(&_11, 443);
	} else {
		ZVAL_LONG(&_11, 80);
	}
	RETURN_CCTOR(&_11);

}

/**
 * Returns the HTTP host being requested.
 *
 * The port name will be appended to the host if it's non-standard.
 *
 * @return string
 */
PHP_METHOD(Zim_Http_Request, getHttpHost) {

	zend_bool _0, _1, _2;
	zval scheme, port, _4;
	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scheme);
	ZVAL_UNDEF(&port);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&scheme, this_ptr, "getscheme", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&port, this_ptr, "getport", NULL, 0);
	zephir_check_call_status();
	_0 = ZEPHIR_IS_STRING(&scheme, "http");
	if (_0) {
		_0 = ZEPHIR_IS_LONG(&port, 80);
	}
	_1 = _0;
	if (!(_1)) {
		_2 = ZEPHIR_IS_STRING(&scheme, "https");
		if (_2) {
			_2 = ZEPHIR_IS_LONG(&port, 443);
		}
		_1 = _2;
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "gethost", &_3, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "gethost", &_3, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VSV(return_value, &_4, ":", &port);
	RETURN_MM();

}

/**
 * Returns the requested URI (path and query string).
 *
 * @return string The raw URI (i.e. not URI decoded)
 */
PHP_METHOD(Zim_Http_Request, getRequestUri) {

	zval _0, _1$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("requestUri"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "preparerequesturi", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("requestUri"), &_1$$3);
	}
	RETURN_MM_MEMBER(getThis(), "requestUri");

}

/**
 * Gets the scheme and HTTP host.
 *
 * If the URL was called with basic authentication, the user
 * and the password are not added to the generated string.
 *
 * @return string The scheme and HTTP host
 */
PHP_METHOD(Zim_Http_Request, getSchemeAndHttpHost) {

	zval _0, _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getscheme", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "gethttphost", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VSV(return_value, &_0, "://", &_1);
	RETURN_MM();

}

/**
 * Generates a normalized URI (URL) for the Request.
 *
 * @return string A normalized URI (URL) for the Request
 *
 * @see getQueryString()
 */
PHP_METHOD(Zim_Http_Request, getUri) {

	zval qs, _1, _2, _0$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&qs);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&qs, this_ptr, "getquerystring", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&qs) != IS_NULL) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_CONCAT_SV(&_0$$3, "?", &qs);
		ZEPHIR_CPY_WRT(&qs, &_0$$3);
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getschemeandhttphost", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getpathinfo", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VVV(return_value, &_1, &_2, &qs);
	RETURN_MM();

}

/**
 * Generates the normalized query string for the Request.
 *
 * It builds a normalized query string, where keys/value pairs are alphabetized
 * and have consistent escaping.
 *
 * @return string|null A normalized query string for the Request
 */
PHP_METHOD(Zim_Http_Request, getQueryString) {

	zval qs, _0, _1, _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&qs);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "QUERY_STRING");
	ZEPHIR_CALL_METHOD(&_1, &_0, "get", NULL, 0, &_2);
	zephir_check_call_status();
	ZEPHIR_CALL_STATIC(&qs, "normalizequerystring", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_2);
	if (ZEPHIR_IS_STRING_IDENTICAL(&qs, "")) {
		ZVAL_NULL(&_2);
	} else {
		ZEPHIR_CPY_WRT(&_2, &qs);
	}
	RETURN_CCTOR(&_2);

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
PHP_METHOD(Zim_Http_Request, getHost) {

	zval host, _7, _8, _9, _10, _0$$4, _1$$4, _2$$5, _3$$5, _4$$6, _5$$6, _6$$6;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&host);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&host, this_ptr, "getforwardedfor", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&host)) {
	} else {
		zephir_read_property(&_0$$4, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_1$$4);
		ZVAL_STRING(&_1$$4, "HOST");
		ZEPHIR_CALL_METHOD(&host, &_0$$4, "get", NULL, 0, &_1$$4);
		zephir_check_call_status();
		if (!(zephir_is_true(&host))) {
			zephir_read_property(&_2$$5, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_3$$5);
			ZVAL_STRING(&_3$$5, "SERVER_NAME");
			ZEPHIR_CALL_METHOD(&host, &_2$$5, "get", NULL, 0, &_3$$5);
			zephir_check_call_status();
			if (!(zephir_is_true(&host))) {
				zephir_read_property(&_4$$6, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_5$$6);
				ZVAL_STRING(&_5$$6, "SERVER_ADDR");
				ZEPHIR_INIT_VAR(&_6$$6);
				ZVAL_STRING(&_6$$6, "");
				ZEPHIR_CALL_METHOD(&host, &_4$$6, "get", NULL, 0, &_5$$6, &_6$$6);
				zephir_check_call_status();
			}
		}
	}
	ZEPHIR_INIT_VAR(&_7);
	zephir_fast_trim(&_7, &host, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_8);
	ZVAL_STRING(&_8, "/:\\d+$/");
	ZEPHIR_INIT_VAR(&_9);
	ZVAL_STRING(&_9, "");
	ZEPHIR_CALL_FUNCTION(&_10, "preg_replace", NULL, 78, &_8, &_9, &_7);
	zephir_check_call_status();
	zephir_fast_strtolower(return_value, &_10);
	RETURN_MM();

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
PHP_METHOD(Zim_Http_Request, getMethod) {

	zval method, _0, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3, _6$$3, _7$$4, _8$$4, _9$$5;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("method"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_read_property(&_2$$3, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "REQUEST_METHOD");
		ZEPHIR_INIT_VAR(&_5$$3);
		ZVAL_STRING(&_5$$3, "GET");
		ZEPHIR_CALL_METHOD(&_3$$3, &_2$$3, "get", NULL, 0, &_4$$3, &_5$$3);
		zephir_check_call_status();
		zephir_fast_strtoupper(&_1$$3, &_3$$3);
		zephir_update_property_zval(this_ptr, SL("method"), &_1$$3);
		zephir_read_property(&_6$$3, this_ptr, SL("method"), PH_NOISY_CC | PH_READONLY);
		if (ZEPHIR_IS_STRING_IDENTICAL(&_6$$3, "POST")) {
			zephir_read_property(&_7$$4, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_8$$4);
			ZVAL_STRING(&_8$$4, "X-HTTP-METHOD-OVERRIDE");
			ZEPHIR_CALL_METHOD(&method, &_7$$4, "get", NULL, 0, &_8$$4);
			zephir_check_call_status();
			if (zephir_is_true(&method)) {
				ZEPHIR_INIT_VAR(&_9$$5);
				zephir_fast_strtoupper(&_9$$5, &method);
				zephir_update_property_zval(this_ptr, SL("method"), &_9$$5);
			}
		}
	}
	RETURN_MM_MEMBER(getThis(), "method");

}

/**
 * Gets the "real" request method.
 *
 * @return string The request method
 *
 * @see getMethod()
 */
PHP_METHOD(Zim_Http_Request, getRealMethod) {

	zval _0, _1, _2, _3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "REQUEST_METHOD");
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "GET");
	ZEPHIR_CALL_METHOD(&_1, &_0, "get", NULL, 0, &_2, &_3);
	zephir_check_call_status();
	zephir_fast_strtoupper(return_value, &_1);
	RETURN_MM();

}

/**
 * Checks if the request method is of specified type.
 *
 * @param string $method Uppercase request method (GET, POST etc)
 *
 * @return bool
 */
PHP_METHOD(Zim_Http_Request, isMethod) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *method_param = NULL, _0, _1;
	zval method;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &method_param);

	zephir_get_strval(&method, method_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getmethod", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	zephir_fast_strtoupper(&_1, &method);
	RETURN_MM_BOOL(ZEPHIR_IS_IDENTICAL(&_0, &_1));

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
PHP_METHOD(Zim_Http_Request, getContent) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_2 = NULL, *_6 = NULL;
	zval *asResource_param = NULL, __$true, __$false, currentContentIsResource, resourcee, _0, _12, _14, _1$$4, _3$$3, _8$$3, _9$$3, _4$$5, _5$$5, _7$$5, _10$$6, _11$$6, _15$$7, _16$$7;
	zend_bool asResource, _13;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&currentContentIsResource);
	ZVAL_UNDEF(&resourcee);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$7);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &asResource_param);

	if (!asResource_param) {
		asResource = 0;
	} else {
		asResource = zephir_get_boolval(asResource_param);
	}


	zephir_read_property(&_0, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&currentContentIsResource);
	ZVAL_BOOL(&currentContentIsResource, Z_TYPE_P(&_0) == IS_RESOURCE);
	if (asResource == 1) {
		if (zephir_is_true(&currentContentIsResource)) {
			zephir_read_property(&_1$$4, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_FUNCTION(NULL, "rewind", &_2, 95, &_1$$4);
			zephir_check_call_status();
			RETURN_MM_MEMBER(getThis(), "content");
		}
		zephir_read_property(&_3$$3, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_3$$3) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_4$$5);
			ZVAL_STRING(&_4$$5, "php://temp");
			ZEPHIR_INIT_VAR(&_5$$5);
			ZVAL_STRING(&_5$$5, "r+");
			ZEPHIR_CALL_FUNCTION(&resourcee, "fopen", &_6, 96, &_4$$5, &_5$$5);
			zephir_check_call_status();
			zephir_read_property(&_7$$5, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
			zephir_fwrite(NULL, &resourcee, &_7$$5 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(NULL, "rewind", &_2, 95, &resourcee);
			zephir_check_call_status();
			RETURN_CCTOR(&resourcee);
		}
		if (0) {
			zephir_update_property_zval(this_ptr, SL("content"), &__$true);
		} else {
			zephir_update_property_zval(this_ptr, SL("content"), &__$false);
		}
		ZEPHIR_INIT_VAR(&_8$$3);
		ZVAL_STRING(&_8$$3, "php://input");
		ZEPHIR_INIT_VAR(&_9$$3);
		ZVAL_STRING(&_9$$3, "rb");
		ZEPHIR_RETURN_CALL_FUNCTION("fopen", &_6, 96, &_8$$3, &_9$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_is_true(&currentContentIsResource)) {
		zephir_read_property(&_10$$6, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_FUNCTION(NULL, "rewind", &_2, 95, &_10$$6);
		zephir_check_call_status();
		zephir_read_property(&_11$$6, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_RETURN_CALL_FUNCTION("stream_get_contents", NULL, 97, &_11$$6);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_read_property(&_12, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
	_13 = Z_TYPE_P(&_12) == IS_NULL;
	if (!(_13)) {
		zephir_read_property(&_14, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
		_13 = ZEPHIR_IS_FALSE_IDENTICAL(&_14);
	}
	if (_13) {
		ZEPHIR_INIT_VAR(&_15$$7);
		ZEPHIR_INIT_VAR(&_16$$7);
		ZVAL_STRING(&_16$$7, "php://input");
		zephir_file_get_contents(&_15$$7, &_16$$7 TSRMLS_CC);
		zephir_update_property_zval(this_ptr, SL("content"), &_15$$7);
	}
	RETURN_MM_MEMBER(getThis(), "content");

}

/**
 * @return string
 */
PHP_METHOD(Zim_Http_Request, prepareRequestUri) {

	zval requestUri, schemeAndHttpHost, _0, _1, _2$$3, _3$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&requestUri);
	ZVAL_UNDEF(&schemeAndHttpHost);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "REQUEST_URI");
	ZEPHIR_CALL_METHOD(&requestUri, &_0, "get", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&schemeAndHttpHost, this_ptr, "getschemeandhttphost", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	zephir_fast_strpos(&_1, &requestUri, &schemeAndHttpHost, 0 );
	if (ZEPHIR_IS_LONG_IDENTICAL(&_1, 0)) {
		ZVAL_LONG(&_2$$3, zephir_fast_strlen_ev(&schemeAndHttpHost));
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_substr(&_3$$3, &requestUri, zephir_get_intval(&_2$$3), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_CPY_WRT(&requestUri, &_3$$3);
	}
	RETURN_CCTOR(&requestUri);

}

/**
 * Prepares the path info.
 *
 * @return string path info
 */
PHP_METHOD(Zim_Http_Request, preparePathInfo) {

	zend_bool _3;
	zval requestUri, pos, _0, _4, _5, _6, _1$$4, _2$$4, _7$$5;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&requestUri);
	ZVAL_UNDEF(&pos);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_7$$5);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&requestUri, this_ptr, "getrequesturi", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&requestUri) == IS_NULL) {
		RETURN_MM_STRING("/");
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "?");
	ZEPHIR_INIT_VAR(&pos);
	zephir_fast_strpos(&pos, &requestUri, &_0, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&pos)) {
		ZVAL_LONG(&_1$$4, 0);
		ZEPHIR_INIT_VAR(&_2$$4);
		zephir_substr(&_2$$4, &requestUri, 0 , zephir_get_intval(&pos), 0);
		ZEPHIR_CPY_WRT(&requestUri, &_2$$4);
	}
	_3 = !ZEPHIR_IS_STRING_IDENTICAL(&requestUri, "");
	if (_3) {
		ZVAL_LONG(&_4, 0);
		ZVAL_LONG(&_5, 1);
		ZEPHIR_INIT_VAR(&_6);
		zephir_substr(&_6, &requestUri, 0 , 1 , 0);
		_3 = !ZEPHIR_IS_STRING_IDENTICAL(&_6, "/");
	}
	if (_3) {
		ZEPHIR_INIT_VAR(&_7$$5);
		ZEPHIR_CONCAT_SV(&_7$$5, "/", &requestUri);
		ZEPHIR_CPY_WRT(&requestUri, &_7$$5);
	}
	RETURN_CCTOR(&requestUri);

}

void zephir_init_static_properties_Zim_Http_Request(TSRMLS_D) {

	zval _1;
	zval _0;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 3, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "FORWARDED");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "X_FORWARDED_FOR");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "X_FORWARDED_HOST");
	zephir_array_fast_append(&_0, &_1);
	zend_update_static_property(zim_http_request_ce, ZEND_STRL("forwardedHeaders"), &_0);
	ZEPHIR_MM_RESTORE();

}

