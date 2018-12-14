
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * File RequestInterface.php
 * @henter
 * Time: 2018-11-24 19:52
 *
 */
ZEPHIR_INIT_CLASS(Zim_Contract_Arrayable) {

	ZEPHIR_REGISTER_INTERFACE(Zim\\Contract, Arrayable, zim, contract_arrayable, zim_contract_arrayable_method_entry);

	return SUCCESS;

}

ZEPHIR_DOC_METHOD(Zim_Contract_Arrayable, toArray);

