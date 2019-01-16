
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
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/string.h"


/**
 * ParameterBag is a container for key/value pairs.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
ZEPHIR_INIT_CLASS(Zim_Http_ParameterBag) {

	ZEPHIR_REGISTER_CLASS(Zim\\Http, ParameterBag, zim, http_parameterbag, zim_http_parameterbag_method_entry, 0);

	/**
	 * Parameter storage.
	 */
	zend_declare_property_null(zim_http_parameterbag_ce, SL("parameters"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_http_parameterbag_ce->create_object = zephir_init_properties_Zim_Http_ParameterBag;

	zend_class_implements(zim_http_parameterbag_ce TSRMLS_CC, 1, zend_ce_aggregate);
	zend_class_implements(zim_http_parameterbag_ce TSRMLS_CC, 1, spl_ce_Countable);
	return SUCCESS;

}

/**
 * @param array $parameters An array of parameters
 */
PHP_METHOD(Zim_Http_ParameterBag, __construct) {

	zval *parameters_param = NULL;
	zval parameters;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &parameters_param);

	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}


	zephir_update_property_zval(this_ptr, SL("parameters"), &parameters);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the parameters.
 *
 * @return array An array of parameters
 */
PHP_METHOD(Zim_Http_ParameterBag, all) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "parameters");

}

/**
 * Returns the parameter keys.
 *
 * @return array An array of parameter keys
 */
PHP_METHOD(Zim_Http_ParameterBag, keys) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	zephir_array_keys(return_value, &_0 TSRMLS_CC);
	return;

}

/**
 * Replaces the current parameters by a new set.
 *
 * @param array $parameters An array of parameters
 */
PHP_METHOD(Zim_Http_ParameterBag, replace) {

	zval *parameters_param = NULL;
	zval parameters;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &parameters_param);

	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}


	zephir_update_property_zval(this_ptr, SL("parameters"), &parameters);
	ZEPHIR_MM_RESTORE();

}

/**
 * Adds parameters.
 *
 * @param array $parameters An array of parameters
 */
PHP_METHOD(Zim_Http_ParameterBag, add) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameters_param = NULL, _0, _1;
	zval parameters;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &parameters_param);

	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}


	zephir_read_property(&_0, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_1, "array_replace", NULL, 22, &_0, &parameters);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("parameters"), &_1);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns a parameter by name.
 *
 * @param string $key     The key
 * @param mixed  $default The default value if the parameter key does not exist
 *
 * @return mixed
 */
PHP_METHOD(Zim_Http_ParameterBag, get) {

	zval *key_param = NULL, *deft = NULL, deft_sub, __$null, _0, _1, _2;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_NULL(&__$null);
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


	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_key_exists(&_1, &key TSRMLS_CC)) {
		zephir_read_property(&_2, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_0, &_2, &key, PH_NOISY, "/Users/henter/Dev/zim/zim/http/parameterbag.zep", 72 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(&_0, deft);
	}
	RETURN_CCTOR(&_0);

}

/**
 * Sets a parameter by name.
 *
 * @param string $key   The key
 * @param mixed  $value The value
 */
PHP_METHOD(Zim_Http_ParameterBag, set) {

	zval *key_param = NULL, *value, value_sub;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &value);

	zephir_get_strval(&key, key_param);


	zephir_update_property_array(this_ptr, SL("parameters"), &key, value TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns true if the parameter is defined.
 *
 * @param string $key The key
 *
 * @return bool true if the parameter exists, false otherwise
 */
PHP_METHOD(Zim_Http_ParameterBag, has) {

	zval *key_param = NULL, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(&key, key_param);


	zephir_read_property(&_0, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	RETURN_MM_BOOL(zephir_array_key_exists(&_0, &key TSRMLS_CC));

}

/**
 * Removes a parameter.
 *
 * @param string $key The key
 */
PHP_METHOD(Zim_Http_ParameterBag, remove) {

	zval *key_param = NULL, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(&key, key_param);


	zephir_read_property(&_0, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, &key, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the alphabetic characters of the parameter value.
 *
 * @param string $key     The parameter key
 * @param string $default The default value if the parameter key does not exist
 *
 * @return string The filtered value
 */
PHP_METHOD(Zim_Http_ParameterBag, getAlpha) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *deft = NULL, deft_sub, _0, _1, _2;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &key_param, &deft);

	zephir_get_strval(&key, key_param);
	if (!deft) {
		deft = &deft_sub;
		ZEPHIR_INIT_VAR(deft);
		ZVAL_STRING(deft, "");
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "get", NULL, 0, &key, deft);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "/[^[:alpha:]]/");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "");
	ZEPHIR_RETURN_CALL_FUNCTION("preg_replace", NULL, 23, &_1, &_2, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the alphabetic characters and digits of the parameter value.
 *
 * @param string $key     The parameter key
 * @param string $default The default value if the parameter key does not exist
 *
 * @return string The filtered value
 */
PHP_METHOD(Zim_Http_ParameterBag, getAlnum) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *deft = NULL, deft_sub, _0, _1, _2;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &key_param, &deft);

	zephir_get_strval(&key, key_param);
	if (!deft) {
		deft = &deft_sub;
		ZEPHIR_INIT_VAR(deft);
		ZVAL_STRING(deft, "");
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "get", NULL, 0, &key, deft);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "/[^[:alnum:]]/");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "");
	ZEPHIR_RETURN_CALL_FUNCTION("preg_replace", NULL, 23, &_1, &_2, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the digits of the parameter value.
 *
 * @param string $key     The parameter key
 * @param string $default The default value if the parameter key does not exist
 *
 * @return string The filtered value
 */
PHP_METHOD(Zim_Http_ParameterBag, getDigits) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *deft = NULL, deft_sub, _1, _2, _3, _4;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &key_param, &deft);

	zephir_get_strval(&key, key_param);
	if (!deft) {
		deft = &deft_sub;
		ZEPHIR_INIT_VAR(deft);
		ZVAL_STRING(deft, "");
	}


	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 2, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "-");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "+");
	zephir_array_fast_append(&_0, &_1);
	ZVAL_LONG(&_3, 519);
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "filter", NULL, 0, &key, deft, &_3);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "");
	ZEPHIR_INIT_VAR(&_4);
	zephir_fast_str_replace(&_4, &_0, &_1, &_2 TSRMLS_CC);
	RETURN_CCTOR(&_4);

}

