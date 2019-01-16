
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
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/concat.h"
#include "kernel/string.h"


/**
 * File Controller.php
 * @henter
 * Time: 2018-11-24 20:07
 *
 */
ZEPHIR_INIT_CLASS(Zim_Http_Controller) {

	ZEPHIR_REGISTER_CLASS(Zim\\Http, Controller, zim, http_controller, zim_http_controller_method_entry, 0);

	zend_declare_property_null(zim_http_controller_ce, SL("method"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(zim_http_controller_ce, SL("actions"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_http_controller_ce->create_object = zephir_init_properties_Zim_Http_Controller;
	return SUCCESS;

}

PHP_METHOD(Zim_Http_Controller, __get) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *name_param = NULL, _0, _2, _3$$3;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	ZEPHIR_CALL_CE_STATIC(&_0, zim_zim_ce, "getinstance", &_1, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, &_0, "has", NULL, 0, &name);
	zephir_check_call_status();
	if (zephir_is_true(&_2)) {
		ZEPHIR_CALL_CE_STATIC(&_3$$3, zim_zim_ce, "getinstance", &_1, 0);
		zephir_check_call_status();
		ZEPHIR_RETURN_CALL_METHOD(&_3$$3, "make", NULL, 0, &name);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_NULL();

}

PHP_METHOD(Zim_Http_Controller, app) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *name_param = NULL, _0;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	ZEPHIR_CALL_CE_STATIC(&_0, zim_zim_ce, "getinstance", &_1, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "make", NULL, 0, &name);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Zim_Http_Controller, bind) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *name_param = NULL, *value, value_sub, _0;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(&name, name_param);


	ZEPHIR_CALL_CE_STATIC(&_0, zim_zim_ce, "getinstance", &_1, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_0, "bind", NULL, 0, &name, value);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * @return Request
 */
PHP_METHOD(Zim_Http_Controller, getRequest) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "request");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "app", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param $uri
 * @return mixed|null
 */
PHP_METHOD(Zim_Http_Controller, getActionClass) {

	zval *uri, uri_sub, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &uri);



	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("actions"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, uri)) {
		zephir_read_property(&_2, this_ptr, SL("actions"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_0, &_2, uri, PH_NOISY, "/Users/henter/Dev/zim/zim/http/controller.zep", 51 TSRMLS_CC);
	} else {
		ZVAL_NULL(&_0);
	}
	RETURN_CCTOR(&_0);

}

/**
 * @param $uri
 * @return null
 */
PHP_METHOD(Zim_Http_Controller, getAction) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *uri, uri_sub, method, _0, _1, *_2, _3$$4, _4$$4, _5$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri_sub);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &uri);



	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CONCAT_VS(&_0, uri, "Action");
	if ((zephir_method_exists(this_ptr, &_0 TSRMLS_CC)  == SUCCESS)) {
		ZEPHIR_CONCAT_VS(return_value, uri, "Action");
		RETURN_MM();
	}
	ZEPHIR_CALL_FUNCTION(&_1, "get_class_methods", NULL, 15, this_ptr);
	zephir_check_call_status();
	zephir_is_iterable(&_1, 0, "/Users/henter/Dev/zim/zim/http/controller.zep", 70);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_1), _2)
	{
		ZEPHIR_INIT_NVAR(&method);
		ZVAL_COPY(&method, _2);
		ZEPHIR_INIT_NVAR(&_3$$4);
		zephir_fast_strtolower(&_3$$4, &method);
		ZEPHIR_INIT_NVAR(&_4$$4);
		zephir_fast_strtolower(&_4$$4, uri);
		ZEPHIR_INIT_LNVAR(_5$$4);
		ZEPHIR_CONCAT_VS(&_5$$4, &_4$$4, "action");
		if (ZEPHIR_IS_EQUAL(&_3$$4, &_5$$4)) {
			RETURN_CCTOR(&method);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&method);
	RETURN_MM_NULL();

}

PHP_METHOD(Zim_Http_Controller, getActions) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "actions");

}

zend_object *zephir_init_properties_Zim_Http_Controller(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _1$$3;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("actions"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("actions"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

