
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
#include "ext/spl/spl_iterators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "kernel/string.h"


/**
 * HeaderBag is a container for HTTP headers.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
ZEPHIR_INIT_CLASS(Zim_Http_HeaderBag) {

	ZEPHIR_REGISTER_CLASS(Zim\\Http, HeaderBag, zim, http_headerbag, zim_http_headerbag_method_entry, 0);

	zend_declare_property_null(zim_http_headerbag_ce, SL("headers"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_http_headerbag_ce, SL("cacheControl"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_http_headerbag_ce->create_object = zephir_init_properties_Zim_Http_HeaderBag;

	zend_class_implements(zim_http_headerbag_ce TSRMLS_CC, 1, zend_ce_aggregate);
	zend_class_implements(zim_http_headerbag_ce TSRMLS_CC, 1, spl_ce_Countable);
	return SUCCESS;

}

/**
 * @param array $headers An array of HTTP headers
 */
PHP_METHOD(Zim_Http_HeaderBag, __construct) {

	zend_string *_2;
	zend_ulong _1;
	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *headers_param = NULL, key, values, *_0;
	zval headers;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&values);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &headers_param);

	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}


	zephir_is_iterable(&headers, 0, "zim/http/headerbag.zep", 30);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&headers), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&key, _2);
		} else {
			ZVAL_LONG(&key, _1);
		}
		ZEPHIR_INIT_NVAR(&values);
		ZVAL_COPY(&values, _0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", &_3, 0, &key, &values);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&values);
	ZEPHIR_INIT_NVAR(&key);
	ZEPHIR_MM_RESTORE();

}

/**
 * Parses a Cache-Control HTTP header.
 *
 * @param string $header The value of the Cache-Control HTTP header
 *
 * @return array An array representing the attribute values
 */
PHP_METHOD(Zim_Http_HeaderBag, parseCacheControl) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL, *_2 = NULL;
	zval *header_param = NULL, parts, _1;
	zval header;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&header);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &header_param);

	zephir_get_strval(&header, header_param);


	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, ",=");
	ZEPHIR_CALL_CE_STATIC(&parts, zim_http_headerutils_ce, "split", &_0, 0, &header, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(zim_http_headerutils_ce, "combine", &_2, 0, &parts);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Zim_Http_HeaderBag, getCacheControlHeader) {

	zval _0, _2, _3;
	zephir_fcall_cache_entry *_1 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("cacheControl"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_MAKE_REF(&_0);
	ZEPHIR_CALL_FUNCTION(NULL, "ksort", NULL, 14, &_0);
	ZEPHIR_UNREF(&_0);
	zephir_check_call_status();
	zephir_read_property(&_2, this_ptr, SL("cacheControl"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, ",");
	ZEPHIR_RETURN_CALL_CE_STATIC(zim_http_headerutils_ce, "tostring", &_1, 0, &_2, &_3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the headers as a string.
 *
 * @return string The headers
 */
PHP_METHOD(Zim_Http_HeaderBag, __toString) {

	zend_string *_2;
	zend_ulong _1;
	zval headers, content, name, values, value, *_0, _3$$4, _4$$4, *_6$$4, _7$$5;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_7$$5);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&headers, this_ptr, "all", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&headers))) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_MAKE_REF(&headers);
	ZEPHIR_CALL_FUNCTION(NULL, "ksort", NULL, 14, &headers);
	ZEPHIR_UNREF(&headers);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&content);
	ZVAL_STRING(&content, "");
	zephir_is_iterable(&headers, 0, "zim/http/headerbag.zep", 74);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&headers), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&name, _2);
		} else {
			ZVAL_LONG(&name, _1);
		}
		ZEPHIR_INIT_NVAR(&values);
		ZVAL_COPY(&values, _0);
		ZEPHIR_INIT_NVAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "-");
		ZEPHIR_CALL_FUNCTION(&_4$$4, "ucwords", &_5, 15, &name, &_3$$4);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&name, &_4$$4);
		zephir_is_iterable(&values, 0, "zim/http/headerbag.zep", 73);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&values), _6$$4)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6$$4);
			ZEPHIR_INIT_LNVAR(_7$$5);
			ZEPHIR_CONCAT_VVSVS(&_7$$5, &content, &name, ":", &value, "\r\n");
			ZEPHIR_CPY_WRT(&content, &_7$$5);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&value);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&values);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_CCTOR(&content);

}

/**
 * Returns the headers.
 *
 * @return array An array of headers
 */
PHP_METHOD(Zim_Http_HeaderBag, all) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "headers");

}

/**
 * Returns the parameter keys.
 *
 * @return array An array of parameter keys
 */
