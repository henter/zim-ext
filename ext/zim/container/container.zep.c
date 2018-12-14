
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
#include "kernel/array.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "Zend/zend_closures.h"
#include "kernel/concat.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "ext/spl/spl_exceptions.h"


ZEPHIR_INIT_CLASS(Zim_Container_Container) {

	ZEPHIR_REGISTER_CLASS(Zim\\Container, Container, zim, container_container, zim_container_container_method_entry, 0);

	/**
	 * The current globally available container (if any).
	 *
	 * @var static
	 */
	zend_declare_property_null(zim_container_container_ce, SL("instance"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * An array of the types that have been resolved.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("resolved"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The container's bindings.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("bindings"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The container's method bindings.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("methodBindings"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The container's shared instances.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("instances"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The registered type aliases.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("aliases"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The registered aliases keyed by the abstract name.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("abstractAliases"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The extension closures for services.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("extenders"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The stack of concretions currently being built.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("buildStack"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The parameter override stack.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("with"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The contextual binding map.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("contextual"), ZEND_ACC_PUBLIC TSRMLS_CC);

	zim_container_container_ce->create_object = zephir_init_properties_Zim_Container_Container;
	return SUCCESS;

}

/**
 * Define a contextual binding.
 *
 * @param  array|string  $concrete
 * @return \Zim\Container\ContextualBindingBuilder
 */
PHP_METHOD(Zim_Container_Container, when) {

	zephir_fcall_cache_entry *_2 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *concrete, concrete_sub, aliases, concretes, c, *_0, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&concrete_sub);
	ZVAL_UNDEF(&aliases);
	ZVAL_UNDEF(&concretes);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &concrete);



	ZEPHIR_INIT_VAR(&aliases);
	array_init(&aliases);
	if (Z_TYPE_P(concrete) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&concretes, concrete);
	} else {
		ZEPHIR_INIT_NVAR(&concretes);
		zephir_create_array(&concretes, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&concretes, concrete);
	}
	zephir_is_iterable(&concretes, 0, "zim/container/container.zep", 91);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&concretes), _0)
	{
		ZEPHIR_INIT_NVAR(&c);
		ZVAL_COPY(&c, _0);
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "getalias", &_2, 0, &c);
		zephir_check_call_status();
		zephir_array_append(&aliases, &_1$$3, PH_SEPARATE, "zim/container/container.zep", 89);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&c);
	object_init_ex(return_value, zim_container_contextualbindingbuilder_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 1, this_ptr, &aliases);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Determine if the given abstract type has been bound.
 *
 * @param  string  $abstract
 * @return bool
 */
PHP_METHOD(Zim_Container_Container, bound) {

	zend_bool _1, _3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, _0, _2, _4;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	zephir_read_property(&_0, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
	_1 = zephir_array_isset(&_0, &abstractt);
	if (!(_1)) {
		zephir_read_property(&_2, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
		_1 = zephir_array_isset(&_2, &abstractt);
	}
	_3 = _1;
	if (!(_3)) {
		ZEPHIR_CALL_METHOD(&_4, this_ptr, "isalias", NULL, 0, &abstractt);
		zephir_check_call_status();
		_3 = zephir_is_true(&_4);
	}
	RETURN_MM_BOOL(_3);

}

/**
 *  {@inheritdoc}
 */
PHP_METHOD(Zim_Container_Container, has) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *id, id_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&id_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id);



	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "bound", NULL, 0, id);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Determine if the given abstract type has been resolved.
 *
 * @param  string  $abstract
 * @return bool
 */
PHP_METHOD(Zim_Container_Container, resolved) {

	zend_bool _3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, _0, _2, _4, _1$$3;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isalias", NULL, 0, &abstractt);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "getalias", NULL, 0, &abstractt);
		zephir_check_call_status();
		zephir_get_strval(&abstractt, &_1$$3);
	}
	zephir_read_property(&_2, this_ptr, SL("resolved"), PH_NOISY_CC | PH_READONLY);
	_3 = zephir_array_isset(&_2, &abstractt);
	if (!(_3)) {
		zephir_read_property(&_4, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
		_3 = zephir_array_isset(&_4, &abstractt);
	}
	RETURN_MM_BOOL(_3);

}

/**
 * Determine if a given type is shared.
 *
 * @param  string  $abstract
 * @return bool
 */
