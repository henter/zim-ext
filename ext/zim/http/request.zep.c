
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
#include "kernel/time.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"
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

	zend_declare_property_bool(zim_http_request_ce, SL("httpMethodParameterOverride"), 0, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

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
	zend_declare_property_null(zim_http_request_ce, SL("baseUrl"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(zim_http_request_ce, SL("basePath"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(zim_http_request_ce, SL("method"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(zim_http_request_ce, SL("format"), ZEND_ACC_PROTECTED TSRMLS_CC);

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
	zephir_is_iterable(&_0, 0, "zim/http/request.zep", 121);
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
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", &_1, 93, &request);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("request"), &_0);
	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, zim_http_parameterbag_ce);
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", &_1, 93, &query);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("query"), &_2);
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, zim_http_parameterbag_ce);
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", &_1, 93, &attributes);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("attributes"), &_3);
	ZEPHIR_INIT_VAR(&_4);
	object_init_ex(&_4, zim_http_serverbag_ce);
	ZEPHIR_CALL_METHOD(NULL, &_4, "__construct", &_1, 93, &server);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("server"), &_4);
	ZEPHIR_INIT_VAR(&_5);
	object_init_ex(&_5, zim_http_headerbag_ce);
	zephir_read_property(&_6, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_7, &_6, "getheaders", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_5, "__construct", NULL, 94, &_7);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("headers"), &_5);
	zephir_update_property_zval(this_ptr, SL("content"), content);
	zephir_update_property_zval(this_ptr, SL("pathInfo"), &__$null);
	zephir_update_property_zval(this_ptr, SL("requestUri"), &__$null);
	zephir_update_property_zval(this_ptr, SL("baseUrl"), &__$null);
	zephir_update_property_zval(this_ptr, SL("basePath"), &__$null);
	zephir_update_property_zval(this_ptr, SL("method"), &__$null);
	zephir_update_property_zval(this_ptr, SL("format"), &__$null);
	ZEPHIR_MM_RESTORE();

}

/**
 * Creates a new request with values from PHP's super globals.
 *
 * @return static
 */
PHP_METHOD(Zim_Http_Request, createFromGlobals) {

	zval _17;
	zend_bool _11;
	zval _9;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *_SERVER, *_GET, *_POST, request, data, server, _0, _5, _6, _7, _8, _10, _12, _13, _14, _15, _16, _1$$3, _3$$3, _2$$4, _4$$5, _18$$6, _19$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&request);
	ZVAL_UNDEF(&data);
	ZVAL_UNDEF(&server);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_17);

	ZEPHIR_MM_GROW();
	zephir_get_global(&_POST, SL("_POST"));
	zephir_get_global(&_GET, SL("_GET"));
	zephir_get_global(&_SERVER, SL("_SERVER"));

	ZEPHIR_CPY_WRT(&server, _SERVER);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_GET_CONSTANT(&_0, "PHP_SAPI");
	if (ZEPHIR_IS_STRING_IDENTICAL(&_0, "cli-server")) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "HTTP_CONTENT_LENGTH");
		if (zephir_array_key_exists(_SERVER, &_1$$3 TSRMLS_CC)) {
			zephir_array_fetch_string(&_2$$4, _SERVER, SL("HTTP_CONTENT_LENGTH"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 168 TSRMLS_CC);
			zephir_array_update_string(&server, SL("CONTENT_LENGTH"), &_2$$4, PH_COPY | PH_SEPARATE);
		}
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "HTTP_CONTENT_TYPE");
		if (zephir_array_key_exists(_SERVER, &_3$$3 TSRMLS_CC)) {
			zephir_array_fetch_string(&_4$$5, _SERVER, SL("HTTP_CONTENT_TYPE"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 171 TSRMLS_CC);
			zephir_array_update_string(&server, SL("CONTENT_TYPE"), &_4$$5, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_VAR(&request);
	object_init_ex(&request, zim_http_request_ce);
	ZEPHIR_INIT_VAR(&_5);
	array_init(&_5);
	ZEPHIR_CALL_METHOD(NULL, &request, "__construct", NULL, 95, _GET, _POST, &_5, &server);
	zephir_check_call_status();
	zephir_read_property(&_6, &request, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_8);
	ZVAL_STRING(&_8, "CONTENT_TYPE");
	ZEPHIR_CALL_METHOD(&_7, &_6, "get", NULL, 0, &_8);
	zephir_check_call_status();
	zephir_get_strval(&_9, &_7);
	ZEPHIR_INIT_NVAR(&_8);
	ZVAL_STRING(&_8, "application/x-www-form-urlencoded");
	ZEPHIR_INIT_VAR(&_10);
	zephir_fast_strpos(&_10, &_9, &_8, 0 );
	_11 = ZEPHIR_IS_LONG_IDENTICAL(&_10, 0);
	if (_11) {
		ZEPHIR_INIT_VAR(&_12);
		zephir_read_property(&_13, &request, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_15);
		ZVAL_STRING(&_15, "REQUEST_METHOD");
		ZEPHIR_INIT_VAR(&_16);
		ZVAL_STRING(&_16, "GET");
		ZEPHIR_CALL_METHOD(&_14, &_13, "get", NULL, 0, &_15, &_16);
		zephir_check_call_status();
		zephir_fast_strtoupper(&_12, &_14);
		ZEPHIR_INIT_VAR(&_17);
		zephir_create_array(&_17, 3, 0 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&_15);
		ZVAL_STRING(&_15, "PUT");
		zephir_array_fast_append(&_17, &_15);
		ZEPHIR_INIT_NVAR(&_15);
		ZVAL_STRING(&_15, "DELETE");
		zephir_array_fast_append(&_17, &_15);
		ZEPHIR_INIT_NVAR(&_15);
		ZVAL_STRING(&_15, "PATCH");
		zephir_array_fast_append(&_17, &_15);
		_11 = zephir_fast_in_array(&_12, &_17 TSRMLS_CC);
	}
	if (_11) {
		ZEPHIR_CALL_METHOD(&_18$$6, &request, "getcontent", NULL, 96);
		zephir_check_call_status();
		ZEPHIR_MAKE_REF(&data);
		ZEPHIR_CALL_FUNCTION(NULL, "parse_str", NULL, 97, &_18$$6, &data);
		ZEPHIR_UNREF(&data);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_19$$6);
		object_init_ex(&_19$$6, zim_http_parameterbag_ce);
		ZEPHIR_CALL_METHOD(NULL, &_19$$6, "__construct", NULL, 93, &data);
		zephir_check_call_status();
		zephir_update_property_zval(&request, SL("request"), &_19$$6);
	}
	RETURN_CCTOR(&request);

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
PHP_METHOD(Zim_Http_Request, create) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_3 = NULL;
	zval parameters, server, _0;
	zval *uri_param = NULL, *method_param = NULL, *parameters_param = NULL, *server_param = NULL, *content = NULL, content_sub, __$null, components, request, query, queryString, qs, _1, _2, _4, _19, _28, _29, _30, _31, _5$$3, _6$$3, _7$$4, _8$$4, _9$$5, _10$$5, _11$$6, _12$$7, _13$$7, _14$$7, _15$$7, _16$$8, _17$$9, _18$$10, _20$$12, _21$$15, _22$$15, _23$$16, _24$$16, _25$$16, _26$$18, _27$$18;
	zval uri, method;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&content_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&components);
	ZVAL_UNDEF(&request);
	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&queryString);
	ZVAL_UNDEF(&qs);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_28);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_21$$15);
	ZVAL_UNDEF(&_22$$15);
	ZVAL_UNDEF(&_23$$16);
	ZVAL_UNDEF(&_24$$16);
	ZVAL_UNDEF(&_25$$16);
	ZVAL_UNDEF(&_26$$18);
	ZVAL_UNDEF(&_27$$18);
	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&server);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 4, &uri_param, &method_param, &parameters_param, &server_param, &content);

	zephir_get_strval(&uri, uri_param);
	if (!method_param) {
		ZEPHIR_INIT_VAR(&method);
		ZVAL_STRING(&method, "GET");
	} else {
		zephir_get_strval(&method, method_param);
	}
	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
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
	zephir_create_array(&_0, 12, 0 TSRMLS_CC);
	add_assoc_stringl_ex(&_0, SL("SERVER_NAME"), SL("localhost"));
	add_assoc_long_ex(&_0, SL("SERVER_PORT"), 80);
	add_assoc_stringl_ex(&_0, SL("HTTP_HOST"), SL("localhost"));
	add_assoc_stringl_ex(&_0, SL("HTTP_USER_AGENT"), SL("ZimPHP"));
	add_assoc_stringl_ex(&_0, SL("HTTP_ACCEPT"), SL("text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"));
	add_assoc_stringl_ex(&_0, SL("HTTP_ACCEPT_LANGUAGE"), SL("en-us,en;q=0.5"));
	add_assoc_stringl_ex(&_0, SL("HTTP_ACCEPT_CHARSET"), SL("ISO-8859-1,utf-8;q=0.7,*;q=0.7"));
	add_assoc_stringl_ex(&_0, SL("REMOTE_ADDR"), SL("127.0.0.1"));
	add_assoc_stringl_ex(&_0, SL("SCRIPT_NAME"), SL(""));
	add_assoc_stringl_ex(&_0, SL("SCRIPT_FILENAME"), SL(""));
	add_assoc_stringl_ex(&_0, SL("SERVER_PROTOCOL"), SL("HTTP/1.1"));
	ZEPHIR_INIT_VAR(&_1);
	zephir_time(&_1);
	zephir_array_update_string(&_0, SL("REQUEST_TIME"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_FUNCTION(&_2, "array_replace", &_3, 22, &_0, &server);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&server, &_2);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "");
	zephir_array_update_string(&server, SL("PATH_INFO"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_4);
	zephir_fast_strtoupper(&_4, &method);
	zephir_array_update_string(&server, SL("REQUEST_METHOD"), &_4, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_FUNCTION(&components, "parse_url", NULL, 98, &uri);
	zephir_check_call_status();
	if (zephir_array_isset_string(&components, SL("host"))) {
		zephir_array_fetch_string(&_5$$3, &components, SL("host"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 224 TSRMLS_CC);
		zephir_array_update_string(&server, SL("SERVER_NAME"), &_5$$3, PH_COPY | PH_SEPARATE);
		zephir_array_fetch_string(&_6$$3, &components, SL("host"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 225 TSRMLS_CC);
		zephir_array_update_string(&server, SL("HTTP_HOST"), &_6$$3, PH_COPY | PH_SEPARATE);
	}
	if (zephir_array_isset_string(&components, SL("scheme"))) {
		zephir_array_fetch_string(&_7$$4, &components, SL("scheme"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 229 TSRMLS_CC);
		ZEPHIR_SINIT_VAR(_8$$4);
		ZVAL_STRING(&_8$$4, "https");
		if (ZEPHIR_IS_IDENTICAL(&_8$$4, &_7$$4)) {
			ZEPHIR_INIT_VAR(&_9$$5);
			ZVAL_STRING(&_9$$5, "on");
			zephir_array_update_string(&server, SL("HTTPS"), &_9$$5, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_VAR(&_10$$5);
			ZVAL_LONG(&_10$$5, 443);
			zephir_array_update_string(&server, SL("SERVER_PORT"), &_10$$5, PH_COPY | PH_SEPARATE);
		} else {
			zephir_array_unset_string(&server, SL("HTTPS"), PH_SEPARATE);
			ZEPHIR_INIT_VAR(&_11$$6);
			ZVAL_LONG(&_11$$6, 80);
			zephir_array_update_string(&server, SL("SERVER_PORT"), &_11$$6, PH_COPY | PH_SEPARATE);
		}
	}
	if (zephir_array_isset_string(&components, SL("port"))) {
		zephir_array_fetch_string(&_12$$7, &components, SL("port"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 239 TSRMLS_CC);
		zephir_array_update_string(&server, SL("SERVER_PORT"), &_12$$7, PH_COPY | PH_SEPARATE);
		zephir_array_fetch_string(&_13$$7, &server, SL("HTTP_HOST"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 240 TSRMLS_CC);
		zephir_array_fetch_string(&_14$$7, &components, SL("port"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 240 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_15$$7);
		ZEPHIR_CONCAT_VSV(&_15$$7, &_13$$7, ":", &_14$$7);
		zephir_array_update_string(&server, SL("HTTP_HOST"), &_15$$7, PH_COPY | PH_SEPARATE);
	}
	if (zephir_array_isset_string(&components, SL("user"))) {
		zephir_array_fetch_string(&_16$$8, &components, SL("user"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 244 TSRMLS_CC);
		zephir_array_update_string(&server, SL("PHP_AUTH_USER"), &_16$$8, PH_COPY | PH_SEPARATE);
	}
	if (zephir_array_isset_string(&components, SL("pass"))) {
		zephir_array_fetch_string(&_17$$9, &components, SL("pass"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 248 TSRMLS_CC);
		zephir_array_update_string(&server, SL("PHP_AUTH_PW"), &_17$$9, PH_COPY | PH_SEPARATE);
	}
	if (!(zephir_array_isset_string(&components, SL("path")))) {
		ZEPHIR_INIT_VAR(&_18$$10);
		ZVAL_STRING(&_18$$10, "/");
		zephir_array_update_string(&components, SL("path"), &_18$$10, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(&_19);
	zephir_fast_strtoupper(&_19, &method);
	do {
		if (ZEPHIR_IS_STRING(&_19, "POST") || ZEPHIR_IS_STRING(&_19, "PUT") || ZEPHIR_IS_STRING(&_19, "DELETE")) {
			if (!(zephir_array_isset_string(&server, SL("CONTENT_TYPE")))) {
				ZEPHIR_INIT_VAR(&_20$$12);
				ZVAL_STRING(&_20$$12, "application/x-www-form-urlencoded");
				zephir_array_update_string(&server, SL("CONTENT_TYPE"), &_20$$12, PH_COPY | PH_SEPARATE);
			}
		}
		if (ZEPHIR_IS_STRING(&_19, "PATCH")) {
			ZEPHIR_CPY_WRT(&request, &parameters);
			ZEPHIR_INIT_VAR(&query);
			array_init(&query);
			break;
		}
		ZEPHIR_INIT_NVAR(&request);
		array_init(&request);
		ZEPHIR_CPY_WRT(&query, &parameters);
		break;
	} while(0);

	ZEPHIR_INIT_VAR(&queryString);
	ZVAL_STRING(&queryString, "");
	if (zephir_array_isset_string(&components, SL("query"))) {
		zephir_array_fetch_string(&_21$$15, &components, SL("query"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 275 TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_22$$15, "html_entity_decode", NULL, 99, &_21$$15);
		zephir_check_call_status();
		ZEPHIR_MAKE_REF(&qs);
		ZEPHIR_CALL_FUNCTION(NULL, "parse_str", NULL, 97, &_22$$15, &qs);
		ZEPHIR_UNREF(&qs);
		zephir_check_call_status();
		if (zephir_is_true(&query)) {
			ZEPHIR_CALL_FUNCTION(&_23$$16, "array_replace", &_3, 22, &qs, &query);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&query, &_23$$16);
			ZEPHIR_INIT_VAR(&_24$$16);
			ZVAL_STRING(&_24$$16, "");
			ZEPHIR_INIT_VAR(&_25$$16);
			ZVAL_STRING(&_25$$16, "&");
			ZEPHIR_CALL_FUNCTION(&queryString, "http_build_query", NULL, 100, &query, &_24$$16, &_25$$16);
			zephir_check_call_status();
		} else {
			ZEPHIR_CPY_WRT(&query, &qs);
			ZEPHIR_OBS_NVAR(&queryString);
			zephir_array_fetch_string(&queryString, &components, SL("query"), PH_NOISY, "zim/http/request.zep", 282 TSRMLS_CC);
		}
	} else if (zephir_is_true(&query)) {
		ZEPHIR_INIT_VAR(&_26$$18);
		ZVAL_STRING(&_26$$18, "");
		ZEPHIR_INIT_VAR(&_27$$18);
		ZVAL_STRING(&_27$$18, "&");
		ZEPHIR_CALL_FUNCTION(&queryString, "http_build_query", NULL, 100, &query, &_26$$18, &_27$$18);
		zephir_check_call_status();
	}
	zephir_array_fetch_string(&_28, &components, SL("path"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 288 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_29);
	if (!ZEPHIR_IS_STRING_IDENTICAL(&queryString, "")) {
		ZEPHIR_INIT_NVAR(&_29);
		ZEPHIR_CONCAT_SV(&_29, "?", &queryString);
	} else {
		ZEPHIR_INIT_NVAR(&_29);
		ZVAL_STRING(&_29, "");
	}
	ZEPHIR_INIT_VAR(&_30);
	ZEPHIR_CONCAT_VV(&_30, &_28, &_29);
	zephir_array_update_string(&server, SL("REQUEST_URI"), &_30, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&server, SL("QUERY_STRING"), &queryString, PH_COPY | PH_SEPARATE);
	object_init_ex(return_value, zim_http_request_ce);
	ZEPHIR_INIT_VAR(&_31);
	array_init(&_31);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 95, &query, &request, &_31, &server, content);
	zephir_check_call_status();
	RETURN_MM();

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
PHP_METHOD(Zim_Http_Request, duplicate) {

	zend_bool _10;
	zephir_fcall_cache_entry *_1 = NULL, *_12 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *query_param = NULL, *request_param = NULL, *attributes_param = NULL, *server_param = NULL, __$null, dup, _8, _9, _11, _16, _17, _0$$3, _2$$4, _3$$5, _4$$6, _5$$6, _6$$6, _7$$6, _13$$7, _14$$7, _15$$7, _18$$8, _19$$8;
	zval query, request, attributes, server;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&query);
	ZVAL_UNDEF(&request);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&server);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&dup);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&_19$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 4, &query_param, &request_param, &attributes_param, &server_param);

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


	ZEPHIR_INIT_VAR(&dup);
	if (zephir_clone(&dup, this_ptr TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	if (zephir_fast_count_int(&query TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, zim_http_parameterbag_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", &_1, 93, &query);
		zephir_check_call_status();
		zephir_update_property_zval(&dup, SL("query"), &_0$$3);
	}
	if (zephir_fast_count_int(&request TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(&_2$$4);
		object_init_ex(&_2$$4, zim_http_parameterbag_ce);
		ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", &_1, 93, &request);
		zephir_check_call_status();
		zephir_update_property_zval(&dup, SL("request"), &_2$$4);
	}
	if (zephir_fast_count_int(&attributes TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(&_3$$5);
		object_init_ex(&_3$$5, zim_http_parameterbag_ce);
		ZEPHIR_CALL_METHOD(NULL, &_3$$5, "__construct", &_1, 93, &attributes);
		zephir_check_call_status();
		zephir_update_property_zval(&dup, SL("attributes"), &_3$$5);
	}
	if (zephir_fast_count_int(&server TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(&_4$$6);
		object_init_ex(&_4$$6, zim_http_serverbag_ce);
		ZEPHIR_CALL_METHOD(NULL, &_4$$6, "__construct", &_1, 93, &server);
		zephir_check_call_status();
		zephir_update_property_zval(&dup, SL("server"), &_4$$6);
		ZEPHIR_INIT_VAR(&_5$$6);
		object_init_ex(&_5$$6, zim_http_headerbag_ce);
		zephir_read_property(&_6$$6, &dup, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_7$$6, &_6$$6, "getheaders", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_5$$6, "__construct", NULL, 94, &_7$$6);
		zephir_check_call_status();
		zephir_update_property_zval(&dup, SL("headers"), &_5$$6);
	}
	zephir_update_property_zval(&dup, SL("pathInfo"), &__$null);
	zephir_update_property_zval(&dup, SL("requestUri"), &__$null);
	zephir_update_property_zval(&dup, SL("baseUrl"), &__$null);
	zephir_update_property_zval(&dup, SL("basePath"), &__$null);
	zephir_update_property_zval(&dup, SL("method"), &__$null);
	zephir_update_property_zval(&dup, SL("format"), &__$null);
	ZEPHIR_INIT_VAR(&_9);
	ZVAL_STRING(&_9, "_format");
	ZEPHIR_CALL_METHOD(&_8, &dup, "get", NULL, 0, &_9);
	zephir_check_call_status();
	_10 = !zephir_is_true(&_8);
	if (_10) {
		ZEPHIR_INIT_NVAR(&_9);
		ZVAL_STRING(&_9, "_format");
		ZEPHIR_CALL_METHOD(&_11, this_ptr, "get", &_12, 0, &_9);
		zephir_check_call_status();
		_10 = zephir_is_true(&_11);
	}
	if (_10) {
		zephir_read_property(&_13$$7, &dup, SL("attributes"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_15$$7);
		ZVAL_STRING(&_15$$7, "_format");
		ZEPHIR_CALL_METHOD(&_14$$7, this_ptr, "get", &_12, 0, &_15$$7);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_15$$7);
		ZVAL_STRING(&_15$$7, "_format");
		ZEPHIR_CALL_METHOD(NULL, &_13$$7, "set", NULL, 0, &_15$$7, &_14$$7);
		zephir_check_call_status();
	}
	ZVAL_NULL(&_17);
	ZEPHIR_CALL_METHOD(&_16, &dup, "getrequestformat", NULL, 0, &_17);
	zephir_check_call_status();
	if (!(zephir_is_true(&_16))) {
		ZVAL_NULL(&_19$$8);
		ZEPHIR_CALL_METHOD(&_18$$8, this_ptr, "getrequestformat", NULL, 0, &_19$$8);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &dup, "setrequestformat", NULL, 0, &_18$$8);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&dup);

}

/**
 * Returns the user.
 *
 * @return string|null
 */
PHP_METHOD(Zim_Http_Request, getUser) {

	zval _0, _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "PHP_AUTH_USER");
	ZEPHIR_RETURN_CALL_METHOD(&_0, "get", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the password.
 *
 * @return string|null
 */
PHP_METHOD(Zim_Http_Request, getPassword) {

	zval _0, _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "PHP_AUTH_PW");
	ZEPHIR_RETURN_CALL_METHOD(&_0, "get", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Gets the user info.
 *
 * @return string A user name and, optionally, scheme-specific information about how to gain authorization to access the server
 */
PHP_METHOD(Zim_Http_Request, getUserInfo) {

	zval userinfo, pass, _0$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&userinfo);
	ZVAL_UNDEF(&pass);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&userinfo, this_ptr, "getuser", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&pass, this_ptr, "getpassword", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_STRING(&pass, "")) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZEPHIR_CONCAT_SV(&_0$$3, ":", &pass);
		zephir_concat_self(&userinfo, &_0$$3 TSRMLS_CC);
	}
	RETURN_CCTOR(&userinfo);

}

/**
 * @return bool
 */
PHP_METHOD(Zim_Http_Request, isNoCache) {

	zend_bool _3;
	zval _0, _1, _2, _4, _5, _6;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "no-cache");
	ZEPHIR_CALL_METHOD(&_1, &_0, "hascachecontroldirective", NULL, 0, &_2);
	zephir_check_call_status();
	_3 = zephir_is_true(&_1);
	if (!(_3)) {
		zephir_read_property(&_4, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_STRING(&_2, "Pragma");
		ZEPHIR_CALL_METHOD(&_5, &_4, "get", NULL, 0, &_2);
		zephir_check_call_status();
		ZEPHIR_SINIT_VAR(_6);
		ZVAL_STRING(&_6, "no-cache");
		_3 = ZEPHIR_IS_EQUAL(&_6, &_5);
	}
	RETURN_MM_BOOL(_3);

}

/**
 * Associates a format with mime types.
 *
 * @param string       $format    The format
 * @param string|array $mimeTypes The associated mime types (the preferred one must be the first as it will be used as the content type)
 */
PHP_METHOD(Zim_Http_Request, setFormat) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *format, format_sub, *mimeTypes, mimeTypes_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&format_sub);
	ZVAL_UNDEF(&mimeTypes_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &format, &mimeTypes);



	zephir_read_static_property_ce(&_0, zim_http_request_ce, SL("formats"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_CALL_STATIC(NULL, "initializeformats", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_1);
	if (Z_TYPE_P(mimeTypes) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&_1, mimeTypes);
	} else {
		ZEPHIR_INIT_NVAR(&_1);
		zephir_create_array(&_1, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&_1, mimeTypes);
	}
	zephir_update_static_property_array_multi_ce(zim_http_request_ce, SL("formats"), &_1 TSRMLS_CC, SL("z"), 1, format);
	ZEPHIR_MM_RESTORE();

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
	zval *deft = NULL, deft_sub, _0, _4, _5, _1$$3, _2$$3, _3$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&deft_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &deft);

	if (!deft) {
		deft = &deft_sub;
		ZEPHIR_INIT_VAR(deft);
		ZVAL_STRING(deft, "html");
	}


	zephir_read_property(&_0, this_ptr, SL("format"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		zephir_read_property(&_1$$3, this_ptr, SL("attributes"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "_format");
		ZEPHIR_CALL_METHOD(&_2$$3, &_1$$3, "get", NULL, 0, &_3$$3);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("format"), &_2$$3);
	}
	ZEPHIR_INIT_VAR(&_4);
	zephir_read_property(&_5, this_ptr, SL("format"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_5) == IS_NULL) {
		ZEPHIR_CPY_WRT(&_4, deft);
	} else {
		zephir_read_property(&_4, this_ptr, SL("format"), PH_NOISY_CC);
	}
	RETURN_CCTOR(&_4);

}

/**
 * Sets the request format.
 *
 * @param string $format The request format
 */
PHP_METHOD(Zim_Http_Request, setRequestFormat) {

	zval *format_param = NULL;
	zval format;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&format);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &format_param);

	zephir_get_strval(&format, format_param);


	zephir_update_property_zval(this_ptr, SL("format"), &format);
	ZEPHIR_MM_RESTORE();

}

/**
 * Gets the format associated with the request.
 *
 * @return string|null The format (null if no content type is present)
 */
PHP_METHOD(Zim_Http_Request, getContentType) {

	zval _3;
	zval _0, _1, _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "CONTENT_TYPE");
	ZEPHIR_CALL_METHOD(&_1, &_0, "get", NULL, 0, &_2);
	zephir_check_call_status();
	zephir_get_strval(&_3, &_1);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getformat", NULL, 0, &_3);
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
		zephir_array_fetch(&_4, &_3, &format, PH_NOISY | PH_READONLY, "zim/http/request.zep", 452 TSRMLS_CC);
		zephir_array_fetch_long(&_1, &_4, 0, PH_NOISY, "zim/http/request.zep", 452 TSRMLS_CC);
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
		zephir_array_fetch(&_1, &_3, &format, PH_NOISY, "zim/http/request.zep", 467 TSRMLS_CC);
	} else {
		array_init(&_1);
	}
	RETURN_CCTOR(&_1);

}

/**
 * Gets the format associated with the mime type.
 *
 * @param string $mimeType The associated mime type
 *
 * @return string|null The format (null if not found)
 */
PHP_METHOD(Zim_Http_Request, getFormat) {

	zend_bool _9$$5;
	zval _8$$5, _10$$5;
	zend_string *_7;
	zend_ulong _6;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *mimeType_param = NULL, canonicalMimeType, pos, _0, _3, format, mimeTypes, _4, *_5, _1$$3, _2$$3;
	zval mimeType;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&mimeType);
	ZVAL_UNDEF(&canonicalMimeType);
	ZVAL_UNDEF(&pos);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&format);
	ZVAL_UNDEF(&mimeTypes);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &mimeType_param);

	zephir_get_strval(&mimeType, mimeType_param);


	ZEPHIR_INIT_VAR(&canonicalMimeType);
	ZVAL_NULL(&canonicalMimeType);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, ";");
	ZEPHIR_INIT_VAR(&pos);
	zephir_fast_strpos(&pos, &mimeType, &_0, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&pos)) {
		ZVAL_LONG(&_1$$3, 0);
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_substr(&_2$$3, &mimeType, 0 , zephir_get_intval(&pos), 0);
		ZEPHIR_INIT_NVAR(&canonicalMimeType);
		zephir_fast_trim(&canonicalMimeType, &_2$$3, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	}
	zephir_read_static_property_ce(&_3, zim_http_request_ce, SL("formats"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_3) == IS_NULL) {
		ZEPHIR_CALL_STATIC(NULL, "initializeformats", NULL, 0);
		zephir_check_call_status();
	}
	zephir_read_static_property_ce(&_4, zim_http_request_ce, SL("formats"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_4, 0, "zim/http/request.zep", 501);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_4), _6, _7, _5)
	{
		ZEPHIR_INIT_NVAR(&format);
		if (_7 != NULL) { 
			ZVAL_STR_COPY(&format, _7);
		} else {
			ZVAL_LONG(&format, _6);
		}
		ZEPHIR_INIT_NVAR(&mimeTypes);
		ZVAL_COPY(&mimeTypes, _5);
		zephir_get_arrval(&_8$$5, &mimeTypes);
		if (zephir_fast_in_array(&mimeType, &_8$$5 TSRMLS_CC)) {
			RETURN_CCTOR(&format);
		}
		_9$$5 = Z_TYPE_P(&canonicalMimeType) != IS_NULL;
		if (_9$$5) {
			zephir_get_arrval(&_10$$5, &mimeTypes);
			_9$$5 = zephir_fast_in_array(&canonicalMimeType, &_10$$5 TSRMLS_CC);
		}
		if (_9$$5) {
			RETURN_CCTOR(&format);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&mimeTypes);
	ZEPHIR_INIT_NVAR(&format);
	ZEPHIR_MM_RESTORE();

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
			ZEPHIR_RETURN_CALL_FUNCTION("trigger_error", NULL, 101, &e, &_1$$4);
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
	ZEPHIR_CALL_FUNCTION(&_7, "sprintf", NULL, 17, &_6, &_2, &_3, &_5);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CONCAT_VSVV(return_value, &_7, "\n", &_8, &content);
	RETURN_MM();

}

/**
 * Overrides the PHP global variables according to this request instance.
 *
 * It overrides $_GET, $_POST, $_REQUEST, $_SERVER, $_COOKIE.
 * $_FILES is never overridden, see rfc1867
 */
PHP_METHOD(Zim_Http_Request, overrideGlobals) {

	zval _18$$3;
	zend_string *_14;
	zend_ulong _13;
	zval *_GET = NULL, *_POST = NULL, *_SERVER = NULL, *_REQUEST = NULL, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, key, value, _10, _11, *_12, request, requestOrder, _23, _26, _27, order, _31, *_32, _15$$3, _16$$3, _17$$3, _19$$3, _20$$4, _21$$5, _22$$5, _24$$6, _25$$7, _28$$9, _29$$9, _30$$9, _33$$10, _34$$10;
	zend_long ZEPHIR_LAST_CALL_STATUS;
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
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&request);
	ZVAL_UNDEF(&requestOrder);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&order);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_16$$3);
	ZVAL_UNDEF(&_17$$3);
	ZVAL_UNDEF(&_19$$3);
	ZVAL_UNDEF(&_20$$4);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_22$$5);
	ZVAL_UNDEF(&_24$$6);
	ZVAL_UNDEF(&_25$$7);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&_30$$9);
	ZVAL_UNDEF(&_33$$10);
	ZVAL_UNDEF(&_34$$10);
	ZVAL_UNDEF(&_18$$3);

	ZEPHIR_MM_GROW();
	zephir_get_global(&_REQUEST, SL("_REQUEST"));
	zephir_get_global(&_SERVER, SL("_SERVER"));
	zephir_get_global(&_POST, SL("_POST"));
	zephir_get_global(&_GET, SL("_GET"));

	zephir_read_property(&_0, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_2, this_ptr, SL("query"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_3, &_2, "all", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "");
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "&");
	ZEPHIR_CALL_FUNCTION(&_6, "http_build_query", NULL, 100, &_3, &_4, &_5);
	zephir_check_call_status();
	ZEPHIR_CALL_STATIC(&_1, "normalizequerystring", NULL, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_4);
	ZVAL_STRING(&_4, "QUERY_STRING");
	ZEPHIR_CALL_METHOD(NULL, &_0, "set", NULL, 0, &_4, &_1);
	zephir_check_call_status();
	zephir_read_property(&_7, this_ptr, SL("query"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(_GET, &_7, "all", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("request"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(_POST, &_8, "all", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_9, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(_SERVER, &_9, "all", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_10, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_11, &_10, "all", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_11, 0, "zim/http/request.zep", 579);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11), _13, _14, _12)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_14 != NULL) { 
			ZVAL_STR_COPY(&key, _14);
		} else {
			ZVAL_LONG(&key, _13);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _12);
		ZEPHIR_INIT_NVAR(&_15$$3);
		ZEPHIR_INIT_NVAR(&_16$$3);
		ZVAL_STRING(&_16$$3, "-");
		ZEPHIR_INIT_NVAR(&_17$$3);
		ZVAL_STRING(&_17$$3, "_");
		zephir_fast_str_replace(&_15$$3, &_16$$3, &_17$$3, &key TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&key);
		zephir_fast_strtoupper(&key, &_15$$3);
		ZEPHIR_INIT_NVAR(&_18$$3);
		zephir_create_array(&_18$$3, 2, 0 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&_19$$3);
		ZVAL_STRING(&_19$$3, "CONTENT_TYPE");
		zephir_array_fast_append(&_18$$3, &_19$$3);
		ZEPHIR_INIT_NVAR(&_19$$3);
		ZVAL_STRING(&_19$$3, "CONTENT_LENGTH");
		zephir_array_fast_append(&_18$$3, &_19$$3);
		if (zephir_fast_in_array(&key, &_18$$3 TSRMLS_CC)) {
			ZEPHIR_INIT_NVAR(&_20$$4);
			zephir_fast_join_str(&_20$$4, SL(", "), &value TSRMLS_CC);
			zephir_array_update_zval(_SERVER, &key, &_20$$4, PH_COPY | PH_SEPARATE);
		} else {
			ZEPHIR_INIT_NVAR(&_21$$5);
			zephir_fast_join_str(&_21$$5, SL(", "), &value TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_22$$5);
			ZEPHIR_CONCAT_SV(&_22$$5, "HTTP_", &key);
			zephir_array_update_zval(_SERVER, &_22$$5, &_21$$5, PH_COPY | PH_SEPARATE);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	ZEPHIR_INIT_VAR(&request);
	zephir_create_array(&request, 2, 0 TSRMLS_CC);
	zephir_array_update_string(&request, SL("g"), _GET, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&request, SL("p"), _POST, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_4);
	ZVAL_STRING(&_4, "request_order");
	ZEPHIR_CALL_FUNCTION(&_23, "ini_get", NULL, 53, &_4);
	zephir_check_call_status();
	if (!(zephir_is_true(&_23))) {
		ZEPHIR_INIT_VAR(&_24$$6);
		ZVAL_STRING(&_24$$6, "variables_order");
		ZEPHIR_CALL_FUNCTION(&requestOrder, "ini_get", NULL, 53, &_24$$6);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_VAR(&_25$$7);
		ZVAL_STRING(&_25$$7, "request_order");
		ZEPHIR_CALL_FUNCTION(&requestOrder, "ini_get", NULL, 53, &_25$$7);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_NVAR(&_4);
	zephir_fast_strtolower(&_4, &requestOrder);
	ZEPHIR_INIT_NVAR(&_5);
	ZVAL_STRING(&_5, "#[^cgp]#");
	ZEPHIR_INIT_VAR(&_26);
	ZVAL_STRING(&_26, "");
	ZEPHIR_CALL_FUNCTION(&_27, "preg_replace", NULL, 23, &_5, &_26, &_4);
	zephir_check_call_status();
	if (!(zephir_is_true(&_27))) {
		ZEPHIR_INIT_NVAR(&requestOrder);
		ZVAL_STRING(&requestOrder, "gp");
	} else {
		ZEPHIR_INIT_VAR(&_28$$9);
		zephir_fast_strtolower(&_28$$9, &requestOrder);
		ZEPHIR_INIT_VAR(&_29$$9);
		ZVAL_STRING(&_29$$9, "#[^cgp]#");
		ZEPHIR_INIT_VAR(&_30$$9);
		ZVAL_STRING(&_30$$9, "");
		ZEPHIR_CALL_FUNCTION(&requestOrder, "preg_replace", NULL, 23, &_29$$9, &_30$$9, &_28$$9);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_NVAR(_REQUEST);
	zephir_create_array(_REQUEST, 1, 0 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_5);
	array_init(&_5);
	zephir_array_fast_append(_REQUEST, &_5);
	ZEPHIR_CALL_FUNCTION(&_31, "str_split", NULL, 102, &requestOrder);
	zephir_check_call_status();
	zephir_is_iterable(&_31, 0, "zim/http/request.zep", 590);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_31), _32)
	{
		ZEPHIR_INIT_NVAR(&order);
		ZVAL_COPY(&order, _32);
		ZEPHIR_INIT_NVAR(&_33$$10);
		zephir_array_fetch(&_34$$10, &request, &order, PH_NOISY | PH_READONLY, "zim/http/request.zep", 588 TSRMLS_CC);
		zephir_fast_array_merge(&_33$$10, _REQUEST, &_34$$10 TSRMLS_CC);
		ZEPHIR_CPY_WRT(_REQUEST, &_33$$10);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&order);
	ZEPHIR_MM_RESTORE();

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
PHP_METHOD(Zim_Http_Request, enableHttpMethodParameterOverride) {

	zval __$true;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);


	zend_update_static_property(zim_http_request_ce, ZEND_STRL("httpMethodParameterOverride"), &__$true);

}

/**
 * Checks whether support for the _method request parameter is enabled.
 *
 * @return bool True when the _method request parameter is enabled, false otherwise
 */
PHP_METHOD(Zim_Http_Request, getHttpMethodParameterOverride) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_static_property_ce(&_0, zim_http_request_ce, SL("httpMethodParameterOverride"), PH_NOISY_CC | PH_READONLY);
	RETURN_CTORW(&_0);

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
	ZEPHIR_CALL_FUNCTION(NULL, "parse_str", NULL, 97, &qs, &qs);
	ZEPHIR_UNREF(&qs);
	zephir_check_call_status();
	ZEPHIR_MAKE_REF(&qs);
	ZEPHIR_CALL_FUNCTION(NULL, "ksort", NULL, 16, &qs);
	ZEPHIR_UNREF(&qs);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "&");
	ZVAL_LONG(&_2, 2);
	ZEPHIR_RETURN_CALL_FUNCTION("http_build_query", NULL, 100, &qs, &_0, &_1, &_2);
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

	zval host, port, pos, _2, _3, _4, _5, _12, _0$$3, _1$$3, _6$$5, _7$$5, _9$$6, _10$$7, _11$$7;
	zephir_fcall_cache_entry *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&host);
	ZVAL_UNDEF(&port);
	ZVAL_UNDEF(&pos);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_11$$7);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&host, this_ptr, "getforwardedfor", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&host))) {
		zephir_read_property(&_0$$3, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "SERVER_PORT");
		ZEPHIR_CALL_METHOD(&port, &_0$$3, "get", NULL, 0, &_1$$3);
		zephir_check_call_status();
		if (zephir_is_true(&port)) {
			RETURN_CCTOR(&port);
		}
	}
	zephir_read_property(&_2, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "HOST");
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "");
	ZEPHIR_CALL_METHOD(&host, &_2, "get", NULL, 0, &_3, &_4);
	zephir_check_call_status();
	zephir_array_fetch_long(&_5, &host, 0, PH_NOISY | PH_READONLY, "zim/http/request.zep", 734 TSRMLS_CC);
	if (ZEPHIR_IS_LONG_IDENTICAL(&_5, '[')) {
		ZEPHIR_INIT_VAR(&_6$$5);
		ZVAL_STRING(&_6$$5, "]");
		ZEPHIR_CALL_FUNCTION(&_7$$5, "strrpos", &_8, 64, &host, &_6$$5);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_6$$5);
		ZVAL_STRING(&_6$$5, ":");
		ZEPHIR_INIT_VAR(&pos);
		zephir_fast_strpos(&pos, &host, &_6$$5, zephir_get_intval(&_7$$5) );
	} else {
		ZEPHIR_INIT_VAR(&_9$$6);
		ZVAL_STRING(&_9$$6, ":");
		ZEPHIR_CALL_FUNCTION(&pos, "strrpos", &_8, 64, &host, &_9$$6);
		zephir_check_call_status();
	}
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&pos)) {
		ZVAL_LONG(&_10$$7, (zephir_get_numberval(&pos) + 1));
		ZEPHIR_INIT_VAR(&_11$$7);
		zephir_substr(&_11$$7, &host, zephir_get_intval(&_10$$7), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		RETURN_MM_LONG(zephir_get_intval(&_11$$7));
	}
	ZEPHIR_INIT_NVAR(&_3);
	ZEPHIR_CALL_METHOD(&_12, this_ptr, "getscheme", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING_IDENTICAL(&_12, "https")) {
		ZVAL_LONG(&_3, 443);
	} else {
		ZVAL_LONG(&_3, 80);
	}
	RETURN_CCTOR(&_3);

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

	zval qs, _1, _2, _3, _0$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&qs);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
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
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getbaseurl", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getpathinfo", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VVVV(return_value, &_1, &_2, &_3, &qs);
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

	zval host, _7, _8, _9, _10, _0$$3, _1$$3, _2$$4, _3$$4, _4$$5, _5$$5, _6$$5;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&host);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&host, this_ptr, "getforwardedfor", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&host))) {
		zephir_read_property(&_0$$3, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "HOST");
		ZEPHIR_CALL_METHOD(&host, &_0$$3, "get", NULL, 0, &_1$$3);
		zephir_check_call_status();
		if (!(zephir_is_true(&host))) {
			zephir_read_property(&_2$$4, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_3$$4);
			ZVAL_STRING(&_3$$4, "SERVER_NAME");
			ZEPHIR_CALL_METHOD(&host, &_2$$4, "get", NULL, 0, &_3$$4);
			zephir_check_call_status();
			if (!(zephir_is_true(&host))) {
				zephir_read_property(&_4$$5, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_5$$5);
				ZVAL_STRING(&_5$$5, "SERVER_ADDR");
				ZEPHIR_INIT_VAR(&_6$$5);
				ZVAL_STRING(&_6$$5, "");
				ZEPHIR_CALL_METHOD(&host, &_4$$5, "get", NULL, 0, &_5$$5, &_6$$5);
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
	ZEPHIR_CALL_FUNCTION(&_10, "preg_replace", NULL, 23, &_8, &_9, &_7);
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

	zval method, _0, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3, _6$$3, _7$$4, _8$$4, _9$$4, _10$$5, _11$$6, _12$$6, _13$$6, _14$$6, _15$$6, _16$$7;
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
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16$$7);

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
			zephir_read_static_property_ce(&_9$$4, zim_http_request_ce, SL("httpMethodParameterOverride"), PH_NOISY_CC | PH_READONLY);
			if (zephir_is_true(&method)) {
				ZEPHIR_INIT_VAR(&_10$$5);
				zephir_fast_strtoupper(&_10$$5, &method);
				zephir_update_property_zval(this_ptr, SL("method"), &_10$$5);
			} else if (zephir_is_true(&_9$$4)) {
				zephir_read_property(&_11$$6, this_ptr, SL("request"), PH_NOISY_CC | PH_READONLY);
				zephir_read_property(&_12$$6, this_ptr, SL("query"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_INIT_VAR(&_14$$6);
				ZVAL_STRING(&_14$$6, "_method");
				ZEPHIR_INIT_VAR(&_15$$6);
				ZVAL_STRING(&_15$$6, "POST");
				ZEPHIR_CALL_METHOD(&_13$$6, &_12$$6, "get", NULL, 0, &_14$$6, &_15$$6);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_14$$6);
				ZVAL_STRING(&_14$$6, "_method");
				ZEPHIR_CALL_METHOD(&method, &_11$$6, "get", NULL, 0, &_14$$6, &_13$$6);
				zephir_check_call_status();
				if (Z_TYPE_P(&method) == IS_STRING) {
					ZEPHIR_INIT_VAR(&_16$$7);
					zephir_fast_strtoupper(&_16$$7, &method);
					zephir_update_property_zval(this_ptr, SL("method"), &_16$$7);
				}
			}
		}
	}
	RETURN_MM_MEMBER(getThis(), "method");

}

