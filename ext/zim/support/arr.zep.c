
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
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/string.h"


ZEPHIR_INIT_CLASS(Zim_Support_Arr) {

	ZEPHIR_REGISTER_CLASS(Zim\\Support, Arr, zim, support_arr, zim_support_arr_method_entry, 0);

	return SUCCESS;

}

/**
 * Determine whether the given value is array accessible.
 *
 * @param  mixed  $value
 * @return bool
 */
PHP_METHOD(Zim_Support_Arr, accessible) {

	zend_bool _0, _1;
	zval *value, value_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value_sub);

	zephir_fetch_params(0, 1, 0, &value);



	_0 = Z_TYPE_P(value) == IS_ARRAY;
	if (!(_0)) {
		_1 = Z_TYPE_P(value) == IS_OBJECT;
		if (_1) {
			_1 = zephir_is_instance_of(value, SL("ArrayAccess") TSRMLS_CC);
		}
		_0 = _1;
	}
	RETURN_BOOL(_0);

}

/**
 * Determine if the given key exists in the provided array.
 *
 * @param  \ArrayAccess|array  $array
 * @param  string|int  $key
 * @return bool
 */
PHP_METHOD(Zim_Support_Arr, exists) {

	zend_bool _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *myArray, myArray_sub, *key, key_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&myArray_sub);
	ZVAL_UNDEF(&key_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &myArray, &key);



	_0 = Z_TYPE_P(myArray) == IS_OBJECT;
	if (_0) {
		_0 = zephir_is_instance_of(myArray, SL("ArrayAccess") TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_RETURN_CALL_METHOD(myArray, "offsetexists", NULL, 0, key);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(zephir_array_key_exists(myArray, key TSRMLS_CC));

}

/**
 * Get an item from an array using "dot" notation.
 *
 * @param  \ArrayAccess|array  $array
 * @param  string  $key
 * @param  mixed   $deft
 * @return mixed
 */
PHP_METHOD(Zim_Support_Arr, get) {

	zend_bool _10$$7;
	zephir_fcall_cache_entry *_9 = NULL, *_12 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval key;
	zval *myArray = NULL, myArray_sub, *key_param = NULL, *deft = NULL, deft_sub, __$null, segment, _0, _1, _3, _4, _6, *_7, _2$$5, _5$$6, _8$$7, _11$$7, _13$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&myArray_sub);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&segment);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&key);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &myArray, &key_param, &deft);

	ZEPHIR_SEPARATE_PARAM(myArray);
	zephir_get_strval(&key, key_param);
	if (!deft) {
		deft = &deft_sub;
		deft = &__$null;
	}


	ZEPHIR_CALL_STATIC(&_0, "accessible", NULL, 0, myArray);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		RETVAL_ZVAL(deft, 1, 0);
		RETURN_MM();
	}
	if (Z_TYPE_P(&key) == IS_NULL) {
		RETVAL_ZVAL(myArray, 1, 0);
		RETURN_MM();
	}
	ZEPHIR_CALL_STATIC(&_1, "exists", NULL, 0, myArray, &key);
	zephir_check_call_status();
	if (zephir_is_true(&_1)) {
		zephir_array_fetch(&_2$$5, myArray, &key, PH_NOISY | PH_READONLY, "zim/support/arr.zep", 52 TSRMLS_CC);
		RETURN_CTOR(&_2$$5);
	}
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, ".");
	ZEPHIR_INIT_VAR(&_4);
	zephir_fast_strpos(&_4, &key, &_3, 0 );
	if (ZEPHIR_IS_FALSE_IDENTICAL(&_4)) {
		ZEPHIR_INIT_VAR(&_5$$6);
		if (zephir_array_isset(myArray, &key)) {
			zephir_array_fetch(&_5$$6, myArray, &key, PH_NOISY, "zim/support/arr.zep", 55 TSRMLS_CC);
		} else {
			ZEPHIR_CPY_WRT(&_5$$6, deft);
		}
		RETURN_CCTOR(&_5$$6);
	}
	ZEPHIR_INIT_VAR(&_6);
	zephir_fast_explode_str(&_6, SL("."), &key, LONG_MAX TSRMLS_CC);
	zephir_is_iterable(&_6, 0, "zim/support/arr.zep", 64);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_6), _7)
	{
		ZEPHIR_INIT_NVAR(&segment);
		ZVAL_COPY(&segment, _7);
		ZEPHIR_CALL_STATIC(&_8$$7, "accessible", &_9, 0, myArray);
		zephir_check_call_status();
		_10$$7 = zephir_is_true(&_8$$7);
		if (_10$$7) {
			ZEPHIR_CALL_STATIC(&_11$$7, "exists", &_12, 0, myArray, &segment);
			zephir_check_call_status();
			_10$$7 = zephir_is_true(&_11$$7);
		}
		if (_10$$7) {
			zephir_array_fetch(&_13$$8, myArray, &segment, PH_NOISY | PH_READONLY, "zim/support/arr.zep", 59 TSRMLS_CC);
			ZEPHIR_CPY_WRT(myArray, &_13$$8);
		} else {
			RETVAL_ZVAL(deft, 1, 0);
			RETURN_MM();
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&segment);
	RETVAL_ZVAL(myArray, 1, 0);
	RETURN_MM();

}

