
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
ZEPHIR_INIT_CLASS(Zim_Debug_ExceptionHandler) {

	ZEPHIR_REGISTER_CLASS(Zim\\Debug, ExceptionHandler, zim, debug_exceptionhandler, zim_debug_exceptionhandler_method_entry, 0);

	zend_declare_property_null(zim_debug_exceptionhandler_ce, SL("debug"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_exceptionhandler_ce, SL("charset"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_exceptionhandler_ce, SL("fileLinkFormat"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Zim_Debug_ExceptionHandler, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *debug_param = NULL, *fileLinkFormat = NULL, fileLinkFormat_sub, __$true, __$false, __$null, _0, _1, _2;
	zend_bool debug;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fileLinkFormat_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &debug_param, &fileLinkFormat);

	if (!debug_param) {
		debug = 1;
	} else {
		debug = zephir_get_boolval(debug_param);
	}
	if (!fileLinkFormat) {
		fileLinkFormat = &fileLinkFormat_sub;
		fileLinkFormat = &__$null;
	}


	if (debug) {
		zephir_update_property_zval(this_ptr, SL("debug"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("debug"), &__$false);
	}
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "default_charset");
	ZEPHIR_CALL_FUNCTION(&_2, "ini_get", NULL, 44, &_1);
	zephir_check_call_status();
	if (zephir_is_true(&_2)) {
		ZEPHIR_INIT_NVAR(&_1);
		ZVAL_STRING(&_1, "default_charset");
		ZEPHIR_CALL_FUNCTION(&_0, "ini_get", NULL, 44, &_1);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_STRING(&_0, "UTF-8");
	}
	zephir_update_property_zval(this_ptr, SL("charset"), &_0);
	zephir_update_property_zval(this_ptr, SL("fileLinkFormat"), fileLinkFormat);
	ZEPHIR_MM_RESTORE();

}

/**
 * Registers the exception handler.
 *
 * @param bool        $debug          Enable/disable debug mode, where the stack trace is displayed
 * @param string|null $fileLinkFormat The IDE link template
 *
 * @return static
 */
PHP_METHOD(Zim_Debug_ExceptionHandler, register) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *debug_param = NULL, *fileLinkFormat = NULL, fileLinkFormat_sub, __$null, handler, tmpArray45b76a47b5bb3fdab106b03e7c1e698d, _0, _1;
	zend_bool debug;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&fileLinkFormat_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&handler);
	ZVAL_UNDEF(&tmpArray45b76a47b5bb3fdab106b03e7c1e698d);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &debug_param, &fileLinkFormat);

	if (!debug_param) {
		debug = 1;
	} else {
		debug = zephir_get_boolval(debug_param);
	}
	if (!fileLinkFormat) {
		fileLinkFormat = &fileLinkFormat_sub;
		fileLinkFormat = &__$null;
	}


	ZEPHIR_INIT_VAR(&handler);
	object_init_ex(&handler, zim_debug_exceptionhandler_ce);
	if (debug) {
		ZVAL_BOOL(&_0, 1);
	} else {
		ZVAL_BOOL(&_0, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &handler, "__construct", NULL, 45, &_0, fileLinkFormat);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&tmpArray45b76a47b5bb3fdab106b03e7c1e698d);
	zephir_create_array(&tmpArray45b76a47b5bb3fdab106b03e7c1e698d, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(&tmpArray45b76a47b5bb3fdab106b03e7c1e698d, &handler);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "handle");
	zephir_array_fast_append(&tmpArray45b76a47b5bb3fdab106b03e7c1e698d, &_1);
	ZEPHIR_CALL_FUNCTION(NULL, "set_exception_handler", NULL, 35, &tmpArray45b76a47b5bb3fdab106b03e7c1e698d);
	zephir_check_call_status();
	RETURN_CCTOR(&handler);

}

/**
 * Sends a response for the given Exception.
 *
 * To be as fail-safe as possible, the exception is first handled
 * by our simple exception handler, then by the user exception handler.
 * The latter takes precedence and any output from the former is cancelled,
 * if and only if nothing bad happens in this handling path.
 */
PHP_METHOD(Zim_Debug_ExceptionHandler, handle) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *exception, exception_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &exception);



	ZEPHIR_CALL_METHOD(NULL, this_ptr, "sendphpresponse", NULL, 0, exception);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Sends the error associated with the given Exception as a plain PHP response.
 *
 * This method uses plain PHP functions like header() and echo to output
 * the response.
 *
 * @param \Exception|FlattenException $exception An \Exception or FlattenException instance
 */