PHP_METHOD(Zim_Container_Container, isShared) {

	zend_bool _1, _4;
	zval *abstractt_param = NULL, _0, _2, _3, _5, _6, _7;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	zephir_read_property(&_0, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	_1 = zephir_array_isset(&_0, &abstractt);
	if (!(_1)) {
		zephir_read_property(&_2, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_3, &_2, &abstractt, PH_READONLY, "zim/container/container.zep", 135 TSRMLS_CC);
		_4 = zephir_array_isset_string(&_3, SL("shared"));
		if (_4) {
			zephir_read_property(&_5, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_6, &_5, &abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 135 TSRMLS_CC);
			zephir_array_fetch_string(&_7, &_6, SL("shared"), PH_NOISY | PH_READONLY, "zim/container/container.zep", 135 TSRMLS_CC);
			_4 = ZEPHIR_IS_TRUE_IDENTICAL(&_7);
		}
		_1 = _4;
	}
	RETURN_MM_BOOL(_1);

}

/**
 * Determine if a given string is an alias.
 *
 * @param  string  $name
 * @return bool
 */
PHP_METHOD(Zim_Container_Container, isAlias) {

	zval *name_param = NULL, _0;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	zephir_read_property(&_0, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	RETURN_MM_BOOL(zephir_array_isset(&_0, &name));

}

/**
 * Register a binding with the container.
 *
 * @param  string  $abstract
 * @param  \Closure|string|null  $concrete
 * @param  bool  $shared
 * @return void
 */
PHP_METHOD(Zim_Container_Container, bind) {

	zval _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool shared, _0;
	zval *abstractt_param = NULL, *concrete = NULL, concrete_sub, *shared_param = NULL, __$null, _3, _1$$4;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&concrete_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &abstractt_param, &concrete, &shared_param);

	zephir_get_strval(&abstractt, abstractt_param);
	if (!concrete) {
		concrete = &concrete_sub;
		ZEPHIR_CPY_WRT(concrete, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(concrete);
	}
	if (!shared_param) {
		shared = 0;
	} else {
		shared = zephir_get_boolval(shared_param);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "dropstaleinstances", NULL, 0, &abstractt);
	zephir_check_call_status();
	if (Z_TYPE_P(concrete) == IS_NULL) {
		ZEPHIR_CPY_WRT(concrete, &abstractt);
	}
	_0 = Z_TYPE_P(concrete) == IS_OBJECT;
	if (_0) {
		_0 = zephir_instance_of_ev(concrete, zend_ce_closure TSRMLS_CC);
	}
	if (!(_0)) {
		ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "getclosure", NULL, 0, &abstractt, concrete);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(concrete, &_1$$4);
	}
	ZEPHIR_INIT_VAR(&_2);
	zephir_create_array(&_2, 2, 0 TSRMLS_CC);
	zephir_array_update_string(&_2, SL("concrete"), concrete, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_BOOL(&_3, shared);
	zephir_array_update_string(&_2, SL("shared"), &_3, PH_COPY | PH_SEPARATE);
	zephir_update_property_array(this_ptr, SL("bindings"), &abstractt, &_2 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Get the Closure to be used when building a type.
 *
 * @param  string  $abstract
 * @param  string  $concrete
 * @return \Closure
 */
PHP_METHOD(Zim_Container_Container, getClosure) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, *concrete_param = NULL;
	zval abstractt, concrete;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&concrete);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &abstractt_param, &concrete_param);

	zephir_get_strval(&abstractt, abstractt_param);
	zephir_get_strval(&concrete, concrete_param);


	object_init_ex(return_value, zim_container_containergetclosureclosurezero_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 2, &abstractt, &concrete);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Determine if the container has a method binding.
 *
 * @param  string  $method
 * @return bool
 */
PHP_METHOD(Zim_Container_Container, hasMethodBinding) {

	zval *method_param = NULL, _0;
	zval method;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &method_param);

	zephir_get_strval(&method, method_param);


	zephir_read_property(&_0, this_ptr, SL("methodBindings"), PH_NOISY_CC | PH_READONLY);
	RETURN_MM_BOOL(zephir_array_isset(&_0, &method));

}

/**
 * Bind a callback to resolve with Container::call.
 *
 * @param  array|string  $method
 * @param  \Closure  $callback
 * @return void
 */
PHP_METHOD(Zim_Container_Container, bindMethod) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *method, method_sub, *callback, callback_sub, tmpThis1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method_sub);
	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&tmpThis1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &method, &callback);



	ZEPHIR_CALL_METHOD(NULL, this_ptr, "parsebindmethod", NULL, 0, method);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&tmpThis1, this_ptr);
	zephir_update_property_array(this_ptr, SL("methodBindings"), &tmpThis1, callback TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Get the method to be bound in class@method format.
 *
 * @param  array|string $method
 * @return string
 */
PHP_METHOD(Zim_Container_Container, parseBindMethod) {

	zval *method, method_sub, _0$$3, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);

	zephir_fetch_params(0, 1, 0, &method);



	if (Z_TYPE_P(method) == IS_ARRAY) {
		zephir_array_fetch_long(&_0$$3, method, 0, PH_NOISY | PH_READONLY, "zim/container/container.zep", 228 TSRMLS_CC);
		zephir_array_fetch_long(&_1$$3, method, 1, PH_NOISY | PH_READONLY, "zim/container/container.zep", 228 TSRMLS_CC);
		ZEPHIR_CONCAT_VSV(return_value, &_0$$3, "@", &_1$$3);
		return;
	}
	RETVAL_ZVAL(method, 1, 0);
	return;

}

/**
 * Get the method binding for the given method.
 *
 * @param  string  $method
 * @param  mixed  $instance
 * @return mixed
 */
PHP_METHOD(Zim_Container_Container, callMethodBinding) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *method_param = NULL, *instance, instance_sub, _0, _1;
	zval method;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&instance_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &method_param, &instance);

	zephir_get_strval(&method, method_param);


	zephir_read_property(&_0, this_ptr, SL("methodBindings"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_1, &_0, &method, PH_NOISY | PH_READONLY, "zim/container/container.zep", 242 TSRMLS_CC);
	ZEPHIR_RETURN_CALL_FUNCTION("call_user_func", NULL, 3, &_1, instance, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add a contextual binding to the container.
 *
 * @param  string  $concrete
 * @param  string  $abstract
 * @param  \Closure|string  $implementation
 * @return void
 */
PHP_METHOD(Zim_Container_Container, addContextualBinding) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *concrete_param = NULL, *abstractt_param = NULL, *implementation, implementation_sub, tmpThis1;
	zval concrete, abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&concrete);
	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&implementation_sub);
	ZVAL_UNDEF(&tmpThis1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &concrete_param, &abstractt_param, &implementation);

	zephir_get_strval(&concrete, concrete_param);
	zephir_get_strval(&abstractt, abstractt_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "getalias", NULL, 0, &abstractt);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&tmpThis1, this_ptr);
	zephir_update_property_array_multi(this_ptr, SL("contextual"), implementation TSRMLS_CC, SL("zz"), 2, &concrete, &tmpThis1);
	ZEPHIR_MM_RESTORE();

}

/**
 * Register a shared binding in the container.
 *
 * @param  string  $abstract
 * @param  \Closure|string|null  $concrete
 * @return void
 */
