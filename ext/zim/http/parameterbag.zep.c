
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
	ZEPHIR_CALL_FUNCTION(&_1, "array_replace", NULL, 19, &_0, &parameters);
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
		zephir_array_fetch(&_0, &_2, &key, PH_NOISY, "zim/http/parameterbag.zep", 72 TSRMLS_CC);
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
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 18, &_0);
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