PHP_METHOD(Zim_Debug_ExceptionHandler, sendPhpResponse) {

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
	ZEPHIR_CALL_FUNCTION(&_2, "headers_sent", NULL, 23);
	zephir_check_call_status();
	if (!(zephir_is_true(&_2))) {
		ZEPHIR_CALL_METHOD(&_3$$4, exception, "getstatuscode", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$4);
		ZVAL_STRING(&_4$$4, "HTTP/1.0 %s");
		ZEPHIR_CALL_FUNCTION(&_5$$4, "sprintf", NULL, 21, &_4$$4, &_3$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(NULL, "header", &_6, 24, &_5$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_7$$4, exception, "getheaders", NULL, 0);
		zephir_check_call_status();
		zephir_is_iterable(&_7$$4, 0, "zim/debug/exceptionhandler.zep", 86);
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
			ZEPHIR_CALL_FUNCTION(NULL, "header", &_6, 24, &_11$$5, &__$false);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&value);
		ZEPHIR_INIT_NVAR(&name);
		zephir_read_property(&_12$$4, this_ptr, SL("charset"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_13$$4);
		ZEPHIR_CONCAT_SV(&_13$$4, "Content-Type: text/html; charset=", &_12$$4);
		ZEPHIR_CALL_FUNCTION(NULL, "header", &_6, 24, &_13$$4);
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
 * @param FlattenException $exception
 * @return string
 */
PHP_METHOD(Zim_Debug_ExceptionHandler, getContent) {

	zend_bool _28$$8;
	zend_string *_5$$6;
	zend_ulong _4$$6;
	zephir_fcall_cache_entry *_8 = NULL, *_11 = NULL, *_12 = NULL, *_15 = NULL, *_25 = NULL, *_32 = NULL, *_36 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *exception, exception_sub, title, content, count, total, position, e, ind, classs, message, trace, _0, _33, _1$$6, _2$$6, *_3$$6, _6$$7, _7$$7, _9$$7, _10$$7, _13$$7, _14$$7, _16$$7, *_17$$7, _18$$8, _19$$9, _20$$9, _21$$9, _22$$9, _23$$9, _24$$9, _26$$9, _27$$9, _29$$10, _30$$10, _31$$10, _34$$11, _35$$12, _37$$12, _38$$12, _39$$12;
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
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_1$$6);
	ZVAL_UNDEF(&_2$$6);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&_19$$9);
	ZVAL_UNDEF(&_20$$9);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&_23$$9);
	ZVAL_UNDEF(&_24$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_29$$10);
	ZVAL_UNDEF(&_30$$10);
	ZVAL_UNDEF(&_31$$10);
	ZVAL_UNDEF(&_34$$11);
	ZVAL_UNDEF(&_35$$12);
	ZVAL_UNDEF(&_37$$12);
	ZVAL_UNDEF(&_38$$12);
	ZVAL_UNDEF(&_39$$12);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &exception);



	ZEPHIR_INIT_VAR(&title);
	if (404) {
		ZVAL_STRING(&title, "Sorry, the page you are looking for could not be found.");
	} else {
		ZVAL_STRING(&title, "Whoops, looks like something went wrong.");
	}
	zephir_read_property(&_0, this_ptr, SL("debug"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_is_true(&_0))) {
		RETURN_MM_STRING("                <div class=\"container\">\n                    <h1>{title}</h1>\n                </div>");
	}
	ZEPHIR_INIT_VAR(&content);
	ZVAL_STRING(&content, "");

	/* try_start_1: */

		ZEPHIR_CALL_METHOD(&_1$$6, exception, "getallprevious", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);
		ZEPHIR_INIT_VAR(&count);
		ZVAL_LONG(&count, zephir_fast_count_int(&_1$$6 TSRMLS_CC));
		ZEPHIR_INIT_VAR(&total);
		ZVAL_LONG(&total, (zephir_get_numberval(&count) + 1));
		ZEPHIR_CALL_METHOD(&_2$$6, exception, "toarray", NULL, 0);
		zephir_check_call_status_or_jump(try_end_1);
		zephir_is_iterable(&_2$$6, 0, "zim/debug/exceptionhandler.zep", 128);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_2$$6), _4$$6, _5$$6, _3$$6)
		{
			ZEPHIR_INIT_NVAR(&position);
			if (_5$$6 != NULL) { 
				ZVAL_STR_COPY(&position, _5$$6);
			} else {
				ZVAL_LONG(&position, _4$$6);
			}
			ZEPHIR_INIT_NVAR(&e);
			ZVAL_COPY(&e, _3$$6);
			ZEPHIR_SINIT_NVAR(_6$$7);
			zephir_sub_function(&_6$$7, &count, &position);
			ZEPHIR_INIT_NVAR(&ind);
			ZVAL_LONG(&ind, (zephir_get_numberval(&_6$$7) + 1));
			zephir_array_fetch_string(&_7$$7, &e, SL("class"), PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 113 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&classs, this_ptr, "formatclass", &_8, 0, &_7$$7);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_array_fetch_string(&_10$$7, &e, SL("message"), PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 114 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_9$$7, this_ptr, "escapehtml", &_11, 0, &_10$$7);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_CALL_FUNCTION(&message, "nl2br", &_12, 46, &_9$$7);
			zephir_check_call_status_or_jump(try_end_1);
			ZEPHIR_INIT_NVAR(&_13$$7);
			ZVAL_STRING(&_13$$7, "                    <div class=\"trace trace-as-html\">\n                        <table class=\"trace-details\">\n                            <thead class=\"trace-head\"><tr><th>\n                                <h3 class=\"trace-class\">\n                                    <span class=\"text-muted\">(%d/%d)</span>\n                                    <span class=\"exception_title\">%s</span>\n                                </h3>\n                                <p class=\"break-long-words trace-message\">%s</p>\n                            </th></tr></thead>\n                            <tbody>");
			ZEPHIR_CALL_FUNCTION(&_14$$7, "sprintf", &_15, 21, &_13$$7, &ind, &total, &classs, &message);
			zephir_check_call_status_or_jump(try_end_1);
			zephir_concat_self(&content, &_14$$7 TSRMLS_CC);
			zephir_array_fetch_string(&_16$$7, &e, SL("trace"), PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 116 TSRMLS_CC);
			zephir_is_iterable(&_16$$7, 0, "zim/debug/exceptionhandler.zep", 126);
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_16$$7), _17$$7)
			{
				ZEPHIR_INIT_NVAR(&trace);
				ZVAL_COPY(&trace, _17$$7);
				zephir_concat_self_str(&content, SL("<tr><td>") TSRMLS_CC);
				zephir_array_fetch_string(&_18$$8, &trace, SL("function"), PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 118 TSRMLS_CC);
				if (zephir_is_true(&_18$$8)) {
					zephir_array_fetch_string(&_20$$9, &trace, SL("class"), PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 119 TSRMLS_CC);
					ZEPHIR_CALL_METHOD(&_19$$9, this_ptr, "formatclass", &_8, 0, &_20$$9);
					zephir_check_call_status_or_jump(try_end_1);
					zephir_array_fetch_string(&_21$$9, &trace, SL("type"), PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 119 TSRMLS_CC);
					zephir_array_fetch_string(&_22$$9, &trace, SL("function"), PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 119 TSRMLS_CC);
					zephir_array_fetch_string(&_24$$9, &trace, SL("args"), PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 119 TSRMLS_CC);
					ZEPHIR_CALL_METHOD(&_23$$9, this_ptr, "formatargs", &_25, 0, &_24$$9);
					zephir_check_call_status_or_jump(try_end_1);
					ZEPHIR_INIT_NVAR(&_26$$9);
					ZVAL_STRING(&_26$$9, "at <span class=\"trace-class\">%s</span><span class=\"trace-type\">%s</span><span class=\"trace-method\">%s</span>(<span class=\"trace-arguments\">%s</span>)");
					ZEPHIR_CALL_FUNCTION(&_27$$9, "sprintf", &_15, 21, &_26$$9, &_19$$9, &_21$$9, &_22$$9, &_23$$9);
					zephir_check_call_status_or_jump(try_end_1);
					zephir_concat_self(&content, &_27$$9 TSRMLS_CC);
				}
				_28$$8 = zephir_array_isset_string(&trace, SL("file"));
				if (_28$$8) {
					_28$$8 = zephir_array_isset_string(&trace, SL("line"));
				}
				if (_28$$8) {
					zephir_array_fetch_string(&_30$$10, &trace, SL("file"), PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 122 TSRMLS_CC);
					zephir_array_fetch_string(&_31$$10, &trace, SL("line"), PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 122 TSRMLS_CC);
					ZEPHIR_CALL_METHOD(&_29$$10, this_ptr, "formatpath", &_32, 0, &_30$$10, &_31$$10);
					zephir_check_call_status_or_jump(try_end_1);
					zephir_concat_self(&content, &_29$$10 TSRMLS_CC);
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
		ZEPHIR_INIT_VAR(&_33);
		ZVAL_OBJ(&_33, EG(exception));
		Z_ADDREF_P(&_33);
		if (zephir_instance_of_ev(&_33, zend_exception_get_default(TSRMLS_C) TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CPY_WRT(&e, &_33);
			zephir_read_property(&_34$$11, this_ptr, SL("debug"), PH_NOISY_CC | PH_READONLY);
			if (zephir_is_true(&_34$$11)) {
				ZEPHIR_CALL_CE_STATIC(&_35$$12, zim_debug_flattenexception_ce, "create", &_36, 0, &e);
				zephir_check_call_status();
				ZEPHIR_CPY_WRT(&e, &_35$$12);
				ZEPHIR_CALL_METHOD(&_35$$12, &e, "getclass", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_38$$12, &e, "getmessage", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&_37$$12, this_ptr, "escapehtml", &_11, 0, &_38$$12);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(&_39$$12);
				ZVAL_STRING(&_39$$12, "Exception thrown when handling an exception (%s: %s)");
				ZEPHIR_CALL_FUNCTION(&title, "sprintf", &_15, 21, &_39$$12, &_35$$12, &_37$$12);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&title);
				ZVAL_STRING(&title, "Whoops, looks like something went wrong.");
			}
		}
	}
	RETURN_MM_STRING("            <div class=\"exception-summary\">\n                <div class=\"container\">\n                    <div class=\"exception-message-wrapper\">\n                        <h1 class=\"break-long-words exception-message\">{title}</h1>\n                        <div class=\"exception-illustration hidden-xs-down\">Zim v1.0.0</div>\n                    </div>\n                </div>\n            </div>\n\n            <div class=\"container\">\n                {content}\n            </div>");

}