PHP_METHOD(Zim_Container_Container, singleton) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, *concrete = NULL, concrete_sub, __$null, _0;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&concrete_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &abstractt_param, &concrete);

	zephir_get_strval(&abstractt, abstractt_param);
	if (!concrete) {
		concrete = &concrete_sub;
		concrete = &__$null;
	}


	ZVAL_BOOL(&_0, 1);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "bind", NULL, 0, &abstractt, concrete, &_0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * "Extend" an abstract type in the container.
 *
 * @param  string    $abstract
 * @param  \Closure  $closure
 * @return void
 *
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Zim_Container_Container, extend) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, *closure, closure_sub, _0, _1, _2$$3, _3$$3, _4$$3;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&closure_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &abstractt_param, &closure);

	zephir_get_strval(&abstractt, abstractt_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getalias", NULL, 0, &abstractt);
	zephir_check_call_status();
	zephir_get_strval(&abstractt, &_0);
	zephir_read_property(&_1, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, &abstractt)) {
		zephir_read_property(&_2$$3, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_3$$3, &_2$$3, &abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 289 TSRMLS_CC);
		ZEPHIR_CALL_ZVAL_FUNCTION(&_4$$3, closure, NULL, 0, &_3$$3, this_ptr);
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("instances"), &abstractt, &_4$$3 TSRMLS_CC);
	} else {
		zephir_update_property_array_multi(this_ptr, SL("extenders"), closure TSRMLS_CC, SL("za"), 2, &abstractt);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Register an existing instance as shared in the container.
 *
 * @param  string  $abstract
 * @param  mixed   $instance
 * @return mixed
 */
PHP_METHOD(Zim_Container_Container, instance) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, *instance, instance_sub, _0;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&instance_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &abstractt_param, &instance);

	zephir_get_strval(&abstractt, abstractt_param);


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "removeabstractalias", NULL, 0, &abstractt);
	zephir_check_call_status();
	zephir_read_property(&_0, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, &abstractt, PH_SEPARATE);
	zephir_update_property_array(this_ptr, SL("instances"), &abstractt, instance TSRMLS_CC);
	RETVAL_ZVAL(instance, 1, 0);
	RETURN_MM();

}

/**
 * Remove an alias from the contextual binding alias cache.
 *
 * @param  string  $searched
 * @return void
 */
PHP_METHOD(Zim_Container_Container, removeAbstractAlias) {

	zend_string *_4, *_7$$4;
	zend_ulong _3, _6$$4;
	zval *searched_param = NULL, abstractt, aliases, index, alias, _0, _1, *_2, *_5$$4, _8$$6, _9$$6;
	zval searched;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&searched);
	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&aliases);
	ZVAL_UNDEF(&index);
	ZVAL_UNDEF(&alias);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &searched_param);

	zephir_get_strval(&searched, searched_param);


	zephir_read_property(&_0, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset(&_0, &searched))) {
		RETURN_MM_NULL();
	}
	zephir_read_property(&_1, this_ptr, SL("abstractAliases"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_1, 0, "zim/container/container.zep", 332);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_1), _3, _4, _2)
	{
		ZEPHIR_INIT_NVAR(&abstractt);
		if (_4 != NULL) { 
			ZVAL_STR_COPY(&abstractt, _4);
		} else {
			ZVAL_LONG(&abstractt, _3);
		}
		ZEPHIR_INIT_NVAR(&aliases);
		ZVAL_COPY(&aliases, _2);
		zephir_is_iterable(&aliases, 0, "zim/container/container.zep", 331);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&aliases), _6$$4, _7$$4, _5$$4)
		{
			ZEPHIR_INIT_NVAR(&index);
			if (_7$$4 != NULL) { 
				ZVAL_STR_COPY(&index, _7$$4);
			} else {
				ZVAL_LONG(&index, _6$$4);
			}
			ZEPHIR_INIT_NVAR(&alias);
			ZVAL_COPY(&alias, _5$$4);
			if (ZEPHIR_IS_EQUAL(&alias, &searched)) {
				zephir_read_property(&_8$$6, this_ptr, SL("abstractAliases"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_9$$6, &_8$$6, &abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 327 TSRMLS_CC);
				zephir_array_unset(&_9$$6, &index, PH_SEPARATE);
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&alias);
		ZEPHIR_INIT_NVAR(&index);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&aliases);
	ZEPHIR_INIT_NVAR(&abstractt);
	ZEPHIR_MM_RESTORE();

}

/**
 * Alias a type to a different name.
 *
 * @param  string  $abstract
 * @param  string  $alias
 * @return void
 */
PHP_METHOD(Zim_Container_Container, alias) {

	zval *abstractt_param = NULL, *alias_param = NULL;
	zval abstractt, alias;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&alias);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &abstractt_param, &alias_param);

	zephir_get_strval(&abstractt, abstractt_param);
	zephir_get_strval(&alias, alias_param);


	zephir_update_property_array(this_ptr, SL("aliases"), &alias, &abstractt TSRMLS_CC);
	zephir_update_property_array_multi(this_ptr, SL("abstractAliases"), &alias TSRMLS_CC, SL("za"), 2, &abstractt);
	ZEPHIR_MM_RESTORE();

}

/**
 * Call the given Closure / class@method and inject its dependencies.
 *
 * @param  callable|string  $callback
 * @param  array  $parameters
 * @param  string|null  $defaultMethod
 * @return mixed
 */
PHP_METHOD(Zim_Container_Container, call) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval parameters;
	zval *callback, callback_sub, *parameters_param = NULL, *defaultMethod = NULL, defaultMethod_sub, __$null;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&defaultMethod_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &callback, &parameters_param, &defaultMethod);

	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}
	if (!defaultMethod) {
		defaultMethod = &defaultMethod_sub;
		defaultMethod = &__$null;
	}


	ZEPHIR_RETURN_CALL_CE_STATIC(zim_container_boundmethod_ce, "call", &_0, 0, this_ptr, callback, &parameters, defaultMethod);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Resolve the given type from the container.
 *
 * @param  string  $abstract
 * @param  array  $parameters
 * @return mixed
 */