/**
 * Sets the request method.
 *
 * @param string $method
 */
PHP_METHOD(Zim_Http_Request, setMethod) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *method, method_sub, __$null, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &method);



	zephir_update_property_zval(this_ptr, SL("method"), &__$null);
	zephir_read_property(&_0, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "REQUEST_METHOD");
	ZEPHIR_CALL_METHOD(NULL, &_0, "set", NULL, 0, &_1, method);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

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
			ZEPHIR_CALL_FUNCTION(NULL, "rewind", &_2, 103, &_1$$4);
			zephir_check_call_status();
			RETURN_MM_MEMBER(getThis(), "content");
		}
		zephir_read_property(&_3$$3, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_3$$3) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_4$$5);
			ZVAL_STRING(&_4$$5, "php://temp");
			ZEPHIR_INIT_VAR(&_5$$5);
			ZVAL_STRING(&_5$$5, "r+");
			ZEPHIR_CALL_FUNCTION(&resourcee, "fopen", &_6, 104, &_4$$5, &_5$$5);
			zephir_check_call_status();
			zephir_read_property(&_7$$5, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
			zephir_fwrite(NULL, &resourcee, &_7$$5 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(NULL, "rewind", &_2, 103, &resourcee);
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
		ZEPHIR_RETURN_CALL_FUNCTION("fopen", &_6, 104, &_8$$3, &_9$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (zephir_is_true(&currentContentIsResource)) {
		zephir_read_property(&_10$$6, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_FUNCTION(NULL, "rewind", &_2, 103, &_10$$6);
		zephir_check_call_status();
		zephir_read_property(&_11$$6, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_RETURN_CALL_FUNCTION("stream_get_contents", NULL, 105, &_11$$6);
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

	zend_bool _7;
	zval requestUri, uriComponents, _0, _1, _2, _3, _4, _5, _6, _8, _9, _27, _10$$3, _11$$3, _12$$5, _13$$5, _14$$6, _15$$6, _16$$6, _17$$6, _22$$6, _18$$7, _19$$7, _20$$7, _21$$7, _23$$8, _24$$8, _25$$8, _26$$8;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&requestUri);
	ZVAL_UNDEF(&uriComponents);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_22$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&requestUri);
	ZVAL_STRING(&requestUri, "");
	zephir_read_property(&_0, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "REQUEST_URI");
	ZEPHIR_CALL_METHOD(&_1, &_0, "has", NULL, 0, &_2);
	zephir_check_call_status();
	zephir_read_property(&_3, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "ORIG_PATH_INFO");
	ZEPHIR_CALL_METHOD(&_4, &_3, "has", NULL, 0, &_2);
	zephir_check_call_status();
	zephir_read_property(&_5, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "IIS_WasUrlRewritten");
	ZEPHIR_CALL_METHOD(&_6, &_5, "get", NULL, 0, &_2);
	zephir_check_call_status();
	_7 = ZEPHIR_IS_STRING(&_6, "1");
	if (_7) {
		zephir_read_property(&_8, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_STRING(&_2, "UNENCODED_URL");
		ZEPHIR_CALL_METHOD(&_9, &_8, "get", NULL, 0, &_2);
		zephir_check_call_status();
		_7 = !ZEPHIR_IS_STRING(&_9, "");
	}
	if (zephir_is_true(&_1)) {
		zephir_read_property(&_10$$3, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_11$$3);
		ZVAL_STRING(&_11$$3, "REQUEST_URI");
		ZEPHIR_CALL_METHOD(&requestUri, &_10$$3, "get", NULL, 0, &_11$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&uriComponents, "parse_url", NULL, 98, &requestUri);
		zephir_check_call_status();
		if (zephir_array_isset_string(&uriComponents, SL("path"))) {
			ZEPHIR_OBS_NVAR(&requestUri);
			zephir_array_fetch_string(&requestUri, &uriComponents, SL("path"), PH_NOISY, "zim/http/request.zep", 975 TSRMLS_CC);
		}
		if (zephir_array_isset_string(&uriComponents, SL("query"))) {
			zephir_array_fetch_string(&_12$$5, &uriComponents, SL("query"), PH_NOISY | PH_READONLY, "zim/http/request.zep", 979 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_13$$5);
			ZEPHIR_CONCAT_SV(&_13$$5, "?", &_12$$5);
			zephir_concat_self(&requestUri, &_13$$5 TSRMLS_CC);
		}
	} else if (zephir_is_true(&_4)) {
		zephir_read_property(&_14$$6, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_15$$6);
		ZVAL_STRING(&_15$$6, "ORIG_PATH_INFO");
		ZEPHIR_CALL_METHOD(&requestUri, &_14$$6, "get", NULL, 0, &_15$$6);
		zephir_check_call_status();
		zephir_read_property(&_16$$6, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_15$$6);
		ZVAL_STRING(&_15$$6, "QUERY_STRING");
		ZEPHIR_CALL_METHOD(&_17$$6, &_16$$6, "get", NULL, 0, &_15$$6);
		zephir_check_call_status();
		if (!ZEPHIR_IS_STRING(&_17$$6, "")) {
			zephir_read_property(&_18$$7, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_VAR(&_20$$7);
			ZVAL_STRING(&_20$$7, "QUERY_STRING");
			ZEPHIR_CALL_METHOD(&_19$$7, &_18$$7, "get", NULL, 0, &_20$$7);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_21$$7);
			ZEPHIR_CONCAT_SV(&_21$$7, "?", &_19$$7);
			zephir_concat_self(&requestUri, &_21$$7 TSRMLS_CC);
		}
		zephir_read_property(&_22$$6, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_15$$6);
		ZVAL_STRING(&_15$$6, "ORIG_PATH_INFO");
		ZEPHIR_CALL_METHOD(NULL, &_22$$6, "remove", NULL, 0, &_15$$6);
		zephir_check_call_status();
	} else if (_7) {
		zephir_read_property(&_23$$8, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_24$$8);
		ZVAL_STRING(&_24$$8, "UNENCODED_URL");
		ZEPHIR_CALL_METHOD(&requestUri, &_23$$8, "get", NULL, 0, &_24$$8);
		zephir_check_call_status();
		zephir_read_property(&_25$$8, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_24$$8);
		ZVAL_STRING(&_24$$8, "UNENCODED_URL");
		ZEPHIR_CALL_METHOD(NULL, &_25$$8, "remove", NULL, 0, &_24$$8);
		zephir_check_call_status();
		zephir_read_property(&_26$$8, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_24$$8);
		ZVAL_STRING(&_24$$8, "IIS_WasUrlRewritten");
		ZEPHIR_CALL_METHOD(NULL, &_26$$8, "remove", NULL, 0, &_24$$8);
		zephir_check_call_status();
	}
	zephir_read_property(&_27, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "REQUEST_URI");
	ZEPHIR_CALL_METHOD(NULL, &_27, "set", NULL, 0, &_2, &requestUri);
	zephir_check_call_status();
	RETURN_CCTOR(&requestUri);

}

/**
 * Prepares the path info.
 *
 * @return string path info
 */
PHP_METHOD(Zim_Http_Request, preparePathInfo) {

	zval _10;
	zend_bool _3, _9;
	zval requestUri, pos, baseUrl, pathInfo, _0, _4, _5, _6, _8, _1$$4, _2$$4, _7$$5;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&requestUri);
	ZVAL_UNDEF(&pos);
	ZVAL_UNDEF(&baseUrl);
	ZVAL_UNDEF(&pathInfo);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_10);

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
	ZEPHIR_CALL_METHOD(&baseUrl, this_ptr, "getbaseurl", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&baseUrl) == IS_NULL) {
		RETURN_CCTOR(&requestUri);
	}
	ZVAL_LONG(&_8, zephir_fast_strlen_ev(&baseUrl));
	ZEPHIR_INIT_VAR(&pathInfo);
	zephir_substr(&pathInfo, &requestUri, zephir_get_intval(&_8), 0, ZEPHIR_SUBSTR_NO_LENGTH);
	_9 = ZEPHIR_IS_FALSE_IDENTICAL(&pathInfo);
	if (!(_9)) {
		_9 = ZEPHIR_IS_STRING_IDENTICAL(&pathInfo, "");
	}
	if (_9) {
		RETURN_MM_STRING("/");
	}
	zephir_get_strval(&_10, &pathInfo);
	RETURN_CTOR(&_10);

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
PHP_METHOD(Zim_Http_Request, getBasePath) {

	zval _0, _1$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("basePath"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "preparebasepath", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("basePath"), &_1$$3);
	}
	RETURN_MM_MEMBER(getThis(), "basePath");

}

/**
 * Prepares the base path.
 *
 * @return string base path
 */
PHP_METHOD(Zim_Http_Request, prepareBasePath) {

	zval baseUrl, filename, basePath, _0, _1, _2, _3, _7, _4$$6, _5$$6, _6$$6;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&baseUrl);
	ZVAL_UNDEF(&filename);
	ZVAL_UNDEF(&basePath);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&baseUrl, this_ptr, "getbaseurl", NULL, 0);
	zephir_check_call_status();
	if (ZEPHIR_IS_EMPTY(&baseUrl)) {
		RETURN_MM_STRING("");
	}
	zephir_read_property(&_0, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "SCRIPT_FILENAME");
	ZEPHIR_CALL_METHOD(&_1, &_0, "get", NULL, 0, &_2);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&filename);
	zephir_basename(&filename, &_1 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	zephir_basename(&_2, &baseUrl TSRMLS_CC);
	if (ZEPHIR_IS_IDENTICAL(&_2, &filename)) {
		ZEPHIR_CALL_FUNCTION(&basePath, "dirname", NULL, 106, &baseUrl);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&basePath, &baseUrl);
	}
	ZEPHIR_SINIT_VAR(_3);
	ZVAL_STRING(&_3, "\\");
	if (ZEPHIR_IS_STRING_IDENTICAL(&_3, "/")) {
		ZEPHIR_INIT_VAR(&_4$$6);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZVAL_STRING(&_5$$6, "\\");
		ZEPHIR_INIT_VAR(&_6$$6);
		ZVAL_STRING(&_6$$6, "/");
		zephir_fast_str_replace(&_4$$6, &_5$$6, &_6$$6, &basePath TSRMLS_CC);
		ZEPHIR_CPY_WRT(&basePath, &_4$$6);
	}
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, "/");
	zephir_fast_trim(return_value, &basePath, &_7, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	RETURN_MM();

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
PHP_METHOD(Zim_Http_Request, getBaseUrl) {

	zval _0, _1$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("baseUrl"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "preparebaseurl", NULL, 0);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("baseUrl"), &_1$$3);
	}
	RETURN_MM_MEMBER(getThis(), "baseUrl");

}