/**
 * Check if an item or items exist in an array using "dot" notation.
 *
 * @param  \ArrayAccess|array  $array
 * @param  string|array  $keys
 * @return bool
 */
PHP_METHOD(Zim_Support_Arr, has) {

	zend_bool _8$$8;
	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_3 = NULL, *_7 = NULL;
	zval *myArray, myArray_sub, *keys = NULL, keys_sub, tmpArray40cd750bba9870f18aada2478b24840a, key, subKeyArray, segment, *_1, _2$$6, _4$$6, *_5$$6, _6$$8, _9$$8, _10$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&myArray_sub);
	ZVAL_UNDEF(&keys_sub);
	ZVAL_UNDEF(&tmpArray40cd750bba9870f18aada2478b24840a);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&subKeyArray);
	ZVAL_UNDEF(&segment);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &myArray, &keys);

	ZEPHIR_SEPARATE_PARAM(keys);


	if (Z_TYPE_P(keys) == IS_NULL) {
		RETURN_MM_BOOL(0);
	}
	zephir_get_arrval(&_0, keys);
	ZEPHIR_CPY_WRT(keys, &_0);
	if (!(zephir_is_true(myArray))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_VAR(&tmpArray40cd750bba9870f18aada2478b24840a);
	array_init(&tmpArray40cd750bba9870f18aada2478b24840a);
	if (ZEPHIR_IS_IDENTICAL(keys, &tmpArray40cd750bba9870f18aada2478b24840a)) {
		RETURN_MM_BOOL(0);
	}
	zephir_is_iterable(keys, 0, "zim/support/arr.zep", 102);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(keys), _1)
	{
		ZEPHIR_INIT_NVAR(&key);
		ZVAL_COPY(&key, _1);
		ZEPHIR_CPY_WRT(&subKeyArray, myArray);
		ZEPHIR_CALL_STATIC(&_2$$6, "exists", &_3, 0, myArray, &key);
		zephir_check_call_status();
		if (zephir_is_true(&_2$$6)) {
			continue;
		}
		ZEPHIR_INIT_NVAR(&_4$$6);
		zephir_fast_explode_str(&_4$$6, SL("."), &key, LONG_MAX TSRMLS_CC);
		zephir_is_iterable(&_4$$6, 0, "zim/support/arr.zep", 101);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_4$$6), _5$$6)
		{
			ZEPHIR_INIT_NVAR(&segment);
			ZVAL_COPY(&segment, _5$$6);
			ZEPHIR_CALL_STATIC(&_6$$8, "accessible", &_7, 0, &subKeyArray);
			zephir_check_call_status();
			_8$$8 = zephir_is_true(&_6$$8);
			if (_8$$8) {
				ZEPHIR_CALL_STATIC(&_9$$8, "exists", &_3, 0, &subKeyArray, &segment);
				zephir_check_call_status();
				_8$$8 = zephir_is_true(&_9$$8);
			}
			if (_8$$8) {
				zephir_array_fetch(&_10$$9, &subKeyArray, &segment, PH_NOISY | PH_READONLY, "zim/support/arr.zep", 96 TSRMLS_CC);
				ZEPHIR_CPY_WRT(&subKeyArray, &_10$$9);
			} else {
				RETURN_MM_BOOL(0);
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&segment);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&key);
	RETURN_MM_BOOL(1);

}