PHP_METHOD(Zim_Container_Container, make) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters;
	zval *abstractt_param = NULL, *parameters_param = NULL;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &abstractt_param, &parameters_param);

	zephir_get_strval(&abstractt, abstractt_param);
	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "resolve", NULL, 0, &abstractt, &parameters);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * get service
 */
PHP_METHOD(Zim_Container_Container, get) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *id, id_sub, e, _0, _1$$4, _2$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&id_sub);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &id);




	/* try_start_1: */

		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "resolve", NULL, 0, id);
		zephir_check_call_status_or_jump(try_end_1);
		RETURN_MM();

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_VAR(&_0);
		ZVAL_OBJ(&_0, EG(exception));
		Z_ADDREF_P(&_0);
		if (zephir_instance_of_ev(&_0, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CPY_WRT(&e, &_0);
			ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "has", NULL, 0, id);
			zephir_check_call_status();
			if (zephir_is_true(&_1$$4)) {
				zephir_throw_exception_debug(&e, "zim/container/container.zep", 383 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_VAR(&_2$$4);
			object_init_ex(&_2$$4, zim_container_entrynotfoundexception_ce);
			ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_2$$4, "zim/container/container.zep", 385 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}

}

/**
 * Resolve the given type from the container.
 *
 * @param  string  $abstract
 * @param  array  $parameters
 * @return mixed
 */
PHP_METHOD(Zim_Container_Container, resolve) {

	zend_bool needsContextualBuild = 0, _1, _4, _12;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters;
	zval *abstractt_param = NULL, *parameters_param = NULL, __$true, concrete, obj, extender, _0, _2, _3, _7, _8, *_9, _11, _13, _5$$3, _6$$3, _10$$6;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&concrete);
	ZVAL_UNDEF(&obj);
	ZVAL_UNDEF(&extender);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &abstractt_param, &parameters_param);

	zephir_get_strval(&abstractt, abstractt_param);
	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getalias", NULL, 0, &abstractt);
	zephir_check_call_status();
	zephir_get_strval(&abstractt, &_0);
	_1 = !(ZEPHIR_IS_EMPTY(&parameters));
	if (!(_1)) {
		ZEPHIR_CALL_METHOD(&_2, this_ptr, "getcontextualconcrete", NULL, 0, &abstractt);
		zephir_check_call_status();
		_1 = !(Z_TYPE_P(&_2) == IS_NULL);
	}
	needsContextualBuild = _1;
	zephir_read_property(&_3, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	_4 = zephir_array_isset(&_3, &abstractt);
	if (_4) {
		_4 = !needsContextualBuild;
	}
	if (_4) {
		zephir_read_property(&_5$$3, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_6$$3, &_5$$3, &abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 406 TSRMLS_CC);
		RETURN_CTOR(&_6$$3);
	}
	zephir_update_property_array_append(this_ptr, SL("with"), &parameters TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&concrete, this_ptr, "getconcrete", NULL, 0, &abstractt);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_7, this_ptr, "isbuildable", NULL, 0, &concrete, &abstractt);
	zephir_check_call_status();
	if (zephir_is_true(&_7)) {
		ZEPHIR_CALL_METHOD(&obj, this_ptr, "build", NULL, 0, &concrete);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&obj, this_ptr, "make", NULL, 0, &concrete);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_8, this_ptr, "getextenders", NULL, 0, &abstractt);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "zim/container/container.zep", 427);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
	{
		ZEPHIR_INIT_NVAR(&extender);
		ZVAL_COPY(&extender, _9);
		ZEPHIR_CALL_ZVAL_FUNCTION(&_10$$6, &extender, NULL, 0, &obj, this_ptr);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&obj, &_10$$6);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&extender);
	ZEPHIR_CALL_METHOD(&_11, this_ptr, "isshared", NULL, 0, &abstractt);
	zephir_check_call_status();
	_12 = zephir_is_true(&_11);
	if (_12) {
		_12 = !needsContextualBuild;
	}
	if (_12) {
		zephir_update_property_array(this_ptr, SL("instances"), &abstractt, &obj TSRMLS_CC);
	}
	zephir_update_property_array(this_ptr, SL("resolved"), &abstractt, &__$true TSRMLS_CC);
	zephir_read_property(&_13, this_ptr, SL("with"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_MAKE_REF(&_13);
	ZEPHIR_CALL_FUNCTION(NULL, "array_pop", NULL, 5, &_13);
	ZEPHIR_UNREF(&_13);
	zephir_check_call_status();
	RETURN_CCTOR(&obj);

}

/**
 * Get the concrete type for a given abstract.
 *
 * @param  string  $abstract
 * @return mixed   $concrete
 */
PHP_METHOD(Zim_Container_Container, getConcrete) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, concrete, _0, _1$$4, _2$$4, _3$$4;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&concrete);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	ZEPHIR_CALL_METHOD(&concrete, this_ptr, "getcontextualconcrete", NULL, 0, &abstractt);
	zephir_check_call_status();
	if (!(Z_TYPE_P(&concrete) == IS_NULL)) {
		RETURN_CCTOR(&concrete);
	}
	zephir_read_property(&_0, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_0, &abstractt)) {
		zephir_read_property(&_1$$4, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_2$$4, &_1$$4, &abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 456 TSRMLS_CC);
		zephir_array_fetch_string(&_3$$4, &_2$$4, SL("concrete"), PH_NOISY | PH_READONLY, "zim/container/container.zep", 456 TSRMLS_CC);
		RETURN_CTOR(&_3$$4);
	}
	RETURN_CTOR(&abstractt);

}

/**
 * Get the contextual concrete binding for the given abstract.
 *
 * @param  string  $abstract
 * @return string|null
 */
