
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
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"


/**
 * @method get(string $uri, \Closure|array|string|null $info = null)
 * @method post(string $uri, \Closure|array|string|null $info = null)
 * @method put(string $uri, \Closure|array|string|null $info = null)
 * @method delete(string $uri, \Closure|array|string|null $info = null)
 * @method patch(string $uri, \Closure|array|string|null $info = null)
 * @method options(string $uri, \Closure|array|string|null $info = null)
 * @method any(string $uri, \Closure|array|string|null $info = null)
 * @method static match(array|string $method, string $uri, \Closure|array|string|null $info = null)
 */
ZEPHIR_INIT_CLASS(Zim_Routing_Registrar) {

	ZEPHIR_REGISTER_CLASS(Zim\\Routing, Registrar, zim, routing_registrar, zim_routing_registrar_method_entry, 0);

	/**
	 * The router instance.
	 *
	 * @var Router
	 */
	zend_declare_property_null(zim_routing_registrar_ce, SL("router"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The methods to dynamically pass through to the router.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_routing_registrar_ce, SL("passthru"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_routing_registrar_ce->create_object = zephir_init_properties_Zim_Routing_Registrar;
	return SUCCESS;

}

/**
 * Create a new route registrar instance.
 *
 * @param  Router  $router
 * @return void
 */
PHP_METHOD(Zim_Routing_Registrar, __construct) {

	zval *router, router_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&router_sub);

	zephir_fetch_params(0, 1, 0, &router);



	zephir_update_property_zval(this_ptr, SL("router"), router);

}

/**
 * Registrar a new route with the router.
 *
 * @param  string  $method
 * @param  string  $uri
 * @param  \Closure|array|string|null  $info
 * @return Route
 */
PHP_METHOD(Zim_Routing_Registrar, registrarRoute) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *method_param = NULL, *uri_param = NULL, *info = NULL, info_sub, __$null, _0$$3, _1$$3, _2;
	zval method, uri;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&uri);
	ZVAL_UNDEF(&info_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &method_param, &uri_param, &info);

	zephir_get_strval(&method, method_param);
	zephir_get_strval(&uri, uri_param);
	if (!info) {
		info = &info_sub;
		info = &__$null;
	}


	if (ZEPHIR_IS_STRING(&method, "any")) {
		zephir_read_property(&_0$$3, this_ptr, SL("router"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_1$$3);
		array_init(&_1$$3);
		ZEPHIR_RETURN_CALL_METHOD(&_0$$3, "addroute", NULL, 0, &_1$$3, &uri, info);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_read_property(&_2, this_ptr, SL("router"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_2, "addroute", NULL, 0, &method, &uri, info);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Register a new route with the given verbs.
 *
 * @param  array|string  $methods
 * @param  string  $uri
 * @param  \Closure|array|string|null  $info
 * @return Route
 */
PHP_METHOD(Zim_Routing_Registrar, doMatch) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval uri;
	zval *methods, methods_sub, *uri_param = NULL, *info = NULL, info_sub, __$null, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&methods_sub);
	ZVAL_UNDEF(&info_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&uri);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &methods, &uri_param, &info);

	zephir_get_strval(&uri, uri_param);
	if (!info) {
		info = &info_sub;
		info = &__$null;
	}


	zephir_read_property(&_0, this_ptr, SL("router"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "addroute", NULL, 0, methods, &uri, info);
	zephir_check_call_status();
	RETURN_MM();

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
PHP_METHOD(Zim_Routing_Registrar, __call) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters, _1$$3, _3$$4;
	zval *method_param = NULL, *parameters_param = NULL, all, _0, _5, _6, _7, _8, _2$$3, _4$$4;
	zval method;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&all);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &method_param, &parameters_param);

	zephir_get_strval(&method, method_param);
	zephir_get_arrval(&parameters, parameters_param);


	zephir_read_property(&_0, this_ptr, SL("passthru"), PH_NOISY_CC | PH_READONLY);
	if (zephir_fast_in_array(&method, &_0 TSRMLS_CC)) {
		ZEPHIR_CPY_WRT(&all, &parameters);
		ZEPHIR_MAKE_REF(&all);
		ZEPHIR_CALL_FUNCTION(NULL, "array_unshift", NULL, 33, &all, &method);
		ZEPHIR_UNREF(&all);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_create_array(&_1$$3, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&_1$$3, this_ptr);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "registrarRoute");
		zephir_array_fast_append(&_1$$3, &_2$$3);
		ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &_1$$3, &all);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(&method, "match")) {
		ZEPHIR_INIT_VAR(&_3$$4);
		zephir_create_array(&_3$$4, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&_3$$4, this_ptr);
		ZEPHIR_INIT_VAR(&_4$$4);
		ZVAL_STRING(&_4$$4, "doMatch");
		zephir_array_fast_append(&_3$$4, &_4$$4);
		ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &_3$$4, &parameters);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_5);
	object_init_ex(&_5, spl_ce_BadMethodCallException);
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_STRING(&_6, "Method %s::%s does not exist.");
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, "Registrar");
	ZEPHIR_CALL_FUNCTION(&_8, "sprintf", NULL, 17, &_6, &_7, &method);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_5, "__construct", NULL, 112, &_8);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_5, "zim/routing/registrar.zep", 94 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

zend_object *zephir_init_properties_Zim_Routing_Registrar(zend_class_entry *class_type TSRMLS_DC) {

		zval _1$$3;
	zval _0, _2$$3;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("passthru"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			zephir_create_array(&_1$$3, 7, 0 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_2$$3);
			ZVAL_STRING(&_2$$3, "get");
			zephir_array_fast_append(&_1$$3, &_2$$3);
			ZEPHIR_INIT_NVAR(&_2$$3);
			ZVAL_STRING(&_2$$3, "post");
			zephir_array_fast_append(&_1$$3, &_2$$3);
			ZEPHIR_INIT_NVAR(&_2$$3);
			ZVAL_STRING(&_2$$3, "put");
			zephir_array_fast_append(&_1$$3, &_2$$3);
			ZEPHIR_INIT_NVAR(&_2$$3);
			ZVAL_STRING(&_2$$3, "patch");
			zephir_array_fast_append(&_1$$3, &_2$$3);
			ZEPHIR_INIT_NVAR(&_2$$3);
			ZVAL_STRING(&_2$$3, "delete");
			zephir_array_fast_append(&_1$$3, &_2$$3);
			ZEPHIR_INIT_NVAR(&_2$$3);
			ZVAL_STRING(&_2$$3, "options");
			zephir_array_fast_append(&_1$$3, &_2$$3);
			ZEPHIR_INIT_NVAR(&_2$$3);
			ZVAL_STRING(&_2$$3, "any");
			zephir_array_fast_append(&_1$$3, &_2$$3);
			zephir_update_property_zval(this_ptr, SL("passthru"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

