
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


ZEPHIR_INIT_CLASS(Zim_Container_ContainersetClosureOne) {

	ZEPHIR_REGISTER_CLASS(Zim\\Container, ContainersetClosureOne, zim, container_containersetclosureone, zim_container_containersetclosureone_method_entry, 0);

	zend_declare_property_null(zim_container_containersetclosureone_ce, SL("value"), ZEND_ACC_PRIVATE TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Zim_Container_ContainersetClosureOne, __construct) {

	zval *value, value_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value_sub);

	zephir_fetch_params(0, 1, 0, &value);



	zephir_update_property_zval(this_ptr, SL("value"), value);

}

PHP_METHOD(Zim_Container_ContainersetClosureOne, __invoke) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "value");

}

