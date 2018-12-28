
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
#include "ext/spl/spl_array.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/object.h"


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
ZEPHIR_INIT_CLASS(Zim_Http_JsonResponse) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Http, JsonResponse, zim, http_jsonresponse, zim_http_response_ce, zim_http_jsonresponse_method_entry, 0);

	zend_declare_property_null(zim_http_jsonresponse_ce, SL("data"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_http_jsonresponse_ce, SL("callback"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(zim_http_jsonresponse_ce, SL("encodingOptions"), 15, ZEND_ACC_PROTECTED TSRMLS_CC);

	zephir_declare_class_constant_long(zim_http_jsonresponse_ce, SL("DEFAULT_ENCODING_OPTIONS"), 15);

	zephir_declare_class_constant_long(zim_http_jsonresponse_ce, SL("JSON_PARTIAL_OUTPUT_ON_ERROR"), 512);

	zephir_declare_class_constant_long(zim_http_jsonresponse_ce, SL("JSON_ERROR_RECURSION"), 6);

	zephir_declare_class_constant_long(zim_http_jsonresponse_ce, SL("JSON_ERROR_INF_OR_NAN"), 7);

	zephir_declare_class_constant_long(zim_http_jsonresponse_ce, SL("JSON_ERROR_UNSUPPORTED_TYPE"), 8);

	return SUCCESS;

}

/**
 * @param mixed $data    The response data
 * @param int   $status  The response status code
 * @param array $headers An array of response headers
 * @param bool  $json    If the data is already a JSON string
 */
PHP_METHOD(Zim_Http_JsonResponse, __construct) {

	zephir_fcall_cache_entry *_0 = NULL;
	zend_bool json;
	zval headers;
	zend_long status, ZEPHIR_LAST_CALL_STATUS;
	zval *data = NULL, data_sub, *status_param = NULL, *headers_param = NULL, *json_param = NULL, __$null, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&headers);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 4, &data, &status_param, &headers_param, &json_param);

	if (!data) {
		data = &data_sub;
		ZEPHIR_CPY_WRT(data, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(data);
	}
	if (!status_param) {
		status = 200;
	} else {
		status = zephir_get_intval(status_param);
	}
	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}
	if (!json_param) {
		json = 0;
	} else {
		json = zephir_get_boolval(json_param);
	}


	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "");
	ZVAL_LONG(&_2, status);
	ZEPHIR_CALL_PARENT(NULL, zim_http_jsonresponse_ce, getThis(), "__construct", &_0, 0, &_1, &_2, &headers);
	zephir_check_call_status();
	if (Z_TYPE_P(data) == IS_NULL) {
		ZEPHIR_INIT_NVAR(data);
		object_init_ex(data, spl_ce_ArrayObject);
		ZEPHIR_CALL_METHOD(NULL, data, "__construct", NULL, 52);
		zephir_check_call_status();
	}
	if (json) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setjson", NULL, 0, data);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setdata", NULL, 0, data);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

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
PHP_METHOD(Zim_Http_JsonResponse, create) {

	zval headers;
	zend_long status, ZEPHIR_LAST_CALL_STATUS;
	zval *data = NULL, data_sub, *status_param = NULL, *headers_param = NULL, __$null, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&headers);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 3, &data, &status_param, &headers_param);

	if (!data) {
		data = &data_sub;
		data = &__$null;
	}
	if (!status_param) {
		status = 200;
	} else {
		status = zephir_get_intval(status_param);
	}
	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}


	object_init_ex(return_value, zim_http_jsonresponse_ce);
	ZVAL_LONG(&_0, status);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 78, data, &_0, &headers);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Make easier the creation of JsonResponse from raw json.
 */
