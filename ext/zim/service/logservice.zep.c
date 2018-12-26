
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
 * File LogService.php
 * @henter
 * Time: 2018-11-27 14:47
 *
 */
ZEPHIR_INIT_CLASS(Zim_Service_LogService) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Service, LogService, zim, service_logservice, zim_service_service_ce, zim_service_logservice_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Zim_Service_LogService, boot) {

	zval *this_ptr = getThis();



}

PHP_METHOD(Zim_Service_LogService, register) {

	zval *this_ptr = getThis();



}

