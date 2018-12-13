
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
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/array.h"


/**
 * File Config.php
 * @henter
 * Time: 2018-11-26 16:50
 *
 */
ZEPHIR_INIT_CLASS(Zim_Config_Config) {

	ZEPHIR_REGISTER_CLASS(Zim\\Config, Config, zim, config_config, zim_config_config_method_entry, 0);

	/**
	 * All of the configuration items.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_config_config_ce, SL("items"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_config_config_ce->create_object = zephir_init_properties_Zim_Config_Config;

	zend_class_implements(zim_config_config_ce TSRMLS_CC, 1, zend_ce_arrayaccess);
	zend_class_implements(zim_config_config_ce TSRMLS_CC, 1, zim_contract_config_ce);
	return SUCCESS;

}

/**
 * Create a new configuration repository.
 *
 * @param  array  $items
 * @return void
 */
PHP_METHOD(Zim_Config_Config, __construct) {

	zval *items_param = NULL;
	zval items;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&items);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &items_param);

	if (!items_param) {
		ZEPHIR_INIT_VAR(&items);
		array_init(&items);
	} else {
		zephir_get_arrval(&items, items_param);
	}


	zephir_update_property_zval(this_ptr, SL("items"), &items);
	ZEPHIR_MM_RESTORE();

}

/**
 * Determine if the given configuration value exists.
 *
 * @param  string  $key
 * @return bool
 */
PHP_METHOD(Zim_Config_Config, has) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *key_param = NULL, _1;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(&key, key_param);


	zephir_read_property(&_1, this_ptr, SL("items"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_CE_STATIC(zim_support_arr_ce, "has", &_0, 0, &_1, &key);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Get the specified configuration value.
 *
 * @param  array|string  $key
 * @param  mixed   $deft
 * @return mixed
 */
PHP_METHOD(Zim_Config_Config, get) {

	zephir_fcall_cache_entry *_0 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key, key_sub, *deft = NULL, deft_sub, __$null, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_sub);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &key, &deft);

	if (!deft) {
		deft = &deft_sub;
		deft = &__$null;
	}


	if (Z_TYPE_P(key) == IS_ARRAY) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getmany", NULL, 0, key);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_read_property(&_1, this_ptr, SL("items"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_CE_STATIC(zim_support_arr_ce, "get", &_0, 0, &_1, key, deft);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Get many configuration values.
 *
 * @param  array  $keys
 * @return array
 */
PHP_METHOD(Zim_Config_Config, getMany) {

	zend_string *_2;
	zend_ulong _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_4 = NULL;
	zval *keys_param = NULL, config, key, deft, *_0, _3$$3, _5$$3;
	zval keys;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&keys);
	ZVAL_UNDEF(&config);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&deft);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &keys_param);

	zephir_get_arrval(&keys, keys_param);


	ZEPHIR_INIT_VAR(&config);
	array_init(&config);
	zephir_is_iterable(&keys, 0, "zim/config/config.zep", 76);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&keys), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&key, _2);
		} else {
			ZVAL_LONG(&key, _1);
		}
		ZEPHIR_INIT_NVAR(&deft);
		ZVAL_COPY(&deft, _0);
		if (zephir_is_numeric(&key)) {
			ZEPHIR_CPY_WRT(&key, &deft);
			ZEPHIR_INIT_NVAR(&deft);
			ZVAL_NULL(&deft);
		}
		zephir_read_property(&_5$$3, this_ptr, SL("items"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_CE_STATIC(&_3$$3, zim_support_arr_ce, "get", &_4, 0, &_5$$3, &key, &deft);
		zephir_check_call_status();
		zephir_array_update_zval(&config, &key, &_3$$3, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&deft);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_CCTOR(&config);

}

/**
 * Set a given configuration value.
 *
 * @param  array|string  $key
 * @param  mixed   $value
 * @return void
 */
PHP_METHOD(Zim_Config_Config, set) {

	zend_string *_2;
	zend_ulong _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_4 = NULL;
	zval *key = NULL, key_sub, *value = NULL, value_sub, __$null, keys, *_0, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_sub);
	ZVAL_UNDEF(&value_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&keys);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &key, &value);

	ZEPHIR_SEPARATE_PARAM(key);
	if (!value) {
		value = &value_sub;
		ZEPHIR_CPY_WRT(value, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(value);
	}


	if (Z_TYPE_P(key) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&keys, key);
	} else {
		ZEPHIR_INIT_NVAR(&keys);
		zephir_create_array(&keys, 1, 0 TSRMLS_CC);
		zephir_array_update_zval(&keys, key, value, PH_COPY);
	}
	zephir_is_iterable(&keys, 0, "zim/config/config.zep", 94);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&keys), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(key);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(key, _2);
		} else {
			ZVAL_LONG(key, _1);
		}
		ZEPHIR_INIT_NVAR(value);
		ZVAL_COPY(value, _0);
		zephir_read_property(&_5$$3, this_ptr, SL("items"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_CE_STATIC(&_3$$3, zim_support_arr_ce, "set", &_4, 0, &_5$$3, key, value);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("items"), &_3$$3);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(value);
	ZEPHIR_INIT_NVAR(key);
	ZEPHIR_MM_RESTORE();

}

/**
 * Prepend a value onto an array configuration value.
 *
 * @param  string  $key
 * @param  mixed  $value
 * @return void
 */
PHP_METHOD(Zim_Config_Config, prepend) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *value, value_sub, myArray;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&myArray);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &value);

	zephir_get_strval(&key, key_param);


	ZEPHIR_CALL_METHOD(&myArray, this_ptr, "get", NULL, 0, &key);
	zephir_check_call_status();
	ZEPHIR_MAKE_REF(&myArray);
	ZEPHIR_CALL_FUNCTION(NULL, "array_unshift", NULL, 29, &myArray, value);
	ZEPHIR_UNREF(&myArray);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", NULL, 0, &key, &myArray);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Push a value onto an array configuration value.
 *
 * @param  string  $key
 * @param  mixed  $value
 * @return void
 */
PHP_METHOD(Zim_Config_Config, push) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *value, value_sub, myArray;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&myArray);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &value);

	zephir_get_strval(&key, key_param);


	ZEPHIR_CALL_METHOD(&myArray, this_ptr, "get", NULL, 0, &key);
	zephir_check_call_status();
	zephir_array_append(&myArray, value, PH_SEPARATE, "zim/config/config.zep", 124);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", NULL, 0, &key, &myArray);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Get all of the configuration items for the application.
 *
 * @return array
 */
PHP_METHOD(Zim_Config_Config, all) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "items");

}

/**
 * Determine if the given configuration option exists.
 *
 * @param  string  $key
 * @return bool
 */
PHP_METHOD(Zim_Config_Config, offsetExists) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(&key, key_param);


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "has", NULL, 0, &key);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Get a configuration option.
 *
 * @param  string  $key
 * @return mixed
 */
PHP_METHOD(Zim_Config_Config, offsetGet) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(&key, key_param);


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "get", NULL, 0, &key);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Set a configuration option.
 *
 * @param  string  $key
 * @param  mixed  $value
 * @return void
 */
PHP_METHOD(Zim_Config_Config, offsetSet) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *value, value_sub;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &value);

	zephir_get_strval(&key, key_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", NULL, 0, &key, value);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Unset a configuration option.
 *
 * @param  string  $key
 * @return void
 */
PHP_METHOD(Zim_Config_Config, offsetUnset) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(&key, key_param);


	ZVAL_NULL(&_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "set", NULL, 0, &key, &_0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

zend_object *zephir_init_properties_Zim_Config_Config(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _1$$3;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("items"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("items"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

