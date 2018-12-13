
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
#include "kernel/array.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"


/**
 * @method get(string $uri, \Closure|array|string|null $info = null)
 * @method post(string $uri, \Closure|array|string|null $info = null)
 * @method put(string $uri, \Closure|array|string|null $info = null)
 * @method delete(string $uri, \Closure|array|string|null $info = null)
 * @method patch(string $uri, \Closure|array|string|null $info = null)
 * @method options(string $uri, \Closure|array|string|null $info = null)
 * @method any(string $uri, \Closure|array|string|null $info = null)
 * @method name(string $value)
 * @method where(array  $where)
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
	 * The attributes to pass on to the router.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_routing_registrar_ce, SL("attributes"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The methods to dynamically pass through to the router.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_routing_registrar_ce, SL("passthru"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The attributes that can be set through this class.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_routing_registrar_ce, SL("allowedAttributes"), ZEND_ACC_PROTECTED TSRMLS_CC);

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
 * Set the value for a given attribute.
 *
 * @param  string  $key
 * @param  mixed  $value
 * @return $this
 *
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Zim_Routing_Registrar, attribute) {

	zval *key_param = NULL, *value, value_sub, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &value);

	zephir_get_strval(&key, key_param);


	zephir_read_property(&_0, this_ptr, SL("allowedAttributes"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_fast_in_array(&key, &_0 TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Attribute [{key}] does not exist.", "zim/routing/registrar.zep", 65);
		return;
	}
	zephir_update_property_array(this_ptr, SL("attributes"), &key, value TSRMLS_CC);
	RETURN_THIS();

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

	zend_string *_3$$3;
	zend_ulong _2$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters, _4$$3, _8$$6;
	zval *method_param = NULL, *parameters_param = NULL, parmeters, k, v, _0, _6, _10, _11, _12, _13, all$$3, *_1$$3, _5$$3, _7$$5, _9$$6;
	zval method;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&parmeters);
	ZVAL_UNDEF(&k);
	ZVAL_UNDEF(&v);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&all$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &method_param, &parameters_param);

	zephir_get_strval(&method, method_param);
	zephir_get_arrval(&parameters, parameters_param);


	zephir_read_property(&_0, this_ptr, SL("passthru"), PH_NOISY_CC | PH_READONLY);
	if (zephir_fast_in_array(&method, &_0 TSRMLS_CC)) {
		zephir_array_append(&all$$3, &method, PH_SEPARATE, "zim/routing/registrar.zep", 114);
		zephir_is_iterable(&parmeters, 0, "zim/routing/registrar.zep", 119);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&parmeters), _2$$3, _3$$3, _1$$3)
		{
			ZEPHIR_INIT_NVAR(&k);
			if (_3$$3 != NULL) { 
				ZVAL_STR_COPY(&k, _3$$3);
			} else {
				ZVAL_LONG(&k, _2$$3);
			}
			ZEPHIR_INIT_NVAR(&v);
			ZVAL_COPY(&v, _1$$3);
			zephir_array_append(&all$$3, &v, PH_SEPARATE, "zim/routing/registrar.zep", 116);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&v);
		ZEPHIR_INIT_NVAR(&k);
		ZEPHIR_INIT_VAR(&_4$$3);
		zephir_create_array(&_4$$3, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&_4$$3, this_ptr);
		ZEPHIR_INIT_VAR(&_5$$3);
		ZVAL_STRING(&_5$$3, "registrarRoute");
		zephir_array_fast_append(&_4$$3, &_5$$3);
		ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &_4$$3, &all$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_read_property(&_6, this_ptr, SL("allowedAttributes"), PH_NOISY_CC | PH_READONLY);
	if (zephir_fast_in_array(&method, &_6 TSRMLS_CC)) {
		zephir_array_fetch_long(&_7$$5, &parameters, 0, PH_NOISY | PH_READONLY, "zim/routing/registrar.zep", 122 TSRMLS_CC);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "attribute", NULL, 0, &method, &_7$$5);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(&method, "match")) {
		ZEPHIR_INIT_VAR(&_8$$6);
		zephir_create_array(&_8$$6, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&_8$$6, this_ptr);
		ZEPHIR_INIT_VAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "doMatch");
		zephir_array_fast_append(&_8$$6, &_9$$6);
		ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &_8$$6, &parameters);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_10);
	object_init_ex(&_10, spl_ce_BadMethodCallException);
	ZEPHIR_INIT_VAR(&_11);
	ZVAL_STRING(&_11, "Method %s::%s does not exist.");
	ZEPHIR_INIT_VAR(&_12);
	ZVAL_STRING(&_12, "Registrar");
	ZEPHIR_CALL_FUNCTION(&_13, "sprintf", NULL, 22, &_11, &_12, &method);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_10, "__construct", NULL, 104, &_13);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_10, "zim/routing/registrar.zep", 128 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

zend_object *zephir_init_properties_Zim_Routing_Registrar(zend_class_entry *class_type TSRMLS_DC) {

		zval _1$$3, _4$$4;
	zval _0, _3, _6, _2$$3, _5$$4, _7$$5;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_4$$4);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("allowedAttributes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			zephir_create_array(&_1$$3, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_2$$3);
			ZVAL_STRING(&_2$$3, "name");
			zephir_array_fast_append(&_1$$3, &_2$$3);
			ZEPHIR_INIT_NVAR(&_2$$3);
			ZVAL_STRING(&_2$$3, "where");
			zephir_array_fast_append(&_1$$3, &_2$$3);
			zephir_update_property_zval(this_ptr, SL("allowedAttributes"), &_1$$3);
		}
		zephir_read_property(&_3, this_ptr, SL("passthru"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_3) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_4$$4);
			zephir_create_array(&_4$$4, 7, 0 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_5$$4);
			ZVAL_STRING(&_5$$4, "get");
			zephir_array_fast_append(&_4$$4, &_5$$4);
			ZEPHIR_INIT_NVAR(&_5$$4);
			ZVAL_STRING(&_5$$4, "post");
			zephir_array_fast_append(&_4$$4, &_5$$4);
			ZEPHIR_INIT_NVAR(&_5$$4);
			ZVAL_STRING(&_5$$4, "put");
			zephir_array_fast_append(&_4$$4, &_5$$4);
			ZEPHIR_INIT_NVAR(&_5$$4);
			ZVAL_STRING(&_5$$4, "patch");
			zephir_array_fast_append(&_4$$4, &_5$$4);
			ZEPHIR_INIT_NVAR(&_5$$4);
			ZVAL_STRING(&_5$$4, "delete");
			zephir_array_fast_append(&_4$$4, &_5$$4);
			ZEPHIR_INIT_NVAR(&_5$$4);
			ZVAL_STRING(&_5$$4, "options");
			zephir_array_fast_append(&_4$$4, &_5$$4);
			ZEPHIR_INIT_NVAR(&_5$$4);
			ZVAL_STRING(&_5$$4, "any");
			zephir_array_fast_append(&_4$$4, &_5$$4);
			zephir_update_property_zval(this_ptr, SL("passthru"), &_4$$4);
		}
		zephir_read_property(&_6, this_ptr, SL("attributes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$5);
			array_init(&_7$$5);
			zephir_update_property_zval(this_ptr, SL("attributes"), &_7$$5);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

