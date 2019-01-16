
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
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/concat.h"
#include "kernel/exception.h"
#include "kernel/string.h"
#include "kernel/variables.h"


/**
 * ExceptionHandler converts an exception to a Response object.
 *
 * It is mostly useful in debug mode to replace the default PHP/XDebug
 * output with something prettier and more useful.
 *
 * As this class is mainly used during Kernel boot, where nothing is yet
 * available, the Response content is always HTML.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 * @author Nicolas Grekas <p@tchwork.com>
 */
ZEPHIR_INIT_CLASS(Zim_Debug_Handler) {

	ZEPHIR_REGISTER_CLASS(Zim\\Debug, Handler, zim, debug_handler, zim_debug_handler_method_entry, 0);

	zend_declare_property_null(zim_debug_handler_ce, SL("debug"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_handler_ce, SL("charset"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(zim_debug_handler_ce, SL("fileLinkFormat"), "phpstorm://open?file=%f&line=%l", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_handler_ce, SL("errorLevels"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_handler_ce, SL("traceReflector"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_handler_ce, SL("instance"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zim_debug_handler_ce->create_object = zephir_init_properties_Zim_Debug_Handler;
	return SUCCESS;

}

PHP_METHOD(Zim_Debug_Handler, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *debug_param = NULL, *fileLinkFormat = NULL, fileLinkFormat_sub, __$true, __$false, _0, _1, _2, _4, _5, _6, _7, _3$$4;
	zend_bool debug;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fileLinkFormat_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_3$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &debug_param, &fileLinkFormat);

	if (!debug_param) {
		debug = 1;
	} else {
		debug = zephir_get_boolval(debug_param);
	}
	if (!fileLinkFormat) {
		fileLinkFormat = &fileLinkFormat_sub;
		ZEPHIR_INIT_VAR(fileLinkFormat);
		ZVAL_STRING(fileLinkFormat, "");
	}


	if (debug) {
		zephir_update_property_zval(this_ptr, SL("debug"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("debug"), &__$false);
	}
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "default_charset");
	ZEPHIR_CALL_FUNCTION(&_2, "ini_get", NULL, 53, &_1);
	zephir_check_call_status();
	if (!(zephir_is_true(&_2))) {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_STRING(&_0, "UTF-8");
	} else {
		ZEPHIR_INIT_VAR(&_3$$4);
		ZVAL_STRING(&_3$$4, "default_charset");
		ZEPHIR_CALL_FUNCTION(&_0, "ini_get", NULL, 53, &_3$$4);
		zephir_check_call_status();
	}
	zephir_update_property_zval(this_ptr, SL("charset"), &_0);
	if (zephir_is_true(fileLinkFormat)) {
		zephir_update_property_zval(this_ptr, SL("fileLinkFormat"), fileLinkFormat);
	}
	ZEPHIR_INIT_NVAR(&_1);
	object_init_ex(&_1, zephir_get_internal_ce(SL("reflectionproperty")));
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "Exception");
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "trace");
	ZEPHIR_CALL_METHOD(NULL, &_1, "__construct", NULL, 34, &_4, &_5);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("traceReflector"), &_1);
	zephir_read_property(&_6, this_ptr, SL("traceReflector"), PH_NOISY_CC | PH_READONLY);
	ZVAL_BOOL(&_7, 1);
	ZEPHIR_CALL_METHOD(NULL, &_6, "setaccessible", NULL, 0, &_7);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Zim_Debug_Handler, getInstance) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_static_property_ce(&_0, zim_debug_handler_ce, SL("instance"), PH_NOISY_CC | PH_READONLY);
	RETURN_CTORW(&_0);

}

/**
 * Registers the exception handler.
 *
 * @param bool        $debug          Enable/disable debug mode, where the stack trace is displayed
 * @param string|null $fileLinkFormat The IDE link template
 *
 * @return static
 */
PHP_METHOD(Zim_Debug_Handler, register) {

	zval _1, _3, _4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval fileLinkFormat;
	zval *debug_param = NULL, *fileLinkFormat_param = NULL, handler, _0, _2;
	zend_bool debug;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&handler);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&fileLinkFormat);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &debug_param, &fileLinkFormat_param);

	if (!debug_param) {
		debug = 1;
	} else {
		debug = zephir_get_boolval(debug_param);
	}
	if (!fileLinkFormat_param) {
		ZEPHIR_INIT_VAR(&fileLinkFormat);
		ZVAL_STRING(&fileLinkFormat, "");
	} else {
		zephir_get_strval(&fileLinkFormat, fileLinkFormat_param);
	}


	ZEPHIR_INIT_VAR(&handler);
	object_init_ex(&handler, zim_debug_handler_ce);
	if (debug) {
		ZVAL_BOOL(&_0, 1);
	} else {
		ZVAL_BOOL(&_0, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &handler, "__construct", NULL, 54, &_0, &fileLinkFormat);
	zephir_check_call_status();
	zend_update_static_property(zim_debug_handler_ce, ZEND_STRL("instance"), &handler);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(&_1, &handler);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "handleError");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_CALL_FUNCTION(NULL, "set_error_handler", NULL, 55, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	zephir_create_array(&_3, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(&_3, &handler);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "handleException");
	zephir_array_fast_append(&_3, &_2);
	ZEPHIR_CALL_FUNCTION(NULL, "set_exception_handler", NULL, 56, &_3);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_4);
	zephir_create_array(&_4, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(&_4, &handler);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "handleShutdown");
	zephir_array_fast_append(&_4, &_2);
	ZEPHIR_CALL_FUNCTION(NULL, "register_shutdown_function", NULL, 57, &_4);
	zephir_check_call_status();
	RETURN_CCTOR(&handler);

}

