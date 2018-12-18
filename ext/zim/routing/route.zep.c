
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"


/**
 * A Route describes a route and its parameters.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 * @author Tobias Schultze <http://tobion.de>
 *
 *
 * static method for route definition
 *
 * @method static get(string $uri, \Closure|array|string|null $info = null)
 * @method static post(string $uri, \Closure|array|string|null $info = null)
 * @method static put(string $uri, \Closure|array|string|null $info = null)
 * @method static delete(string $uri, \Closure|array|string|null $info = null)
 * @method static patch(string $uri, \Closure|array|string|null $info = null)
 * @method static options(string $uri, \Closure|array|string|null $info = null)
 * @method static match(array|string $method, string $uri, \Closure|array|string|null $info = null)
 * @method static any(string $uri, \Closure|array|string|null $info = null)
 * @method static name(string $value)
 * @method static where(array  $where)
 */
ZEPHIR_INIT_CLASS(Zim_Routing_Route) {

	ZEPHIR_REGISTER_CLASS(Zim\\Routing, Route, zim, routing_route, zim_routing_route_method_entry, 0);

	/**
	 * @var Registrar
	 */
	zend_declare_property_null(zim_routing_route_ce, SL("registrar"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_string(zim_routing_route_ce, SL("path"), "/", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_routing_route_ce, SL("methods"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_routing_route_ce, SL("defaults"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_routing_route_ce, SL("requirements"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_routing_route_ce, SL("options"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_routing_route_ce, SL("parameters"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var CompiledRoute|null
	 */
	zend_declare_property_null(zim_routing_route_ce, SL("compiled"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_routing_route_ce->create_object = zephir_init_properties_Zim_Routing_Route;
	return SUCCESS;

}

/**
 * Constructor.
 *
 * Available options:
 *  * utf8:           Whether UTF-8 matching is enforced ot not
 *
 * @param string          $path         The path pattern to match
 * @param array           $defaults     An array of default parameter values
 * @param array           $requirements An array of requirements for parameters (regexes)
 * @param string|string[] $methods      A required HTTP method or an array of restricted methods
 * @param array           $options      An array of options
 */
PHP_METHOD(Zim_Routing_Route, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval defaults, requirements, options;
	zval *path_param = NULL, *defaults_param = NULL, *requirements_param = NULL, *methods = NULL, methods_sub, *options_param = NULL;
	zval path;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&methods_sub);
	ZVAL_UNDEF(&defaults);
	ZVAL_UNDEF(&requirements);
	ZVAL_UNDEF(&options);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 4, &path_param, &defaults_param, &requirements_param, &methods, &options_param);

	zephir_get_strval(&path, path_param);
	if (!defaults_param) {
		ZEPHIR_INIT_VAR(&defaults);
		array_init(&defaults);
	} else {
		zephir_get_arrval(&defaults, defaults_param);
	}
	if (!requirements_param) {
		ZEPHIR_INIT_VAR(&requirements);
		array_init(&requirements);
	} else {
		zephir_get_arrval(&requirements, requirements_param);
	}
	if (!methods) {
		methods = &methods_sub;
		ZEPHIR_INIT_VAR(methods);
		array_init(methods);
	}
	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setpath", NULL, 0, &path);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "adddefaults", NULL, 0, &defaults);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addrequirements", NULL, 0, &requirements);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setmethods", NULL, 0, methods);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "addoptions", NULL, 0, &options);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * @param array $parameters
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, setParameters) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameters_param = NULL, _0, _1, _2;
	zval parameters;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters_param);

	zephir_get_arrval(&parameters, parameters_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "mergedefaults", NULL, 0, &parameters);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("parameters"), &_0);
	zephir_read_property(&_1, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset_string(&_1, SL("_controller"), PH_SEPARATE);
	zephir_read_property(&_2, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset_string(&_2, SL("_action"), PH_SEPARATE);
	RETURN_THIS();

}

PHP_METHOD(Zim_Routing_Route, getParameters) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "parameters");

}

/**
 * Get merged default parameters.
 *
 * @param array $params   The parameters
 *
 * @return array Merged default parameters
 */
PHP_METHOD(Zim_Routing_Route, mergeDefaults) {

	zend_bool _3$$3;
	zend_string *_2;
	zend_ulong _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *params_param = NULL, defaults, key, value, *_0;
	zval params;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&defaults);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &params_param);

	zephir_get_arrval(&params, params_param);


	ZEPHIR_CALL_METHOD(&defaults, this_ptr, "getdefaults", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&params, 0, "zim/routing/route.zep", 96);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&params), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&key, _2);
		} else {
			ZVAL_LONG(&key, _1);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _0);
		_3$$3 = !((Z_TYPE_P(&key) == IS_LONG));
		if (_3$$3) {
			_3$$3 = Z_TYPE_P(&value) != IS_NULL;
		}
		if (_3$$3) {
			zephir_array_update_zval(&defaults, &key, &value, PH_COPY | PH_SEPARATE);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_CCTOR(&defaults);

}