PHP_METHOD(Zim_Container_Container, getContextualConcrete) {

	zephir_fcall_cache_entry *_0 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, binding, alias, _1, _2, _3, *_4;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&binding);
	ZVAL_UNDEF(&alias);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	ZEPHIR_CALL_METHOD(&binding, this_ptr, "findincontextualbindings", &_0, 0, &abstractt);
	zephir_check_call_status();
	if (!(Z_TYPE_P(&binding) == IS_NULL)) {
		RETURN_CCTOR(&binding);
	}
	zephir_read_property(&_1, this_ptr, SL("abstractAliases"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset(&_1, &abstractt))) {
		RETURN_MM_NULL();
	}
	zephir_read_property(&_2, this_ptr, SL("abstractAliases"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_3, &_2, &abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 482 TSRMLS_CC);
	zephir_is_iterable(&_3, 0, "zim/container/container.zep", 488);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_3), _4)
	{
		ZEPHIR_INIT_NVAR(&alias);
		ZVAL_COPY(&alias, _4);
		ZEPHIR_CALL_METHOD(&binding, this_ptr, "findincontextualbindings", &_0, 0, &alias);
		zephir_check_call_status();
		if (!(Z_TYPE_P(&binding) == IS_NULL)) {
			RETURN_CCTOR(&binding);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&alias);
	ZEPHIR_MM_RESTORE();

}

/**
 * Find the concrete binding for the given abstract in the contextual binding array.
 *
 * @param  string  $abstract
 * @return string|null
 */
PHP_METHOD(Zim_Container_Container, findInContextualBindings) {

	zval *abstractt_param = NULL, end, _0, _1, _2, _3, _4, _5$$4, _6$$4, _7$$4;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&end);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	zephir_read_property(&_0, this_ptr, SL("buildStack"), PH_NOISY_CC | PH_READONLY);
	if (zephir_fast_count_int(&_0 TSRMLS_CC) == 0) {
		RETURN_MM_NULL();
	}
	zephir_read_property(&_1, this_ptr, SL("buildStack"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_2, this_ptr, SL("buildStack"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&end, &_1, (zephir_fast_count_int(&_2 TSRMLS_CC) - 1), PH_NOISY | PH_READONLY, "zim/container/container.zep", 503 TSRMLS_CC);
	zephir_read_property(&_3, this_ptr, SL("contextual"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_4, &_3, &end, PH_READONLY, "zim/container/container.zep", 504 TSRMLS_CC);
	if (zephir_array_isset(&_4, &abstractt)) {
		zephir_read_property(&_5$$4, this_ptr, SL("contextual"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_6$$4, &_5$$4, &end, PH_NOISY | PH_READONLY, "zim/container/container.zep", 505 TSRMLS_CC);
		zephir_array_fetch(&_7$$4, &_6$$4, &abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 505 TSRMLS_CC);
		RETURN_CTOR(&_7$$4);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Determine if the given concrete is buildable.
 *
 * @param  mixed   $concrete
 * @param  string  $abstract
 * @return bool
 */
PHP_METHOD(Zim_Container_Container, isBuildable) {

	zend_bool _0, _1;
	zval abstractt;
	zval *concrete, concrete_sub, *abstractt_param = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&concrete_sub);
	ZVAL_UNDEF(&abstractt);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &concrete, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	_0 = ZEPHIR_IS_IDENTICAL(concrete, &abstractt);
	if (!(_0)) {
		_1 = Z_TYPE_P(concrete) == IS_OBJECT;
		if (_1) {
			_1 = zephir_instance_of_ev(concrete, zend_ce_closure TSRMLS_CC);
		}
		_0 = _1;
	}
	RETURN_MM_BOOL(_0);

}

/**
 * Instantiate a concrete instance of the given type.
 *
 * @param  string  $concrete
 * @return mixed
 *
 * @throws \Zim\Container\BindingResolutionException
 */
PHP_METHOD(Zim_Container_Container, build) {

	zend_class_entry *_7$$5;
	zval _1$$3;
	zend_bool _0;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *concrete_param = NULL, reflector, constructor, dependencies, instances, _3, _8, _2$$3, _4$$5, _6$$5;
	zval concrete;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&concrete);
	ZVAL_UNDEF(&reflector);
	ZVAL_UNDEF(&constructor);
	ZVAL_UNDEF(&dependencies);
	ZVAL_UNDEF(&instances);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &concrete_param);

	zephir_get_strval(&concrete, concrete_param);


	_0 = 1 != 1;
	if (_0) {
		_0 = zephir_is_callable(&concrete TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_create_array(&_1$$3, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&_1$$3, this_ptr);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "getlastparameteroverride", NULL, 0);
		zephir_check_call_status();
		zephir_array_fast_append(&_1$$3, &_2$$3);
		ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, &concrete, &_1$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&reflector);
	object_init_ex(&reflector, zephir_get_internal_ce(SL("reflectionclass")));
	ZEPHIR_CALL_METHOD(NULL, &reflector, "__construct", NULL, 6, &concrete);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, &reflector, "isinstantiable", NULL, 7);
	zephir_check_call_status();
	if (!(zephir_is_true(&_3))) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notinstantiable", NULL, 0, &concrete);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_update_property_array_append(this_ptr, SL("buildStack"), &concrete TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&constructor, &reflector, "getconstructor", NULL, 8);
	zephir_check_call_status();
	if (Z_TYPE_P(&constructor) == IS_NULL) {
		zephir_read_property(&_4$$5, this_ptr, SL("buildStack"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_MAKE_REF(&_4$$5);
		ZEPHIR_CALL_FUNCTION(NULL, "array_pop", &_5, 5, &_4$$5);
		ZEPHIR_UNREF(&_4$$5);
		zephir_check_call_status();
		zephir_fetch_safe_class(&_6$$5, &concrete);
		_7$$5 = zephir_fetch_class_str_ex(Z_STRVAL_P(&_6$$5), Z_STRLEN_P(&_6$$5), ZEND_FETCH_CLASS_AUTO);
		object_init_ex(return_value, _7$$5);
		if (zephir_has_constructor(return_value TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 0);
			zephir_check_call_status();
		}
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&dependencies, &constructor, "getparameters", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&instances, this_ptr, "resolvedependencies", NULL, 0, &dependencies);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("buildStack"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_MAKE_REF(&_8);
	ZEPHIR_CALL_FUNCTION(NULL, "array_pop", &_5, 5, &_8);
	ZEPHIR_UNREF(&_8);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&reflector, "newinstanceargs", NULL, 9, &instances);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Resolve all of the dependencies from the ReflectionParameters.
 *
 * @param  array  $dependencies
 * @return array
 */
PHP_METHOD(Zim_Container_Container, resolveDependencies) {

	zephir_fcall_cache_entry *_2 = NULL, *_4 = NULL, *_7 = NULL, *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *dependencies_param = NULL, results, dependency, *_0, _1$$3, _5$$3, _6$$3, _3$$4;
	zval dependencies;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&dependencies);
	ZVAL_UNDEF(&results);
	ZVAL_UNDEF(&dependency);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_3$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &dependencies_param);

	zephir_get_arrval(&dependencies, dependencies_param);


	ZEPHIR_INIT_VAR(&results);
	array_init(&results);
	zephir_is_iterable(&dependencies, 0, "zim/container/container.zep", 590);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&dependencies), _0)
	{
		ZEPHIR_INIT_NVAR(&dependency);
		ZVAL_COPY(&dependency, _0);
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "hasparameteroverride", &_2, 0, &dependency);
		zephir_check_call_status();
		if (zephir_is_true(&_1$$3)) {
			ZEPHIR_CALL_METHOD(&_3$$4, this_ptr, "getparameteroverride", &_4, 0, &dependency);
			zephir_check_call_status();
			zephir_array_append(&results, &_3$$4, PH_SEPARATE, "zim/container/container.zep", 582);
			continue;
		}
		ZEPHIR_INIT_LNVAR(_5$$3);
		ZEPHIR_CALL_METHOD(&_6$$3, &dependency, "getclass", NULL, 0);
		zephir_check_call_status();
		if (Z_TYPE_P(&_6$$3) == IS_NULL) {
			ZEPHIR_CALL_METHOD(&_5$$3, this_ptr, "resolveprimitive", &_7, 0, &dependency);
			zephir_check_call_status();
		} else {
			ZEPHIR_CALL_METHOD(&_5$$3, this_ptr, "resolveclass", &_8, 0, &dependency);
			zephir_check_call_status();
		}
		zephir_array_append(&results, &_5$$3, PH_SEPARATE, "zim/container/container.zep", 588);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&dependency);
	RETURN_CCTOR(&results);

}