PHP_METHOD(Zim_Http_JsonResponse, fromJsonString) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data = NULL, data_sub, *status = NULL, status_sub, *headers = NULL, headers_sub, __$null, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&status_sub);
	ZVAL_UNDEF(&headers_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 3, &data, &status, &headers);

	if (!data) {
		data = &data_sub;
		data = &__$null;
	}
	if (!status) {
		status = &status_sub;
		ZEPHIR_INIT_VAR(status);
		ZVAL_LONG(status, 200);
	}
	if (!headers) {
		headers = &headers_sub;
		ZEPHIR_INIT_VAR(headers);
		array_init(headers);
	}


	object_init_ex(return_value, zim_http_jsonresponse_ce);
	ZVAL_BOOL(&_0, 1);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 78, data, status, headers, &_0);
	zephir_check_call_status();
	RETURN_MM();

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
PHP_METHOD(Zim_Http_JsonResponse, setCallback) {

	zend_bool _4$$4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_6 = NULL;
	zval *callback = NULL, callback_sub, __$true, __$null, pattern, reserved, parts, part, _0$$3, *_1$$3, _2$$4, _3$$4, _5$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&pattern);
	ZVAL_UNDEF(&reserved);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&part);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &callback);

	if (!callback) {
		callback = &callback_sub;
		callback = &__$null;
	}


	if (Z_TYPE_P(callback) != IS_NULL) {
		ZEPHIR_INIT_VAR(&pattern);
		ZVAL_STRING(&pattern, "/^[$_\\p{L}][$_\\p{L}\\p{Mn}\\p{Mc}\\p{Nd}\\p{Pc}\\x{200C}\\x{200D}]*(?:\\[(?:\"(?:\\\\.|[^\"\\\\])*\"|'(?:\\\\.|[^'\\\\])*'|\\d+)\\])*?$/u");
		ZEPHIR_INIT_VAR(&reserved);
		zephir_create_array(&reserved, 47, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "break");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "do");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "instanceof");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "typeof");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "case");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "else");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "new");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "var");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "catch");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "finally");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "return");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "void");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "continue");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "for");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "switch");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "while");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "debugger");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "function");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "this");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "with");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "default");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "if");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "throw");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "delete");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "in");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "try");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "class");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "enum");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "extends");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "super");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "const");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "export");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "import");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "implements");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "let");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "private");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "public");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "yield");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "interface");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "package");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "protected");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "static");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "null");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "true");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_NVAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "false");
		zephir_array_fast_append(&reserved, &_0$$3);
		ZEPHIR_INIT_VAR(&parts);
		zephir_fast_explode_str(&parts, SL("."), callback, LONG_MAX TSRMLS_CC);
		zephir_is_iterable(&parts, 0, "zim/http/jsonresponse.zep", 112);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&parts), _1$$3)
		{
			ZEPHIR_INIT_NVAR(&part);
			ZVAL_COPY(&part, _1$$3);
			ZEPHIR_INIT_NVAR(&_2$$4);
			ZEPHIR_INIT_NVAR(&_3$$4);
			zephir_preg_match(&_3$$4, &pattern, &part, &_2$$4, 0, 0 , 0  TSRMLS_CC);
			_4$$4 = !zephir_is_true(&_3$$4);
			if (!(_4$$4)) {
				ZEPHIR_CALL_FUNCTION(&_5$$4, "in_array", &_6, 79, &part, &reserved, &__$true);
				zephir_check_call_status();
				_4$$4 = zephir_is_true(&_5$$4);
			}
			if (_4$$4) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "The callback name is not valid.", "zim/http/jsonresponse.zep", 109);
				return;
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&part);
	}
	zephir_update_property_zval(this_ptr, SL("callback"), callback);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "update", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

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
PHP_METHOD(Zim_Http_JsonResponse, setJson) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *json_param = NULL;
	zval json;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&json);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &json_param);

	zephir_get_strval(&json, json_param);


	zephir_update_property_zval(this_ptr, SL("data"), &json);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "update", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Get the json_decoded data from the response.
 *
 * @param  bool  $assoc
 * @param  int  $depth
 * @return mixed
 */
PHP_METHOD(Zim_Http_JsonResponse, getData) {

	zend_long depth;
	zval *assoc_param = NULL, *depth_param = NULL, _0, _1, _2;
	zend_bool assoc;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	zephir_fetch_params(0, 0, 2, &assoc_param, &depth_param);

	if (!assoc_param) {
		assoc = 1;
	} else {
		assoc = zephir_get_boolval(assoc_param);
	}
	if (!depth_param) {
		depth = 512;
	} else {
		depth = zephir_get_intval(depth_param);
	}


	zephir_read_property(&_0, this_ptr, SL("data"), PH_NOISY_CC | PH_READONLY);
	ZVAL_BOOL(&_1, (assoc ? 1 : 0));
	ZVAL_LONG(&_2, depth);
	zephir_json_decode(return_value, &_0, zephir_get_intval(&_1) );
	return;

}

