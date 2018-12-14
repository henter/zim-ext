
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
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "kernel/time.h"
#include "ext/date/php_date.h"


/**
 * ResponseHeaderBag is a container for Response HTTP headers.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
ZEPHIR_INIT_CLASS(Zim_Http_ResponseHeaderBag) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Http, ResponseHeaderBag, zim, http_responseheaderbag, zim_http_headerbag_ce, zim_http_responseheaderbag_method_entry, 0);

	zend_declare_property_null(zim_http_responseheaderbag_ce, SL("computedCacheControl"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_http_responseheaderbag_ce, SL("headerNames"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_http_responseheaderbag_ce->create_object = zephir_init_properties_Zim_Http_ResponseHeaderBag;
	return SUCCESS;

}

PHP_METHOD(Zim_Http_ResponseHeaderBag, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *headers_param = NULL, _1, _2, _3;
	zval headers;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &headers_param);

	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}


	ZEPHIR_CALL_PARENT(NULL, zim_http_responseheaderbag_ce, getThis(), "__construct", &_0, 0, &headers);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Cache-Control");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", NULL, 0, &_1, &_2);
	zephir_check_call_status();
	zephir_read_property(&_3, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_string(&_3, SL("date")))) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "initdate", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the headers, with original capitalizations.
 *
 * @return array An array of headers
 */
PHP_METHOD(Zim_Http_ResponseHeaderBag, allPreserveCase) {

	zend_string *_3;
	zend_ulong _2;
	zval headers, name, value, _0, *_1, _4$$3, _5$$3, _6$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&headers);
	array_init(&headers);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "all", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_0, 0, "zim/http/responseheaderbag.zep", 43);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_0), _2, _3, _1)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_3 != NULL) { 
			ZVAL_STR_COPY(&name, _3);
		} else {
			ZVAL_LONG(&name, _2);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _1);
		ZEPHIR_INIT_LNVAR(_4$$3);
		zephir_read_property(&_5$$3, this_ptr, SL("headerNames"), PH_NOISY_CC | PH_READONLY);
		if (zephir_array_isset(&_5$$3, &name)) {
			zephir_read_property(&_6$$3, this_ptr, SL("headerNames"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_4$$3);
			zephir_array_fetch(&_4$$3, &_6$$3, &name, PH_NOISY, "zim/http/responseheaderbag.zep", 41 TSRMLS_CC);
		} else {
			ZEPHIR_CPY_WRT(&_4$$3, &name);
		}
		zephir_array_update_zval(&headers, &_4$$3, &value, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_CCTOR(&headers);

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Zim_Http_ResponseHeaderBag, replace) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *headers_param = NULL, _0, _2, _5, _3$$3, _4$$3;
	zval headers;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

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
	zephir_update_property_zval(this_ptr, SL("headerNames"), &_0);
	ZEPHIR_CALL_PARENT(NULL, zim_http_responseheaderbag_ce, getThis(), "replace", &_1, 0, &headers);
	zephir_check_call_status();
	zephir_read_property(&_2, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_string(&_2, SL("cache-control")))) {
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "Cache-Control");
		ZEPHIR_INIT_VAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", NULL, 0, &_3$$3, &_4$$3);
		zephir_check_call_status();
	}
	zephir_read_property(&_5, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_string(&_5, SL("date")))) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "initdate", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Zim_Http_ResponseHeaderBag, set) {

	zval _6$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_3 = NULL;
	zval *key, key_sub, *values, values_sub, *replace = NULL, replace_sub, __$true, uniqueKey, tmpArrayd0d6087f950982817b4a268511aa1623, computed, _0, _1, _2, _4, _5, _7$$3, _8$$3, _9$$3, _10$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_sub);
	ZVAL_UNDEF(&values_sub);
	ZVAL_UNDEF(&replace_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&uniqueKey);
	ZVAL_UNDEF(&tmpArrayd0d6087f950982817b4a268511aa1623);
	ZVAL_UNDEF(&computed);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &key, &values, &replace);

	if (!replace) {
		replace = &replace_sub;
		replace = &__$true;
	}


	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_strtolower(&_0, key);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "_");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "-");
	ZEPHIR_INIT_VAR(&uniqueKey);
	zephir_fast_str_replace(&uniqueKey, &_1, &_2, &_0 TSRMLS_CC);
	zephir_update_property_array(this_ptr, SL("headerNames"), &uniqueKey, key TSRMLS_CC);
	ZEPHIR_CALL_PARENT(NULL, zim_http_responseheaderbag_ce, getThis(), "set", &_3, 0, key, values, replace);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&tmpArrayd0d6087f950982817b4a268511aa1623);
	zephir_create_array(&tmpArrayd0d6087f950982817b4a268511aa1623, 4, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "cache-control");
	zephir_array_fast_append(&tmpArrayd0d6087f950982817b4a268511aa1623, &_4);
	ZEPHIR_INIT_NVAR(&_4);
	ZVAL_STRING(&_4, "etag");
	zephir_array_fast_append(&tmpArrayd0d6087f950982817b4a268511aa1623, &_4);
	ZEPHIR_INIT_NVAR(&_4);
	ZVAL_STRING(&_4, "last-modified");
	zephir_array_fast_append(&tmpArrayd0d6087f950982817b4a268511aa1623, &_4);
	ZEPHIR_INIT_NVAR(&_4);
	ZVAL_STRING(&_4, "expires");
	zephir_array_fast_append(&tmpArrayd0d6087f950982817b4a268511aa1623, &_4);
	ZEPHIR_CALL_FUNCTION(&_5, "in_array", NULL, 82, &uniqueKey, &tmpArrayd0d6087f950982817b4a268511aa1623, &__$true);
	zephir_check_call_status();
	if (zephir_is_true(&_5)) {
		ZEPHIR_CALL_METHOD(&computed, this_ptr, "computecachecontrolvalue", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_6$$3);
		zephir_create_array(&_6$$3, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&_6$$3, &computed);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZVAL_STRING(&_7$$3, "cache-control");
		zephir_update_property_array(this_ptr, SL("headers"), &_7$$3, &_6$$3 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_8$$3);
		ZVAL_STRING(&_8$$3, "cache-control");
		ZEPHIR_INIT_VAR(&_9$$3);
		ZVAL_STRING(&_9$$3, "Cache-Control");
		zephir_update_property_array(this_ptr, SL("headerNames"), &_8$$3, &_9$$3 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_10$$3, this_ptr, "parsecachecontrol", NULL, 0, &computed);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("computedCacheControl"), &_10$$3);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * {@inheritdoc}
 */