/**
 * Determine if the given dependency has a parameter override.
 *
 * @param  \ReflectionParameter  $dependency
 * @return bool
 */
PHP_METHOD(Zim_Container_Container, hasParameterOverride) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *dependency, dependency_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&dependency_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &dependency);



	zephir_read_property(&_0, dependency, SL("name"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getlastparameteroverride", NULL, 0);
	zephir_check_call_status();
	RETURN_MM_BOOL(zephir_array_key_exists(&_1, &_0 TSRMLS_CC));

}

/**
 * Get a parameter override for a dependency.
 *
 * @param  \ReflectionParameter  $dependency
 * @return mixed
 */
PHP_METHOD(Zim_Container_Container, getParameterOverride) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *dependency, dependency_sub, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&dependency_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &dependency);



	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getlastparameteroverride", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&_2);
	zephir_read_property(&_2, dependency, SL("name"), PH_NOISY_CC);
	zephir_array_fetch(&_1, &_0, &_2, PH_NOISY | PH_READONLY, "zim/container/container.zep", 612 TSRMLS_CC);
	RETURN_CTOR(&_1);

}

/**
 * Get the last parameter override.
 *
 * @return array
 */
PHP_METHOD(Zim_Container_Container, getLastParameterOverride) {

	zval _0, _1, _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("with"), PH_NOISY_CC | PH_READONLY);
	if (zephir_fast_count_int(&_1 TSRMLS_CC)) {
		zephir_read_property(&_2, this_ptr, SL("with"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_MAKE_REF(&_2);
		ZEPHIR_CALL_FUNCTION(&_0, "end", NULL, 10, &_2);
		ZEPHIR_UNREF(&_2);
		zephir_check_call_status();
	} else {
		array_init(&_0);
	}
	RETURN_CCTOR(&_0);

}

/**
 * Resolve a non-class hinted primitive dependency.
 *
 * @param  \ReflectionParameter  $parameter
 * @return mixed
 *
 * @throws \Zim\Container\BindingResolutionException
 */
PHP_METHOD(Zim_Container_Container, resolvePrimitive) {

	zend_bool _3$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameter, parameter_sub, concrete, _0, _1, _4, _2$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameter_sub);
	ZVAL_UNDEF(&concrete);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameter);



	zephir_read_property(&_0, parameter, SL("name"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SV(&_1, "$", &_0);
	ZEPHIR_CALL_METHOD(&concrete, this_ptr, "getcontextualconcrete", NULL, 0, &_1);
	zephir_check_call_status();
	if (!(Z_TYPE_P(&concrete) == IS_NULL)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		_3$$3 = Z_TYPE_P(&concrete) == IS_OBJECT;
		if (_3$$3) {
			_3$$3 = zephir_instance_of_ev(&concrete, zend_ce_closure TSRMLS_CC);
		}
		if (_3$$3) {
			ZEPHIR_CALL_ZVAL_FUNCTION(&_2$$3, &concrete, NULL, 0, this_ptr);
			zephir_check_call_status();
		} else {
			ZEPHIR_CPY_WRT(&_2$$3, &concrete);
		}
		RETURN_CCTOR(&_2$$3);
	}
	ZEPHIR_CALL_METHOD(&_4, parameter, "isdefaultvalueavailable", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_4)) {
		ZEPHIR_RETURN_CALL_METHOD(parameter, "getdefaultvalue", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "unresolvableprimitive", NULL, 0, parameter);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Resolve a class based dependency from the container.
 *
 * @param  \ReflectionParameter  $parameter
 * @return mixed
 *
 * @throws \Zim\Container\BindingResolutionException
 */
PHP_METHOD(Zim_Container_Container, resolveClass) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameter, parameter_sub, e, _2, _0$$3, _1$$3, _3$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameter_sub);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameter);




	/* try_start_1: */

		ZEPHIR_CALL_METHOD(&_0$$3, parameter, "getclass", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);
		zephir_read_property(&_1$$3, &_0$$3, SL("name"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "make", NULL, 0, &_1$$3);
		zephir_check_call_status_or_jump(try_end_1);
		RETURN_MM();

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_VAR(&_2);
		ZVAL_OBJ(&_2, EG(exception));
		Z_ADDREF_P(&_2);
		if (zephir_instance_of_ev(&_2, zim_container_bindingresolutionexception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CPY_WRT(&e, &_2);
			ZEPHIR_CALL_METHOD(&_3$$4, parameter, "isoptional", NULL, 0);
			zephir_check_call_status();
			if (zephir_is_true(&_3$$4)) {
				ZEPHIR_RETURN_CALL_METHOD(parameter, "getdefaultvalue", NULL, 0);
				zephir_check_call_status();
				RETURN_MM();
			}
			zephir_throw_exception_debug(&e, "zim/container/container.zep", 665 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}

}

/**
 * Throw an exception that the concrete is not instantiable.
 *
 * @param  string  $concrete
 * @return void
 *
 * @throws \Zim\Container\BindingResolutionException
 */
PHP_METHOD(Zim_Container_Container, notInstantiable) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *concrete_param = NULL, previous, message, _0, _2, _1$$3;
	zval concrete;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&concrete);
	ZVAL_UNDEF(&previous);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &concrete_param);

	zephir_get_strval(&concrete, concrete_param);


	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("buildStack"), PH_NOISY_CC);
	ZEPHIR_INIT_VAR(&message);
	if (!(ZEPHIR_IS_EMPTY(&_0))) {
		zephir_read_property(&_1$$3, this_ptr, SL("buildStack"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&previous);
		zephir_fast_join_str(&previous, SL(", "), &_1$$3 TSRMLS_CC);
		ZVAL_STRING(&message, "Target [{concrete}] is not instantiable while building [{previous}].");
	} else {
		ZVAL_STRING(&message, "Target [{concrete}] is not instantiable.");
	}
	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, zim_container_bindingresolutionexception_ce);
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 4, &message);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "zim/container/container.zep", 687 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Throw an exception for an unresolvable primitive.
 *
 * @param  \ReflectionParameter  $parameter
 * @return void
 *
 * @throws \Zim\Container\BindingResolutionException
 */