/**
 * Gets the stylesheet associated with the given exception.
 *
 * @return string The stylesheet as a string
 */
PHP_METHOD(Zim_Debug_ExceptionHandler, getStylesheet) {

	zval *this_ptr = getThis();


	RETURN_STRING("            body { background-color: #F9F9F9; color: #222; font: 14px/1.4 Helvetica, Arial, sans-serif; margin: 0; padding-bottom: 45px; }\n\n            a { cursor: pointer; text-decoration: none; }\n            a:hover { text-decoration: underline; }\n            abbr[title] { border-bottom: none; cursor: help; text-decoration: none; }\n\n            code, pre { font: 13px/1.5 Consolas, Monaco, Menlo, \"Ubuntu Mono\", \"Liberation Mono\", monospace; }\n\n            table, tr, th, td { background: #FFF; border-collapse: collapse; vertical-align: top; }\n            table { background: #FFF; border: 1px solid #E0E0E0; box-shadow: 0px 0px 1px rgba(128, 128, 128, .2); margin: 1em 0; width: 100%; }\n            table th, table td { border: solid #E0E0E0; border-width: 1px 0; padding: 8px 10px; }\n            table th { background-color: #E0E0E0; font-weight: bold; text-align: left; }\n\n            .hidden-xs-down { display: none; }\n            .block { display: block; }\n            .break-long-words { -ms-word-break: break-all; word-break: break-all; word-break: break-word; -webkit-hyphens: auto; -moz-hyphens: auto; hyphens: auto; }\n            .text-muted { color: #999; }\n\n            .container { max-width: 1024px; margin: 0 auto; padding: 0 15px; }\n            .container::after { content: \"\"; display: table; clear: both; }\n\n            .exception-summary { background: #B0413E; border-bottom: 2px solid rgba(0, 0, 0, 0.1); border-top: 1px solid rgba(0, 0, 0, .3); flex: 0 0 auto; margin-bottom: 30px; }\n\n            .exception-message-wrapper { display: flex; align-items: center; min-height: 70px; }\n            .exception-message { flex-grow: 1; padding: 30px 0; }\n            .exception-message, .exception-message a { color: #FFF; font-size: 21px; font-weight: 400; margin: 0; }\n            .exception-message.long { font-size: 18px; }\n            .exception-message a { border-bottom: 1px solid rgba(255, 255, 255, 0.5); font-size: inherit; text-decoration: none; }\n            .exception-message a:hover { border-bottom-color: #ffffff; }\n\n            .exception-illustration { flex-basis: 111px; flex-shrink: 0; height: 66px; margin-left: 15px; opacity: .7; color: #fff; }\n\n            .trace + .trace { margin-top: 30px; }\n            .trace-head .trace-class { color: #222; font-size: 18px; font-weight: bold; line-height: 1.3; margin: 0; position: relative; }\n\n            .trace-message { font-size: 14px; font-weight: normal; margin: .5em 0 0; }\n\n            .trace-file-path, .trace-file-path a { color: #222; margin-top: 3px; font-size: 13px; }\n            .trace-class { color: #B0413E; }\n            .trace-type { padding: 0 2px; }\n            .trace-method { color: #B0413E; font-weight: bold; }\n            .trace-arguments { color: #777; font-weight: normal; padding-left: 2px; }\n\n            @media (min-width: 575px) {\n                .hidden-xs-down { display: initial; }\n            }");

}