/**
 * Returns the pattern for the path.
 *
 * @return string The path pattern
 */
PHP_METHOD(Zim_Routing_Route, getPath) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "path");

}

/**
 * Sets the pattern for the path.
 *
 * This method implements a fluent interface.
 *
 * @param string $pattern The path pattern
 *
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, setPath) {

	zval _2$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *pattern_param = NULL, __$null, _0, _1, _5, _6, _7, _3$$3, _4$$3;
	zval pattern;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &pattern_param);

	zephir_get_strval(&pattern, pattern_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "?<");
	ZEPHIR_CALL_FUNCTION(&_1, "strpbrk", NULL, 102, &pattern, &_0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_create_array(&_2$$3, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&_2$$3, this_ptr);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "setPathCallback");
		zephir_array_fast_append(&_2$$3, &_3$$3);
		ZEPHIR_INIT_NVAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "#\\{(\\w++)(<.*?>)?(\\?[^\\}]*+)?\\}#");
		ZEPHIR_CALL_FUNCTION(&_4$$3, "preg_replace_callback", NULL, 66, &_3$$3, &_2$$3, &pattern);
		zephir_check_call_status();
		zephir_get_strval(&pattern, &_4$$3);
	}
	ZEPHIR_INIT_NVAR(&_0);
	ZEPHIR_INIT_VAR(&_5);
	zephir_fast_trim(&_5, &pattern, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_STRING(&_6, "/");
	zephir_fast_trim(&_0, &_5, &_6, ZEPHIR_TRIM_LEFT TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_7);
	ZEPHIR_CONCAT_SV(&_7, "/", &_0);
	zephir_update_property_zval(this_ptr, SL("path"), &_7);
	zephir_update_property_zval(this_ptr, SL("compiled"), &__$null);
	RETURN_THIS();

}

PHP_METHOD(Zim_Routing_Route, setPathCallback) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *m_param = NULL, _0, _6, _12, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3, _7$$4, _8$$4, _9$$4, _10$$4, _11$$4;
	zval m;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&m);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &m_param);

	zephir_get_arrval(&m, m_param);


	zephir_array_fetch_long(&_0, &m, 3, PH_NOISY | PH_READONLY, "zim/routing/route.zep", 130 TSRMLS_CC);
	if (zephir_fast_strlen_ev(&_0) > 0) {
		zephir_array_fetch_long(&_1$$3, &m, 1, PH_NOISY | PH_READONLY, "zim/routing/route.zep", 131 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_array_fetch_long(&_3$$3, &m, 3, PH_NOISY | PH_READONLY, "zim/routing/route.zep", 131 TSRMLS_CC);
		if (!ZEPHIR_IS_STRING_IDENTICAL(&_3$$3, "?")) {
			zephir_array_fetch_long(&_4$$3, &m, 3, PH_NOISY | PH_READONLY, "zim/routing/route.zep", 131 TSRMLS_CC);
			ZVAL_LONG(&_5$$3, 1);
			ZEPHIR_INIT_NVAR(&_2$$3);
			zephir_substr(&_2$$3, &_4$$3, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		} else {
			ZEPHIR_INIT_NVAR(&_2$$3);
			ZVAL_NULL(&_2$$3);
		}
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setdefault", NULL, 0, &_1$$3, &_2$$3);
		zephir_check_call_status();
	}
	zephir_array_fetch_long(&_6, &m, 2, PH_NOISY | PH_READONLY, "zim/routing/route.zep", 134 TSRMLS_CC);
	if (zephir_fast_strlen_ev(&_6) > 0) {
		zephir_array_fetch_long(&_7$$4, &m, 1, PH_NOISY | PH_READONLY, "zim/routing/route.zep", 135 TSRMLS_CC);
		zephir_array_fetch_long(&_8$$4, &m, 2, PH_NOISY | PH_READONLY, "zim/routing/route.zep", 135 TSRMLS_CC);
		ZVAL_LONG(&_9$$4, 1);
		ZVAL_LONG(&_10$$4, -1);
		ZEPHIR_INIT_VAR(&_11$$4);
		zephir_substr(&_11$$4, &_8$$4, 1 , -1 , 0);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setrequirement", NULL, 0, &_7$$4, &_11$$4);
		zephir_check_call_status();
	}
	zephir_array_fetch_long(&_12, &m, 1, PH_NOISY | PH_READONLY, "zim/routing/route.zep", 137 TSRMLS_CC);
	ZEPHIR_CONCAT_SVS(return_value, "{", &_12, "}");
	RETURN_MM();

}

/**
 * Returns the uppercased HTTP methods this route is restricted to.
 * So an empty array means that any method is allowed.
 *
 * @return string[] The methods
 */