PHP_METHOD(Zim_Http_ResponseHeaderBag, remove) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_4 = NULL;
	zval *key, key_sub, uniqueKey, _0, _1, _2, _3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_sub);
	ZVAL_UNDEF(&uniqueKey);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key);



	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_strtolower(&_0, key);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "_");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "-");
	ZEPHIR_INIT_VAR(&uniqueKey);
	zephir_fast_str_replace(&uniqueKey, &_1, &_2, &_0 TSRMLS_CC);
	zephir_read_property(&_3, this_ptr, SL("headerNames"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_3, &uniqueKey, PH_SEPARATE);
	ZEPHIR_CALL_PARENT(NULL, zim_http_responseheaderbag_ce, getThis(), "remove", &_4, 0, key);
	zephir_check_call_status();
	if (ZEPHIR_IS_STRING_IDENTICAL(&uniqueKey, "cache-control")) {
		ZEPHIR_INIT_VAR(&_5$$3);
		array_init(&_5$$3);
		zephir_update_property_zval(this_ptr, SL("computedCacheControl"), &_5$$3);
	}
	if (ZEPHIR_IS_STRING_IDENTICAL(&uniqueKey, "date")) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "initdate", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the calculated value of the cache-control header.
 *
 * This considers several other headers and calculates or modifies the
 * cache-control header to a sensible, conservative value.
 *
 * @return string
 */
PHP_METHOD(Zim_Http_ResponseHeaderBag, computeCacheControlValue) {

	zend_bool _1, _4, _6, _10;
	zval header, _0, _2, _3, _5, _7, _8, _9, _11, _12;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&header);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("cacheControl"), PH_NOISY_CC);
	_1 = !zephir_is_true(&_0);
	if (_1) {
		ZEPHIR_INIT_VAR(&_3);
		ZVAL_STRING(&_3, "ETag");
		ZEPHIR_CALL_METHOD(&_2, this_ptr, "has", NULL, 0, &_3);
		zephir_check_call_status();
		_1 = !zephir_is_true(&_2);
	}
	_4 = _1;
	if (_4) {
		ZEPHIR_INIT_NVAR(&_3);
		ZVAL_STRING(&_3, "Last-Modified");
		ZEPHIR_CALL_METHOD(&_5, this_ptr, "has", NULL, 0, &_3);
		zephir_check_call_status();
		_4 = !zephir_is_true(&_5);
	}
	_6 = _4;
	if (_6) {
		ZEPHIR_INIT_NVAR(&_3);
		ZVAL_STRING(&_3, "Expires");
		ZEPHIR_CALL_METHOD(&_7, this_ptr, "has", NULL, 0, &_3);
		zephir_check_call_status();
		_6 = !zephir_is_true(&_7);
	}
	if (_6) {
		RETURN_MM_STRING("no-cache, private");
	}
	zephir_read_property(&_8, this_ptr, SL("cacheControl"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_8))) {
		RETURN_MM_STRING("private, must-revalidate");
	}
	ZEPHIR_CALL_METHOD(&header, this_ptr, "getcachecontrolheader", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_9, this_ptr, SL("cacheControl"), PH_NOISY_CC | PH_READONLY);
	_10 = zephir_array_isset_string(&_9, SL("public"));
	if (!(_10)) {
		zephir_read_property(&_11, this_ptr, SL("cacheControl"), PH_NOISY_CC | PH_READONLY);
		_10 = zephir_array_isset_string(&_11, SL("private"));
	}
	if (_10) {
		RETURN_CCTOR(&header);
	}
	zephir_read_property(&_12, this_ptr, SL("cacheControl"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_string(&_12, SL("s-maxage")))) {
		ZEPHIR_CONCAT_VS(return_value, &header, ", private");
		RETURN_MM();
	}
	RETURN_CCTOR(&header);

}

