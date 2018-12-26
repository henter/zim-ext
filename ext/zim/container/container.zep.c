
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
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "Zend/zend_closures.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
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
	 * The container's bindings.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("bindings"), ZEND_ACC_PROTECTED TSRMLS_CC);

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
	 * The extension closures for services.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_container_container_ce, SL("extenders"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_container_container_ce->create_object = zephir_init_properties_Zim_Container_Container;
	return SUCCESS;

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
	zval *abstractt, abstractt_sub, _0, _2, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt);



	zephir_read_property(&_0, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
	_1 = zephir_array_isset(&_0, abstractt);
	if (!(_1)) {
		zephir_read_property(&_2, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
		_1 = zephir_array_isset(&_2, abstractt);
	}
	_3 = _1;
	if (!(_3)) {
		ZEPHIR_CALL_METHOD(&_4, this_ptr, "isalias", NULL, 0, abstractt);
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
 * Determine if a given type is shared.
 *
 * @param  string  $abstract
 * @return bool
 */
PHP_METHOD(Zim_Container_Container, isShared) {

	zend_bool _1, _4;
	zval *abstractt, abstractt_sub, _0, _2, _3, _5, _6, _7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);

	zephir_fetch_params(0, 1, 0, &abstractt);



	zephir_read_property(&_0, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	_1 = zephir_array_isset(&_0, abstractt);
	if (!(_1)) {
		zephir_read_property(&_2, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_3, &_2, abstractt, PH_READONLY, "zim/container/container.zep", 68 TSRMLS_CC);
		_4 = zephir_array_isset_string(&_3, SL("shared"));
		if (_4) {
			zephir_read_property(&_5, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_6, &_5, abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 68 TSRMLS_CC);
			zephir_array_fetch_string(&_7, &_6, SL("shared"), PH_NOISY | PH_READONLY, "zim/container/container.zep", 68 TSRMLS_CC);
			_4 = ZEPHIR_IS_TRUE_IDENTICAL(&_7);
		}
		_1 = _4;
	}
	RETURN_BOOL(_1);

}

/**
 * Determine if a given string is an alias.
 *
 * @param  string  $name
 * @return bool
 */
PHP_METHOD(Zim_Container_Container, isAlias) {

	zval *name, name_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_sub);
	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &name);



	zephir_read_property(&_0, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset(&_0, name));

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

	zval _3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool shared, _0, _1;
	zval *abstractt, abstractt_sub, *concrete = NULL, concrete_sub, *shared_param = NULL, __$null, _4, _2$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&concrete_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &abstractt, &concrete, &shared_param);

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


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "dropstaleinstances", NULL, 0, abstractt);
	zephir_check_call_status();
	if (Z_TYPE_P(concrete) == IS_NULL) {
		ZEPHIR_CPY_WRT(concrete, abstractt);
	}
	_0 = Z_TYPE_P(concrete) == IS_OBJECT;
	if (_0) {
		_1 = zephir_instance_of_ev(concrete, zend_ce_closure TSRMLS_CC);
		if (!(_1)) {
			_1 = zephir_instance_of_ev(concrete, zim_container_containersetclosureone_ce TSRMLS_CC);
		}
		_0 = _1;
	}
	if (!(_0)) {
		ZEPHIR_CALL_METHOD(&_2$$4, this_ptr, "getclosure", NULL, 0, abstractt, concrete);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(concrete, &_2$$4);
	}
	ZEPHIR_INIT_VAR(&_3);
	zephir_create_array(&_3, 2, 0 TSRMLS_CC);
	zephir_array_update_string(&_3, SL("concrete"), concrete, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_BOOL(&_4, shared);
	zephir_array_update_string(&_3, SL("shared"), &_4, PH_COPY | PH_SEPARATE);
	zephir_update_property_array(this_ptr, SL("bindings"), abstractt, &_3 TSRMLS_CC);
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
	zval *abstractt, abstractt_sub, *concrete, concrete_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&concrete_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &abstractt, &concrete);



	object_init_ex(return_value, zim_container_containergetclosureclosurezero_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 1, abstractt, concrete);
	zephir_check_call_status();
	RETURN_MM();

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
	zval *abstractt, abstractt_sub, *concrete = NULL, concrete_sub, __$null, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&concrete_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &abstractt, &concrete);

	if (!concrete) {
		concrete = &concrete_sub;
		concrete = &__$null;
	}


	ZVAL_BOOL(&_0, 1);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "bind", NULL, 0, abstractt, concrete, &_0);
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
	zval *abstractt = NULL, abstractt_sub, *closure, closure_sub, _0, _1, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&closure_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &abstractt, &closure);

	ZEPHIR_SEPARATE_PARAM(abstractt);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getalias", NULL, 0, abstractt);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(abstractt, &_0);
	zephir_read_property(&_1, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, abstractt)) {
		zephir_read_property(&_2$$3, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_3$$3, &_2$$3, abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 148 TSRMLS_CC);
		ZEPHIR_CALL_ZVAL_FUNCTION(&_4$$3, closure, NULL, 0, &_3$$3, this_ptr);
		zephir_check_call_status();
		zephir_update_property_array(this_ptr, SL("instances"), abstractt, &_4$$3 TSRMLS_CC);
	} else {
		zephir_update_property_array_multi(this_ptr, SL("extenders"), closure TSRMLS_CC, SL("za"), 2, abstractt);
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

	zval *abstractt, abstractt_sub, *instance, instance_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&instance_sub);
	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 2, 0, &abstractt, &instance);



	zephir_read_property(&_0, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, abstractt, PH_SEPARATE);
	zephir_update_property_array(this_ptr, SL("instances"), abstractt, instance TSRMLS_CC);
	RETVAL_ZVAL(instance, 1, 0);
	return;

}