PHP_METHOD(Zim_Routing_Route, getMethods) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "methods");

}

/**
 * Sets the HTTP methods (e.g. 'POST') this route is restricted to.
 * So an empty array means that any method is allowed.
 *
 * This method implements a fluent interface.
 *
 * @param string[] $methods The method or an array of methods
 *
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, setMethods) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *methods_param = NULL, __$null, _0, _1;
	zval methods;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&methods);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &methods_param);

	zephir_get_arrval(&methods, methods_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "strtoupper");
	ZEPHIR_CALL_FUNCTION(&_1, "array_map", NULL, 75, &_0, &methods);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("methods"), &_1);
	zephir_update_property_zval(this_ptr, SL("compiled"), &__$null);
	RETURN_THIS();

}

/**
 * Returns the options.
 *
 * @return array The options
 */
PHP_METHOD(Zim_Routing_Route, getOptions) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "options");

}

/**
 * Adds options.
 *
 * This method implements a fluent interface.
 *
 * @param array $options The options
 *
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, addOptions) {

	zend_string *_2;
	zend_ulong _1;
	zval *options_param = NULL, __$null, name, option, *_0;
	zval options;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&options);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&option);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &options_param);

	zephir_get_arrval(&options, options_param);


	zephir_is_iterable(&options, 0, "zim/routing/route.zep", 194);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&options), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&name, _2);
		} else {
			ZVAL_LONG(&name, _1);
		}
		ZEPHIR_INIT_NVAR(&option);
		ZVAL_COPY(&option, _0);
		zephir_update_property_array(this_ptr, SL("options"), &name, &option TSRMLS_CC);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&option);
	ZEPHIR_INIT_NVAR(&name);
	zephir_update_property_zval(this_ptr, SL("compiled"), &__$null);
	RETURN_THIS();

}

/**
 * Sets an option value.
 *
 * This method implements a fluent interface.
 *
 * @param string $name  An option name
 * @param mixed  $value The option value
 *
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, setOption) {

	zval *name_param = NULL, *value, value_sub, __$null;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value_sub);
	ZVAL_NULL(&__$null);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &value);

	zephir_get_strval(&name, name_param);


	zephir_update_property_array(this_ptr, SL("options"), &name, value TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("compiled"), &__$null);
	RETURN_THIS();

}

/**
 * Get an option value.
 *
 * @param string $name An option name
 *
 * @return mixed The option value or null when not given
 */