PHP_METHOD(Zim_Http_ResponseHeaderBag, initDate) {

	zend_class_entry *_0;
	zval now, _1, _2, _3, _4, _5;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&now);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_class_str_ex(SL("DateTime"), ZEND_FETCH_CLASS_AUTO);
	ZEPHIR_INIT_VAR(&_1);
	zephir_time(&_1);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "U");
	ZEPHIR_CALL_CE_STATIC(&now, _0, "createfromformat", NULL, 0, &_2, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_2);
	object_init_ex(&_2, php_date_get_timezone_ce());
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "UTC");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &now, "settimezone", NULL, 0, &_2);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_STRING(&_3, "D, d M Y H:i:s");
	ZEPHIR_CALL_METHOD(&_4, &now, "format", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_VS(&_5, &_4, " GMT");
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_STRING(&_3, "Date");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", NULL, 0, &_3, &_5);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

zend_object *zephir_init_properties_Zim_Http_ResponseHeaderBag(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _2, _4, _6, _1$$3, _3$$4, _5$$5, _7$$6;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("headerNames"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("headerNames"), &_1$$3);
		}
		zephir_read_property(&_2, this_ptr, SL("cacheControl"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval(this_ptr, SL("cacheControl"), &_3$$4);
		}
		zephir_read_property(&_4, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval(this_ptr, SL("headers"), &_5$$5);
		}
		zephir_read_property(&_6, this_ptr, SL("computedCacheControl"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval(this_ptr, SL("computedCacheControl"), &_7$$6);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