/**
 * @param array $data
 * @return self
 */
PHP_METHOD(Zim_Http_JsonResponse, setData) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *data = NULL, data_sub, _0$$4, _1$$4, _2$$5, _3$$5, _4$$5, _5$$6, _6$$6, _7$$6, _8$$7, _9$$7, _10$$8, _11$$8, _12, _13, _14$$9, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&data_sub);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_15$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &data);

	if (!data) {
		data = &data_sub;
		ZEPHIR_INIT_VAR(data);
		array_init(data);
	}


	if (Z_TYPE_P(data) == IS_OBJECT) {
		if (zephir_instance_of_ev(data, zim_contract_jsonable_ce TSRMLS_CC)) {
			zephir_read_property(&_1$$4, this_ptr, SL("encodingOptions"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(&_0$$4, data, "tojson", NULL, 0, &_1$$4);
			zephir_check_call_status();
			zephir_update_property_zval(this_ptr, SL("data"), &_0$$4);
		} else if (zephir_is_instance_of(data, SL("JsonSerializable") TSRMLS_CC)) {
			ZEPHIR_INIT_VAR(&_2$$5);
			ZEPHIR_CALL_METHOD(&_3$$5, data, "jsonserialize", NULL, 0);
			zephir_check_call_status();
			zephir_read_property(&_4$$5, this_ptr, SL("encodingOptions"), PH_NOISY_CC | PH_READONLY);
			zephir_json_encode(&_2$$5, &_3$$5, zephir_get_intval(&_4$$5) );
			zephir_update_property_zval(this_ptr, SL("data"), &_2$$5);
		} else if (zephir_instance_of_ev(data, zim_contract_arrayable_ce TSRMLS_CC)) {
			ZEPHIR_INIT_VAR(&_5$$6);
			ZEPHIR_CALL_METHOD(&_6$$6, data, "toarray", NULL, 0);
			zephir_check_call_status();
			zephir_read_property(&_7$$6, this_ptr, SL("encodingOptions"), PH_NOISY_CC | PH_READONLY);
			zephir_json_encode(&_5$$6, &_6$$6, zephir_get_intval(&_7$$6) );
			zephir_update_property_zval(this_ptr, SL("data"), &_5$$6);
		} else {
			ZEPHIR_INIT_VAR(&_8$$7);
			zephir_read_property(&_9$$7, this_ptr, SL("encodingOptions"), PH_NOISY_CC | PH_READONLY);
			zephir_json_encode(&_8$$7, data, zephir_get_intval(&_9$$7) );
			zephir_update_property_zval(this_ptr, SL("data"), &_8$$7);
		}
	} else {
		ZEPHIR_INIT_VAR(&_10$$8);
		zephir_read_property(&_11$$8, this_ptr, SL("encodingOptions"), PH_NOISY_CC | PH_READONLY);
		zephir_json_encode(&_10$$8, data, zephir_get_intval(&_11$$8) );
		zephir_update_property_zval(this_ptr, SL("data"), &_10$$8);
	}
	ZEPHIR_CALL_FUNCTION(&_13, "json_last_error", NULL, 80);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_12, this_ptr, "hasvalidjson", NULL, 0, &_13);
	zephir_check_call_status();
	if (!(zephir_is_true(&_12))) {
		ZEPHIR_INIT_VAR(&_14$$9);
		object_init_ex(&_14$$9, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_FUNCTION(&_15$$9, "json_last_error_msg", NULL, 81);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_14$$9, "__construct", NULL, 32, &_15$$9);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_14$$9, "zim/http/jsonresponse.zep", 165 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "update", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Determine if an error occurred during JSON encoding.
 *
 * @param  int  $jsonError
 * @return bool
 */
PHP_METHOD(Zim_Http_JsonResponse, hasValidJson) {

	zval _3;
	zend_bool _2;
	zval *jsonError_param = NULL, _0, _1, _4;
	zend_long jsonError, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &jsonError_param);

	jsonError = zephir_get_intval(jsonError_param);


	if (jsonError == 0) {
		RETURN_MM_BOOL(1);
	}
	ZVAL_LONG(&_1, 512);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "hasencodingoption", NULL, 0, &_1);
	zephir_check_call_status();
	_2 = zephir_is_true(&_0);
	if (_2) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_create_array(&_3, 3, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4);
		ZVAL_LONG(&_4, 6);
		zephir_array_fast_append(&_3, &_4);
		ZEPHIR_INIT_NVAR(&_4);
		ZVAL_LONG(&_4, 7);
		zephir_array_fast_append(&_3, &_4);
		ZEPHIR_INIT_NVAR(&_4);
		ZVAL_LONG(&_4, 8);
		zephir_array_fast_append(&_3, &_4);
		ZVAL_LONG(&_1, jsonError);
		_2 = zephir_fast_in_array(&_1, &_3 TSRMLS_CC);
	}
	RETURN_MM_BOOL(_2);

}

