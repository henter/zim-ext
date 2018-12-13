
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


ZEPHIR_INIT_CLASS(Zim_Container_BoundMethodcallClosureZero) {

	ZEPHIR_REGISTER_CLASS(Zim\\Container, BoundMethodcallClosureZero, zim, container_boundmethodcallclosurezero, zim_container_boundmethodcallclosurezero_method_entry, 0);

	zend_declare_property_null(zim_container_boundmethodcallclosurezero_ce, SL("container"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(zim_container_boundmethodcallclosurezero_ce, SL("callback"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(zim_container_boundmethodcallclosurezero_ce, SL("parameters"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Zim_Container_BoundMethodcallClosureZero, __construct) {

	zval *container, container_sub, *callback, callback_sub, *parameters, parameters_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&parameters_sub);

	zephir_fetch_params(0, 3, 0, &container, &callback, &parameters);



	zephir_update_property_zval(this_ptr, SL("container"), container);
	zephir_update_property_zval(this_ptr, SL("callback"), callback);
	zephir_update_property_zval(this_ptr, SL("parameters"), parameters);

}

PHP_METHOD(Zim_Container_BoundMethodcallClosureZero, __invoke) {

	zval _0, _1, _3, _4, _5;
	zephir_fcall_cache_entry *_2 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("callback"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_3, this_ptr, SL("container"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_4, this_ptr, SL("callback"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_5, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_CE_STATIC(&_1, zim_container_boundmethod_ce, "getmethoddependencies", &_2, 0, &_3, &_4, &_5);
	zephir_check_call_status();
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