PHP_METHOD(Zim_Http_HeaderBag, keys) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "all", NULL, 0);
	zephir_check_call_status();
	zephir_array_keys(return_value, &_0 TSRMLS_CC);
	RETURN_MM();

}

/**
 * Replaces the current HTTP headers by a new set.
 *
 * @param array $headers An array of HTTP headers
 */
PHP_METHOD(Zim_Http_HeaderBag, replace) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *headers_param = NULL, _0;
	zval headers;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &headers_param);

	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("headers"), &_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "add", NULL, 0, &headers);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Adds new headers the current HTTP headers set.
 *
 * @param array $headers An array of HTTP headers
 */
PHP_METHOD(Zim_Http_HeaderBag, add) {

	zend_string *_2;
	zend_ulong _1;
	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *headers_param = NULL, key, values, *_0;
	zval headers;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&values);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &headers_param);

	zephir_get_arrval(&headers, headers_param);


	zephir_is_iterable(&headers, 0, "zim/http/headerbag.zep", 120);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&headers), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&key, _2);
		} else {
			ZVAL_LONG(&key, _1);
		}
		ZEPHIR_INIT_NVAR(&values);
		ZVAL_COPY(&values, _0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", &_3, 0, &key, &values);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&values);
	ZEPHIR_INIT_NVAR(&key);
	ZEPHIR_MM_RESTORE();

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
PHP_METHOD(Zim_Http_HeaderBag, get) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool first;
	zval *key_param = NULL, *deft = NULL, deft_sub, *first_param = NULL, __$null, headers, _0, _1, _2, _8, _3$$4, _4$$3, _5$$5, _6$$5, _7$$5;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &key_param, &deft, &first_param);

	zephir_get_strval(&key, key_param);
	if (!deft) {
		deft = &deft_sub;
		deft = &__$null;
	}
	if (!first_param) {
		first = 1;
	} else {
		first = zephir_get_boolval(first_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_strtolower(&_0, &key);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "_");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "-");
	ZEPHIR_INIT_NVAR(&key);
	zephir_fast_str_replace(&key, &_1, &_2, &_0 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&headers, this_ptr, "all", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_array_key_exists(&headers, &key TSRMLS_CC))) {
		if (Z_TYPE_P(deft) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			if (first) {
				ZVAL_NULL(&_3$$4);
			} else {
				array_init(&_3$$4);
			}
			RETURN_CCTOR(&_3$$4);
		}
		ZEPHIR_INIT_VAR(&_4$$3);
		if (first) {
			ZEPHIR_CPY_WRT(&_4$$3, deft);
		} else {
			zephir_create_array(&_4$$3, 1, 0 TSRMLS_CC);
			zephir_array_fast_append(&_4$$3, deft);
		}
		RETURN_CCTOR(&_4$$3);
	}
	if (first) {
		ZEPHIR_INIT_VAR(&_5$$5);
		zephir_array_fetch(&_6$$5, &headers, &key, PH_NOISY | PH_READONLY, "zim/http/headerbag.zep", 144 TSRMLS_CC);
		if (zephir_fast_count_int(&_6$$5 TSRMLS_CC)) {
			zephir_array_fetch(&_7$$5, &headers, &key, PH_NOISY | PH_READONLY, "zim/http/headerbag.zep", 144 TSRMLS_CC);
			zephir_array_fetch_long(&_5$$5, &_7$$5, 0, PH_NOISY, "zim/http/headerbag.zep", 144 TSRMLS_CC);
		} else {
			ZEPHIR_CPY_WRT(&_5$$5, deft);
		}
		RETURN_CCTOR(&_5$$5);
	}
	zephir_array_fetch(&_8, &headers, &key, PH_NOISY | PH_READONLY, "zim/http/headerbag.zep", 146 TSRMLS_CC);
	RETURN_CTOR(&_8);

}

/**
 * Sets a header by name.
 *
 * @param string          $key     The key
 * @param string|string[] $values  The value or an array of values
 * @param bool            $replace Whether to replace the actual value or not (true by default)
 */