/**
 * Alias a type to a different name.
 *
 * @param  string  $abstract
 * @param  string  $alias
 * @return void
 */
PHP_METHOD(Zim_Container_Container, alias) {

	zval *abstractt, abstractt_sub, *alias, alias_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&alias_sub);

	zephir_fetch_params(0, 2, 0, &abstractt, &alias);



	zephir_update_property_array(this_ptr, SL("aliases"), alias, abstractt TSRMLS_CC);

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

		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "make", NULL, 0, id);
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
				zephir_throw_exception_debug(&e, "zim/container/container.zep", 192 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_VAR(&_2$$4);
			object_init_ex(&_2$$4, zim_container_entrynotfoundexception_ce);
			ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 2);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_2$$4, "zim/container/container.zep", 194 TSRMLS_CC);
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
PHP_METHOD(Zim_Container_Container, make) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters;
	zval *abstractt = NULL, abstractt_sub, *parameters_param = NULL, concrete, obj, extender, _0, _1, _4, *_5, _7, _2$$3, _3$$3, _6$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&concrete);
	ZVAL_UNDEF(&obj);
	ZVAL_UNDEF(&extender);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &abstractt, &parameters_param);

	ZEPHIR_SEPARATE_PARAM(abstractt);
	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getalias", NULL, 0, abstractt);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(abstractt, &_0);
	zephir_read_property(&_1, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, abstractt)) {
		zephir_read_property(&_2$$3, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_3$$3, &_2$$3, abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 211 TSRMLS_CC);
		RETURN_CTOR(&_3$$3);
	}
	ZEPHIR_CALL_METHOD(&concrete, this_ptr, "getconcrete", NULL, 0, abstractt);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "isbuildable", NULL, 0, &concrete, abstractt);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		ZEPHIR_CALL_METHOD(&obj, this_ptr, "build", NULL, 0, &concrete, &parameters);
		zephir_check_call_status();
	} else {
		ZEPHIR_CALL_METHOD(&obj, this_ptr, "make", NULL, 3, &concrete, &parameters);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "getextenders", NULL, 0, abstractt);
	zephir_check_call_status();
	zephir_is_iterable(&_4, 0, "zim/container/container.zep", 225);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_4), _5)
	{
		ZEPHIR_INIT_NVAR(&extender);
		ZVAL_COPY(&extender, _5);
		ZEPHIR_CALL_ZVAL_FUNCTION(&_6$$6, &extender, NULL, 0, &obj, this_ptr);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&obj, &_6$$6);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&extender);
	ZEPHIR_CALL_METHOD(&_7, this_ptr, "isshared", NULL, 0, abstractt);
	zephir_check_call_status();
	if (zephir_is_true(&_7)) {
		zephir_update_property_array(this_ptr, SL("instances"), abstractt, &obj TSRMLS_CC);
	}
	RETURN_CCTOR(&obj);

}

/**
 * Get the concrete type for a given abstract.
 *
 * @param  string  $abstract
 * @return mixed   $concrete
 */
