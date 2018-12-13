
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


ZEPHIR_INIT_CLASS(Zim_Container_ContainergetClosureClosureZero) {

	ZEPHIR_REGISTER_CLASS(Zim\\Container, ContainergetClosureClosureZero, zim, container_containergetclosureclosurezero, zim_container_containergetclosureclosurezero_method_entry, 0);

	zend_declare_property_null(zim_container_containergetclosureclosurezero_ce, SL("abstractt"), ZEND_ACC_PRIVATE TSRMLS_CC);

	zend_declare_property_null(zim_container_containergetclosureclosurezero_ce, SL("concrete"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Zim_Container_ContainergetClosureClosureZero, __construct) {

	zval *abstractt, abstractt_sub, *concrete, concrete_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&concrete_sub);

	zephir_fetch_params(0, 2, 0, &abstractt, &concrete);



	zephir_update_property_zval(this_ptr, SL("abstractt"), abstractt);
	zephir_update_property_zval(this_ptr, SL("concrete"), concrete);

}

PHP_METHOD(Zim_Container_ContainergetClosureClosureZero, __invoke) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *container, container_sub, *parameters = NULL, parameters_sub, _0, _1, _3, _2$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&parameters_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &container, &parameters);

	if (!parameters) {
		parameters = &parameters_sub;
		ZEPHIR_INIT_VAR(parameters);
		array_init(parameters);
	}


	zephir_read_property(&_0, this_ptr, SL("abstractt"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_1, this_ptr, SL("concrete"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_EQUAL(&_0, &_1)) {
		zephir_read_property(&_2$$3, this_ptr, SL("concrete"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_RETURN_CALL_METHOD(container, "build", NULL, 0, &_2$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_read_property(&_3, this_ptr, SL("concrete"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(container, "make", NULL, 0, &_3, parameters);
	zephir_check_call_status();
	RETURN_MM();

}

