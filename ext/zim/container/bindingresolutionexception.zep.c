
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
 * File BindingResolutionException.php
 * @henter
 * Time: 2018-11-26 15:43
 *
 */
ZEPHIR_INIT_CLASS(Zim_Container_BindingResolutionException) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Container, BindingResolutionException, zim, container_bindingresolutionexception, zend_exception_get_default(TSRMLS_C), NULL, 0);

	return SUCCESS;

}