PHP_METHOD(Zim_Container_Container, getConcrete) {

	zval *abstractt, abstractt_sub, _0, _1$$3, _2$$3, _3$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	zephir_fetch_params(0, 1, 0, &abstractt);



	zephir_read_property(&_0, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_0, abstractt)) {
		zephir_read_property(&_1$$3, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_2$$3, &_1$$3, abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 241 TSRMLS_CC);
		zephir_array_fetch_string(&_3$$3, &_2$$3, SL("concrete"), PH_NOISY | PH_READONLY, "zim/container/container.zep", 241 TSRMLS_CC);
		RETURN_CTORW(&_3$$3);
	}
	RETVAL_ZVAL(abstractt, 1, 0);
	return;

}

/**
 * Determine if the given concrete is buildable.
 *
 * @param  mixed   $concrete
 * @param  string  $abstract
 * @return bool
 */
PHP_METHOD(Zim_Container_Container, isBuildable) {

	zend_bool _0, _1, _2;
	zval *concrete, concrete_sub, *abstractt, abstractt_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&concrete_sub);
	ZVAL_UNDEF(&abstractt_sub);

	zephir_fetch_params(0, 2, 0, &concrete, &abstractt);



	_0 = ZEPHIR_IS_IDENTICAL(concrete, abstractt);
	if (!(_0)) {
		_1 = Z_TYPE_P(concrete) == IS_OBJECT;
		if (_1) {
			_2 = zephir_instance_of_ev(concrete, zend_ce_closure TSRMLS_CC);
			if (!(_2)) {
				_2 = zephir_instance_of_ev(concrete, zim_container_containergetclosureclosurezero_ce TSRMLS_CC);
			}
			_1 = _2;
		}
		_0 = _1;
	}
	RETURN_BOOL(_0);

}

/**
 * Instantiate a concrete instance of the given type.
 *
 * @param  string $concrete
 * @param  array  $parameters
 * @return mixed
 *
 * @throws \Zim\Container\BindingResolutionException
 */
PHP_METHOD(Zim_Container_Container, build) {

	zend_bool _0, _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters;
	zval *concrete, concrete_sub, *parameters_param = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&concrete_sub);
	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &concrete, &parameters_param);

	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}


	_0 = Z_TYPE_P(concrete) == IS_OBJECT;
	if (_0) {
		_1 = zephir_instance_of_ev(concrete, zim_container_containergetclosureclosurezero_ce TSRMLS_CC);
		if (!(_1)) {
			_1 = zephir_instance_of_ev(concrete, zend_ce_closure TSRMLS_CC);
		}
		_0 = _1;
	}
	if (_0) {
		ZEPHIR_RETURN_CALL_ZVAL_FUNCTION(concrete, NULL, 0, this_ptr, &parameters);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "buildobject", NULL, 0, concrete, &parameters);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Throw an exception that the concrete is not instantiable.
 *
 * @param  string $concrete
 * @return void
 *
 * @throws \Zim\Container\BindingResolutionException
 */
PHP_METHOD(Zim_Container_Container, notInstantiable) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *concrete, concrete_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&concrete_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &concrete);



	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, zim_container_bindingresolutionexception_ce);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SVS(&_1, "Target [{", concrete, "}] is not instantiable.");
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 2, &_1);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_0, "zim/container/container.zep", 288 TSRMLS_CC);
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
	zval *abstractt, abstractt_sub, _0, _1, _2, _5, _6, _3$$4, _4$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt);



	zephir_read_property(&_0, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset(&_0, abstractt))) {
		RETVAL_ZVAL(abstractt, 1, 0);
		RETURN_MM();
	}
	zephir_read_property(&_1, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_2, &_1, abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 314 TSRMLS_CC);
	if (ZEPHIR_IS_IDENTICAL(&_2, abstractt)) {
		ZEPHIR_INIT_VAR(&_3$$4);
		object_init_ex(&_3$$4, spl_ce_LogicException);
		ZEPHIR_INIT_VAR(&_4$$4);
		ZEPHIR_CONCAT_SVS(&_4$$4, "[{", abstractt, "}] is aliased to itself.");
		ZEPHIR_CALL_METHOD(NULL, &_3$$4, "__construct", NULL, 4, &_4$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$4, "zim/container/container.zep", 315 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_5, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_6, &_5, abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 317 TSRMLS_CC);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getalias", NULL, 5, &_6);
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
	zval *abstractt = NULL, abstractt_sub, _0, _1, _2$$3, _3$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt);

	ZEPHIR_SEPARATE_PARAM(abstractt);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getalias", NULL, 0, abstractt);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(abstractt, &_0);
	zephir_read_property(&_1, this_ptr, SL("extenders"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, abstractt)) {
		zephir_read_property(&_2$$3, this_ptr, SL("extenders"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_3$$3, &_2$$3, abstractt, PH_NOISY | PH_READONLY, "zim/container/container.zep", 330 TSRMLS_CC);
		RETURN_CTOR(&_3$$3);
	}
	array_init(return_value);
	RETURN_MM();

}

