
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
#include "kernel/operators.h"
#include "kernel/concat.h"


ZEPHIR_INIT_CLASS(Zim_Debug_FlattenExceptionsetMessageClosureZero) {

	ZEPHIR_REGISTER_CLASS(Zim\\Debug, FlattenExceptionsetMessageClosureZero, zim, debug_flattenexceptionsetmessageclosurezero, zim_debug_flattenexceptionsetmessageclosurezero_method_entry, 0);

	return SUCCESS;

}

PHP_METHOD(Zim_Debug_FlattenExceptionsetMessageClosureZero, __construct) {

	zval *this_ptr = getThis();



}

PHP_METHOD(Zim_Debug_FlattenExceptionsetMessageClosureZero, __invoke) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *m, m_sub, __$false, _0, _1, _2, _3, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&m_sub);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &m);



	ZEPHIR_INIT_VAR(&_0);
	zephir_array_fetch_long(&_1, m, 0, PH_NOISY | PH_READONLY, "zim/debug/flattenexceptionsetmessageclosurezero.zep", 13 TSRMLS_CC);
	ZEPHIR_CALL_FUNCTION(&_2, "\class_exists", NULL, 72, &_1, &__$false);
	zephir_check_call_status();
	if (zephir_is_true(&_2)) {
		zephir_array_fetch_long(&_3, m, 0, PH_NOISY | PH_READONLY, "zim/debug/flattenexceptionsetmessageclosurezero.zep", 13 TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_4, "get_parent_class", NULL, 66, &_3);
		zephir_check_call_status();
		ZEPHIR_CONCAT_VS(&_0, &_4, "@anonymous");
	} else {
		zephir_array_fetch_long(&_0, m, 0, PH_NOISY, "zim/debug/flattenexceptionsetmessageclosurezero.zep", 13 TSRMLS_CC);
	}
	RETURN_CCTOR(&_0);

}