PHP_METHOD(Zim_Container_Container, unresolvablePrimitive) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *parameter, parameter_sub, message, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parameter_sub);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameter);



	ZEPHIR_INIT_VAR(&message);
	ZVAL_STRING(&message, "Unresolvable dependency resolving [{parameter}] in class {parameter->getDeclaringClass()->getName()}");
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, zim_container_bindingresolutionexception_ce);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 4, &message);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_0, "zim/container/container.zep", 703 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Get the container's bindings.
 *
 * @return array
 */
PHP_METHOD(Zim_Container_Container, getBindings) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "bindings");

}

/**
 * Get the alias for an abstract if available.
 *
 * @param  string  $abstract
 * @return string
 *
 * @throws \LogicException
 */
PHP_METHOD(Zim_Container_Container, getAlias) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, _0, _1, _2, _3, _4;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	zephir_read_property(&_0, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset(&_0, &abstractt))) {
		RETURN_CTOR(&abstractt);
	}
	zephir_read_property(&_1, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_2, &_1, &abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 729 TSRMLS_CC);
	if (ZEPHIR_IS_IDENTICAL(&_2, &abstractt)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_LogicException, "[{abstractt}] is aliased to itself.", "zim/container/container.zep", 730);
		return;
	}
	zephir_read_property(&_3, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_4, &_3, &abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 732 TSRMLS_CC);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getalias", NULL, 11, &_4);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Get the extender callbacks for a given type.
 *
 * @param  string  $abstract
 * @return array
 */
PHP_METHOD(Zim_Container_Container, getExtenders) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, tmpArray40cd750bba9870f18aada2478b24840a, _0, _1, _2$$3, _3$$3;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&tmpArray40cd750bba9870f18aada2478b24840a);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getalias", NULL, 0, &abstractt);
	zephir_check_call_status();
	zephir_get_strval(&abstractt, &_0);
	zephir_read_property(&_1, this_ptr, SL("extenders"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, &abstractt)) {
		zephir_read_property(&_2$$3, this_ptr, SL("extenders"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_3$$3, &_2$$3, &abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 747 TSRMLS_CC);
		RETURN_CTOR(&_3$$3);
	}
	ZEPHIR_INIT_VAR(&tmpArray40cd750bba9870f18aada2478b24840a);
	array_init(&tmpArray40cd750bba9870f18aada2478b24840a);
	RETURN_CCTOR(&tmpArray40cd750bba9870f18aada2478b24840a);

}

/**
 * Remove all of the extender callbacks for a given type.
 *
 * @param  string  $abstract
 * @return void
 */