PHP_METHOD(Zim_Routing_Route, getOption) {

	zval *name_param = NULL, _0, _1, _2;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("options"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, &name)) {
		zephir_read_property(&_2, this_ptr, SL("options"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_0, &_2, &name, PH_NOISY, "zim/routing/route.zep", 224 TSRMLS_CC);
	} else {
		ZVAL_NULL(&_0);
	}
	RETURN_CCTOR(&_0);

}

/**
 * Checks if an option has been set.
 *
 * @param string $name An option name
 *
 * @return bool true if the option is set, false otherwise
 */
PHP_METHOD(Zim_Routing_Route, hasOption) {

	zval *name_param = NULL, _0;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	zephir_read_property(&_0, this_ptr, SL("options"), PH_NOISY_CC | PH_READONLY);
	RETURN_MM_BOOL(zephir_array_key_exists(&_0, &name TSRMLS_CC));

}

/**
 * Returns the defaults.
 *
 * @return array The defaults
 */
PHP_METHOD(Zim_Routing_Route, getDefaults) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "defaults");

}

/**
 * Sets the defaults.
 *
 * This method implements a fluent interface.
 *
 * @param array $defaults The defaults
 *
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, setDefaults) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *defaults_param = NULL, _0;
	zval defaults;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&defaults);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &defaults_param);

	zephir_get_arrval(&defaults, defaults_param);


	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("defaults"), &_0);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "adddefaults", NULL, 0, &defaults);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Adds defaults.
 *
 * This method implements a fluent interface.
 *
 * @param array $defaults The defaults
 *
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, addDefaults) {

	zend_string *_2;
	zend_ulong _1;
	zval *defaults_param = NULL, __$null, name, deft, *_0;
	zval defaults;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&defaults);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&deft);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &defaults_param);

	zephir_get_arrval(&defaults, defaults_param);


	zephir_is_iterable(&defaults, 0, "zim/routing/route.zep", 280);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&defaults), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&name, _2);
		} else {
			ZVAL_LONG(&name, _1);
		}
		ZEPHIR_INIT_NVAR(&deft);
		ZVAL_COPY(&deft, _0);
		zephir_update_property_array(this_ptr, SL("defaults"), &name, &deft TSRMLS_CC);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&deft);
	ZEPHIR_INIT_NVAR(&name);
	zephir_update_property_zval(this_ptr, SL("compiled"), &__$null);
	RETURN_THIS();

}

/**
 * Gets a default value.
 *
 * @param string $name A variable name
 *
 * @return mixed The default value or null when not given
 */
PHP_METHOD(Zim_Routing_Route, getDefault) {

	zval *name_param = NULL, _0, _1, _2;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("defaults"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, &name)) {
		zephir_read_property(&_2, this_ptr, SL("defaults"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_0, &_2, &name, PH_NOISY, "zim/routing/route.zep", 293 TSRMLS_CC);
	} else {
		ZVAL_NULL(&_0);
	}
	RETURN_CCTOR(&_0);

}

/**
 * Checks if a default value is set for the given variable.
 *
 * @param string $name A variable name
 *
 * @return bool true if the default value is set, false otherwise
 */
PHP_METHOD(Zim_Routing_Route, hasDefault) {

	zval *name_param = NULL, _0;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	zephir_read_property(&_0, this_ptr, SL("defaults"), PH_NOISY_CC | PH_READONLY);
	RETURN_MM_BOOL(zephir_array_key_exists(&_0, &name TSRMLS_CC));

}

/**
 * Sets a default value.
 *
 * @param string $name    A variable name
 * @param mixed  $default The default value
 *
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, setDefault) {

	zval *name_param = NULL, *deft, deft_sub, __$null;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_NULL(&__$null);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &deft);

	zephir_get_strval(&name, name_param);


	zephir_update_property_array(this_ptr, SL("defaults"), &name, deft TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("compiled"), &__$null);
	RETURN_THIS();

}

/**
 * Returns the requirements.
 *
 * @return array The requirements
 */
PHP_METHOD(Zim_Routing_Route, getRequirements) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "requirements");

}