PHP_METHOD(Zim_Http_HeaderBag, set) {

	zval _11$$7;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool replace, _4$$3, _9$$6;
	zval *key_param = NULL, *values = NULL, values_sub, *replace_param = NULL, _0, _1, _2, _3$$3, _5$$3, _6$$5, _7$$5, _8$$5, _10$$6;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&values_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$7);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &key_param, &values, &replace_param);

	zephir_get_strval(&key, key_param);
	ZEPHIR_SEPARATE_PARAM(values);
	if (!replace_param) {
		replace = 1;
	} else {
		replace = zephir_get_boolval(replace_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_strtolower(&_0, &key);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "_");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "-");
	ZEPHIR_INIT_NVAR(&key);
	zephir_fast_str_replace(&key, &_1, &_2, &_0 TSRMLS_CC);
	if (Z_TYPE_P(values) == IS_ARRAY) {
		ZEPHIR_CALL_FUNCTION(&_3$$3, "array_values", NULL, 16, values);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(values, &_3$$3);
		_4$$3 = replace == 1;
		if (!(_4$$3)) {
			zephir_read_property(&_5$$3, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
			_4$$3 = !((zephir_array_isset(&_5$$3, &key)));
		}
		if (_4$$3) {
			zephir_update_property_array(this_ptr, SL("headers"), &key, values TSRMLS_CC);
		} else {
			ZEPHIR_INIT_VAR(&_6$$5);
			zephir_read_property(&_7$$5, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_8$$5, &_7$$5, &key, PH_NOISY | PH_READONLY, "zim/http/headerbag.zep", 164 TSRMLS_CC);
			zephir_fast_array_merge(&_6$$5, &_8$$5, values TSRMLS_CC);
			zephir_update_property_array(this_ptr, SL("headers"), &key, &_6$$5 TSRMLS_CC);
		}
	} else {
		_9$$6 = replace == 1;
		if (!(_9$$6)) {
			zephir_read_property(&_10$$6, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
			_9$$6 = !((zephir_array_isset(&_10$$6, &key)));
		}
		if (_9$$6) {
			ZEPHIR_INIT_VAR(&_11$$7);
			zephir_create_array(&_11$$7, 1, 0 TSRMLS_CC);
			zephir_array_fast_append(&_11$$7, values);
			zephir_update_property_array(this_ptr, SL("headers"), &key, &_11$$7 TSRMLS_CC);
		} else {
			zephir_update_property_array_multi(this_ptr, SL("headers"), values TSRMLS_CC, SL("za"), 2, &key);
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns true if the HTTP header is defined.
 *
 * @param string $key The HTTP header
 *
 * @return bool true if the parameter exists, false otherwise
 */
PHP_METHOD(Zim_Http_HeaderBag, has) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, _0, _1, _2, _3, _4;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(&key, key_param);


	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	zephir_fast_strtolower(&_1, &key);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "_");
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "-");
	zephir_fast_str_replace(&_0, &_2, &_3, &_1 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "all", NULL, 0);
	zephir_check_call_status();
	RETURN_MM_BOOL(zephir_array_key_exists(&_4, &_0 TSRMLS_CC));

}

/**
 * Returns true if the given HTTP header contains the given value.
 *
 * @param string $key   The HTTP header name
 * @param string $value The HTTP value
 *
 * @return bool true if the value is contained in the header, false otherwise
 */
PHP_METHOD(Zim_Http_HeaderBag, contains) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *value_param = NULL, _0, _1, _2;
	zval key, value;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &value_param);

	zephir_get_strval(&key, key_param);
	zephir_get_strval(&value, value_param);


	ZVAL_NULL(&_1);
	ZVAL_BOOL(&_2, 0);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "get", NULL, 0, &key, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM_BOOL(zephir_fast_in_array(&value, &_0 TSRMLS_CC));

}

/**
 * Removes a header.
 *
 * @param string $key The HTTP header name
 */
PHP_METHOD(Zim_Http_HeaderBag, remove) {

	zval *key_param = NULL, _0, _1, _2, _3;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(&key, key_param);


	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_strtolower(&_0, &key);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "_");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "-");
	ZEPHIR_INIT_NVAR(&key);
	zephir_fast_str_replace(&key, &_1, &_2, &_0 TSRMLS_CC);
	zephir_read_property(&_3, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_3, &key, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns an iterator for headers.
 *
 * @return \ArrayIterator An \ArrayIterator instance
 */
PHP_METHOD(Zim_Http_HeaderBag, getIterator) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, zephir_get_internal_ce(SL("arrayiterator")));
	zephir_read_property(&_0, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 17, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the number of headers.
 *
 * @return int The number of headers
 */
PHP_METHOD(Zim_Http_HeaderBag, count) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	RETURN_LONG(zephir_fast_count_int(&_0 TSRMLS_CC));

}

zend_object *zephir_init_properties_Zim_Http_HeaderBag(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _2, _1$$3, _3$$4;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("cacheControl"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("cacheControl"), &_1$$3);
		}
		zephir_read_property(&_2, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval(this_ptr, SL("headers"), &_3$$4);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