/**
 * Remove all of the extender callbacks for a given type.
 *
 * @param  string  $abstract
 * @return void
 */
PHP_METHOD(Zim_Container_Container, forgetExtenders) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *abstractt, abstractt_sub, ext, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&ext);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt);



	ZEPHIR_CALL_METHOD(&ext, this_ptr, "getalias", NULL, 0, abstractt);
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

	zval *abstractt, abstractt_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	zephir_fetch_params(0, 1, 0, &abstractt);



	zephir_read_property(&_0, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, abstractt, PH_SEPARATE);
	zephir_read_property(&_1, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_1, abstractt, PH_SEPARATE);

}

/**
 * Remove a resolved instance from the instance cache.
 *
 * @param  string  $abstract
 * @return void
 */
PHP_METHOD(Zim_Container_Container, forgetInstance) {

	zval *abstractt, abstractt_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt_sub);
	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &abstractt);



	zephir_read_property(&_0, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, abstractt, PH_SEPARATE);

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

	zval _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("aliases"), &_0);
	ZEPHIR_INIT_VAR(&_1);
	array_init(&_1);
	zephir_update_property_zval(this_ptr, SL("bindings"), &_1);
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zephir_update_property_zval(this_ptr, SL("instances"), &_2);
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
	zval *key, key_sub, *value, value_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_sub);
	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key, &value);



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
		ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 6, value);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "bind", NULL, 0, key, &_0);
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

	zval *key, key_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	zephir_fetch_params(0, 1, 0, &key);



	zephir_read_property(&_0, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, key, PH_SEPARATE);
	zephir_read_property(&_1, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_1, key, PH_SEPARATE);

}

/**
 * blow methods from Trait MagicInjection
 *
 * call callable
 *
 * @param       $callback
 * @param array $parameters
 * @return mixed
 * @throws BindingResolutionException
 * @throws \ReflectionException
 */
PHP_METHOD(Zim_Container_Container, call) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters;
	zval *callback, callback_sub, *parameters_param = NULL, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &callback, &parameters_param);

	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getdependencies", NULL, 0, callback, &parameters);
	zephir_check_call_status();
	ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, callback, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param string $class
 * @param array  $params
 * @return object
 * @throws BindingResolutionException
 * @throws \ReflectionException
 */
PHP_METHOD(Zim_Container_Container, buildObject) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params;
	zval *c_param = NULL, *params_param = NULL, deps, _0;
	zval c;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&deps);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&params);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &c_param, &params_param);

	zephir_get_strval(&c, c_param);
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}


	ZEPHIR_CALL_METHOD(&deps, this_ptr, "getdependencies", NULL, 0, &c, &params);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, zephir_get_internal_ce(SL("reflectionclass")));
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 7, &c);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "newinstanceargs", NULL, 8, &deps);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param       $call
 * @param array $params
 * @return array
 * @throws BindingResolutionException
 * @throws \ReflectionException
 */
