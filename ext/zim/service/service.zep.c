
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


ZEPHIR_INIT_CLASS(Zim_Service_Service) {

	ZEPHIR_REGISTER_CLASS(Zim\\Service, Service, zim, service_service, zim_service_service_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	/**
	 * @var Zim
	 */
	zend_declare_property_null(zim_service_service_ce, SL("zim"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Create a new service provider instance.
 *
 * @param  Zim $zim
 * @return void
 */
PHP_METHOD(Zim_Service_Service, __construct) {

	zval *zim, zim_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&zim_sub);

	zephir_fetch_params(0, 1, 0, &zim);



	zephir_update_property_zval(this_ptr, SL("zim"), zim);

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

	zval tmpArray40cd750bba9870f18aada2478b24840a;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tmpArray40cd750bba9870f18aada2478b24840a);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&tmpArray40cd750bba9870f18aada2478b24840a);
	array_init(&tmpArray40cd750bba9870f18aada2478b24840a);
	RETURN_CCTOR(&tmpArray40cd750bba9870f18aada2478b24840a);

}

/**
 * TODO, deferred register
 *
 * Get the events that trigger this service provider to register.
 *
 * @return array
 */
PHP_METHOD(Zim_Service_Service, when) {

	zval tmpArray40cd750bba9870f18aada2478b24840a;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tmpArray40cd750bba9870f18aada2478b24840a);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&tmpArray40cd750bba9870f18aada2478b24840a);
	array_init(&tmpArray40cd750bba9870f18aada2478b24840a);
	RETURN_CCTOR(&tmpArray40cd750bba9870f18aada2478b24840a);

}

