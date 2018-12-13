
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
#include "kernel/array.h"
#include "kernel/fcall.h"


ZEPHIR_INIT_CLASS(Zim_Container_ContextualBindingBuilder) {

	ZEPHIR_REGISTER_CLASS(Zim\\Container, ContextualBindingBuilder, zim, container_contextualbindingbuilder, zim_container_contextualbindingbuilder_method_entry, 0);

	/**
	 * The underlying container instance.
	 *
	 * @var \Zim\Container\Container
	 */
	zend_declare_property_null(zim_container_contextualbindingbuilder_ce, SL("container"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The concrete instance.
	 *
	 * @var string
	 */
	zend_declare_property_null(zim_container_contextualbindingbuilder_ce, SL("concrete"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The abstract target.
	 *
	 * @var string
	 */
	zend_declare_property_null(zim_container_contextualbindingbuilder_ce, SL("needs"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Create a new contextual binding builder.
 *
 * @param  \Zim\Container\Container  $container
 * @param  string|array  $concrete
 * @return void
 */
PHP_METHOD(Zim_Container_ContextualBindingBuilder, __construct) {

	zval *container, container_sub, *concrete, concrete_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_UNDEF(&concrete_sub);

	zephir_fetch_params(0, 2, 0, &container, &concrete);



	zephir_update_property_zval(this_ptr, SL("concrete"), concrete);
	zephir_update_property_zval(this_ptr, SL("container"), container);

}

/**
 * Define the abstract target that depends on the context.
 *
 * @param  string  $abstract
 * @return $this
 */
PHP_METHOD(Zim_Container_ContextualBindingBuilder, needs) {

	zval *abstractt_param = NULL;
	zval abstractt;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&abstractt);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &abstractt_param);

	zephir_get_strval(&abstractt, abstractt_param);


	zephir_update_property_zval(this_ptr, SL("needs"), &abstractt);
	RETURN_THIS();

}

/**
 * Define the implementation for the contextual binding.
 *
 * @param  \Closure|string  $implementation
 * @return void
 */
PHP_METHOD(Zim_Container_ContextualBindingBuilder, give) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *implementation, implementation_sub, concretes, concrete, _0, _1, *_2, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&implementation_sub);
	ZVAL_UNDEF(&concretes);
	ZVAL_UNDEF(&concrete);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &implementation);



	zephir_read_property(&_0, this_ptr, SL("concrete"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEPHIR_OBS_VAR(&concretes);
		zephir_read_property(&concretes, this_ptr, SL("concrete"), PH_NOISY_CC);
	} else {
		ZEPHIR_INIT_NVAR(&concretes);
		zephir_create_array(&concretes, 1, 0 TSRMLS_CC);
		ZEPHIR_OBS_VAR(&_1);
		zephir_read_property(&_1, this_ptr, SL("concrete"), PH_NOISY_CC);
		zephir_array_fast_append(&concretes, &_1);
	}
	zephir_is_iterable(&concretes, 0, "zim/container/contextualbindingbuilder.zep", 62);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&concretes), _2)
	{
		ZEPHIR_INIT_NVAR(&concrete);
		ZVAL_COPY(&concrete, _2);
		zephir_read_property(&_3$$3, this_ptr, SL("container"), PH_NOISY_CC | PH_READONLY);
		zephir_read_property(&_4$$3, this_ptr, SL("needs"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "addcontextualbinding", NULL, 0, &concrete, &_4$$3, implementation);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&concrete);
	ZEPHIR_MM_RESTORE();

}

