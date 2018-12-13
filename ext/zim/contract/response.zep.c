
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * File ResponseInterface.php
 * @henter
 * Time: 2018-11-24 19:52
 *
 */
ZEPHIR_INIT_CLASS(Zim_Contract_Response) {

	ZEPHIR_REGISTER_INTERFACE(Zim\\Contract, Response, zim, contract_response, zim_contract_response_method_entry);

	return SUCCESS;

}

ZEPHIR_DOC_METHOD(Zim_Contract_Response, prepare);

