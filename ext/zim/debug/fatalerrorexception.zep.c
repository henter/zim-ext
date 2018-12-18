
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
#include "kernel/object.h"
#include "kernel/fcall.h"


/**
 * Fatal Error Exception.
 *
 * @author Konstanton Myakshin <koc-dp@yandex.ru>
 */
ZEPHIR_INIT_CLASS(Zim_Debug_FatalErrorException) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Debug, FatalErrorException, zim, debug_fatalerrorexception, zephir_get_internal_ce(SL("errorexception")), zim_debug_fatalerrorexception_method_entry, 0);

	zend_declare_property_null(zim_debug_fatalerrorexception_ce, SL("originalClassName"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Zim_Debug_FatalErrorException, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *e, e_sub, severity, _0, _1, _2, _3, _4, _5, _6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&e_sub);
	ZVAL_UNDEF(&severity);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &e);



	ZEPHIR_INIT_VAR(&_0);
	zephir_get_class(&_0, e, 0 TSRMLS_CC);
	zephir_update_property_zval(this_ptr, SL("originalClassName"), &_0);
	if (zephir_instance_of_ev(e, zephir_get_internal_ce(SL("parseerror")) TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(&severity);
		ZVAL_LONG(&severity, 4);
	} else if (zephir_instance_of_ev(e, zephir_get_internal_ce(SL("typeerror")) TSRMLS_CC)) {
		ZEPHIR_INIT_NVAR(&severity);
		ZVAL_LONG(&severity, 4096);
	} else {
		ZEPHIR_INIT_NVAR(&severity);
		ZVAL_LONG(&severity, 1);
	}
	ZEPHIR_CALL_METHOD(&_1, e, "getmessage", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, e, "getcode", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, e, "getfile", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_4, e, "getline", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, e, "getprevious", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_PARENT(NULL, zim_debug_fatalerrorexception_ce, getThis(), "__construct", NULL, 0, &_1, &_2, &severity, &_3, &_4, &_5);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_6, e, "gettrace", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "settrace", NULL, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Zim_Debug_FatalErrorException, getOriginalClassName) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "originalClassName");

}

PHP_METHOD(Zim_Debug_FatalErrorException, setTrace) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *trace, trace_sub, traceReflector, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&trace_sub);
	ZVAL_UNDEF(&traceReflector);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &trace);



	ZEPHIR_INIT_VAR(&traceReflector);
	object_init_ex(&traceReflector, zephir_get_internal_ce(SL("reflectionproperty")));
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Exception");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "trace");
	ZEPHIR_CALL_METHOD(NULL, &traceReflector, "__construct", NULL, 38, &_0, &_1);
	zephir_check_call_status();
	ZVAL_BOOL(&_2, 1);
	ZEPHIR_CALL_METHOD(NULL, &traceReflector, "setaccessible", NULL, 54, &_2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &traceReflector, "setvalue", NULL, 55, this_ptr, trace);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