/**
 * Returns the parameter value converted to integer.
 *
 * @param string $key     The parameter key
 * @param int    $default The default value if the parameter key does not exist
 *
 * @return int The filtered value
 */
PHP_METHOD(Zim_Http_ParameterBag, getInt) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *deft = NULL, deft_sub, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &key_param, &deft);

	zephir_get_strval(&key, key_param);
	if (!deft) {
		deft = &deft_sub;
		ZEPHIR_INIT_VAR(deft);
		ZVAL_LONG(deft, 0);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "get", NULL, 0, &key, deft);
	zephir_check_call_status();
	RETURN_MM_LONG(zephir_get_intval(&_0));

}

/**
 * Returns the parameter value converted to boolean.
 *
 * @param string $key     The parameter key
 * @param bool   $default The default value if the parameter key does not exist
 *
 * @return bool The filtered value
 */
PHP_METHOD(Zim_Http_ParameterBag, getBoolean) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *deft = NULL, deft_sub, __$false, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &key_param, &deft);

	zephir_get_strval(&key, key_param);
	if (!deft) {
		deft = &deft_sub;
		deft = &__$false;
	}


	ZVAL_LONG(&_0, 258);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "filter", NULL, 0, &key, deft, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Filter key.
 *
 * @param string $key     Key
 * @param mixed  $default Default = null
 * @param int    $filter  FILTER_* constant
 * @param mixed  $options Filter options
 *
 * @see http://php.net/manual/en/function.filter-var.php
 *
 * @return mixed
 */
PHP_METHOD(Zim_Http_ParameterBag, filter) {

	zend_bool _0, _1;
	zend_long filter, ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *deft = NULL, deft_sub, *filter_param = NULL, *options = NULL, options_sub, __$null, value, ops, _3, ops$$4, _2$$5;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_UNDEF(&options_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&ops);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&ops$$4);
	ZVAL_UNDEF(&_2$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 3, &key_param, &deft, &filter_param, &options);

	zephir_get_strval(&key, key_param);
	if (!deft) {
		deft = &deft_sub;
		deft = &__$null;
	}
	if (!filter_param) {
		filter = -1;
	} else {
		filter = zephir_get_intval(filter_param);
	}
	if (!options) {
		options = &options_sub;
		ZEPHIR_INIT_VAR(options);
		array_init(options);
	}


	if (filter == -1) {
		filter = 516;
	}
	ZEPHIR_CALL_METHOD(&value, this_ptr, "get", NULL, 0, &key, deft);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&ops, options);
	_0 = !(Z_TYPE_P(&ops) == IS_ARRAY);
	if (_0) {
		_0 = zephir_is_true(&ops);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&ops$$4);
		zephir_create_array(&ops$$4, 1, 0 TSRMLS_CC);
		zephir_array_update_string(&ops$$4, SL("flags"), &ops$$4, PH_COPY | PH_SEPARATE);
	}
	_1 = Z_TYPE_P(&value) == IS_ARRAY;
	if (_1) {
		_1 = !(zephir_array_isset_string(&ops, SL("flags")));
	}
	if (_1) {
		ZEPHIR_INIT_VAR(&_2$$5);
		ZVAL_LONG(&_2$$5, 16777216);
		zephir_array_update_string(&ops, SL("flags"), &_2$$5, PH_COPY | PH_SEPARATE);
	}
	ZVAL_LONG(&_3, filter);
	ZEPHIR_RETURN_CALL_FUNCTION("filter_var", NULL, 24, &value, &_3, &ops);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns an iterator for parameters.
 *
 * @return \ArrayIterator An \ArrayIterator instance
 */
PHP_METHOD(Zim_Http_ParameterBag, getIterator) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, zephir_get_internal_ce(SL("arrayiterator")));
	zephir_read_property(&_0, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 21, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the number of parameters.
 *
 * @return int The number of parameters
 */
PHP_METHOD(Zim_Http_ParameterBag, count) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	RETURN_LONG(zephir_fast_count_int(&_0 TSRMLS_CC));

}

zend_object *zephir_init_properties_Zim_Http_ParameterBag(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _1$$3;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("parameters"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