/**
 * Handle the PHP shutdown event.
 *
 * @return void
 */
PHP_METHOD(Zim_Debug_Handler, handleShutdown) {

	zend_bool _0;
	zval error, _1, _2, _3$$3, _4$$3, _5$$3, _6$$3, _7$$3, _8$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&error);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_FUNCTION(&error, "error_get_last", NULL, 58);
	zephir_check_call_status();
	_0 = !(Z_TYPE_P(&error) == IS_NULL);
	if (_0) {
		zephir_array_fetch_string(&_2, &error, SL("type"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 101 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_1, this_ptr, "isfatal", NULL, 0, &_2);
		zephir_check_call_status();
		_0 = zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_3$$3);
		object_init_ex(&_3$$3, zephir_get_internal_ce(SL("errorexception")));
		zephir_array_fetch_string(&_4$$3, &error, SL("message"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 102 TSRMLS_CC);
		zephir_array_fetch_string(&_5$$3, &error, SL("type"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 102 TSRMLS_CC);
		zephir_array_fetch_string(&_6$$3, &error, SL("file"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 102 TSRMLS_CC);
		zephir_array_fetch_string(&_7$$3, &error, SL("line"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 102 TSRMLS_CC);
		ZVAL_LONG(&_8$$3, 0);
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "__construct", NULL, 59, &_4$$3, &_5$$3, &_8$$3, &_6$$3, &_7$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "handleexception", NULL, 0, &_3$$3);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Determine if the error type is fatal.
 *
 * @param  int  $type
 * @return bool
 */
PHP_METHOD(Zim_Debug_Handler, isFatal) {

	zval _0;
	zval *type_param = NULL, _1, _2;
	zend_long type;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &type_param);

	type = zephir_get_intval(type_param);


	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 4, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_LONG(&_1, 64);
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 16);
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 1);
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_LONG(&_1, 4);
	zephir_array_fast_append(&_0, &_1);
	ZVAL_LONG(&_2, type);
	RETURN_MM_BOOL(zephir_fast_in_array(&_2, &_0 TSRMLS_CC));

}

/**
 * Handles errors by filtering then logging them according to the configured bit fields.
 *
 * @param int    $level    One of the E_* constants
 * @param string $message
 * @param string $file
 * @param int    $line
 * @param array  $context
 *
 * @throws \ErrorException
 *
 * @internal
 */
PHP_METHOD(Zim_Debug_Handler, handleError) {

	zval context;
	zval message, file;
	zval *level_param = NULL, *message_param = NULL, *file_param = NULL, *line_param = NULL, *context_param = NULL, _0, msg$$3, errorAsException$$3, _1$$3, _2$$3, _3$$3, _4$$3, _5$$3, _6$$3;
	zend_long level, line, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&msg$$3);
	ZVAL_UNDEF(&errorAsException$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&context);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 3, &level_param, &message_param, &file_param, &line_param, &context_param);

	level = zephir_get_intval(level_param);
	zephir_get_strval(&message, message_param);
	if (!file_param) {
		ZEPHIR_INIT_VAR(&file);
		ZVAL_STRING(&file, "");
	} else {
		zephir_get_strval(&file, file_param);
	}
	if (!line_param) {
		line = 0;
	} else {
		line = zephir_get_intval(line_param);
	}
	if (!context_param) {
		ZEPHIR_INIT_VAR(&context);
		array_init(&context);
	} else {
		zephir_get_arrval(&context, context_param);
	}


	ZEPHIR_CALL_FUNCTION(&_0, "error_reporting", NULL, 60);
	zephir_check_call_status();
	if (((int) (zephir_get_numberval(&_0)) & level)) {
		zephir_read_property(&_1$$3, this_ptr, SL("errorLevels"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_long(&_2$$3, &_1$$3, level, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 134 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&msg$$3);
		ZEPHIR_CONCAT_VSV(&msg$$3, &_2$$3, ": ", &message);
		ZEPHIR_INIT_VAR(&errorAsException$$3);
		object_init_ex(&errorAsException$$3, zephir_get_internal_ce(SL("errorexception")));
		ZVAL_LONG(&_3$$3, 0);
		ZVAL_LONG(&_4$$3, level);
		ZVAL_LONG(&_5$$3, line);
		ZEPHIR_CALL_METHOD(NULL, &errorAsException$$3, "__construct", NULL, 59, &msg$$3, &_3$$3, &_4$$3, &file, &_5$$3);
		zephir_check_call_status();
		zephir_read_property(&_3$$3, this_ptr, SL("traceReflector"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_6$$3, &errorAsException$$3, "gettrace", NULL, 61);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "setvalue", NULL, 0, &errorAsException$$3, &_6$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&errorAsException$$3, "/Users/henter/Dev/zim/zim/debug/handler.zep", 137 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * @param \Throwable $exception
 * @return mixed
 * @throws FatalErrorException
 * @throws \Throwable
 */
PHP_METHOD(Zim_Debug_Handler, handleException) {

	zend_bool _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *exception = NULL, exception_sub, handlerException, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);
	ZVAL_UNDEF(&handlerException);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &exception);

	ZEPHIR_SEPARATE_PARAM(exception);


	_0 = Z_TYPE_P(exception) == IS_OBJECT;
	if (_0) {
		_0 = !((zephir_instance_of_ev(exception, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)));
	}
	if (_0) {
		ZEPHIR_INIT_NVAR(exception);
		object_init_ex(exception, zim_debug_fatalerrorexception_ce);
		ZEPHIR_CALL_METHOD(NULL, exception, "__construct", NULL, 62, exception);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&handlerException);
	ZVAL_NULL(&handlerException);

	/* try_start_1: */

		ZEPHIR_CALL_METHOD(NULL, this_ptr, "sendphpresponse", NULL, 0, exception);
		zephir_check_call_status_or_jump(try_end_1);
		RETURN_MM_NULL();

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_VAR(&_1);
		ZVAL_OBJ(&_1, EG(exception));
		Z_ADDREF_P(&_1);
		if (zephir_is_instance_of(&_1, SL("Throwable") TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CPY_WRT(&handlerException, &_1);
		}
	}
	if (ZEPHIR_IS_IDENTICAL(exception, &handlerException)) {
		zephir_throw_exception_debug(exception, "/Users/henter/Dev/zim/zim/debug/handler.zep", 160 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_throw_exception_debug(&handlerException, "/Users/henter/Dev/zim/zim/debug/handler.zep", 163 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Sends the error associated with the given Exception as a plain PHP response.
 *
 * This method uses plain PHP functions like header() and echo to output
 * the response.
 *
 * @param \Exception|FlattenException $exception An \Exception or FlattenException instance
 */
PHP_METHOD(Zim_Debug_Handler, sendPhpResponse) {

	zend_string *_10$$4;
	zend_ulong _9$$4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL, *_6 = NULL;
	zval *exception = NULL, exception_sub, __$false, name, value, _2, _14, _15, _16, _0$$3, _3$$4, _4$$4, _5$$4, _7$$4, *_8$$4, _12$$4, _13$$4, _11$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_11$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &exception);

	ZEPHIR_SEPARATE_PARAM(exception);


	if (!(zephir_instance_of_ev(exception, zim_debug_flattenexception_ce TSRMLS_CC))) {
		ZEPHIR_CALL_CE_STATIC(&_0$$3, zim_debug_flattenexception_ce, "create", &_1, 0, exception);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(exception, &_0$$3);
	}
	ZEPHIR_CALL_FUNCTION(&_2, "headers_sent", NULL, 28);
	zephir_check_call_status();
	if (!(zephir_is_true(&_2))) {
		ZEPHIR_CALL_METHOD(&_3$$4, exception, "getstatuscode", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$4);
		ZVAL_STRING(&_4$$4, "HTTP/1.0 %s");
		ZEPHIR_CALL_FUNCTION(&_5$$4, "sprintf", NULL, 17, &_4$$4, &_3$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(NULL, "header", &_6, 29, &_5$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_7$$4, exception, "getheaders", NULL, 0);
		zephir_check_call_status();
		zephir_is_iterable(&_7$$4, 0, "/Users/henter/Dev/zim/zim/debug/handler.zep", 186);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_7$$4), _9$$4, _10$$4, _8$$4)
		{
			ZEPHIR_INIT_NVAR(&name);
			if (_10$$4 != NULL) { 
				ZVAL_STR_COPY(&name, _10$$4);
			} else {
				ZVAL_LONG(&name, _9$$4);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _8$$4);
			ZEPHIR_INIT_LNVAR(_11$$5);
			ZEPHIR_CONCAT_VSV(&_11$$5, &name, ": ", &value);
			ZEPHIR_CALL_FUNCTION(NULL, "header", &_6, 29, &_11$$5, &__$false);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&value);
		ZEPHIR_INIT_NVAR(&name);
		zephir_read_property(&_12$$4, this_ptr, SL("charset"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_13$$4);
		ZEPHIR_CONCAT_SV(&_13$$4, "Content-Type: text/html; charset=", &_12$$4);
		ZEPHIR_CALL_FUNCTION(NULL, "header", &_6, 29, &_13$$4);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_15, this_ptr, "getcontent", NULL, 0, exception);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_16, this_ptr, "getstylesheet", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_14, this_ptr, "decorate", NULL, 0, &_15, &_16);
	zephir_check_call_status();
	zend_print_zval(&_14, 0);
	ZEPHIR_MM_RESTORE();

}

/**
 * Gets the full HTML content associated with the given exception.
 *
 * @param \Exception|FlattenException $exception An \Exception or FlattenException instance
 *
 * @return string The HTML content as a string
 */
PHP_METHOD(Zim_Debug_Handler, getHtml) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *exception = NULL, exception_sub, _0$$3, _2, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &exception);

	ZEPHIR_SEPARATE_PARAM(exception);


	if (!(zephir_instance_of_ev(exception, zim_debug_flattenexception_ce TSRMLS_CC))) {
		ZEPHIR_CALL_CE_STATIC(&_0$$3, zim_debug_flattenexception_ce, "create", &_1, 0, exception);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(exception, &_0$$3);
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "getcontent", NULL, 0, exception);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "getstylesheet", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "decorate", NULL, 0, &_2, &_3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param FlattenException $exception
 * @return string
 */
PHP_METHOD(Zim_Debug_Handler, getContent) {

	zend_bool _30$$8;
	zval _18$$7;
	zend_string *_6$$6;
	zend_ulong _5$$6;
	zephir_fcall_cache_entry *_9 = NULL, *_12 = NULL, *_13 = NULL, *_16 = NULL, *_27 = NULL, *_34 = NULL, *_38 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *exception, exception_sub, title, content, count, total, position, e, ind, classs, message, trace, _0, _1, _35, _2$$6, _3$$6, *_4$$6, _7$$7, _8$$7, _10$$7, _11$$7, _14$$7, _15$$7, _17$$7, *_19$$7, _20$$8, _21$$9, _22$$9, _23$$9, _24$$9, _25$$9, _26$$9, _28$$9, _29$$9, _31$$10, _32$$10, _33$$10, _36$$11, _37$$12, _39$$12, _40$$12, _41$$12;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);
	ZVAL_UNDEF(&title);
	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&count);
	ZVAL_UNDEF(&total);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&ind);
	ZVAL_UNDEF(&classs);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&trace);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&_23$$9);
	ZVAL_UNDEF(&_24$$9);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&_31$$10);
	ZVAL_UNDEF(&_32$$10);
	ZVAL_UNDEF(&_33$$10);
	ZVAL_UNDEF(&_36$$11);
	ZVAL_UNDEF(&_37$$12);
	ZVAL_UNDEF(&_39$$12);
	ZVAL_UNDEF(&_40$$12);
	ZVAL_UNDEF(&_41$$12);
	ZVAL_UNDEF(&_18$$7);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &exception);



	ZEPHIR_CALL_METHOD(&_0, exception, "getstatuscode", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&title);
	if (ZEPHIR_IS_LONG(&_0, 404)) {
		ZVAL_STRING(&title, "Sorry, the page you are looking for could not be found.");
	} else {
		ZVAL_STRING(&title, "Whoops, looks like something went wrong.");
	}
	zephir_read_property(&_1, this_ptr, SL("debug"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_1))) {
		ZEPHIR_CONCAT_SVS(return_value, "<div class=\"container\"><h1>", &title, "</h1></div>");
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&content);
	ZVAL_STRING(&content, "");

	/* try_start_1: */

		ZEPHIR_CALL_METHOD(&_2$$6, exception, "getallprevious", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_INIT_VAR(&count);
		ZVAL_LONG(&count, zephir_fast_count_int(&_2$$6 TSRMLS_CC));
		ZEPHIR_INIT_VAR(&total);
		ZVAL_LONG(&total, (zephir_get_numberval(&count) + 1));
		ZEPHIR_CALL_METHOD(&_3$$6, exception, "toarray", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);
		zephir_is_iterable(&_3$$6, 0, "/Users/henter/Dev/zim/zim/debug/handler.zep", 244);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_3$$6), _5$$6, _6$$6, _4$$6)
		{
			ZEPHIR_INIT_NVAR(&position);
			if (_6$$6 != NULL) { 
				ZVAL_STR_COPY(&position, _6$$6);
			} else {
				ZVAL_LONG(&position, _5$$6);
			}
			ZEPHIR_INIT_NVAR(&e);
			ZVAL_COPY(&e, _4$$6);
			ZEPHIR_SINIT_NVAR(_7$$7);
			zephir_sub_function(&_7$$7, &count, &position);
			ZEPHIR_INIT_NVAR(&ind);
			ZVAL_LONG(&ind, (zephir_get_numberval(&_7$$7) + 1));
			zephir_array_fetch_string(&_8$$7, &e, SL("class"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 229 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&classs, this_ptr, "formatclass", &_9, 0, &_8$$7);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_array_fetch_string(&_11$$7, &e, SL("message"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 230 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_10$$7, this_ptr, "escapehtml", &_12, 0, &_11$$7);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_CALL_FUNCTION(&message, "nl2br", &_13, 63, &_10$$7);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_INIT_NVAR(&_14$$7);
			ZVAL_STRING(&_14$$7, "                    <div class=\"trace trace-as-html\">\n                        <table class=\"trace-details\">\n                            <thead class=\"trace-head\"><tr><th>\n                                <h3 class=\"trace-class\">\n                                    <span class=\"text-muted\">(%d/%d)</span>\n                                    <span class=\"exception_title\">%s</span>\n                                </h3>\n                                <p class=\"break-long-words trace-message\">%s</p>\n                            </th></tr></thead>\n                            <tbody>");
			ZEPHIR_CALL_FUNCTION(&_15$$7, "sprintf", &_16, 17, &_14$$7, &ind, &total, &classs, &message);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_concat_self(&content, &_15$$7 TSRMLS_CC);
			ZEPHIR_OBS_NVAR(&_17$$7);
			zephir_array_fetch_string(&_17$$7, &e, SL("trace"), PH_NOISY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 232 TSRMLS_CC);
			zephir_get_arrval(&_18$$7, &_17$$7);
			zephir_is_iterable(&_18$$7, 0, "/Users/henter/Dev/zim/zim/debug/handler.zep", 242);
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_18$$7), _19$$7)
			{
				ZEPHIR_INIT_NVAR(&trace);
				ZVAL_COPY(&trace, _19$$7);
				zephir_concat_self_str(&content, SL("<tr><td>") TSRMLS_CC);
				zephir_array_fetch_string(&_20$$8, &trace, SL("function"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 234 TSRMLS_CC);
				if (zephir_is_true(&_20$$8)) {
					zephir_array_fetch_string(&_22$$9, &trace, SL("class"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 235 TSRMLS_CC);
					ZEPHIR_CALL_METHOD(&_21$$9, this_ptr, "formatclass", &_9, 0, &_22$$9);
					zephir_check_call_status_or_jump(try_end_1);
					zephir_array_fetch_string(&_23$$9, &trace, SL("type"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 235 TSRMLS_CC);
					zephir_array_fetch_string(&_24$$9, &trace, SL("function"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 235 TSRMLS_CC);
					zephir_array_fetch_string(&_26$$9, &trace, SL("args"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 235 TSRMLS_CC);
					ZEPHIR_CALL_METHOD(&_25$$9, this_ptr, "formatargs", &_27, 0, &_26$$9);
					zephir_check_call_status_or_jump(try_end_1);
					ZEPHIR_INIT_NVAR(&_28$$9);
					ZVAL_STRING(&_28$$9, "at <span class=\"trace-class\">%s</span><span class=\"trace-type\">%s</span><span class=\"trace-method\">%s</span>(<span class=\"trace-arguments\">%s</span>)");
					ZEPHIR_CALL_FUNCTION(&_29$$9, "sprintf", &_16, 17, &_28$$9, &_21$$9, &_23$$9, &_24$$9, &_25$$9);
					zephir_check_call_status_or_jump(try_end_1);
					zephir_concat_self(&content, &_29$$9 TSRMLS_CC);
				}
				_30$$8 = zephir_array_isset_string(&trace, SL("file"));
				if (_30$$8) {
					_30$$8 = zephir_array_isset_string(&trace, SL("line"));
				}
				if (_30$$8) {
					zephir_array_fetch_string(&_32$$10, &trace, SL("file"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 238 TSRMLS_CC);
					zephir_array_fetch_string(&_33$$10, &trace, SL("line"), PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 238 TSRMLS_CC);
					ZEPHIR_CALL_METHOD(&_31$$10, this_ptr, "formatpath", &_34, 0, &_32$$10, &_33$$10);
					zephir_check_call_status_or_jump(try_end_1);
					zephir_concat_self(&content, &_31$$10 TSRMLS_CC);
				}
				zephir_concat_self_str(&content, SL("</td></tr>\n") TSRMLS_CC);
			} ZEND_HASH_FOREACH_END();
			ZEPHIR_INIT_NVAR(&trace);
			zephir_concat_self_str(&content, SL("</tbody>\n</table>\n</div>\n") TSRMLS_CC);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&e);
		ZEPHIR_INIT_NVAR(&position);

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_VAR(&_35);
		ZVAL_OBJ(&_35, EG(exception));
		Z_ADDREF_P(&_35);
		if (zephir_instance_of_ev(&_35, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CPY_WRT(&e, &_35);
			zephir_read_property(&_36$$11, this_ptr, SL("debug"), PH_NOISY_CC | PH_READONLY);
			if (zephir_is_true(&_36$$11)) {
				ZEPHIR_CALL_CE_STATIC(&_37$$12, zim_debug_flattenexception_ce, "create", &_38, 0, &e);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&e, &_37$$12);
				ZEPHIR_CALL_METHOD(&_37$$12, &e, "getclass", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_40$$12, &e, "getmessage", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_39$$12, this_ptr, "escapehtml", &_12, 0, &_40$$12);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(&_41$$12);
				ZVAL_STRING(&_41$$12, "Exception thrown when handling an exception (%s: %s)");
				ZEPHIR_CALL_FUNCTION(&title, "sprintf", &_16, 17, &_41$$12, &_37$$12, &_39$$12);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&title);
				ZVAL_STRING(&title, "Whoops, looks like something went wrong.");
			}
		}
	}
	ZEPHIR_CONCAT_SVSSSVS(return_value, "<div class=\"exception-summary\">\n                    <div class=\"container\">\n                    <div class=\"exception-message-wrapper\">\n                        <h1 class=\"break-long-words exception-message\">", &title, "</h1>\n                        <div class=\"exception-illustration hidden-xs-down\">", "Zim (1.0.0)", "</div>\n                    </div>\n                    </div>\n                </div>\n                <div class=\"container\">", &content, "</div>");
	RETURN_MM();

}

/**
 * Gets the stylesheet associated with the given exception.
 *
 * @return string The stylesheet as a string
 */
PHP_METHOD(Zim_Debug_Handler, getStylesheet) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("debug"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_0))) {
		RETURN_STRING("");
	}
	RETURN_STRING("body { background-color: #F9F9F9; color: #222; font: 14px/1.4 Helvetica, Arial, sans-serif; margin: 0; padding-bottom: 45px; }\n\n            a { cursor: pointer; text-decoration: none; }\n            a:hover { text-decoration: underline; }\n            abbr[title] { border-bottom: none; cursor: help; text-decoration: none; }\n\n            code, pre { font: 13px/1.5 Consolas, Monaco, Menlo, \"Ubuntu Mono\", \"Liberation Mono\", monospace; }\n\n            table, tr, th, td { background: #FFF; border-collapse: collapse; vertical-align: top; }\n            table { background: #FFF; border: 1px solid #E0E0E0; box-shadow: 0px 0px 1px rgba(128, 128, 128, .2); margin: 1em 0; width: 100%; }\n            table th, table td { border: solid #E0E0E0; border-width: 1px 0; padding: 8px 10px; }\n            table th { background-color: #E0E0E0; font-weight: bold; text-align: left; }\n\n            .hidden-xs-down { display: none; }\n            .block { display: block; }\n            .break-long-words { -ms-word-break: break-all; word-break: break-all; word-break: break-word; -webkit-hyphens: auto; -moz-hyphens: auto; hyphens: auto; }\n            .text-muted { color: #999; }\n\n            .container { max-width: 1024px; margin: 0 auto; padding: 0 15px; }\n            .container::after { content: \"\"; display: table; clear: both; }\n\n            .exception-summary { background: #B0413E; border-bottom: 2px solid rgba(0, 0, 0, 0.1); border-top: 1px solid rgba(0, 0, 0, .3); flex: 0 0 auto; margin-bottom: 30px; }\n\n            .exception-message-wrapper { display: flex; align-items: center; min-height: 70px; }\n            .exception-message { flex-grow: 1; padding: 30px 0; }\n            .exception-message, .exception-message a { color: #FFF; font-size: 21px; font-weight: 400; margin: 0; }\n            .exception-message.long { font-size: 18px; }\n            .exception-message a { border-bottom: 1px solid rgba(255, 255, 255, 0.5); font-size: inherit; text-decoration: none; }\n            .exception-message a:hover { border-bottom-color: #ffffff; }\n\n            .exception-illustration { flex-basis: 111px; flex-shrink: 0; height: 66px; margin-left: 15px; opacity: .7; color: #fff; }\n\n            .trace + .trace { margin-top: 30px; }\n            .trace-head .trace-class { color: #222; font-size: 18px; font-weight: bold; line-height: 1.3; margin: 0; position: relative; }\n\n            .trace-message { font-size: 14px; font-weight: normal; margin: .5em 0 0; }\n\n            .trace-file-path, .trace-file-path a { color: #222; margin-top: 3px; font-size: 13px; }\n            .trace-class { color: #B0413E; }\n            .trace-type { padding: 0 2px; }\n            .trace-method { color: #B0413E; font-weight: bold; }\n            .trace-arguments { color: #777; font-weight: normal; padding-left: 2px; }\n\n            @media (min-width: 575px) {\n                .hidden-xs-down { display: initial; }\n            }");

}