PHP_METHOD(Zim_Debug_ExceptionHandler, decorate) {

	zval *content, content_sub, *css, css_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_sub);
	ZVAL_UNDEF(&css_sub);

	zephir_fetch_params(0, 2, 0, &content, &css);



	RETURN_STRING("<!DOCTYPE html>\n<html>\n    <head>\n        <meta charset=\"{this->charset}\" />\n        <meta name=\"robots\" content=\"noindex,nofollow\" />\n        <style>{css}</style>\n    </head>\n    <body>\n        {content}\n    </body>\n</html>");

}

PHP_METHOD(Zim_Debug_ExceptionHandler, formatClass) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *classs, classs_sub, parts, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&classs_sub);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &classs);



	ZEPHIR_INIT_VAR(&parts);
	zephir_fast_explode_str(&parts, SL("\\"), classs, LONG_MAX TSRMLS_CC);
	ZEPHIR_MAKE_REF(&parts);
	ZEPHIR_CALL_FUNCTION(&_0, "array_pop", NULL, 5, &parts);
	ZEPHIR_UNREF(&parts);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "<abbr title=\"%s\">%s</abbr>");
	ZEPHIR_RETURN_CALL_FUNCTION("sprintf", NULL, 21, &_1, classs, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Zim_Debug_ExceptionHandler, formatPath) {

	zval _19;
	zephir_fcall_cache_entry *_4 = NULL, *_8 = NULL, *_11 = NULL, *_29 = NULL, *_32 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path = NULL, path_sub, *line, line_sub, file, fmt, i, f, k, link, tmpArray8a110ec4b9f0ab7193f1a4b881c4ec74, _0, _1, _2, _3, _9, _10, _12, _13, _14, _15, _16, _17, _18, _20, _21, _22, _23, _24, _25, _33, _34, _35, _5$$3, _6$$3, _7$$3, _26$$4, _27$$6, _28$$6, _30$$6, _31$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_sub);
	ZVAL_UNDEF(&line_sub);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&fmt);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&f);
	ZVAL_UNDEF(&k);
	ZVAL_UNDEF(&link);
	ZVAL_UNDEF(&tmpArray8a110ec4b9f0ab7193f1a4b881c4ec74);
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
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_26$$4);
	ZVAL_UNDEF(&_27$$6);
	ZVAL_UNDEF(&_28$$6);
	ZVAL_UNDEF(&_30$$6);
	ZVAL_UNDEF(&_31$$6);
	ZVAL_UNDEF(&_19);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &path, &line);

	ZEPHIR_SEPARATE_PARAM(path);


	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "#[^/\\\\]*+$#");
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "#[^/\\\\]*+$#");
	zephir_preg_match(&_2, &_3, path, &file, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(&_2)) {
		ZEPHIR_OBS_NVAR(&_0);
		zephir_array_fetch_long(&_0, &file, 0, PH_NOISY, "zim/debug/exceptionhandler.zep", 167 TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(&_0, path);
	}
	ZEPHIR_CALL_METHOD(&file, this_ptr, "escapehtml", &_4, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&fmt);
	zephir_read_property(&fmt, this_ptr, SL("fileLinkFormat"), PH_NOISY_CC);
	if (!(zephir_is_true(&fmt))) {
		ZEPHIR_CALL_METHOD(&_5$$3, this_ptr, "escapehtml", &_4, 0, path);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_6$$3);
		if (ZEPHIR_GT_LONG(line, 0)) {
			ZEPHIR_INIT_NVAR(&_6$$3);
			ZEPHIR_CONCAT_SV(&_6$$3, " line ", line);
		} else {
			ZEPHIR_INIT_NVAR(&_6$$3);
			ZVAL_STRING(&_6$$3, "");
		}
		ZEPHIR_INIT_VAR(&_7$$3);
		ZVAL_STRING(&_7$$3, "<span class=\"block trace-file-path\">in <a title=\"%s%3$s\"><strong>%s</strong>%s</a></span>");
		ZEPHIR_RETURN_CALL_FUNCTION("sprintf", &_8, 21, &_7$$3, &_5$$3, &file, &_6$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_CPY_WRT(&f, &fmt);
	ZEPHIR_INIT_VAR(&_9);
	ZVAL_STRING(&_9, "%f");
	ZEPHIR_CALL_FUNCTION(&_10, "strrpos", &_11, 47, &f, &_9);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_9);
	ZVAL_STRING(&_9, "%l");
	ZEPHIR_CALL_FUNCTION(&_12, "strrpos", &_11, 47, &f, &_9);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_13, "max", NULL, 48, &_10, &_12);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_9);
	ZVAL_STRING(&_9, "&");
	ZEPHIR_INIT_VAR(&_14);
	zephir_fast_strpos(&_14, &f, &_9, zephir_get_intval(&_13) );
	if (zephir_is_true(&_14)) {
		ZEPHIR_INIT_VAR(&_15);
		ZVAL_STRING(&_15, "%f");
		ZEPHIR_CALL_FUNCTION(&_16, "strrpos", &_11, 47, &f, &_15);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_15);
		ZVAL_STRING(&_15, "%l");
		ZEPHIR_CALL_FUNCTION(&_17, "strrpos", &_11, 47, &f, &_15);
		zephir_check_call_status();
		ZEPHIR_CALL_FUNCTION(&_18, "max", NULL, 48, &_16, &_17);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_15);
		ZVAL_STRING(&_15, "&");
		ZEPHIR_INIT_VAR(&i);
		zephir_fast_strpos(&i, &f, &_15, zephir_get_intval(&_18) );
	} else {
		ZEPHIR_CALL_FUNCTION(&i, "\strlen", NULL, 49, &f);
		zephir_check_call_status();
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
	ZEPHIR_CALL_FUNCTION(&_25, "preg_split", NULL, 50, &_22, &_21, &_23, &_24);
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
		zephir_array_fetch(&k, &fmt, &i, PH_NOISY, "zim/debug/exceptionhandler.zep", 184 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&_26$$4);
		zephir_fast_strpos(&_26$$4, path, &k, 0 );
		if (ZEPHIR_IS_LONG_IDENTICAL(&_26$$4, 0)) {
			zephir_array_fetch(&_27$$6, &fmt, &i, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 186 TSRMLS_CC);
			ZEPHIR_CALL_FUNCTION(&_28$$6, "\strlen", &_29, 49, &k);
			zephir_check_call_status();
			ZVAL_LONG(&_30$$6, 0);
			ZEPHIR_CALL_FUNCTION(&_31$$6, "substr_replace", &_32, 51, path, &_27$$6, &_30$$6, &_28$$6);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(path, &_31$$6);
			break;
		}
		ZEPHIR_SEPARATE(&i);
		zephir_increment(&i);
	}
	ZEPHIR_INIT_VAR(&tmpArray8a110ec4b9f0ab7193f1a4b881c4ec74);
	zephir_create_array(&tmpArray8a110ec4b9f0ab7193f1a4b881c4ec74, 2, 0 TSRMLS_CC);
	zephir_array_update_string(&tmpArray8a110ec4b9f0ab7193f1a4b881c4ec74, SL("%f"), path, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&tmpArray8a110ec4b9f0ab7193f1a4b881c4ec74, SL("%l"), line, PH_COPY | PH_SEPARATE);
	zephir_array_fetch_long(&_33, &fmt, 0, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 193 TSRMLS_CC);
	ZEPHIR_CALL_FUNCTION(&link, "strtr", NULL, 52, &_33, &tmpArray8a110ec4b9f0ab7193f1a4b881c4ec74);
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
	ZEPHIR_RETURN_CALL_FUNCTION("sprintf", &_8, 21, &_22, &_34, &file, &_35);
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
PHP_METHOD(Zim_Debug_ExceptionHandler, formatArgs) {

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
	zephir_is_iterable(&args, 0, "zim/debug/exceptionhandler.zep", 225);
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
		zephir_array_fetch_long(&_3$$3, &item, 0, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 210 TSRMLS_CC);
		zephir_array_fetch_long(&_4$$3, &item, 0, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 212 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_5$$3);
		ZVAL_STRING(&_5$$3, "array");
		zephir_array_fetch_long(&_6$$3, &item, 0, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 214 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_7$$3);
		ZVAL_STRING(&_7$$3, "null");
		zephir_array_fetch_long(&_8$$3, &item, 0, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 216 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_9$$3);
		ZVAL_STRING(&_9$$3, "boolean");
		zephir_array_fetch_long(&_10$$3, &item, 0, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 218 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_11$$3);
		ZVAL_STRING(&_11$$3, "resource");
		if (ZEPHIR_IS_STRING_IDENTICAL(&_3$$3, "object")) {
			zephir_array_fetch_long(&_13$$4, &item, 1, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 211 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_12$$4, this_ptr, "formatclass", &_14, 0, &_13$$4);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_15$$4);
			ZVAL_STRING(&_15$$4, "<em>object</em>(%s)");
			ZEPHIR_CALL_FUNCTION(&formattedValue, "sprintf", &_16, 21, &_15$$4, &_12$$4);
			zephir_check_call_status();
		} else if (ZEPHIR_IS_IDENTICAL(&_5$$3, &_4$$3)) {
			ZEPHIR_INIT_LNVAR(_17$$5);
			zephir_array_fetch_long(&_18$$5, &item, 1, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 213 TSRMLS_CC);
			if (Z_TYPE_P(&_18$$5) == IS_ARRAY) {
				zephir_array_fetch_long(&_19$$5, &item, 1, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 213 TSRMLS_CC);
				ZEPHIR_CALL_METHOD(&_17$$5, this_ptr, "formatargs", &_20, 53, &_19$$5);
				zephir_check_call_status();
			} else {
				ZEPHIR_OBS_NVAR(&_17$$5);
				zephir_array_fetch_long(&_17$$5, &item, 1, PH_NOISY, "zim/debug/exceptionhandler.zep", 213 TSRMLS_CC);
			}
			ZEPHIR_INIT_NVAR(&_21$$5);
			ZVAL_STRING(&_21$$5, "<em>array</em>(%s)");
			ZEPHIR_CALL_FUNCTION(&formattedValue, "sprintf", &_16, 21, &_21$$5, &_17$$5);
			zephir_check_call_status();
		} else if (ZEPHIR_IS_IDENTICAL(&_7$$3, &_6$$3)) {
			ZEPHIR_INIT_NVAR(&formattedValue);
			ZVAL_STRING(&formattedValue, "<em>null</em>");
		} else if (ZEPHIR_IS_IDENTICAL(&_9$$3, &_8$$3)) {
			ZEPHIR_INIT_NVAR(&_22$$7);
			ZEPHIR_INIT_NVAR(&_23$$7);
			zephir_array_fetch_long(&_24$$7, &item, 1, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 217 TSRMLS_CC);
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
			zephir_array_fetch_long(&_27$$9, &item, 1, PH_NOISY | PH_READONLY, "zim/debug/exceptionhandler.zep", 221 TSRMLS_CC);
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
			ZEPHIR_CALL_FUNCTION(&_31$$3, "sprintf", &_16, 21, &_33$$3, &_32$$3, &formattedValue);
			zephir_check_call_status();
		}
		zephir_array_append(&result, &_31$$3, PH_SEPARATE, "zim/debug/exceptionhandler.zep", 223);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&item);
	ZEPHIR_INIT_NVAR(&key);
	zephir_fast_join_str(return_value, SL(", "), &result TSRMLS_CC);
	RETURN_MM();

}

/**
 * HTML-encodes a string.
 */
PHP_METHOD(Zim_Debug_ExceptionHandler, escapeHtml) {

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
	ZEPHIR_RETURN_CALL_FUNCTION("htmlspecialchars", NULL, 54, str, &_1, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

