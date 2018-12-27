
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


ZEPHIR_INIT_CLASS(Zim_Service_Service) {

	ZEPHIR_REGISTER_CLASS(Zim\\Service, Service, zim, service_service, zim_service_service_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	return SUCCESS;

}

PHP_METHOD(Zim_Service_Service, __construct) {

	zval *this_ptr = getThis();



}

PHP_METHOD(Zim_Service_Service, boot) {

	zval *this_ptr = getThis();



}

PHP_METHOD(Zim_Service_Service, register) {

	zval *this_ptr = getThis();



}

/**
 * TODO, deferred register
 *
 * Get the services provided by the provider.
 *
 * @return array
 */
PHP_METHOD(Zim_Service_Service, provides) {

	zval *this_ptr = getThis();


	array_init(return_value);
	return;

}

/**
 * TODO, deferred register
 *
 * Get the events that trigger this service provider to register.
 *
 * @return array
 */
PHP_METHOD(Zim_Service_Service, when) {

	zval *this_ptr = getThis();


	array_init(return_value);
	return;

}