PHP_METHOD(Zim_Debug_Handler, decorate) {

	zval *content_param = NULL, *css_param = NULL, _0;
	zval content, css;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content);
	ZVAL_UNDEF(&css);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &content_param, &css_param);

	zephir_get_strval(&content, content_param);
	zephir_get_strval(&css, css_param);


	zephir_read_property(&_0, this_ptr, SL("charset"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CONCAT_SVSVSVS(return_value, "\n<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"", &_0, "\" />\n<meta name=\"robots\" content=\"noindex,nofollow\" />\n<style>", &css, "</style>\n</head>\n<body>", &content, "</body></html>");
	RETURN_MM();

}

PHP_METHOD(Zim_Debug_Handler, formatClass) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *classs_param = NULL, _0;
	zval classs;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&classs);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &classs_param);

	zephir_get_strval(&classs, classs_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "<abbr title=\"%s\">%s</abbr>");
	ZEPHIR_RETURN_CALL_FUNCTION("sprintf", NULL, 17, &_0, &classs, &classs);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Zim_Debug_Handler, formatPath) {

	zval _19, _33;
	zephir_fcall_cache_entry *_4 = NULL, *_8 = NULL, *_11 = NULL, *_31 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path = NULL, path_sub, *line, line_sub, file, fmt, i, f, k, link, _0, _1, _2, _3, _9, _10, _12, _13, _14, _15, _16, _17, _18, _20, _21, _22, _23, _24, _25, _32, _34, _35, _5$$4, _6$$4, _7$$4, _26$$5, _27$$7, _28$$7, _29$$7, _30$$7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_sub);
	ZVAL_UNDEF(&line_sub);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&fmt);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&f);
	ZVAL_UNDEF(&k);
	ZVAL_UNDEF(&link);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_26$$5);
	ZVAL_UNDEF(&_27$$7);
	ZVAL_UNDEF(&_28$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_30$$7);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_33);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &path, &line);

	ZEPHIR_SEPARATE_PARAM(path);


	if (ZEPHIR_IS_STRING(path, "")) {
		RETURN_MM_STRING("<span class=\"block trace-arguments\"> [in zim extension] </span>");
	}
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "#[^/\\\\]*+$#");
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "#[^/\\\\]*+$#");
	zephir_preg_match(&_2, &_3, path, &file, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(&_2)) {
		ZEPHIR_OBS_NVAR(&_0);
		zephir_array_fetch_long(&_0, &file, 0, PH_NOISY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 286 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(&_0, path);
	}
	ZEPHIR_CALL_METHOD(&file, this_ptr, "escapehtml", &_4, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&fmt);
	zephir_read_property(&fmt, this_ptr, SL("fileLinkFormat"), PH_NOISY_CC);
	if (!(zephir_is_true(&fmt))) {
		ZEPHIR_CALL_METHOD(&_5$$4, this_ptr, "escapehtml", &_4, 0, path);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_6$$4);
		if (ZEPHIR_GT_LONG(line, 0)) {
			ZEPHIR_INIT_NVAR(&_6$$4);
			ZEPHIR_CONCAT_SV(&_6$$4, " line ", line);
		} else {
			ZEPHIR_INIT_NVAR(&_6$$4);
			ZVAL_STRING(&_6$$4, "");
		}
		ZEPHIR_INIT_VAR(&_7$$4);
		ZVAL_STRING(&_7$$4, "<span class=\"block trace-file-path\">in <a title=\"%s%3$s\"><strong>%s</strong>%s</a></span>");
		ZEPHIR_RETURN_CALL_FUNCTION("sprintf", &_8, 17, &_7$$4, &_5$$4, &file, &_6$$4);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_CPY_WRT(&f, &fmt);
	ZEPHIR_INIT_VAR(&_9);
	ZVAL_STRING(&_9, "%f");
	ZEPHIR_CALL_FUNCTION(&_10, "strrpos", &_11, 64, &f, &_9);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_9);
	ZVAL_STRING(&_9, "%l");
	ZEPHIR_CALL_FUNCTION(&_12, "strrpos", &_11, 64, &f, &_9);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_13, "max", NULL, 65, &_10, &_12);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_9);
	ZVAL_STRING(&_9, "&");
	ZEPHIR_INIT_VAR(&_14);
	zephir_fast_strpos(&_14, &f, &_9, zephir_get_intval(&_13) );
	if (zephir_is_true(&_14)) {
		ZEPHIR_INIT_VAR(&_15);
		ZVAL_STRING(&_15, "%f");
		ZEPHIR_CALL_FUNCTION(&_16, "strrpos", &_11, 64, &f, &_15);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_15);
		ZVAL_STRING(&_15, "%l");
		ZEPHIR_CALL_FUNCTION(&_17, "strrpos", &_11, 64, &f, &_15);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_18, "max", NULL, 65, &_16, &_17);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_15);
		ZVAL_STRING(&_15, "&");
		ZEPHIR_INIT_VAR(&i);
		zephir_fast_strpos(&i, &f, &_15, zephir_get_intval(&_18) );
	} else {
		ZEPHIR_INIT_NVAR(&i);
		ZVAL_LONG(&i, zephir_fast_strlen_ev(&f));
	}
	ZEPHIR_INIT_VAR(&_19);
	zephir_create_array(&_19, 1, 0 TSRMLS_CC);
	ZVAL_LONG(&_20, 0);
	ZEPHIR_INIT_VAR(&_21);
	zephir_substr(&_21, &f, 0 , zephir_get_intval(&i), 0);
	zephir_array_fast_append(&_19, &_21);
	ZEPHIR_INIT_NVAR(&_21);
	zephir_substr(&_21, &f, zephir_get_intval(&i), 0, ZEPHIR_SUBSTR_NO_LENGTH);
	ZEPHIR_INIT_VAR(&_22);
	ZVAL_STRING(&_22, "/&([^>]++)>/");
	ZVAL_LONG(&_23, -1);
	ZVAL_LONG(&_24, 2);
	ZEPHIR_CALL_FUNCTION(&_25, "preg_split", NULL, 66, &_22, &_21, &_23, &_24);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&fmt);
	zephir_fast_array_merge(&fmt, &_19, &_25 TSRMLS_CC);
	ZEPHIR_INIT_NVAR(&i);
	ZVAL_LONG(&i, 1);
	while (1) {
		if (zephir_array_isset(&fmt, &i)) {
			break;
		}
		ZEPHIR_SEPARATE(&i);
		zephir_increment(&i);
		ZEPHIR_OBS_NVAR(&k);
		zephir_array_fetch(&k, &fmt, &i, PH_NOISY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 303 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&_26$$5);
		zephir_fast_strpos(&_26$$5, path, &k, 0 );
		if (ZEPHIR_IS_LONG_IDENTICAL(&_26$$5, 0)) {
			zephir_array_fetch(&_27$$7, &fmt, &i, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 305 TSRMLS_CC);
			ZVAL_LONG(&_28$$7, 0);
			ZVAL_LONG(&_29$$7, zephir_fast_strlen_ev(&k));
			ZEPHIR_CALL_FUNCTION(&_30$$7, "substr_replace", &_31, 67, path, &_27$$7, &_28$$7, &_29$$7);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(path, &_30$$7);
			break;
		}
		ZEPHIR_SEPARATE(&i);
		zephir_increment(&i);
	}
	zephir_array_fetch_long(&_32, &fmt, 0, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 311 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_33);
	zephir_create_array(&_33, 2, 0 TSRMLS_CC);
	zephir_array_update_string(&_33, SL("%f"), path, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_33, SL("%l"), line, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_FUNCTION(&link, "strtr", NULL, 68, &_32, &_33);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_34, this_ptr, "escapehtml", &_4, 0, &link);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_35);
	if (ZEPHIR_GT_LONG(line, 0)) {
		ZEPHIR_INIT_NVAR(&_35);
		ZEPHIR_CONCAT_SV(&_35, " line ", line);
	} else {
		ZEPHIR_INIT_NVAR(&_35);
		ZVAL_STRING(&_35, "");
	}
	ZEPHIR_INIT_NVAR(&_22);
	ZVAL_STRING(&_22, "<span class=\"block trace-file-path\">in <a href=\"%s\" title=\"Go to source\"><strong>%s</string>%s</a></span>");
	ZEPHIR_RETURN_CALL_FUNCTION("sprintf", &_8, 17, &_22, &_34, &file, &_35);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Formats an array as a string.
 *
 * @param array $args The argument array
 *
 * @return string
 */