/**
 * Prepares the base URL.
 *
 * @return string
 */
PHP_METHOD(Zim_Http_Request, prepareBaseUrl) {

	zval _32, _45, _35$$11;
	zend_bool _30, _34, _38, _41, _42, _24$$7, _25$$7;
	zval filename, baseUrl, requestUri, pos, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, prefix, _31, _33, truncatedRequestUri, _36, basename, _39, _40, _12$$3, _13$$3, _14$$4, _15$$4, _16$$5, _17$$5, path$$6, file$$6, segs$$6, last$$6, seg$$6, _18$$6, _19$$6, _20$$6, _21$$6, _22$$6, _23$$7, _26$$9, _27$$9, _28$$9, _37$$12, _43$$14, _44$$14;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, index$$6 = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&filename);
	ZVAL_UNDEF(&baseUrl);
	ZVAL_UNDEF(&requestUri);
	ZVAL_UNDEF(&pos);
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
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&truncatedRequestUri);
	ZVAL_UNDEF(&_36);
	ZVAL_UNDEF(&basename);
	ZVAL_UNDEF(&_39);
	ZVAL_UNDEF(&_40);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&path$$6);
	ZVAL_UNDEF(&file$$6);
	ZVAL_UNDEF(&segs$$6);
	ZVAL_UNDEF(&last$$6);
	ZVAL_UNDEF(&seg$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$6);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_22$$6);
	ZVAL_UNDEF(&_23$$7);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_37$$12);
	ZVAL_UNDEF(&_43$$14);
	ZVAL_UNDEF(&_44$$14);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_45);
	ZVAL_UNDEF(&_35$$11);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "SCRIPT_FILENAME");
	ZEPHIR_CALL_METHOD(&_1, &_0, "get", NULL, 0, &_2);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&filename);
	zephir_basename(&filename, &_1 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_2);
	zephir_read_property(&_3, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "SCRIPT_NAME");
	ZEPHIR_CALL_METHOD(&_4, &_3, "get", NULL, 0, &_5);
	zephir_check_call_status();
	zephir_basename(&_2, &_4 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_5);
	zephir_read_property(&_6, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_8);
	ZVAL_STRING(&_8, "PHP_SELF");
	ZEPHIR_CALL_METHOD(&_7, &_6, "get", NULL, 0, &_8);
	zephir_check_call_status();
	zephir_basename(&_5, &_7 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&_8);
	zephir_read_property(&_9, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_11);
	ZVAL_STRING(&_11, "ORIG_SCRIPT_NAME");
	ZEPHIR_CALL_METHOD(&_10, &_9, "get", NULL, 0, &_11);
	zephir_check_call_status();
	zephir_basename(&_8, &_10 TSRMLS_CC);
	if (ZEPHIR_IS_IDENTICAL(&_2, &filename)) {
		zephir_read_property(&_12$$3, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_13$$3);
		ZVAL_STRING(&_13$$3, "SCRIPT_NAME");
		ZEPHIR_CALL_METHOD(&baseUrl, &_12$$3, "get", NULL, 0, &_13$$3);
		zephir_check_call_status();
	} else if (ZEPHIR_IS_IDENTICAL(&_5, &filename)) {
		zephir_read_property(&_14$$4, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_15$$4);
		ZVAL_STRING(&_15$$4, "PHP_SELF");
		ZEPHIR_CALL_METHOD(&baseUrl, &_14$$4, "get", NULL, 0, &_15$$4);
		zephir_check_call_status();
	} else if (ZEPHIR_IS_IDENTICAL(&_8, &filename)) {
		zephir_read_property(&_16$$5, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_17$$5);
		ZVAL_STRING(&_17$$5, "ORIG_SCRIPT_NAME");
		ZEPHIR_CALL_METHOD(&baseUrl, &_16$$5, "get", NULL, 0, &_17$$5);
		zephir_check_call_status();
	} else {
		zephir_read_property(&_18$$6, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_19$$6);
		ZVAL_STRING(&_19$$6, "PHP_SELF");
		ZEPHIR_INIT_VAR(&_20$$6);
		ZVAL_STRING(&_20$$6, "");
		ZEPHIR_CALL_METHOD(&path$$6, &_18$$6, "get", NULL, 0, &_19$$6, &_20$$6);
		zephir_check_call_status();
		zephir_read_property(&_21$$6, this_ptr, SL("server"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_19$$6);
		ZVAL_STRING(&_19$$6, "SCRIPT_FILENAME");
		ZEPHIR_INIT_NVAR(&_20$$6);
		ZVAL_STRING(&_20$$6, "");
		ZEPHIR_CALL_METHOD(&file$$6, &_21$$6, "get", NULL, 0, &_19$$6, &_20$$6);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_19$$6);
		ZEPHIR_INIT_NVAR(&_20$$6);
		ZVAL_STRING(&_20$$6, "/");
		zephir_fast_trim(&_19$$6, &file$$6, &_20$$6, ZEPHIR_TRIM_BOTH TSRMLS_CC);
		ZEPHIR_INIT_VAR(&segs$$6);
		zephir_fast_explode_str(&segs$$6, SL("/"), &_19$$6, LONG_MAX TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_22$$6, "array_reverse", NULL, 107, &segs$$6);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&segs$$6, &_22$$6);
		index$$6 = 0;
		ZEPHIR_INIT_VAR(&last$$6);
		ZVAL_LONG(&last$$6, zephir_fast_count_int(&segs$$6 TSRMLS_CC));
		ZEPHIR_INIT_NVAR(&baseUrl);
		ZVAL_STRING(&baseUrl, "");
		while (1) {
			ZEPHIR_OBS_NVAR(&seg$$6);
			zephir_array_fetch_long(&seg$$6, &segs$$6, index$$6, PH_NOISY, "zim/http/request.zep", 1133 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_23$$7);
			ZEPHIR_CONCAT_SVV(&_23$$7, "/", &seg$$6, &baseUrl);
			ZEPHIR_CPY_WRT(&baseUrl, &_23$$7);
			index$$6++;
			ZEPHIR_INIT_NVAR(&pos);
			zephir_fast_strpos(&pos, &path$$6, &baseUrl, 0 );
			_24$$7 = ZEPHIR_GT_LONG(&last$$6, index$$6);
			if (_24$$7) {
				_24$$7 = !ZEPHIR_IS_FALSE_IDENTICAL(&pos);
			}
			_25$$7 = _24$$7;
			if (_25$$7) {
				_25$$7 = !ZEPHIR_IS_LONG(&pos, 0);
			}
			if (_25$$7) {
				break;
			}
		}
	}
	ZEPHIR_CALL_METHOD(&requestUri, this_ptr, "getrequesturi", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_STRING_IDENTICAL(&requestUri, "")) {
		ZEPHIR_INIT_VAR(&_26$$9);
		ZEPHIR_INIT_VAR(&_27$$9);
		ZVAL_STRING(&_27$$9, "/");
		zephir_fast_trim(&_26$$9, &requestUri, &_27$$9, ZEPHIR_TRIM_LEFT TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_28$$9);
		ZEPHIR_CONCAT_SV(&_28$$9, "/", &_26$$9);
		ZEPHIR_CPY_WRT(&requestUri, &_28$$9);
	}
	ZEPHIR_CALL_METHOD(&prefix, this_ptr, "geturlencodedprefix", &_29, 108, &requestUri, &baseUrl);
	zephir_check_call_status();
	_30 = zephir_is_true(&baseUrl);
	if (_30) {
		_30 = !ZEPHIR_IS_FALSE_IDENTICAL(&prefix);
	}
	if (_30) {
		RETURN_CCTOR(&prefix);
	}
	ZEPHIR_INIT_NVAR(&_11);
	ZEPHIR_CALL_FUNCTION(&_31, "dirname", NULL, 106, &baseUrl);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_32);
	ZEPHIR_CONCAT_SS(&_32, "/", "/");
	zephir_fast_trim(&_11, &_31, &_32, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_33);
	ZEPHIR_CONCAT_VS(&_33, &_11, "/");
	ZEPHIR_CALL_METHOD(&prefix, this_ptr, "geturlencodedprefix", &_29, 108, &requestUri, &_33);
	zephir_check_call_status();
	_34 = zephir_is_true(&baseUrl);
	if (_34) {
		_34 = !ZEPHIR_IS_FALSE_IDENTICAL(&prefix);
	}
	if (_34) {
		ZEPHIR_INIT_VAR(&_35$$11);
		ZEPHIR_CONCAT_SS(&_35$$11, "/", "/");
		zephir_fast_trim(return_value, &prefix, &_35$$11, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
		RETURN_MM();
	}
	ZEPHIR_CPY_WRT(&truncatedRequestUri, &requestUri);
	ZEPHIR_INIT_VAR(&_36);
	ZVAL_STRING(&_36, "?");
	ZEPHIR_INIT_NVAR(&pos);
	zephir_fast_strpos(&pos, &requestUri, &_36, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&pos)) {
		ZVAL_LONG(&_37$$12, 0);
		ZEPHIR_INIT_NVAR(&truncatedRequestUri);
		zephir_substr(&truncatedRequestUri, &requestUri, 0 , zephir_get_intval(&pos), 0);
	}
	ZEPHIR_INIT_VAR(&basename);
	zephir_basename(&basename, &baseUrl TSRMLS_CC);
	_38 = ZEPHIR_IS_EMPTY(&basename);
	if (!(_38)) {
		ZEPHIR_CALL_FUNCTION(&_39, "rawurldecode", NULL, 109, &truncatedRequestUri);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_40);
		zephir_fast_strpos(&_40, &_39, &basename, 0 );
		_38 = !zephir_is_true(&_40);
	}
	if (_38) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_INIT_NVAR(&pos);
	zephir_fast_strpos(&pos, &requestUri, &baseUrl, 0 );
	_41 = zephir_fast_strlen_ev(&requestUri) >= zephir_fast_strlen_ev(&baseUrl);
	if (_41) {
		_41 = !ZEPHIR_IS_FALSE_IDENTICAL(&pos);
	}
	_42 = _41;
	if (_42) {
		_42 = !ZEPHIR_IS_LONG_IDENTICAL(&pos, 0);
	}
	if (_42) {
		ZVAL_LONG(&_43$$14, 0);
		ZVAL_LONG(&_44$$14, (zephir_get_numberval(&pos) + zephir_fast_strlen_ev(&baseUrl)));
		ZEPHIR_INIT_NVAR(&baseUrl);
		zephir_substr(&baseUrl, &requestUri, 0 , zephir_get_intval(&_44$$14), 0);
	}
	ZEPHIR_INIT_VAR(&_45);
	ZEPHIR_CONCAT_SS(&_45, "/", "/");
	zephir_fast_trim(return_value, &baseUrl, &_45, ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	RETURN_MM();

}

