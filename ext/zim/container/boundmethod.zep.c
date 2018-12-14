
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "Zend/zend_closures.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(Zim_Container_BoundMethod) {

	ZEPHIR_REGISTER_CLASS(Zim\\Container, BoundMethod, zim, container_boundmethod, zim_container_boundmethod_method_entry, 0);

	return SUCCESS;

}

/**
 * Call the given Closure / class@method and inject its dependencies.
 *
 * @param  Container  $container
 * @param  callable|string  $callback
 * @param  array  $parameters
 * @param  string|null  $defaultMethod
 * @return mixed
 */
PHP_METHOD(Zim_Container_BoundMethod, call) {

	zend_bool _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters;
	zval *container, container_sub, *callback, callback_sub, *parameters_param = NULL, *defaultMethod = NULL, defaultMethod_sub, __$null, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&defaultMethod_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 2, &container, &callback, &parameters_param, &defaultMethod);

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


	ZEPHIR_CALL_STATIC(&_0, "iscallablewithatsign", NULL, 0, callback);
	zephir_check_call_status();
	_1 = zephir_is_true(&_0);
	if (!(_1)) {
		_1 = zephir_is_true(defaultMethod);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_STATIC("callclass", NULL, 0, container, callback, &parameters, defaultMethod);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, zim_container_boundmethodcallclosurezero_ce);
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 29, container, callback, &parameters);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_STATIC("callboundmethod", NULL, 0, container, callback, &_2);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Call a string reference to a class using Class@method syntax.
 *
 * @param  Container  $container
 * @param  string  $target
 * @param  array  $parameters
 * @param  string|null  $defaultMethod
 * @return mixed
 *
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Zim_Container_BoundMethod, callClass) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters;
	zval target;
	zval *container, container_sub, *target_param = NULL, *parameters_param = NULL, *defaultMethod = NULL, defaultMethod_sub, __$null, segments, method, tmpArrayfc3097742aa3c3120f5545e8f51f1abf, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&defaultMethod_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&segments);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&tmpArrayfc3097742aa3c3120f5545e8f51f1abf);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&target);
	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 2, &container, &target_param, &parameters_param, &defaultMethod);

	zephir_get_strval(&target, target_param);
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


	ZEPHIR_INIT_VAR(&segments);
	zephir_fast_explode_str(&segments, SL("@"), &target, LONG_MAX TSRMLS_CC);
	if (zephir_fast_count_int(&segments TSRMLS_CC) == 2) {
		ZEPHIR_OBS_VAR(&method);
		zephir_array_fetch_long(&method, &segments, 1, PH_NOISY, "zim/container/boundmethod.zep", 45 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(&method, defaultMethod);
	}
	if (Z_TYPE_P(&method) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Method not provided.", "zim/container/boundmethod.zep", 47);
		return;
	}
	ZEPHIR_INIT_VAR(&tmpArrayfc3097742aa3c3120f5545e8f51f1abf);
	zephir_create_array(&tmpArrayfc3097742aa3c3120f5545e8f51f1abf, 2, 0 TSRMLS_CC);
	zephir_array_fetch_long(&_1, &segments, 0, PH_NOISY | PH_READONLY, "zim/container/boundmethod.zep", 49 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_0, container, "make", NULL, 0, &_1);
	zephir_check_call_status();
	zephir_array_fast_append(&tmpArrayfc3097742aa3c3120f5545e8f51f1abf, &_0);
	zephir_array_fast_append(&tmpArrayfc3097742aa3c3120f5545e8f51f1abf, &method);
	ZEPHIR_RETURN_CALL_STATIC("call", NULL, 0, container, &tmpArrayfc3097742aa3c3120f5545e8f51f1abf, &parameters);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Call a method that has been bound to the container.
 *
 * @param  Container  $container
 * @param  callable  $callback
 * @param  mixed  $deft
 * @return mixed
 */
PHP_METHOD(Zim_Container_BoundMethod, callBoundMethod) {

	zend_bool _5, _1$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *container, container_sub, *callback, callback_sub, *deft, deft_sub, method, _2, _4, _0$$3, _3$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_3$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &container, &callback, &deft);



	if (!(Z_TYPE_P(callback) == IS_ARRAY)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		_1$$3 = Z_TYPE_P(deft) == IS_OBJECT;
		if (_1$$3) {
			_1$$3 = zephir_instance_of_ev(deft, zend_ce_closure TSRMLS_CC);
		}
		if (_1$$3) {
			ZEPHIR_CALL_ZVAL_FUNCTION(&_0$$3, deft, NULL, 0);
			zephir_check_call_status();
		} else {
			ZEPHIR_CPY_WRT(&_0$$3, deft);
		}
		RETURN_CCTOR(&_0$$3);
	}
	ZEPHIR_CALL_STATIC(&method, "normalizemethod", NULL, 0, callback);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, container, "hasmethodbinding", NULL, 0, &method);
	zephir_check_call_status();
	if (zephir_is_true(&_2)) {
		zephir_array_fetch_long(&_3$$4, callback, 0, PH_NOISY | PH_READONLY, "zim/container/boundmethod.zep", 73 TSRMLS_CC);
		ZEPHIR_RETURN_CALL_METHOD(container, "callmethodbinding", NULL, 0, &method, &_3$$4);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_4);
	_5 = Z_TYPE_P(deft) == IS_OBJECT;
	if (_5) {
		_5 = zephir_instance_of_ev(deft, zend_ce_closure TSRMLS_CC);
	}
	if (_5) {
		ZEPHIR_CALL_ZVAL_FUNCTION(&_4, deft, NULL, 0);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&_4, deft);
	}
	RETURN_CCTOR(&_4);

}