PHP_METHOD(Zim_Debug_Handler, formatArgs) {

	zend_string *_2;
	zend_ulong _1;
	zephir_fcall_cache_entry *_14 = NULL, *_16 = NULL, *_20 = NULL, *_28 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *args_param = NULL, result, key, item, formattedValue, *_0, _3$$3, _4$$3, _5$$3, _6$$3, _7$$3, _8$$3, _9$$3, _10$$3, _11$$3, _31$$3, _32$$3, _33$$3, _12$$4, _13$$4, _15$$4, _17$$5, _18$$5, _19$$5, _21$$5, _22$$7, _23$$7, _24$$7, _25$$9, _26$$9, _27$$9, _29$$9, _30$$9;
	zval args;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&args);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&item);
	ZVAL_UNDEF(&formattedValue);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_31$$3);
	ZVAL_UNDEF(&_32$$3);
	ZVAL_UNDEF(&_33$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_23$$7);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&_30$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &args_param);

	zephir_get_arrval(&args, args_param);


	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	zephir_is_iterable(&args, 0, "/Users/henter/Dev/zim/zim/debug/handler.zep", 343);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&args), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&key, _2);
		} else {
			ZVAL_LONG(&key, _1);
		}
		ZEPHIR_INIT_NVAR(&item);
		ZVAL_COPY(&item, _0);
		zephir_array_fetch_long(&_3$$3, &item, 0, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 328 TSRMLS_CC);
		zephir_array_fetch_long(&_4$$3, &item, 0, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 330 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_5$$3);
		ZVAL_STRING(&_5$$3, "array");
		zephir_array_fetch_long(&_6$$3, &item, 0, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 332 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_7$$3);
		ZVAL_STRING(&_7$$3, "null");
		zephir_array_fetch_long(&_8$$3, &item, 0, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 334 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_9$$3);
		ZVAL_STRING(&_9$$3, "boolean");
		zephir_array_fetch_long(&_10$$3, &item, 0, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 336 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_11$$3);
		ZVAL_STRING(&_11$$3, "resource");
		if (ZEPHIR_IS_STRING_IDENTICAL(&_3$$3, "object")) {
			zephir_array_fetch_long(&_13$$4, &item, 1, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 329 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_12$$4, this_ptr, "formatclass", &_14, 0, &_13$$4);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_15$$4);
			ZVAL_STRING(&_15$$4, "<em>object</em>(%s)");
			ZEPHIR_CALL_FUNCTION(&formattedValue, "sprintf", &_16, 17, &_15$$4, &_12$$4);
			zephir_check_call_status();
		} else if (ZEPHIR_IS_IDENTICAL(&_5$$3, &_4$$3)) {
			ZEPHIR_INIT_LNVAR(_17$$5);
			zephir_array_fetch_long(&_18$$5, &item, 1, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 331 TSRMLS_CC);
			if (Z_TYPE_P(&_18$$5) == IS_ARRAY) {
				zephir_array_fetch_long(&_19$$5, &item, 1, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 331 TSRMLS_CC);
				ZEPHIR_CALL_METHOD(&_17$$5, this_ptr, "formatargs", &_20, 69, &_19$$5);
				zephir_check_call_status();
			} else {
				ZEPHIR_OBS_NVAR(&_17$$5);
				zephir_array_fetch_long(&_17$$5, &item, 1, PH_NOISY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 331 TSRMLS_CC);
			}
			ZEPHIR_INIT_NVAR(&_21$$5);
			ZVAL_STRING(&_21$$5, "<em>array</em>(%s)");
			ZEPHIR_CALL_FUNCTION(&formattedValue, "sprintf", &_16, 17, &_21$$5, &_17$$5);
			zephir_check_call_status();
		} else if (ZEPHIR_IS_IDENTICAL(&_7$$3, &_6$$3)) {
			ZEPHIR_INIT_NVAR(&formattedValue);
			ZVAL_STRING(&formattedValue, "<em>null</em>");
		} else if (ZEPHIR_IS_IDENTICAL(&_9$$3, &_8$$3)) {
			ZEPHIR_INIT_NVAR(&_22$$7);
			ZEPHIR_INIT_NVAR(&_23$$7);
			zephir_array_fetch_long(&_24$$7, &item, 1, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 335 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_23$$7);
			zephir_var_export_ex(&_23$$7, &_24$$7 TSRMLS_CC);
			zephir_fast_strtolower(&_22$$7, &_23$$7);
			ZEPHIR_INIT_NVAR(&formattedValue);
			ZEPHIR_CONCAT_SVS(&formattedValue, "<em>", &_22$$7, "</em>");
		} else if (ZEPHIR_IS_IDENTICAL(&_11$$3, &_10$$3)) {
			ZEPHIR_INIT_NVAR(&formattedValue);
			ZVAL_STRING(&formattedValue, "<em>resource</em>");
		} else {
			ZEPHIR_INIT_NVAR(&_26$$9);
			zephir_array_fetch_long(&_27$$9, &item, 1, PH_NOISY | PH_READONLY, "/Users/henter/Dev/zim/zim/debug/handler.zep", 339 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_26$$9);
			zephir_var_export_ex(&_26$$9, &_27$$9 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_25$$9, this_ptr, "escapehtml", &_28, 0, &_26$$9);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_29$$9);
			ZVAL_STRING(&_29$$9, "\n");
			ZEPHIR_INIT_NVAR(&_30$$9);
			ZVAL_STRING(&_30$$9, "");
			ZEPHIR_INIT_NVAR(&formattedValue);
			zephir_fast_str_replace(&formattedValue, &_29$$9, &_30$$9, &_25$$9 TSRMLS_CC);
		}
		ZEPHIR_INIT_LNVAR(_31$$3);
		if (Z_TYPE_P(&key) == IS_LONG) {
			ZEPHIR_CPY_WRT(&_31$$3, &formattedValue);
		} else {
			ZEPHIR_CALL_METHOD(&_32$$3, this_ptr, "escapehtml", &_28, 0, &key);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_33$$3);
			ZVAL_STRING(&_33$$3, "'%s' => %s");
			ZEPHIR_CALL_FUNCTION(&_31$$3, "sprintf", &_16, 17, &_33$$3, &_32$$3, &formattedValue);
			zephir_check_call_status();
		}
		zephir_array_append(&result, &_31$$3, PH_SEPARATE, "/Users/henter/Dev/zim/zim/debug/handler.zep", 341);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&item);
	ZEPHIR_INIT_NVAR(&key);
	zephir_fast_join_str(return_value, SL(", "), &result TSRMLS_CC);
	RETURN_MM();

}

/**
 * HTML-encodes a string.
 */
PHP_METHOD(Zim_Debug_Handler, escapeHtml) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *str, str_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&str_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &str);



	zephir_read_property(&_0, this_ptr, SL("charset"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, (2 | 8));
	ZEPHIR_RETURN_CALL_FUNCTION("htmlspecialchars", NULL, 70, str, &_1, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

zend_object *zephir_init_properties_Zim_Debug_Handler(zend_class_entry *class_type TSRMLS_DC) {

		zval _1$$3;
	zval _0;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("errorLevels"), PH_NOISY_CC | PH_READONLY);
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
			zephir_update_property_zval(this_ptr, SL("errorLevels"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