PHP_METHOD(Zim_Http_Request, getUrlencodedPrefix) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *str_param = NULL, *prefix_param = NULL, _0, _1, len, match, _2, _3, _4$$5;
	zval str, prefix;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&str);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&len);
	ZVAL_UNDEF(&match);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &str_param, &prefix_param);

	zephir_get_strval(&str, str_param);
	zephir_get_strval(&prefix, prefix_param);


	if (!(!(Z_TYPE_P(&prefix) == IS_UNDEF) && Z_STRLEN_P(&prefix))) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_CALL_FUNCTION(&_0, "rawurldecode", NULL, 109, &str);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	zephir_fast_strpos(&_1, &_0, &prefix, 0 );
	if (!ZEPHIR_IS_LONG_IDENTICAL(&_1, 0)) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(&len);
	ZVAL_LONG(&len, zephir_fast_strlen_ev(&prefix));
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "#^(%%[[:xdigit:]]{2}|.){%d}#");
	ZEPHIR_CALL_FUNCTION(&_3, "sprintf", NULL, 17, &_2, &len);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_2);
	zephir_preg_match(&_2, &_3, &str, &match, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(&_2)) {
		zephir_array_fetch_long(&_4$$5, &match, 0, PH_NOISY | PH_READONLY, "zim/http/request.zep", 1206 TSRMLS_CC);
		RETURN_CTOR(&_4$$5);
	}
	RETURN_MM_BOOL(0);

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

