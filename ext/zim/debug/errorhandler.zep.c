
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
#include "kernel/operators.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/concat.h"
#include "kernel/exception.h"


/**
 * A generic ErrorHandler for the PHP engine.
 *
 * Provides five bit fields that control how errors are handled:
 * - thrownErrors: errors thrown as \ErrorException
 * - loggedErrors: logged errors, when not @-silenced
 * - scopedErrors: errors thrown or logged with their local context
 * - tracedErrors: errors logged with their stack trace
 * - screamedErrors: never @-silenced errors
 *
 * Each error level can be logged by a dedicated PSR-3 logger object.
 * Screaming only applies to logging.
 * Throwing takes precedence over logging.
 * Uncaught exceptions are logged as E_ERROR.
 * E_DEPRECATED and E_USER_DEPRECATED levels never throw.
 * E_RECOVERABLE_ERROR and E_USER_ERROR levels always throw.
 * Non catchable errors that can be detected at shutdown time are logged when the scream bit field allows so.
 * As errors have a performance cost, repeated errors are all logged, so that the developer
 * can see them and weight them as more important to fix than others of the same level.
 *
 * @author Nicolas Grekas <p@tchwork.com>
 * @author Grégoire Pineau <lyrixx@lyrixx.info>
 */
ZEPHIR_INIT_CLASS(Zim_Debug_ErrorHandler) {

	ZEPHIR_REGISTER_CLASS(Zim\\Debug, ErrorHandler, zim, debug_errorhandler, zim_debug_errorhandler_method_entry, 0);

	zend_declare_property_null(zim_debug_errorhandler_ce, SL("levels"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(zim_debug_errorhandler_ce, SL("thrownErrors"), 8191, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(zim_debug_errorhandler_ce, SL("screamedErrors"), 85, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_errorhandler_ce, SL("traceReflector"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_errorhandler_ce, SL("exceptionHandler"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_debug_errorhandler_ce->create_object = zephir_init_properties_Zim_Debug_ErrorHandler;
	return SUCCESS;

}

/**
 * Registers the error handler.
 *
 * @param self|null $handler The handler to register
 *
 * @return self The registered error handler
 */
PHP_METHOD(Zim_Debug_ErrorHandler, register) {

	zephir_fcall_cache_entry *_1 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *handler = NULL, handler_sub, __$null, tmpArray333792ecce577a1de0b52951dff6478e, prev, tmpArray81691361fa84c744e100422140b616a2, tmpArrayd0d8b94be8374b419e6b740b5ad5bed2, _0, _2$$4, _3$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&tmpArray333792ecce577a1de0b52951dff6478e);
	ZVAL_UNDEF(&prev);
	ZVAL_UNDEF(&tmpArray81691361fa84c744e100422140b616a2);
	ZVAL_UNDEF(&tmpArrayd0d8b94be8374b419e6b740b5ad5bed2);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &handler);

	if (!handler) {
		handler = &handler_sub;
		ZEPHIR_CPY_WRT(handler, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(handler);
	}


	if (Z_TYPE_P(handler) == IS_NULL) {
		ZEPHIR_INIT_NVAR(handler);
		object_init_ex(handler, zim_debug_errorhandler_ce);
		ZEPHIR_CALL_METHOD(NULL, handler, "__construct", NULL, 32);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&tmpArray333792ecce577a1de0b52951dff6478e);
	zephir_create_array(&tmpArray333792ecce577a1de0b52951dff6478e, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(&tmpArray333792ecce577a1de0b52951dff6478e, handler);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "handleError");
	zephir_array_fast_append(&tmpArray333792ecce577a1de0b52951dff6478e, &_0);
	ZEPHIR_CALL_FUNCTION(&prev, "set_error_handler", &_1, 33, &tmpArray333792ecce577a1de0b52951dff6478e);
	zephir_check_call_status();
	if (Z_TYPE_P(&prev) == IS_NULL) {
		ZEPHIR_CALL_FUNCTION(NULL, "restore_error_handler", NULL, 34);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&tmpArray81691361fa84c744e100422140b616a2);
		zephir_create_array(&tmpArray81691361fa84c744e100422140b616a2, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&tmpArray81691361fa84c744e100422140b616a2, handler);
		ZEPHIR_INIT_VAR(&_2$$4);
		ZVAL_STRING(&_2$$4, "handleError");
		zephir_array_fast_append(&tmpArray81691361fa84c744e100422140b616a2, &_2$$4);
		zephir_read_property(&_3$$4, handler, SL("thrownErrors"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_FUNCTION(NULL, "set_error_handler", &_1, 33, &tmpArray81691361fa84c744e100422140b616a2, &_3$$4);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&tmpArrayd0d8b94be8374b419e6b740b5ad5bed2);
	zephir_create_array(&tmpArrayd0d8b94be8374b419e6b740b5ad5bed2, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(&tmpArrayd0d8b94be8374b419e6b740b5ad5bed2, handler);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "handleException");
	zephir_array_fast_append(&tmpArrayd0d8b94be8374b419e6b740b5ad5bed2, &_0);
	ZEPHIR_CALL_FUNCTION(&prev, "set_exception_handler", NULL, 35, &tmpArrayd0d8b94be8374b419e6b740b5ad5bed2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, handler, "setexceptionhandler", NULL, 36, &prev);
	zephir_check_call_status();
	RETVAL_ZVAL(handler, 1, 0);
	RETURN_MM();

}

PHP_METHOD(Zim_Debug_ErrorHandler, __construct) {

	zval _0, _1, _2, _3, _4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, zephir_get_internal_ce(SL("reflectionproperty")));
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Exception");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "trace");
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 37, &_1, &_2);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("traceReflector"), &_0);
	zephir_read_property(&_3, this_ptr, SL("traceReflector"), PH_NOISY_CC | PH_READONLY);
	ZVAL_BOOL(&_4, 1);
	ZEPHIR_CALL_METHOD(NULL, &_3, "setaccessible", NULL, 0, &_4);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets a user exception handler.
 *
 * @param callable $handler A handler that will be called on Exception
 *
 * @return callable|null The previous exception handler
 */
PHP_METHOD(Zim_Debug_ErrorHandler, setExceptionHandler) {

	zval *handler = NULL, handler_sub, __$null, prev;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&prev);

	zephir_fetch_params(0, 0, 1, &handler);

	if (!handler) {
		handler = &handler_sub;
		handler = &__$null;
	}


	zephir_read_property(&prev, this_ptr, SL("exceptionHandler"), PH_NOISY_CC | PH_READONLY);
	zephir_update_property_zval(this_ptr, SL("exceptionHandler"), handler);
	RETURN_CTORW(&prev);

}

/**
 * Handles errors by filtering then logging them according to the configured bit fields.
 *
 * @param int    $type    One of the E_* constants
 * @param string $message
 * @param string $file
 * @param int    $line
 *
 * @throws \ErrorException When $this->thrownErrors requests so
 *
 * @internal
 */
PHP_METHOD(Zim_Debug_ErrorHandler, handleError) {

	zval message, file;
	zval *type_param = NULL, *message_param = NULL, *file_param = NULL, *line_param = NULL, level, msg, errorAsException, _1, _2, _3, _4, _5, _6, _7;
	zend_long type, line, ZEPHIR_LAST_CALL_STATUS, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&level);
	ZVAL_UNDEF(&msg);
	ZVAL_UNDEF(&errorAsException);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&file);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 0, &type_param, &message_param, &file_param, &line_param);

	type = zephir_get_intval(type_param);
	zephir_get_strval(&message, message_param);
	zephir_get_strval(&file, file_param);
	line = zephir_get_intval(line_param);


	ZEPHIR_CALL_FUNCTION(&level, "error_reporting", NULL, 38);
	zephir_check_call_status();
	_0 = (((((int) (zephir_get_numberval(&level)) | 4096) | 256) | 8192) | 16384);
	ZEPHIR_INIT_NVAR(&level);
	ZVAL_LONG(&level, _0);
	zephir_read_property(&_1, this_ptr, SL("screamedErrors"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	zephir_bitwise_or_function(&_2, &level, &_1 TSRMLS_CC);
	type = (type & (int) (zephir_get_numberval(&_2)));
	zephir_read_property(&_1, this_ptr, SL("levels"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_3, &_1, type, PH_NOISY | PH_READONLY, "zim/debug/errorhandler.zep", 127 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&msg);
	ZEPHIR_CONCAT_VSV(&msg, &_3, ": ", &message);
	ZEPHIR_INIT_VAR(&errorAsException);
	object_init_ex(&errorAsException, zephir_get_internal_ce(SL("errorexception")));
	ZVAL_LONG(&_4, 0);
	ZVAL_LONG(&_5, type);
	ZVAL_LONG(&_6, line);
	ZEPHIR_CALL_METHOD(NULL, &errorAsException, "__construct", NULL, 39, &msg, &_4, &_5, &file, &_6);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, SL("traceReflector"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_7, &errorAsException, "gettrace", NULL, 40);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_4, "setvalue", NULL, 0, &errorAsException, &_7);
	zephir_check_call_status();
	zephir_throw_exception_debug(&errorAsException, "zim/debug/errorhandler.zep", 130 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * @param $exception
 * @param array|null $error
 * @return mixed
 * @throws FatalErrorException
 * @throws \Throwable
 */
PHP_METHOD(Zim_Debug_ErrorHandler, handleException) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval error;
	zval *exception = NULL, exception_sub, *error_param = NULL, __$null, handlerException, exceptionHandler, _0, _2, _1$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&handlerException);
	ZVAL_UNDEF(&exceptionHandler);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&error);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &exception, &error_param);

	ZEPHIR_SEPARATE_PARAM(exception);
	if (!error_param) {
		ZEPHIR_INIT_VAR(&error);
		array_init(&error);
	} else {
		zephir_get_arrval(&error, error_param);
	}


	if (!(zephir_instance_of_ev(exception, zend_exception_get_default(TSRMLS_C) TSRMLS_CC))) {
		ZEPHIR_INIT_NVAR(exception);
		object_init_ex(exception, zim_debug_fatalerrorexception_ce);
		ZEPHIR_CALL_METHOD(NULL, exception, "__construct", NULL, 41, exception);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&handlerException);
	ZVAL_NULL(&handlerException);
	zephir_read_property(&_0, this_ptr, SL("exceptionHandler"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&exceptionHandler, &_0);
	zephir_update_property_zval(this_ptr, SL("exceptionHandler"), &__$null);

	/* try_start_1: */

		if (Z_TYPE_P(&exceptionHandler) != IS_NULL) {
			ZEPHIR_RETURN_CALL_FUNCTION("\call_user_func", NULL, 42, &exceptionHandler, exception);
			zephir_check_call_status_or_jump(try_end_1);
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_1$$4);
		if (zephir_is_true(&handlerException)) {
			ZEPHIR_CPY_WRT(&_1$$4, &handlerException);
		} else {
			ZEPHIR_CPY_WRT(&_1$$4, exception);
		}
		ZEPHIR_CPY_WRT(&handlerException, &_1$$4);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_VAR(&_2);
		ZVAL_OBJ(&_2, EG(exception));
		Z_ADDREF_P(&_2);
		if (zephir_is_instance_of(&_2, SL("Throwable") TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CPY_WRT(&handlerException, &_2);
		}
	}
	if (ZEPHIR_IS_IDENTICAL(exception, &handlerException)) {
		zephir_throw_exception_debug(exception, "zim/debug/errorhandler.zep", 158 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "handleexception", NULL, 43, &handlerException);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

zend_object *zephir_init_properties_Zim_Debug_ErrorHandler(zend_class_entry *class_type TSRMLS_DC) {

		zval _1$$3;
	zval _0;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("levels"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			zephir_create_array(&_1$$3, 15, 0 TSRMLS_CC);
			add_index_stringl(&_1$$3, 8192, SL("Deprecated"));
			add_index_stringl(&_1$$3, 16384, SL("User Deprecated"));
			add_index_stringl(&_1$$3, 8, SL("Notice"));
			add_index_stringl(&_1$$3, 1024, SL("User Notice"));
			add_index_stringl(&_1$$3, 2048, SL("Runtime Notice"));
			add_index_stringl(&_1$$3, 2, SL("Warning"));
			add_index_stringl(&_1$$3, 512, SL("User Warning"));
			add_index_stringl(&_1$$3, 128, SL("Compile Warning"));
			add_index_stringl(&_1$$3, 32, SL("Core Warning"));
			add_index_stringl(&_1$$3, 256, SL("User Error"));
			add_index_stringl(&_1$$3, 4096, SL("Catchable Fatal Error"));
			add_index_stringl(&_1$$3, 64, SL("Compile Error"));
			add_index_stringl(&_1$$3, 4, SL("Parse Error"));
			add_index_stringl(&_1$$3, 1, SL("Error"));
			add_index_stringl(&_1$$3, 16, SL("Core Error"));
			zephir_update_property_zval(this_ptr, SL("levels"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