/**
 * Determine if a JSON encoding option is set.
 *
 * @param  int  $option
 * @return bool
 */
PHP_METHOD(Zim_Http_JsonResponse, hasEncodingOption) {

	zval *option_param = NULL, _0;
	zend_long option;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &option_param);

	option = zephir_get_intval(option_param);


	zephir_read_property(&_0, this_ptr, SL("encodingOptions"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL((zend_bool) (((int) (zephir_get_numberval(&_0)) & option)));

}

/**
 * Returns options used while encoding data to JSON.
 *
 * @return int
 */
PHP_METHOD(Zim_Http_JsonResponse, getEncodingOptions) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "encodingOptions");

}

/**
 * Sets options used while encoding data to JSON.
 *
 * @param int $encodingOptions
 *
 * @return $this
 */
PHP_METHOD(Zim_Http_JsonResponse, setEncodingOptions) {

	zval *encodingOptions_param = NULL, _0, _1;
	zend_long encodingOptions, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &encodingOptions_param);

	encodingOptions = zephir_get_intval(encodingOptions_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, encodingOptions);
	zephir_update_property_zval(this_ptr, SL("encodingOptions"), &_0);
	ZEPHIR_INIT_VAR(&_1);
	zephir_read_property(&_0, this_ptr, SL("data"), PH_NOISY_CC | PH_READONLY);
	zephir_json_decode(&_1, &_0, 0 );
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "setdata", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Updates the content and headers according to the JSON data and callback.
 *
 * @return $this
 */
PHP_METHOD(Zim_Http_JsonResponse, update) {

	zend_bool _10;
	zval _0, _7, _8, _9, _11, _12, _16, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3, _6$$3, _13$$4, _14$$4, _15$$4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("callback"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) != IS_NULL) {
		zephir_read_property(&_1$$3, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "Content-Type");
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "text/javascript");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "set", NULL, 0, &_2$$3, &_3$$3);
		zephir_check_call_status();
		zephir_read_property(&_4$$3, this_ptr, SL("callback"), PH_NOISY_CC | PH_READONLY);
		zephir_read_property(&_5$$3, this_ptr, SL("data"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "/**/%s(%s);");
		ZEPHIR_CALL_FUNCTION(&_6$$3, "sprintf", NULL, 17, &_2$$3, &_4$$3, &_5$$3);
		zephir_check_call_status();
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "setcontent", NULL, 0, &_6$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_read_property(&_7, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_9);
	ZVAL_STRING(&_9, "Content-Type");
	ZEPHIR_CALL_METHOD(&_8, &_7, "has", NULL, 0, &_9);
	zephir_check_call_status();
	_10 = !zephir_is_true(&_8);
	if (!(_10)) {
		zephir_read_property(&_11, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_9);
		ZVAL_STRING(&_9, "Content-Type");
		ZEPHIR_CALL_METHOD(&_12, &_11, "get", NULL, 0, &_9);
		zephir_check_call_status();
		_10 = ZEPHIR_IS_STRING_IDENTICAL(&_12, "text/javascript");
	}
	if (_10) {
		zephir_read_property(&_13$$4, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_14$$4);
		ZVAL_STRING(&_14$$4, "Content-Type");
		ZEPHIR_INIT_VAR(&_15$$4);
		ZVAL_STRING(&_15$$4, "application/json");
		ZEPHIR_CALL_METHOD(NULL, &_13$$4, "set", NULL, 0, &_14$$4, &_15$$4);
		zephir_check_call_status();
	}
	zephir_read_property(&_16, this_ptr, SL("data"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "setcontent", NULL, 0, &_16);
	zephir_check_call_status();
	RETURN_MM();

}

