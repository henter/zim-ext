
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
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/exception.h"
#include "kernel/variables.h"


/**
 * File Router.php
 * @henter
 * Time: 2018-11-24 20:17
 *
 */
ZEPHIR_INIT_CLASS(Zim_Routing_Router) {

	ZEPHIR_REGISTER_CLASS(Zim\\Routing, Router, zim, routing_router, zim_routing_router_method_entry, 0);

	/**
	 * @var RouteCollection
	 */
	zend_declare_property_null(zim_routing_router_ce, SL("routes"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * current method
	 *
	 * @var string
	 */
	zend_declare_property_null(zim_routing_router_ce, SL("method"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * current allowed methods for the request.
	 */
	zend_declare_property_null(zim_routing_router_ce, SL("allow"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_routing_router_ce->create_object = zephir_init_properties_Zim_Routing_Router;
	return SUCCESS;

}

/**
 * Router constructor.
 * @param RouteCollection $routes
 */
PHP_METHOD(Zim_Routing_Router, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *routes = NULL, routes_sub, __$null, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&routes_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &routes);

	if (!routes) {
		routes = &routes_sub;
		routes = &__$null;
	}


	ZEPHIR_INIT_VAR(&_0);
	if (zephir_is_true(routes)) {
		ZEPHIR_CPY_WRT(&_0, routes);
	} else {
		ZEPHIR_INIT_NVAR(&_0);
		object_init_ex(&_0, zim_routing_routecollection_ce);
		if (zephir_has_constructor(&_0 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 0);
			zephir_check_call_status();
		}
	}
	zephir_update_property_zval(this_ptr, SL("routes"), &_0);
	ZEPHIR_MM_RESTORE();

}

/**
 * @return RouteCollection
 */
PHP_METHOD(Zim_Routing_Router, getRoutes) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "routes");

}

/**
 * Add a route to the underlying route collection.
 *
 * @param  array|string  $methods
 * @param  string  $uri
 * @param  \Closure|array|string|callable|null  $info
 * @return Route
 */
PHP_METHOD(Zim_Routing_Router, addRoute) {

	zend_bool _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval uri;
	zval *methods, methods_sub, *uri_param = NULL, *info, info_sub, name, _1, _4, _5, _2$$4, _3$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&methods_sub);
	ZVAL_UNDEF(&info_sub);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&uri);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &methods, &uri_param, &info);

	zephir_get_strval(&uri, uri_param);


	_0 = Z_TYPE_P(info) == IS_ARRAY;
	if (_0) {
		ZEPHIR_OBS_VAR(&_1);
		zephir_array_fetch_string(&_1, info, SL("name"), PH_NOISY, "zim/routing/router.zep", 57 TSRMLS_CC);
		_0 = !(ZEPHIR_IS_EMPTY(&_1));
	}
	if (_0) {
		ZEPHIR_OBS_VAR(&name);
		zephir_array_fetch_string(&name, info, SL("name"), PH_NOISY, "zim/routing/router.zep", 58 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(&_2$$4);
		zephir_json_encode(&_2$$4, methods, 0 );
		ZEPHIR_INIT_VAR(&_3$$4);
		ZEPHIR_CONCAT_VV(&_3$$4, &_2$$4, &uri);
		ZEPHIR_CALL_FUNCTION(&name, "sha1", NULL, 109, &_3$$4);
		zephir_check_call_status();
	}
	zephir_read_property(&_4, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "createroute", NULL, 0, methods, &uri, info);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_4, "add", NULL, 0, &name, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Create a new route instance.
 *
 * @param  array|string  $methods
 * @param  string  $uri
 * @param  mixed  $info
 * @return Route
 */
PHP_METHOD(Zim_Routing_Router, createRoute) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval uri;
	zval *methods = NULL, methods_sub, *uri_param = NULL, *info, info_sub, requirements, options, defaults, controller, action, tmpListControllerAction, _0$$4, _1$$4, _2$$5, _3$$5, _4$$5, _5$$5, _6$$5, _7$$5, _8$$6, _9$$6, _10$$6, _11$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&methods_sub);
	ZVAL_UNDEF(&info_sub);
	ZVAL_UNDEF(&requirements);
	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&defaults);
	ZVAL_UNDEF(&controller);
	ZVAL_UNDEF(&action);
	ZVAL_UNDEF(&tmpListControllerAction);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&uri);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &methods, &uri_param, &info);

	ZEPHIR_SEPARATE_PARAM(methods);
	zephir_get_strval(&uri, uri_param);


	ZEPHIR_INIT_VAR(&requirements);
	array_init(&requirements);
	ZEPHIR_INIT_VAR(&options);
	array_init(&options);
	if (zephir_is_callable(info TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(&defaults);
		zephir_create_array(&defaults, 1, 0 TSRMLS_CC);
		zephir_array_update_string(&defaults, SL("_callable"), info, PH_COPY | PH_SEPARATE);
	} else {
		ZEPHIR_INIT_VAR(&_0$$4);
		ZVAL_STRING(&_0$$4, "@");
		ZEPHIR_INIT_VAR(&_1$$4);
		zephir_fast_strpos(&_1$$4, info, &_0$$4, 0 );
		if (Z_TYPE_P(info) == IS_ARRAY) {
			if (zephir_array_isset_string(info, SL("methods"))) {
				ZEPHIR_OBS_NVAR(methods);
				zephir_array_fetch_string(methods, info, SL("methods"), PH_NOISY, "zim/routing/router.zep", 83 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_NVAR(methods);
				array_init(methods);
			}
			if (zephir_array_isset_string(info, SL("defaults"))) {
				ZEPHIR_OBS_NVAR(&defaults);
				zephir_array_fetch_string(&defaults, info, SL("defaults"), PH_NOISY, "zim/routing/router.zep", 84 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_NVAR(&defaults);
				array_init(&defaults);
			}
			if (zephir_array_isset_string(info, SL("requirements"))) {
				ZEPHIR_OBS_NVAR(&requirements);
				zephir_array_fetch_string(&requirements, info, SL("requirements"), PH_NOISY, "zim/routing/router.zep", 85 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_NVAR(&requirements);
				array_init(&requirements);
			}
			if (zephir_array_isset_string(info, SL("options"))) {
				ZEPHIR_OBS_NVAR(&options);
				zephir_array_fetch_string(&options, info, SL("options"), PH_NOISY, "zim/routing/router.zep", 86 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_NVAR(&options);
				array_init(&options);
			}
			zephir_array_fetch_string(&_2$$5, info, SL("use"), PH_NOISY | PH_READONLY, "zim/routing/router.zep", 87 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&tmpListControllerAction);
			zephir_fast_explode_str(&tmpListControllerAction, SL("@"), &_2$$5, LONG_MAX TSRMLS_CC);
			ZEPHIR_OBS_VAR(&controller);
			zephir_array_fetch_long(&controller, &tmpListControllerAction, 0, PH_NOISY, "zim/routing/router.zep", 88 TSRMLS_CC);
			ZEPHIR_OBS_VAR(&action);
			zephir_array_fetch_long(&action, &tmpListControllerAction, 1, PH_NOISY, "zim/routing/router.zep", 89 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_3$$5);
			ZEPHIR_INIT_VAR(&_4$$5);
			ZVAL_STRING(&_4$$5, "/");
			ZEPHIR_INIT_VAR(&_5$$5);
			ZVAL_STRING(&_5$$5, "\\");
			zephir_fast_str_replace(&_3$$5, &_4$$5, &_5$$5, &controller TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_6$$5);
			ZEPHIR_CONCAT_SVS(&_6$$5, "App\\Controller\\", &_3$$5, "Controller");
			zephir_array_update_string(&defaults, SL("_controller"), &_6$$5, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_VAR(&_7$$5);
			ZEPHIR_CONCAT_VS(&_7$$5, &action, "Action");
			zephir_array_update_string(&defaults, SL("_action"), &_7$$5, PH_COPY | PH_SEPARATE);
		} else if (zephir_is_true(&_1$$4)) {
			ZEPHIR_INIT_NVAR(&tmpListControllerAction);
			zephir_fast_explode_str(&tmpListControllerAction, SL("@"), info, LONG_MAX TSRMLS_CC);
			ZEPHIR_OBS_NVAR(&controller);
			zephir_array_fetch_long(&controller, &tmpListControllerAction, 0, PH_NOISY, "zim/routing/router.zep", 94 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(&action);
			zephir_array_fetch_long(&action, &tmpListControllerAction, 1, PH_NOISY, "zim/routing/router.zep", 95 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&defaults);
			zephir_create_array(&defaults, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_8$$6);
			ZEPHIR_INIT_VAR(&_9$$6);
			ZVAL_STRING(&_9$$6, "/");
			ZEPHIR_INIT_VAR(&_10$$6);
			ZVAL_STRING(&_10$$6, "\\");
			zephir_fast_str_replace(&_8$$6, &_9$$6, &_10$$6, &controller TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_11$$6);
			ZEPHIR_CONCAT_SVS(&_11$$6, "App\\Controller\\", &_8$$6, "Controller");
			zephir_array_update_string(&defaults, SL("_controller"), &_11$$6, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_LNVAR(_11$$6);
			ZEPHIR_CONCAT_VS(&_11$$6, &action, "Action");
			zephir_array_update_string(&defaults, SL("_action"), &_11$$6, PH_COPY | PH_SEPARATE);
		}
	}
	object_init_ex(return_value, zim_routing_route_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 110, &uri, &defaults, &requirements, methods, &options);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Dispatch the request to the application.
 *
 * @param  Request  $request
 * @return Route
 */
PHP_METHOD(Zim_Routing_Router, matchRequest) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *request, request_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&request_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	ZEPHIR_CALL_METHOD(&_0, request, "getpathinfo", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, request, "getmethod", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "match", NULL, 0, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param string $path
 * @param string $method
 * @return Route
 */
PHP_METHOD(Zim_Routing_Router, match) {

	zend_bool _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path_param = NULL, *method_param = NULL, route, _0, _1, _3, _5, _6, _7, _8, _9, _10, _4$$4;
	zval path, method;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_4$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &path_param, &method_param);

	zephir_get_strval(&path, path_param);
	if (!method_param) {
		ZEPHIR_INIT_VAR(&method);
		ZVAL_STRING(&method, "GET");
	} else {
		zephir_get_strval(&method, method_param);
	}


	zephir_update_property_zval(this_ptr, SL("method"), &method);
	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("allow"), &_0);
	ZEPHIR_CALL_FUNCTION(&_1, "rawurldecode", NULL, 111, &path);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&route, this_ptr, "matchcollection", NULL, 0, &_1);
	zephir_check_call_status();
	if (zephir_is_true(&route)) {
		RETURN_CCTOR(&route);
	}
	_2 = ZEPHIR_IS_STRING_IDENTICAL(&path, "/");
	if (_2) {
		ZEPHIR_OBS_VAR(&_3);
		zephir_read_property(&_3, this_ptr, SL("allow"), PH_NOISY_CC);
		_2 = !zephir_is_true(&_3);
	}
	if (_2) {
		ZEPHIR_INIT_VAR(&_4$$4);
		object_init_ex(&_4$$4, zim_http_exception_notfoundexception_ce);
		ZEPHIR_CALL_METHOD(NULL, &_4$$4, "__construct", NULL, 87);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$4, "zim/routing/router.zep", 132 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, SL("allow"), PH_NOISY_CC | PH_READONLY);
	if (0 < zephir_fast_count_int(&_6 TSRMLS_CC)) {
		ZEPHIR_INIT_NVAR(&_5);
		object_init_ex(&_5, zim_http_exception_methodnotallowedexception_ce);
		zephir_read_property(&_7, this_ptr, SL("allow"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_FUNCTION(&_8, "array_unique", NULL, 103, &_7);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_5, "__construct", NULL, 112, &_8);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&_5);
		object_init_ex(&_5, zim_http_exception_notfoundexception_ce);
		ZEPHIR_INIT_VAR(&_9);
		ZVAL_STRING(&_9, "No routes found for \"%s\".");
		ZEPHIR_CALL_FUNCTION(&_10, "sprintf", NULL, 22, &_9, &path);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_5, "__construct", NULL, 87, &_10);
		zephir_check_call_status();
	}
	zephir_throw_exception_debug(&_5, "zim/routing/router.zep", 134 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Tries to match a URL with a set of routes.
 *
 * @param string          $path The path info to be parsed
 *
 * @return Route|null
 * @throws NotFoundException If the resource could not be found
 * @throws MethodNotAllowedException If the resource was found but the request method is not allowed
 */
PHP_METHOD(Zim_Routing_Router, matchCollection) {

	zend_bool _5$$3, _10$$3, _17$$3;
	zend_string *_4;
	zend_ulong _3;
	zephir_fcall_cache_entry *_32 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path_param = NULL, name, route, compiledRoute, staticPrefix, requiredMethods, method, matches, _0, _1, *_2, _6$$3, _7$$3, _8$$3, _9$$3, _11$$3, _12$$3, _13$$3, _14$$3, _15$$3, _16$$3, _18$$3, _19$$3, _20$$3, _21$$3, _22$$3, _30$$3, _31$$3, _23$$8, _24$$8, _25$$8, _26$$8, _27$$9, _28$$11, _29$$11;
	zval path;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&compiledRoute);
	ZVAL_UNDEF(&staticPrefix);
	ZVAL_UNDEF(&requiredMethods);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_15$$3);
	ZVAL_UNDEF(&_16$$3);
	ZVAL_UNDEF(&_18$$3);
	ZVAL_UNDEF(&_19$$3);
	ZVAL_UNDEF(&_20$$3);
	ZVAL_UNDEF(&_21$$3);
	ZVAL_UNDEF(&_22$$3);
	ZVAL_UNDEF(&_30$$3);
	ZVAL_UNDEF(&_31$$3);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$11);
	ZVAL_UNDEF(&_29$$11);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &path_param);

	zephir_get_strval(&path, path_param);


	zephir_read_property(&_0, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, &_0, "all", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_1, 0, "zim/routing/router.zep", 182);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_1), _3, _4, _2)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_4 != NULL) { 
			ZVAL_STR_COPY(&name, _4);
		} else {
			ZVAL_LONG(&name, _3);
		}
		ZEPHIR_INIT_NVAR(&route);
		ZVAL_COPY(&route, _2);
		ZEPHIR_CALL_METHOD(&compiledRoute, &route, "compile", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&staticPrefix, &compiledRoute, "getstaticprefix", NULL, 0);
		zephir_check_call_status();
		_5$$3 = ZEPHIR_IS_STRING_IDENTICAL(&staticPrefix, "");
		if (!(_5$$3)) {
			ZEPHIR_INIT_NVAR(&_6$$3);
			zephir_fast_strpos(&_6$$3, &path, &staticPrefix, 0 );
			_5$$3 = ZEPHIR_IS_LONG_IDENTICAL(&_6$$3, 0);
		}
		ZVAL_LONG(&_7$$3, -1);
		ZEPHIR_INIT_NVAR(&_8$$3);
		zephir_substr(&_8$$3, &staticPrefix, -1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_SINIT_NVAR(_9$$3);
		ZVAL_STRING(&_9$$3, "/");
		_10$$3 = ZEPHIR_IS_IDENTICAL(&_9$$3, &_8$$3);
		if (_10$$3) {
			ZVAL_LONG(&_11$$3, 0);
			ZVAL_LONG(&_12$$3, -1);
			ZEPHIR_INIT_NVAR(&_13$$3);
			zephir_substr(&_13$$3, &staticPrefix, 0 , -1 , 0);
			_10$$3 = ZEPHIR_IS_IDENTICAL(&_13$$3, &path);
		}
		ZVAL_LONG(&_14$$3, -1);
		ZEPHIR_INIT_NVAR(&_15$$3);
		zephir_substr(&_15$$3, &path, -1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		ZEPHIR_SINIT_NVAR(_16$$3);
		ZVAL_STRING(&_16$$3, "/");
		_17$$3 = ZEPHIR_IS_IDENTICAL(&_16$$3, &_15$$3);
		if (_17$$3) {
			ZVAL_LONG(&_18$$3, 0);
			ZVAL_LONG(&_19$$3, -1);
			ZEPHIR_INIT_NVAR(&_20$$3);
			zephir_substr(&_20$$3, &path, 0 , -1 , 0);
			_17$$3 = ZEPHIR_IS_IDENTICAL(&_20$$3, &staticPrefix);
		}
		if (_5$$3) {
		} else if (_10$$3) {
			RETURN_MM_NULL();
		} else if (_17$$3) {
			RETURN_MM_NULL();
		} else {
			continue;
		}
		ZEPHIR_CALL_METHOD(&_21$$3, &compiledRoute, "getregex", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_22$$3);
		zephir_preg_match(&_22$$3, &_21$$3, &path, &matches, 0, 0 , 0  TSRMLS_CC);
		if (!(zephir_is_true(&_22$$3))) {
			ZEPHIR_CALL_METHOD(&_23$$8, &route, "getpath", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_24$$8, &compiledRoute, "getregex", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_25$$8);
			ZEPHIR_INIT_NVAR(&_25$$8);
			ZVAL_STRING(&_25$$8, "not match");
			zephir_var_dump(&_25$$8 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_26$$8);
			ZEPHIR_CPY_WRT(&_26$$8, &path);
			zephir_var_dump(&_26$$8 TSRMLS_CC);
			zephir_var_dump(&_23$$8 TSRMLS_CC);
			zephir_var_dump(&_24$$8 TSRMLS_CC);
			continue;
		}
		ZEPHIR_CALL_METHOD(&requiredMethods, &route, "getmethods", NULL, 0);
		zephir_check_call_status();
		if (zephir_is_true(&requiredMethods)) {
			zephir_read_property(&_27$$9, this_ptr, SL("method"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CPY_WRT(&method, &_27$$9);
			if (ZEPHIR_IS_STRING_IDENTICAL(&method, "HEAD")) {
				ZEPHIR_INIT_NVAR(&method);
				ZVAL_STRING(&method, "GET");
			}
			if (!(zephir_fast_in_array(&method, &requiredMethods TSRMLS_CC))) {
				ZEPHIR_INIT_NVAR(&_28$$11);
				zephir_read_property(&_29$$11, this_ptr, SL("allow"), PH_NOISY_CC | PH_READONLY);
				zephir_fast_array_merge(&_28$$11, &_29$$11, &requiredMethods TSRMLS_CC);
				zephir_update_property_zval(this_ptr, SL("allow"), &_28$$11);
				continue;
			}
		}
		ZVAL_LONG(&_30$$3, 1);
		ZEPHIR_CALL_FUNCTION(&_31$$3, "array_slice", &_32, 113, &matches, &_30$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &route, "setparameters", NULL, 0, &_31$$3);
		zephir_check_call_status();
		RETURN_CCTOR(&route);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&route);
	ZEPHIR_INIT_NVAR(&name);
	RETURN_MM_NULL();

}

zend_object *zephir_init_properties_Zim_Routing_Router(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _1$$3;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("allow"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("allow"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