/**
 * Set an array item to a given value using "dot" notation.
 *
 * If no key is given to the method, the entire array will be replaced.
 *
 * @param  array   $array
 * @param  string  $key
 * @param  mixed   $value
 * @return array
 */
PHP_METHOD(Zim_Support_Arr, set) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval key;
	zval *myArray_param = NULL, *key_param = NULL, *value, value_sub, ret;
	zval myArray;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&myArray);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&ret);
	ZVAL_UNDEF(&key);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &myArray_param, &key_param, &value);

	zephir_get_arrval(&myArray, myArray_param);
	zephir_get_strval(&key, key_param);


	if (Z_TYPE_P(&key) == IS_NULL) {
		ZEPHIR_CPY_WRT(&myArray, value);
		RETURN_CTOR(&myArray);
	}
	ZEPHIR_CALL_STATIC(&ret, "_parseinistring", NULL, 0, &key, value);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_FUNCTION("array_merge_recursive", NULL, 113, &myArray, &ret);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Zim_Support_Arr, _parseIniString) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path_param = NULL, *value = NULL, value_sub, pos, key, _0, _1, _2, _3, _4;
	zval path;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&pos);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &path_param, &value);

	zephir_get_strval(&path, path_param);
	ZEPHIR_SEPARATE_PARAM(value);


	ZEPHIR_CALL_STATIC(&_0, "_cast", NULL, 0, value);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(value, &_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, ".");
	ZEPHIR_INIT_VAR(&pos);
	zephir_fast_strpos(&pos, &path, &_1, 0 );
	if (ZEPHIR_IS_FALSE_IDENTICAL(&pos)) {
		zephir_create_array(return_value, 1, 0 TSRMLS_CC);
		zephir_array_update_zval(return_value, &path, value, PH_COPY);
		RETURN_MM();
	}
	ZVAL_LONG(&_2, 0);
	ZEPHIR_INIT_VAR(&key);
	zephir_substr(&key, &path, 0 , zephir_get_intval(&pos), 0);
	ZVAL_LONG(&_3, (zephir_get_numberval(&pos) + 1));
	ZEPHIR_INIT_VAR(&_4);
	zephir_substr(&_4, &path, zephir_get_intval(&_3), 0, ZEPHIR_SUBSTR_NO_LENGTH);
	zephir_get_strval(&path, &_4);
	zephir_create_array(return_value, 1, 0 TSRMLS_CC);
	ZEPHIR_CALL_STATIC(&_0, "_parseinistring", NULL, 0, &path, value);
	zephir_check_call_status();
	zephir_array_update_zval(return_value, &key, &_0, PH_COPY);
	RETURN_MM();

}

PHP_METHOD(Zim_Support_Arr, _cast) {

	zend_string *_2$$3;
	zend_ulong _1$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_4 = NULL;
	zval *ini, ini_sub, key, val, *_0$$3, _3$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ini_sub);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&val);
	ZVAL_UNDEF(&_3$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &ini);

	ZEPHIR_SEPARATE_PARAM(ini);


	if (Z_TYPE_P(ini) == IS_ARRAY) {
		zephir_is_iterable(ini, 1, "zim/support/arr.zep", 149);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(ini), _1$$3, _2$$3, _0$$3)
		{
			ZEPHIR_INIT_NVAR(&key);
			if (_2$$3 != NULL) { 
				ZVAL_STR_COPY(&key, _2$$3);
			} else {
				ZVAL_LONG(&key, _1$$3);
			}
			ZEPHIR_INIT_NVAR(&val);
			ZVAL_COPY(&val, _0$$3);
			ZEPHIR_CALL_STATIC(&_3$$4, "_cast", &_4, 0, &val);
			zephir_check_call_status();
			zephir_array_update_zval(ini, &key, &_3$$4, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&val);
		ZEPHIR_INIT_NVAR(&key);
	}
	RETVAL_ZVAL(ini, 1, 0);
	RETURN_MM();

}