PHP_METHOD(Zim_Container_Container, forgetExtenders) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt_param = NULL, ext, _0;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&ext);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	ZEPHIR_CALL_METHOD(&ext, this_ptr, "getalias", NULL, 0, &abstractt);
	zephir_check_call_status();
	zephir_read_property(&_0, this_ptr, SL("extenders"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, &ext, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Drop all of the stale instances and aliases.
 *
 * @param  string  $abstract
 * @return void
 */
PHP_METHOD(Zim_Container_Container, dropStaleInstances) {

	zval *abstractt_param = NULL, _0, _1;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	zephir_read_property(&_0, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, &abstractt, PH_SEPARATE);
	zephir_read_property(&_1, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_1, &abstractt, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Remove a resolved instance from the instance cache.
 *
 * @param  string  $abstract
 * @return void
 */
PHP_METHOD(Zim_Container_Container, forgetInstance) {

	zval *abstractt_param = NULL, _0;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	zephir_read_property(&_0, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, &abstractt, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Clear all of the instances from the container.
 *
 * @return void
 */
PHP_METHOD(Zim_Container_Container, forgetInstances) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("instances"), &_0);
	ZEPHIR_MM_RESTORE();

}

/**
 * Flush the container of all bindings and resolved instances.
 *
 * @return void
 */
PHP_METHOD(Zim_Container_Container, flush) {

	zval _0, _1, _2, _3, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("aliases"), &_0);
	ZEPHIR_INIT_VAR(&_1);
	array_init(&_1);
	zephir_update_property_zval(this_ptr, SL("resolved"), &_1);
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zephir_update_property_zval(this_ptr, SL("bindings"), &_2);
	ZEPHIR_INIT_VAR(&_3);
	array_init(&_3);
	zephir_update_property_zval(this_ptr, SL("instances"), &_3);
	ZEPHIR_INIT_VAR(&_4);
	array_init(&_4);
	zephir_update_property_zval(this_ptr, SL("abstractAliases"), &_4);
	ZEPHIR_MM_RESTORE();

}

/**
 * Set the globally available instance of the container.
 *
 * @return static
 */
PHP_METHOD(Zim_Container_Container, getInstance) {

	zval _0, _2, _1$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();

	zephir_read_static_property_ce(&_0, zim_container_container_ce, SL("instance"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, zim_container_container_ce);
		if (zephir_has_constructor(&_1$$3 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 0);
			zephir_check_call_status();
		}
		zend_update_static_property(zim_container_container_ce, ZEND_STRL("instance"), &_1$$3);
	}
	zephir_read_static_property_ce(&_2, zim_container_container_ce, SL("instance"), PH_NOISY_CC | PH_READONLY);
	RETURN_CTOR(&_2);

}

/**
 * Set the shared instance of the container.
 *
 * @param  Container|null  $container
 * @return Container|static
 */
PHP_METHOD(Zim_Container_Container, setInstance) {

	zval *container = NULL, container_sub, __$null, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 0, 1, &container);

	if (!container) {
		container = &container_sub;
		container = &__$null;
	}


	zend_update_static_property(zim_container_container_ce, ZEND_STRL("instance"), container);
	zephir_read_static_property_ce(&_0, zim_container_container_ce, SL("instance"), PH_NOISY_CC | PH_READONLY);
	RETURN_CTORW(&_0);

}

/**
 * Set the value at a given key.
 *
 * @param  string  $key
 * @param  mixed   $value
 * @return void
 */
PHP_METHOD(Zim_Container_Container, set) {

	zend_bool _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *value, value_sub, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &value);

	zephir_get_strval(&key, key_param);


	ZEPHIR_INIT_VAR(&_0);
	_1 = Z_TYPE_P(value) == IS_OBJECT;
	if (_1) {
		_1 = zephir_instance_of_ev(value, zend_ce_closure TSRMLS_CC);
	}
	if (_1) {
		ZEPHIR_CPY_WRT(&_0, value);
	} else {
		ZEPHIR_INIT_NVAR(&_0);
		object_init_ex(&_0, zim_container_containersetclosureone_ce);
		ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 12, value);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "bind", NULL, 0, &key, &_0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Unset the value at a given key.
 *
 * @param  string  $key
 * @return void
 */
PHP_METHOD(Zim_Container_Container, remove) {

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


	zephir_read_property(&_0, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, &key, PH_SEPARATE);
	zephir_read_property(&_1, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_1, &key, PH_SEPARATE);
	zephir_read_property(&_2, this_ptr, SL("resolved"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_2, &key, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

zend_object *zephir_init_properties_Zim_Container_Container(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _2, _4, _6, _8, _10, _12, _14, _16, _18, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8, _13$$9, _15$$10, _17$$11, _19$$12;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_17$$11);
	ZVAL_UNDEF(&_19$$12);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("contextual"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("contextual"), &_1$$3);
		}
		zephir_read_property(&_2, this_ptr, SL("with"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval(this_ptr, SL("with"), &_3$$4);
		}
		zephir_read_property(&_4, this_ptr, SL("buildStack"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval(this_ptr, SL("buildStack"), &_5$$5);
		}
		zephir_read_property(&_6, this_ptr, SL("extenders"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval(this_ptr, SL("extenders"), &_7$$6);
		}
		zephir_read_property(&_8, this_ptr, SL("abstractAliases"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval(this_ptr, SL("abstractAliases"), &_9$$7);
		}
		zephir_read_property(&_10, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_11$$8);
			array_init(&_11$$8);
			zephir_update_property_zval(this_ptr, SL("aliases"), &_11$$8);
		}
		zephir_read_property(&_12, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_12) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_13$$9);
			array_init(&_13$$9);
			zephir_update_property_zval(this_ptr, SL("instances"), &_13$$9);
		}
		zephir_read_property(&_14, this_ptr, SL("methodBindings"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_14) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_15$$10);
			array_init(&_15$$10);
			zephir_update_property_zval(this_ptr, SL("methodBindings"), &_15$$10);
		}
		zephir_read_property(&_16, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_16) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_17$$11);
			array_init(&_17$$11);
			zephir_update_property_zval(this_ptr, SL("bindings"), &_17$$11);
		}
		zephir_read_property(&_18, this_ptr, SL("resolved"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_18) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_19$$12);
			array_init(&_19$$12);
			zephir_update_property_zval(this_ptr, SL("resolved"), &_19$$12);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

