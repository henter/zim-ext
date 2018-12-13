
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"


/**
 * File NotFoundException.php
 * @henter
 * Time: 2018-11-25 23:30
 *
 */
ZEPHIR_INIT_CLASS(Zim_Http_Exception_ResponseException) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Http\\Exception, ResponseException, zim, http_exception_responseexception, zim_http_exception_exception_ce, NULL, 0);

	return SUCCESS;

}