PHP_METHOD(Zim_Container_Container, getDependencies) {

	zend_bool _4$$3;
	zephir_fcall_cache_entry *_20 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params;
	zval *call, call_sub, *params_param = NULL, deps, rp, _0, *_1, _2$$3, _3$$3, _5$$3, _6$$3, _7$$3, _8$$3, _9$$4, _10$$4, _11$$4, _12$$5, _13$$5, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, _21$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&call_sub);
	ZVAL_UNDEF(&deps);
	ZVAL_UNDEF(&rp);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&params);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &call, &params_param);

	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}


	ZEPHIR_INIT_VAR(&deps);
	array_init(&deps);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "reflectionparams", NULL, 0, call);
	zephir_check_call_status();
	zephir_is_iterable(&_0, 0, "zim/container/container.zep", 501);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
	{
		ZEPHIR_INIT_NVAR(&rp);
		ZVAL_COPY(&rp, _1);
		zephir_read_property(&_2$$3, &rp, SL("name"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_3$$3, &rp, "getclass", NULL, 0);
		zephir_check_call_status();
		_4$$3 = zephir_is_true(&_3$$3);
		if (_4$$3) {
			ZEPHIR_CALL_METHOD(&_5$$3, &rp, "getclass", NULL, 0);
			zephir_check_call_status();
			zephir_read_property(&_6$$3, &_5$$3, SL("name"), PH_NOISY_CC | PH_READONLY);
			_4$$3 = zephir_array_key_exists(&params, &_6$$3 TSRMLS_CC);
		}
		ZEPHIR_CALL_METHOD(&_7$$3, &rp, "getclass", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_8$$3, &rp, "isdefaultvalueavailable", NULL, 0);
		zephir_check_call_status();
		if (zephir_array_key_exists(&params, &_2$$3 TSRMLS_CC)) {
			ZEPHIR_OBS_NVAR(&_10$$4);
			zephir_read_property(&_10$$4, &rp, SL("name"), PH_NOISY_CC);
			zephir_array_fetch(&_9$$4, &params, &_10$$4, PH_NOISY | PH_READONLY, "zim/container/container.zep", 490 TSRMLS_CC);
			zephir_array_append(&deps, &_9$$4, PH_SEPARATE, "zim/container/container.zep", 490);
			zephir_read_property(&_11$$4, &rp, SL("name"), PH_NOISY_CC | PH_READONLY);
			zephir_array_unset(&params, &_11$$4, PH_SEPARATE);
		} else if (_4$$3) {
			ZEPHIR_CALL_METHOD(&_13$$5, &rp, "getclass", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&_14$$5);
			zephir_read_property(&_14$$5, &_13$$5, SL("name"), PH_NOISY_CC);
			zephir_array_fetch(&_12$$5, &params, &_14$$5, PH_NOISY | PH_READONLY, "zim/container/container.zep", 493 TSRMLS_CC);
			zephir_array_append(&deps, &_12$$5, PH_SEPARATE, "zim/container/container.zep", 493);
			ZEPHIR_CALL_METHOD(&_15$$5, &rp, "getclass", NULL, 0);
			zephir_check_call_status();
			zephir_read_property(&_16$$5, &_15$$5, SL("name"), PH_NOISY_CC | PH_READONLY);
			zephir_array_unset(&params, &_16$$5, PH_SEPARATE);
		} else if (zephir_is_true(&_7$$3)) {
			ZEPHIR_CALL_METHOD(&_18$$6, &rp, "getclass", NULL, 0);
			zephir_check_call_status();
			zephir_read_property(&_19$$6, &_18$$6, SL("name"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_METHOD(&_17$$6, this_ptr, "make", &_20, 0, &_19$$6);
			zephir_check_call_status();
			zephir_array_append(&deps, &_17$$6, PH_SEPARATE, "zim/container/container.zep", 496);
		} else if (zephir_is_true(&_8$$3)) {
			ZEPHIR_CALL_METHOD(&_21$$7, &rp, "getdefaultvalue", NULL, 0);
			zephir_check_call_status();
			zephir_array_append(&deps, &_21$$7, PH_SEPARATE, "zim/container/container.zep", 498);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&rp);
	zephir_fast_array_merge(return_value, &deps, &params TSRMLS_CC);
	RETURN_MM();

}

/**
 * @param $call
 * @return array|\ReflectionParameter[]
 * @throws BindingResolutionException
 * @throws \ReflectionException
 */
PHP_METHOD(Zim_Container_Container, reflectionParams) {

	zend_class_entry *_15$$12 = NULL;
	zend_bool _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *call, call_sub, r, constructor, _1$$3, _2$$3, _3$$3, _4$$5, _5$$6, _6$$9, _7$$9, _8$$9, _9$$9, _10$$9, _11$$11, _12$$11, _13$$11, _14$$12, _16$$12;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&call_sub);
	ZVAL_UNDEF(&r);
	ZVAL_UNDEF(&constructor);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$9);
	ZVAL_UNDEF(&_7$$9);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_11$$11);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_13$$11);
	ZVAL_UNDEF(&_14$$12);
	ZVAL_UNDEF(&_16$$12);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &call);



	_0 = Z_TYPE_P(call) == IS_OBJECT;
	if (_0) {
		_0 = zephir_instance_of_ev(call, zend_ce_closure TSRMLS_CC);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, zephir_get_internal_ce(SL("reflectionfunction")));
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 9, call);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_3$$3, &_2$$3, "getparameters", NULL, 10);
		zephir_check_call_status();
		if (!(zephir_is_true(&_3$$3))) {
			array_init(&_1$$3);
		} else {
			ZEPHIR_INIT_VAR(&_4$$5);
			object_init_ex(&_4$$5, zephir_get_internal_ce(SL("reflectionfunction")));
			ZEPHIR_CALL_METHOD(NULL, &_4$$5, "__construct", NULL, 9, call);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_1$$3, &_4$$5, "getparameters", NULL, 10);
			zephir_check_call_status();
		}
		RETURN_CCTOR(&_1$$3);
	} else if (Z_TYPE_P(call) == IS_STRING) {
		ZEPHIR_INIT_VAR(&r);
		object_init_ex(&r, zephir_get_internal_ce(SL("reflectionclass")));
		ZEPHIR_CALL_METHOD(NULL, &r, "__construct", NULL, 7, call);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_5$$6, &r, "isinstantiable", NULL, 11);
		zephir_check_call_status();
		if (!(zephir_is_true(&_5$$6))) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notinstantiable", NULL, 0, call);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_CALL_METHOD(&constructor, &r, "getconstructor", NULL, 12);
		zephir_check_call_status();
		if (zephir_is_true(&constructor)) {
			ZEPHIR_RETURN_CALL_METHOD(&constructor, "getparameters", NULL, 0);
			zephir_check_call_status();
			RETURN_MM();
		}
		array_init(return_value);
		RETURN_MM();
	} else if (Z_TYPE_P(call) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_6$$9);
		ZEPHIR_INIT_VAR(&_7$$9);
		object_init_ex(&_7$$9, zephir_get_internal_ce(SL("reflectionmethod")));
		zephir_array_fetch_long(&_8$$9, call, 0, PH_NOISY | PH_READONLY, "zim/container/container.zep", 526 TSRMLS_CC);
		zephir_array_fetch_long(&_9$$9, call, 1, PH_NOISY | PH_READONLY, "zim/container/container.zep", 526 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, &_7$$9, "__construct", NULL, 13, &_8$$9, &_9$$9);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_10$$9, &_7$$9, "getparameters", NULL, 14);
		zephir_check_call_status();
		if (!(zephir_is_true(&_10$$9))) {
			array_init(&_6$$9);
		} else {
			ZEPHIR_INIT_VAR(&_11$$11);
			object_init_ex(&_11$$11, zephir_get_internal_ce(SL("reflectionmethod")));
			zephir_array_fetch_long(&_12$$11, call, 0, PH_NOISY | PH_READONLY, "zim/container/container.zep", 526 TSRMLS_CC);
			zephir_array_fetch_long(&_13$$11, call, 1, PH_NOISY | PH_READONLY, "zim/container/container.zep", 526 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(NULL, &_11$$11, "__construct", NULL, 13, &_12$$11, &_13$$11);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_6$$9, &_11$$11, "getparameters", NULL, 14);
			zephir_check_call_status();
		}
		RETURN_CCTOR(&_6$$9);
	} else {
		ZEPHIR_INIT_VAR(&_14$$12);
		if (!_15$$12) {
		_15$$12 = zephir_fetch_class_str_ex(SL("Zim\\Container\\InvalidArgumentException"), ZEND_FETCH_CLASS_AUTO);
		}
		object_init_ex(&_14$$12, _15$$12);
		if (zephir_has_constructor(&_14$$12 TSRMLS_CC)) {
			ZEPHIR_INIT_VAR(&_16$$12);
			ZVAL_STRING(&_16$$12, "unsupported call");
			ZEPHIR_CALL_METHOD(NULL, &_14$$12, "__construct", NULL, 0, &_16$$12);
			zephir_check_call_status();
		}
		zephir_throw_exception_debug(&_14$$12, "zim/container/container.zep", 528 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}

}

zend_object *zephir_init_properties_Zim_Container_Container(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _2, _4, _6, _1$$3, _3$$4, _5$$5, _7$$6;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("extenders"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("extenders"), &_1$$3);
		}
		zephir_read_property(&_2, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval(this_ptr, SL("aliases"), &_3$$4);
		}
		zephir_read_property(&_4, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval(this_ptr, SL("instances"), &_5$$5);
		}
		zephir_read_property(&_6, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval(this_ptr, SL("bindings"), &_7$$6);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

