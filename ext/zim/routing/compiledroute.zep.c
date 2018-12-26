
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
#include "kernel/operators.h"
#include "kernel/memory.h"


/**
 * CompiledRoutes are returned by the RouteCompiler class.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
ZEPHIR_INIT_CLASS(Zim_Routing_CompiledRoute) {

	ZEPHIR_REGISTER_CLASS(Zim\\Routing, CompiledRoute, zim, routing_compiledroute, zim_routing_compiledroute_method_entry, 0);

	zend_declare_property_null(zim_routing_compiledroute_ce, SL("variables"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_routing_compiledroute_ce, SL("tokens"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_routing_compiledroute_ce, SL("staticPrefix"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_routing_compiledroute_ce, SL("regex"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_routing_compiledroute_ce, SL("pathVariables"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * @param string      $staticPrefix  The static prefix of the compiled route
 * @param string      $regex         The regular expression to use to match this route
 * @param array       $tokens        An array of tokens to use to generate URL for this route
 * @param array       $pathVariables An array of path variables
 * @param array       $variables     An array of variables (variables defined in the path and in the host patterns)
 */
PHP_METHOD(Zim_Routing_CompiledRoute, __construct) {

	zval tokens, pathVariables, variables;
	zval *staticPrefix_param = NULL, *regex_param = NULL, *tokens_param = NULL, *pathVariables_param = NULL, *variables_param = NULL;
	zval staticPrefix, regex;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&staticPrefix);
	ZVAL_UNDEF(&regex);
	ZVAL_UNDEF(&tokens);
	ZVAL_UNDEF(&pathVariables);
	ZVAL_UNDEF(&variables);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 1, &staticPrefix_param, &regex_param, &tokens_param, &pathVariables_param, &variables_param);

	zephir_get_strval(&staticPrefix, staticPrefix_param);
	zephir_get_strval(&regex, regex_param);
	zephir_get_arrval(&tokens, tokens_param);
	zephir_get_arrval(&pathVariables, pathVariables_param);
	if (!variables_param) {
		ZEPHIR_INIT_VAR(&variables);
		array_init(&variables);
	} else {
		zephir_get_arrval(&variables, variables_param);
	}


	zephir_update_property_zval(this_ptr, SL("staticPrefix"), &staticPrefix);
	zephir_update_property_zval(this_ptr, SL("regex"), &regex);
	zephir_update_property_zval(this_ptr, SL("tokens"), &tokens);
	zephir_update_property_zval(this_ptr, SL("pathVariables"), &pathVariables);
	zephir_update_property_zval(this_ptr, SL("variables"), &variables);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns the static prefix.
 *
 * @return string The static prefix
 */
PHP_METHOD(Zim_Routing_CompiledRoute, getStaticPrefix) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "staticPrefix");

}

/**
 * Returns the regex.
 *
 * @return string The regex
 */
PHP_METHOD(Zim_Routing_CompiledRoute, getRegex) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "regex");

}

/**
 * Returns the tokens.
 *
 * @return array The tokens
 */
PHP_METHOD(Zim_Routing_CompiledRoute, getTokens) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "tokens");

}

/**
 * Returns the variables.
 *
 * @return array The variables
 */
PHP_METHOD(Zim_Routing_CompiledRoute, getVariables) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "variables");

}

/**
 * Returns the path variables.
 *
 * @return array The variables
 */
PHP_METHOD(Zim_Routing_CompiledRoute, getPathVariables) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "pathVariables");

}