/**
 * Normalize the given callback into a Class@method string.
 *
 * @param  callable  $callback
 * @return string
 */
PHP_METHOD(Zim_Container_BoundMethod, normalizeMethod) {

	zval *callback, callback_sub, classs, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&classs);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &callback);



	zephir_array_fetch_long(&_0, callback, 0, PH_NOISY | PH_READONLY, "zim/container/boundmethod.zep", 88 TSRMLS_CC);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_OBS_VAR(&classs);
		zephir_array_fetch_long(&classs, callback, 0, PH_NOISY, "zim/container/boundmethod.zep", 88 TSRMLS_CC);
	} else {
		zephir_array_fetch_long(&_1, callback, 0, PH_NOISY | PH_READONLY, "zim/container/boundmethod.zep", 88 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&classs);
		zephir_get_class(&classs, &_1, 0 TSRMLS_CC);
	}
	RETURN_MM_STRING("{classs}@{callback[1]}");

}

/**
 * Get all dependencies for a given method.
 *
 * @param  Container  $container
 * @param  callable|string  $callback
 * @param  array  $parameters
 * @return array
 */
PHP_METHOD(Zim_Container_BoundMethod, getMethodDependencies) {

	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters;
	zval *container, container_sub, *callback, callback_sub, *parameters_param = NULL, dependencies, parameter, tmpListParametersDependencies, tmpparams, tmpdeps, _0, _1, *_2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&dependencies);
	ZVAL_UNDEF(&parameter);
	ZVAL_UNDEF(&tmpListParametersDependencies);
	ZVAL_UNDEF(&tmpparams);
	ZVAL_UNDEF(&tmpdeps);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&parameters);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &container, &callback, &parameters_param);

	if (!parameters_param) {
		ZEPHIR_INIT_VAR(&parameters);
		array_init(&parameters);
	} else {
		zephir_get_arrval(&parameters, parameters_param);
	}


	ZEPHIR_INIT_VAR(&dependencies);
	array_init(&dependencies);
	ZEPHIR_CALL_STATIC(&_0, "getcallreflector", NULL, 0, callback);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, &_0, "getparameters", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_1, 0, "zim/container/boundmethod.zep", 114);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_1), _2)
	{
		ZEPHIR_INIT_NVAR(&parameter);
		ZVAL_COPY(&parameter, _2);
		ZEPHIR_CALL_STATIC(&tmpListParametersDependencies, "adddependencyforcallparameter", &_3, 0, container, &parameter, &parameters, &dependencies);
		zephir_check_call_status();
		if (zephir_array_isset_long(&tmpListParametersDependencies, 1)) {
			ZEPHIR_OBS_NVAR(&tmpparams);
			zephir_array_fetch_long(&tmpparams, &tmpListParametersDependencies, 0, PH_NOISY, "zim/container/boundmethod.zep", 108 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(&tmpdeps);
			zephir_array_fetch_long(&tmpdeps, &tmpListParametersDependencies, 1, PH_NOISY, "zim/container/boundmethod.zep", 109 TSRMLS_CC);
			ZEPHIR_CPY_WRT(&parameters, &tmpparams);
			ZEPHIR_CPY_WRT(&dependencies, &tmpdeps);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&parameter);
	zephir_fast_array_merge(return_value, &dependencies, &parameters TSRMLS_CC);
	RETURN_MM();

}

/**
 * Get the proper reflection instance for the given callback.
 *
 * @param  callable|string $callback
 * @return \ReflectionFunctionAbstract
 *
 * @throws \ReflectionException
 */
PHP_METHOD(Zim_Container_BoundMethod, getCallReflector) {

	zend_bool _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *callback = NULL, callback_sub, _1, _2, _4, _5, _6, _3$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &callback);

	ZEPHIR_SEPARATE_PARAM(callback);


	_0 = Z_TYPE_P(callback) == IS_STRING;
	if (_0) {
		ZEPHIR_INIT_VAR(&_1);
		ZVAL_STRING(&_1, "::");
		ZEPHIR_INIT_VAR(&_2);
		zephir_fast_strpos(&_2, callback, &_1, 0 );
		_0 = !ZEPHIR_IS_FALSE_IDENTICAL(&_2);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_fast_explode_str(&_3$$3, SL("::"), callback, LONG_MAX TSRMLS_CC);
		ZEPHIR_CPY_WRT(callback, &_3$$3);
	}
	ZEPHIR_INIT_VAR(&_4);
	if (Z_TYPE_P(callback) == IS_ARRAY) {
		object_init_ex(&_4, zephir_get_internal_ce(SL("reflectionmethod")));
		zephir_array_fetch_long(&_5, callback, 0, PH_NOISY | PH_READONLY, "zim/container/boundmethod.zep", 130 TSRMLS_CC);
		zephir_array_fetch_long(&_6, callback, 1, PH_NOISY | PH_READONLY, "zim/container/boundmethod.zep", 130 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(NULL, &_4, "__construct", NULL, 30, &_5, &_6);
		zephir_check_call_status();
	} else {
		object_init_ex(&_4, zephir_get_internal_ce(SL("reflectionfunction")));
		ZEPHIR_CALL_METHOD(NULL, &_4, "__construct", NULL, 31, callback);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&_4);

}

/**
 * Get the dependency for the given call parameter.
 *
 * @param  Container  $container
 * @param  \ReflectionParameter  $parameter
 * @param  array  $parameters
 * @param  array  $dependencies
 * @return mixed
 */
PHP_METHOD(Zim_Container_BoundMethod, addDependencyForCallParameter) {

	zend_bool _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval parameters, dependencies;
	zval *container, container_sub, *parameter, parameter_sub, *parameters_param = NULL, *dependencies_param = NULL, _0, _1, _3, _4, _5, _6, _7$$3, _8$$3, _9$$3, _10$$4, _11$$4, _12$$4, _13$$4, _14$$4, _15$$5, _16$$5, _17$$5, _18$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&parameter_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&parameters);
	ZVAL_UNDEF(&dependencies);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 0, &container, &parameter, &parameters_param, &dependencies_param);

	zephir_get_arrval(&parameters, parameters_param);
	zephir_get_arrval(&dependencies, dependencies_param);


	zephir_read_property(&_0, parameter, SL("name"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, parameter, "getclass", NULL, 0);
	zephir_check_call_status();
	_2 = zephir_is_true(&_1);
	if (_2) {
		ZEPHIR_CALL_METHOD(&_3, parameter, "getclass", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_4, &_3, SL("name"), PH_NOISY_CC | PH_READONLY);
		_2 = zephir_array_key_exists(&parameters, &_4 TSRMLS_CC);
	}
	ZEPHIR_CALL_METHOD(&_5, parameter, "getclass", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_6, parameter, "isdefaultvalueavailable", NULL, 0);
	zephir_check_call_status();
	if (zephir_array_key_exists(&parameters, &_0 TSRMLS_CC)) {
		ZEPHIR_OBS_VAR(&_8$$3);
		zephir_read_property(&_8$$3, parameter, SL("name"), PH_NOISY_CC);
		zephir_array_fetch(&_7$$3, &parameters, &_8$$3, PH_NOISY | PH_READONLY, "zim/container/boundmethod.zep", 145 TSRMLS_CC);
		zephir_array_append(&dependencies, &_7$$3, PH_SEPARATE, "zim/container/boundmethod.zep", 145);
		zephir_read_property(&_9$$3, parameter, SL("name"), PH_NOISY_CC | PH_READONLY);
		zephir_array_unset(&parameters, &_9$$3, PH_SEPARATE);
	} else if (_2) {
		ZEPHIR_CALL_METHOD(&_11$$4, parameter, "getclass", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_OBS_VAR(&_12$$4);
		zephir_read_property(&_12$$4, &_11$$4, SL("name"), PH_NOISY_CC);
		zephir_array_fetch(&_10$$4, &parameters, &_12$$4, PH_NOISY | PH_READONLY, "zim/container/boundmethod.zep", 149 TSRMLS_CC);
		zephir_array_append(&dependencies, &_10$$4, PH_SEPARATE, "zim/container/boundmethod.zep", 149);
		ZEPHIR_CALL_METHOD(&_13$$4, parameter, "getclass", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_14$$4, &_13$$4, SL("name"), PH_NOISY_CC | PH_READONLY);
		zephir_array_unset(&parameters, &_14$$4, PH_SEPARATE);
	} else if (zephir_is_true(&_5)) {
		ZEPHIR_CALL_METHOD(&_16$$5, parameter, "getclass", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_17$$5, &_16$$5, SL("name"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_15$$5, container, "make", NULL, 0, &_17$$5);
		zephir_check_call_status();
		zephir_array_append(&dependencies, &_15$$5, PH_SEPARATE, "zim/container/boundmethod.zep", 153);
	} else if (zephir_is_true(&_6)) {
		ZEPHIR_CALL_METHOD(&_18$$6, parameter, "getdefaultvalue", NULL, 0);
		zephir_check_call_status();
		zephir_array_append(&dependencies, &_18$$6, PH_SEPARATE, "zim/container/boundmethod.zep", 155);
	}
	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(return_value, &parameters);
	zephir_array_fast_append(return_value, &dependencies);
	RETURN_MM();

}

/**
 * Determine if the given string is in Class@method syntax.
 *
 * @param  mixed  $callback
 * @return bool
 */
PHP_METHOD(Zim_Container_BoundMethod, isCallableWithAtSign) {

	zend_bool _0;
	zval *callback, callback_sub, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &callback);



	_0 = Z_TYPE_P(callback) == IS_STRING;
	if (_0) {
		ZEPHIR_INIT_VAR(&_1);
		ZVAL_STRING(&_1, "@");
		ZEPHIR_INIT_VAR(&_2);
		zephir_fast_strpos(&_2, callback, &_1, 0 );
		_0 = !ZEPHIR_IS_FALSE_IDENTICAL(&_2);
	}
	RETURN_MM_BOOL(_0);

}