/**
 * Sets the requirements.
 *
 * This method implements a fluent interface.
 *
 * @param array $requirements The requirements
 *
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, setRequirements) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *requirements_param = NULL, _0;
	zval requirements;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&requirements);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &requirements_param);

	zephir_get_arrval(&requirements, requirements_param);


	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("requirements"), &_0);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addrequirements", NULL, 0, &requirements);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Adds requirements.
 *
 * This method implements a fluent interface.
 *
 * @param array $requirements The requirements
 *
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, addRequirements) {

	zend_string *_2;
	zend_ulong _1;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *requirements_param = NULL, __$null, key, regex, *_0, _3$$3;
	zval requirements;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&requirements);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&regex);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &requirements_param);

	zephir_get_arrval(&requirements, requirements_param);


	zephir_is_iterable(&requirements, 0, "zim/routing/route.zep", 364);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&requirements), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&key, _2);
		} else {
			ZVAL_LONG(&key, _1);
		}
		ZEPHIR_INIT_NVAR(&regex);
		ZVAL_COPY(&regex, _0);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "sanitizerequirement", &_4, 0, &key, &regex);
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("requirements"), &key, &_3$$3 TSRMLS_CC);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&regex);
	ZEPHIR_INIT_NVAR(&key);
	zephir_update_property_zval(this_ptr, SL("compiled"), &__$null);
	RETURN_THIS();

}

/**
 * Returns the requirement for the given key.
 *
 * @param string $key The key
 *
 * @return string|null The regex or null when not given
 */
PHP_METHOD(Zim_Routing_Route, getRequirement) {

	zval *key_param = NULL, _0, _1, _2;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(&key, key_param);


	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("requirements"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, &key)) {
		zephir_read_property(&_2, this_ptr, SL("requirements"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_0, &_2, &key, PH_NOISY, "zim/routing/route.zep", 377 TSRMLS_CC);
	} else {
		ZVAL_NULL(&_0);
	}
	RETURN_CCTOR(&_0);

}

/**
 * Checks if a requirement is set for the given key.
 *
 * @param string $key A variable name
 *
 * @return bool true if a requirement is specified, false otherwise
 */
PHP_METHOD(Zim_Routing_Route, hasRequirement) {

	zval *key_param = NULL, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	zephir_get_strval(&key, key_param);


	zephir_read_property(&_0, this_ptr, SL("requirements"), PH_NOISY_CC | PH_READONLY);
	RETURN_MM_BOOL(zephir_array_key_exists(&_0, &key TSRMLS_CC));

}

/**
 * Sets a requirement for the given key.
 *
 * @param string $key   The key
 * @param string $regex The regex
 *
 * @return $this
 */
PHP_METHOD(Zim_Routing_Route, setRequirement) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *regex_param = NULL, __$null, _0;
	zval key, regex;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&regex);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &regex_param);

	zephir_get_strval(&key, key_param);
	zephir_get_strval(&regex, regex_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "sanitizerequirement", NULL, 0, &key, &regex);
	zephir_check_call_status();
	zephir_update_property_array(this_ptr, SL("requirements"), &key, &_0 TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("compiled"), &__$null);
	RETURN_THIS();

}

/**
 * Compiles the route.
 *
 * @return CompiledRoute A CompiledRoute instance
 *
 * @throws \LogicException If the Route cannot be compiled because the
 *                         path or host pattern is invalid
 *
 * @see RouteCompiler which is responsible for the compilation process
 */
PHP_METHOD(Zim_Routing_Route, compile) {

	zval _0, _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_2 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("compiled"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) != IS_NULL) {
		RETURN_MM_MEMBER(getThis(), "compiled");
	}
	ZEPHIR_CALL_CE_STATIC(&_1, zim_routing_routecompiler_ce, "compile", &_2, 0, this_ptr);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("compiled"), &_1);
	RETURN_MM_MEMBER(getThis(), "compiled");

}

