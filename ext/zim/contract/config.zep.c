
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Zim_Contract_Config) {

	ZEPHIR_REGISTER_INTERFACE(Zim\\Contract, Config, zim, contract_config, zim_contract_config_method_entry);

	return SUCCESS;

}

/**
 * Determine if the given configuration value exists.
 *
 * @param  string  $key
 * @return bool
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Config, has);

/**
 * Get the specified configuration value.
 *
 * @param  array|string  $key
 * @param  mixed   $deft
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Config, get);

/**
 * Get all of the configuration items for the application.
 *
 * @return array
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Config, all);

/**
 * Set a given configuration value.
 *
 * @param  array|string  $key
 * @param  mixed   $value
 * @return void
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Config, set);

/**
 * Prepend a value onto an array configuration value.
 *
 * @param  string  $key
 * @param  mixed  $value
 * @return void
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Config, prepend);

/**
 * Push a value onto an array configuration value.
 *
 * @param  string  $key
 * @param  mixed  $value
 * @return void
 */
ZEPHIR_DOC_METHOD(Zim_Contract_Config, push);

