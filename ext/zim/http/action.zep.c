
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


/**
 * File Controller.php
 * @henter
 * Time: 2018-11-24 20:07
 *
 */
ZEPHIR_INIT_CLASS(Zim_Http_Action) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Http, Action, zim, http_action, zim_http_controller_ce, zim_http_action_method_entry, 0);

	zend_declare_property_string(zim_http_action_ce, SL("method"), "GET", ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_class_implements(zim_http_action_ce TSRMLS_CC, 1, zim_contract_action_ce);
	return SUCCESS;

}

PHP_METHOD(Zim_Http_Action, execute) {

	zval *this_ptr = getThis();


	RETURN_STRING("default action response");

}