PHP_METHOD(Zim_Routing_Route, sanitizeRequirement) {

	zend_bool _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *regex_param = NULL, _1, _2, _3, _7, _8, _4$$3, _5$$3, _9$$4, _10$$4, _11$$4, _12$$5, _13$$5, _14$$5;
	zval key, regex, _6$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&regex);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &regex_param);

	zephir_get_strval(&key, key_param);
	zephir_get_strval(&regex, regex_param);


	_0 = !ZEPHIR_IS_STRING_IDENTICAL(&regex, "");
	if (_0) {
		ZVAL_LONG(&_1, 0);
		ZVAL_LONG(&_2, 1);
		ZEPHIR_INIT_VAR(&_3);
		zephir_substr(&_3, &regex, 0 , 1 , 0);
		_0 = ZEPHIR_IS_STRING_IDENTICAL(&_3, "^");
	}
	if (_0) {
		ZVAL_LONG(&_4$$3, 1);
		ZEPHIR_INIT_VAR(&_5$$3);
		zephir_substr(&_5$$3, &regex, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_CPY_WRT(&regex, &_6$$3);
	}
	ZVAL_LONG(&_7, -1);
	ZEPHIR_INIT_VAR(&_8);
	zephir_substr(&_8, &regex, -1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
	if (ZEPHIR_IS_STRING_IDENTICAL(&_8, "$")) {
		ZVAL_LONG(&_9$$4, 0);
		ZVAL_LONG(&_10$$4, -1);
		ZEPHIR_INIT_VAR(&_11$$4);
		zephir_substr(&_11$$4, &regex, 0 , -1 , 0);
		zephir_get_strval(&regex, &_11$$4);
	}
	if (ZEPHIR_IS_STRING_IDENTICAL(&regex, "")) {
		ZEPHIR_INIT_VAR(&_12$$5);
		object_init_ex(&_12$$5, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_13$$5);
		ZVAL_STRING(&_13$$5, "Routing requirement for \"%s\" cannot be empty.");
		ZEPHIR_CALL_FUNCTION(&_14$$5, "sprintf", NULL, 22, &_13$$5, &key);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_12$$5, "__construct", NULL, 28, &_14$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_12$$5, "zim/routing/route.zep", 435 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	RETURN_CTOR(&regex);

}

/**
 * Dynamically handle calls into the route registrar.
 *
 * @param  string  $method
 * @param  array  $parameters
 * @return Route|$this
 *
 * @throws \BadMethodCallException
 */
PHP_METHOD(Zim_Routing_Route, __callStatic) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_3 = NULL;
	zval parameters;
	zval *method_param = NULL, *parameters_param = NULL, call, _0, _5, _1$$3, _2$$3, _4$$3;
	zval method;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&call);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &method_param, &parameters_param);

	zephir_get_strval(&method, method_param);
	zephir_get_arrval(&parameters, parameters_param);


	zephir_read_static_property_ce(&_0, zim_routing_route_ce, SL("registrar"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, zim_routing_registrar_ce);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "router");
		ZEPHIR_CALL_CE_STATIC(&_2$$3, zim_zim_ce, "app", &_3, 0, &_4$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 103, &_2$$3);
		zephir_check_call_status();
		zend_update_static_property(zim_routing_route_ce, ZEND_STRL("registrar"), &_1$$3);
	}
	ZEPHIR_INIT_VAR(&call);
	zephir_create_array(&call, 2, 0 TSRMLS_CC);
	ZEPHIR_OBS_VAR(&_5);
	zephir_read_static_property_ce(&_5, zim_routing_route_ce, SL("registrar"), PH_NOISY_CC);
	zephir_array_fast_append(&call, &_5);
	zephir_array_fast_append(&call, &method);
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &call, &parameters);
	zephir_check_call_status();
	RETURN_MM();

}

zend_object *zephir_init_properties_Zim_Routing_Route(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _2, _4, _6, _8, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("parameters"), &_1$$3);
		}
		zephir_read_property(&_2, this_ptr, SL("options"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval(this_ptr, SL("options"), &_3$$4);
		}
		zephir_read_property(&_4, this_ptr, SL("requirements"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval(this_ptr, SL("requirements"), &_5$$5);
		}
		zephir_read_property(&_6, this_ptr, SL("defaults"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval(this_ptr, SL("defaults"), &_7$$6);
		}
		zephir_read_property(&_8, this_ptr, SL("methods"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval(this_ptr, SL("methods"), &_9$$7);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

