
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
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/concat.h"
#include "ext/spl/spl_array.h"


/**
 * FlattenException wraps a PHP Error or Exception to be able to serialize it.
 *
 * Basically, this class removes all objects from the trace.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
ZEPHIR_INIT_CLASS(Zim_Debug_FlattenException) {

	ZEPHIR_REGISTER_CLASS(Zim\\Debug, FlattenException, zim, debug_flattenexception, zim_debug_flattenexception_method_entry, 0);

	zend_declare_property_null(zim_debug_flattenexception_ce, SL("message"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_flattenexception_ce, SL("code"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_flattenexception_ce, SL("previous"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_flattenexception_ce, SL("trace"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_flattenexception_ce, SL("classs"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_flattenexception_ce, SL("statusCode"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_flattenexception_ce, SL("headers"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_flattenexception_ce, SL("file"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_debug_flattenexception_ce, SL("line"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Zim_Debug_FlattenException, create) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval headers;
	zval *exception, exception_sub, *statusCode = NULL, statusCode_sub, *headers_param = NULL, __$null;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);
	ZVAL_UNDEF(&statusCode_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&headers);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &exception, &statusCode, &headers_param);

	if (!statusCode) {
		statusCode = &statusCode_sub;
		statusCode = &__$null;
	}
	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}


	ZEPHIR_RETURN_CALL_STATIC("createfromthrowable", NULL, 0, exception, statusCode, &headers);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Zim_Debug_FlattenException, createFromThrowable) {

	zval headers;
	zend_long statusCode, ZEPHIR_LAST_CALL_STATUS;
	zval *exception, exception_sub, *statusCode_param = NULL, *headers_param = NULL, e, previous, scode, _0, _1, _4, _5, _6, _7, _2$$3, _3$$3, _8$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exception_sub);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&previous);
	ZVAL_UNDEF(&scode);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&headers);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &exception, &statusCode_param, &headers_param);

	if (!statusCode_param) {
		statusCode = 0;
	} else {
		statusCode = zephir_get_intval(statusCode_param);
	}
	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}


	ZEPHIR_INIT_VAR(&e);
	object_init_ex(&e, zim_debug_flattenexception_ce);
	if (zephir_has_constructor(&e TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, &e, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_0, exception, "getmessage", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &e, "setmessage", NULL, 56, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, exception, "getcode", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &e, "setcode", NULL, 57, &_1);
	zephir_check_call_status();
	if (zephir_instance_of_ev(exception, zim_http_exception_exceptioninterface_ce TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&scode, exception, "getstatuscode", NULL, 0);
		zephir_check_call_status();
		statusCode = zephir_get_numberval(&scode);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CALL_METHOD(&_3$$3, exception, "getheaders", NULL, 0);
		zephir_check_call_status();
		zephir_fast_array_merge(&_2$$3, &headers, &_3$$3 TSRMLS_CC);
		ZEPHIR_CPY_WRT(&headers, &_2$$3);
	}
	if (!(statusCode)) {
		statusCode = 500;
	}
	ZVAL_LONG(&_4, statusCode);
	ZEPHIR_CALL_METHOD(NULL, &e, "setstatuscode", NULL, 58, &_4);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &e, "setheaders", NULL, 59, &headers);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &e, "settracefromthrowable", NULL, 60, exception);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_5);
	if (zephir_instance_of_ev(exception, zim_debug_fatalerrorexception_ce TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&_5, exception, "getoriginalclassname", NULL, 0);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&_5);
		zephir_get_class(&_5, exception, 0 TSRMLS_CC);
	}
	ZEPHIR_CALL_METHOD(NULL, &e, "setclass", NULL, 61, &_5);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_6, exception, "getfile", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &e, "setfile", NULL, 62, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_7, exception, "getline", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &e, "setline", NULL, 63, &_7);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&previous, exception, "getprevious", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_instance_of(&previous, SL("Throwable") TSRMLS_CC)) {
		ZEPHIR_CALL_STATIC(&_8$$5, "createfromthrowable", NULL, 0, &previous);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &e, "setprevious", NULL, 64, &_8$$5);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&e);

}

PHP_METHOD(Zim_Debug_FlattenException, toArray) {

	zval _0, _3$$3;
	zval exceptions, exception, _1, *_2, _4$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exceptions);
	ZVAL_UNDEF(&exception);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&exceptions);
	array_init(&exceptions);
	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 3, 0 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getmessage", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("message"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getclass", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("class"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "gettrace", NULL, 0);
	zephir_check_call_status();
	zephir_array_update_string(&_0, SL("trace"), &_1, PH_COPY | PH_SEPARATE);
	zephir_array_append(&exceptions, &_0, PH_SEPARATE, "zim/debug/flattenexception.zep", 67);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getallprevious", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_1, 0, "zim/debug/flattenexception.zep", 72);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_1), _2)
	{
		ZEPHIR_INIT_NVAR(&exception);
		ZVAL_COPY(&exception, _2);
		ZEPHIR_INIT_NVAR(&_3$$3);
		zephir_create_array(&_3$$3, 3, 0 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_4$$3, &exception, "getmessage", NULL, 0);
		zephir_check_call_status();
		zephir_array_update_string(&_3$$3, SL("message"), &_4$$3, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(&_4$$3, &exception, "getclass", NULL, 0);
		zephir_check_call_status();
		zephir_array_update_string(&_3$$3, SL("class"), &_4$$3, PH_COPY | PH_SEPARATE);
		ZEPHIR_CALL_METHOD(&_4$$3, &exception, "gettrace", NULL, 0);
		zephir_check_call_status();
		zephir_array_update_string(&_3$$3, SL("trace"), &_4$$3, PH_COPY | PH_SEPARATE);
		zephir_array_append(&exceptions, &_3$$3, PH_SEPARATE, "zim/debug/flattenexception.zep", 70);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&exception);
	RETURN_CCTOR(&exceptions);

}

PHP_METHOD(Zim_Debug_FlattenException, getStatusCode) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "statusCode");

}

/**
 * @return $this
 */
PHP_METHOD(Zim_Debug_FlattenException, setStatusCode) {

	zval *code, code_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&code_sub);

	zephir_fetch_params(0, 1, 0, &code);



	zephir_update_property_zval(this_ptr, SL("statusCode"), code);
	RETURN_THISW();

}

PHP_METHOD(Zim_Debug_FlattenException, getHeaders) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "headers");

}

/**
 * @return $this
 */
PHP_METHOD(Zim_Debug_FlattenException, setHeaders) {

	zval *headers_param = NULL;
	zval headers;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&headers);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &headers_param);

	zephir_get_arrval(&headers, headers_param);


	zephir_update_property_zval(this_ptr, SL("headers"), &headers);
	RETURN_THIS();

}

PHP_METHOD(Zim_Debug_FlattenException, getClass) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "classs");

}

/**
 * @return $this
 */
PHP_METHOD(Zim_Debug_FlattenException, setClass) {

	zend_bool _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *classs, classs_sub, _0, _1, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&classs_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &classs);



	ZEPHIR_INIT_VAR(&_0);
	zephir_array_fetch_long(&_1, classs, 0, PH_NOISY | PH_READONLY, "zim/debug/flattenexception.zep", 113 TSRMLS_CC);
	_2 = ZEPHIR_IS_STRING_IDENTICAL(&_1, "c");
	if (_2) {
		ZEPHIR_INIT_VAR(&_3);
		ZVAL_STRING(&_3, "class@anonymous\\0");
		ZEPHIR_INIT_VAR(&_4);
		zephir_fast_strpos(&_4, classs, &_3, 0 );
		_2 = ZEPHIR_IS_LONG_IDENTICAL(&_4, 0);
	}
	if (_2) {
		ZEPHIR_CALL_FUNCTION(&_5, "get_parent_class", NULL, 65, classs);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_0);
		ZEPHIR_CONCAT_VS(&_0, &_5, "@anonymous");
	} else {
		ZEPHIR_CPY_WRT(&_0, classs);
	}
	zephir_update_property_zval(this_ptr, SL("classs"), &_0);
	RETURN_THIS();

}

PHP_METHOD(Zim_Debug_FlattenException, getFile) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "file");

}

/**
 * @return $this
 */
PHP_METHOD(Zim_Debug_FlattenException, setFile) {

	zval *file, file_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&file_sub);

	zephir_fetch_params(0, 1, 0, &file);



	zephir_update_property_zval(this_ptr, SL("file"), file);
	RETURN_THISW();

}

PHP_METHOD(Zim_Debug_FlattenException, getLine) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "line");

}

/**
 * @return $this
 */
PHP_METHOD(Zim_Debug_FlattenException, setLine) {

	zval *line, line_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&line_sub);

	zephir_fetch_params(0, 1, 0, &line);



	zephir_update_property_zval(this_ptr, SL("line"), line);
	RETURN_THISW();

}

PHP_METHOD(Zim_Debug_FlattenException, getMessage) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "message");

}

/**
 * @return $this
 */
PHP_METHOD(Zim_Debug_FlattenException, setMessage) {

	zend_class_entry *_3$$3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *message = NULL, message_sub, _0, _1, _2$$3, _4$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&message_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &message);

	ZEPHIR_SEPARATE_PARAM(message);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "class@anonymous\\0");
	ZEPHIR_INIT_VAR(&_1);
	zephir_fast_strpos(&_1, message, &_0, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		if (!_3$$3) {
		_3$$3 = zephir_fetch_class_str_ex(SL("Zim\\Debug\\FlattenExceptionsetMessageClosureOne"), ZEND_FETCH_CLASS_AUTO);
		}
		object_init_ex(&_2$$3, _3$$3);
		if (zephir_has_constructor(&_2$$3 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 0);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_VAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "/class@anonymous\\x00.*?\\.php0x?[0-9a-fA-F]++/");
		ZEPHIR_CALL_FUNCTION(&_5$$3, "preg_replace_callback", NULL, 66, &_4$$3, &_2$$3, message);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(message, &_5$$3);
	}
	zephir_update_property_zval(this_ptr, SL("message"), message);
	RETURN_THIS();

}

PHP_METHOD(Zim_Debug_FlattenException, getCode) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "code");

}

/**
 * @return $this
 */
PHP_METHOD(Zim_Debug_FlattenException, setCode) {

	zval *code, code_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&code_sub);

	zephir_fetch_params(0, 1, 0, &code);



	zephir_update_property_zval(this_ptr, SL("code"), code);
	RETURN_THISW();

}

PHP_METHOD(Zim_Debug_FlattenException, getPrevious) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "previous");

}

/**
 * @return $this
 */
PHP_METHOD(Zim_Debug_FlattenException, setPrevious) {

	zval *previous, previous_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&previous_sub);

	zephir_fetch_params(0, 1, 0, &previous);



	zephir_update_property_zval(this_ptr, SL("previous"), previous);
	RETURN_THISW();

}

PHP_METHOD(Zim_Debug_FlattenException, getAllPrevious) {

	zval exceptions, e, _0, _1$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&exceptions);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&exceptions);
	array_init(&exceptions);
	ZEPHIR_CPY_WRT(&e, this_ptr);
	ZEPHIR_CALL_METHOD(&_0, &e, "getprevious", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&e, &_0);
	while (1) {
		if (!(zephir_is_true(&e))) {
			break;
		}
		zephir_array_append(&exceptions, &e, PH_SEPARATE, "zim/debug/flattenexception.zep", 198);
		ZEPHIR_CALL_METHOD(&_1$$3, &e, "getprevious", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&e, &_1$$3);
	}
	RETURN_CCTOR(&exceptions);

}

PHP_METHOD(Zim_Debug_FlattenException, getTrace) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "trace");

}

PHP_METHOD(Zim_Debug_FlattenException, setTraceFromThrowable) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *throwable, throwable_sub, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&throwable_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &throwable);



	ZEPHIR_CALL_METHOD(&_0, throwable, "gettrace", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, throwable, "getfile", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, throwable, "getline", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "settrace", NULL, 0, &_0, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @return $this
 */
PHP_METHOD(Zim_Debug_FlattenException, setTrace) {

	zval _1, _6$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_5 = NULL, *_9 = NULL;
	zval *trace, trace_sub, *file, file_sub, *line, line_sub, entry, classs, namespacee, parts, _0, _2, *_3, _4$$4, _7$$3, _8$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&trace_sub);
	ZVAL_UNDEF(&file_sub);
	ZVAL_UNDEF(&line_sub);
	ZVAL_UNDEF(&entry);
	ZVAL_UNDEF(&classs);
	ZVAL_UNDEF(&namespacee);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &trace, &file, &line);



	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("trace"), &_0);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 8, 0 TSRMLS_CC);
	add_assoc_stringl_ex(&_1, SL("namespace"), SL(""));
	add_assoc_stringl_ex(&_1, SL("short_class"), SL(""));
	add_assoc_stringl_ex(&_1, SL("class"), SL(""));
	add_assoc_stringl_ex(&_1, SL("type"), SL(""));
	add_assoc_stringl_ex(&_1, SL("function"), SL(""));
	zephir_array_update_string(&_1, SL("file"), file, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_1, SL("line"), line, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zephir_array_update_string(&_1, SL("args"), &_2, PH_COPY | PH_SEPARATE);
	zephir_update_property_array_append(this_ptr, SL("trace"), &_1 TSRMLS_CC);
	zephir_is_iterable(trace, 0, "zim/debug/flattenexception.zep", 241);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(trace), _3)
	{
		ZEPHIR_INIT_NVAR(&entry);
		ZVAL_COPY(&entry, _3);
		ZEPHIR_INIT_NVAR(&classs);
		ZVAL_STRING(&classs, "");
		ZEPHIR_INIT_NVAR(&namespacee);
		ZVAL_STRING(&namespacee, "");
		if (zephir_array_isset_string(&entry, SL("class"))) {
			zephir_array_fetch_string(&_4$$4, &entry, SL("class"), PH_NOISY | PH_READONLY, "zim/debug/flattenexception.zep", 227 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&parts);
			zephir_fast_explode_str(&parts, SL("\\"), &_4$$4, LONG_MAX TSRMLS_CC);
			ZEPHIR_MAKE_REF(&parts);
			ZEPHIR_CALL_FUNCTION(&classs, "array_pop", &_5, 5, &parts);
			ZEPHIR_UNREF(&parts);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&namespacee);
			zephir_fast_join_str(&namespacee, SL("\\"), &parts TSRMLS_CC);
		}
		ZEPHIR_INIT_NVAR(&_6$$3);
		zephir_create_array(&_6$$3, 8, 0 TSRMLS_CC);
		zephir_array_update_string(&_6$$3, SL("namespace"), &namespacee, PH_COPY | PH_SEPARATE);
		zephir_array_update_string(&_6$$3, SL("short_class"), &classs, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_LNVAR(_7$$3);
		if (zephir_array_isset_string(&entry, SL("class"))) {
			ZEPHIR_OBS_NVAR(&_7$$3);
			zephir_array_fetch_string(&_7$$3, &entry, SL("class"), PH_NOISY, "zim/debug/flattenexception.zep", 234 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(&_7$$3);
			ZVAL_STRING(&_7$$3, "");
		}
		zephir_array_update_string(&_6$$3, SL("class"), &_7$$3, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_LNVAR(_7$$3);
		if (zephir_array_isset_string(&entry, SL("type"))) {
			ZEPHIR_OBS_NVAR(&_7$$3);
			zephir_array_fetch_string(&_7$$3, &entry, SL("type"), PH_NOISY, "zim/debug/flattenexception.zep", 235 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(&_7$$3);
			ZVAL_STRING(&_7$$3, "");
		}
		zephir_array_update_string(&_6$$3, SL("type"), &_7$$3, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_LNVAR(_7$$3);
		if (zephir_array_isset_string(&entry, SL("function"))) {
			ZEPHIR_OBS_NVAR(&_7$$3);
			zephir_array_fetch_string(&_7$$3, &entry, SL("function"), PH_NOISY, "zim/debug/flattenexception.zep", 236 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(&_7$$3);
			ZVAL_NULL(&_7$$3);
		}
		zephir_array_update_string(&_6$$3, SL("function"), &_7$$3, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_LNVAR(_7$$3);
		if (zephir_array_isset_string(&entry, SL("file"))) {
			ZEPHIR_OBS_NVAR(&_7$$3);
			zephir_array_fetch_string(&_7$$3, &entry, SL("file"), PH_NOISY, "zim/debug/flattenexception.zep", 237 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(&_7$$3);
			ZVAL_NULL(&_7$$3);
		}
		zephir_array_update_string(&_6$$3, SL("file"), &_7$$3, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_LNVAR(_7$$3);
		if (zephir_array_isset_string(&entry, SL("line"))) {
			ZEPHIR_OBS_NVAR(&_7$$3);
			zephir_array_fetch_string(&_7$$3, &entry, SL("line"), PH_NOISY, "zim/debug/flattenexception.zep", 238 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(&_7$$3);
			ZVAL_NULL(&_7$$3);
		}
		zephir_array_update_string(&_6$$3, SL("line"), &_7$$3, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_LNVAR(_7$$3);
		if (zephir_array_isset_string(&entry, SL("args"))) {
			zephir_array_fetch_string(&_8$$3, &entry, SL("args"), PH_NOISY | PH_READONLY, "zim/debug/flattenexception.zep", 239 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_7$$3, this_ptr, "flattenargs", &_9, 0, &_8$$3);
			zephir_check_call_status();
		} else {
			ZEPHIR_INIT_NVAR(&_7$$3);
			array_init(&_7$$3);
		}
		zephir_array_update_string(&_6$$3, SL("args"), &_7$$3, PH_COPY | PH_SEPARATE);
		zephir_update_property_array_append(this_ptr, SL("trace"), &_6$$3 TSRMLS_CC);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&entry);
	RETURN_THIS();

}

PHP_METHOD(Zim_Debug_FlattenException, flattenArgs) {

	zval _34$$15;
	zval _6$$5, _10$$6, _12$$8, _14$$9, _20$$10, _22$$11, _24$$12, _26$$13, _28$$14, _32$$15;
	zend_string *_2;
	zend_ulong _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_5 = NULL, *_9 = NULL, *_19 = NULL, *_31 = NULL;
	zval *args, args_sub, *level = NULL, level_sub, *count = NULL, count_sub, __$null, result, key, value, *_0, _3$$4, _4$$3, _7$$5, _8$$5, _11$$6, _13$$8, _15$$9, _16$$9, _17$$9, _18$$9, _21$$10, _23$$11, _25$$12, _27$$13, _29$$14, _30$$14, _33$$15;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&args_sub);
	ZVAL_UNDEF(&level_sub);
	ZVAL_UNDEF(&count_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$9);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&_18$$9);
	ZVAL_UNDEF(&_21$$10);
	ZVAL_UNDEF(&_23$$11);
	ZVAL_UNDEF(&_25$$12);
	ZVAL_UNDEF(&_27$$13);
	ZVAL_UNDEF(&_29$$14);
	ZVAL_UNDEF(&_30$$14);
	ZVAL_UNDEF(&_33$$15);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_20$$10);
	ZVAL_UNDEF(&_22$$11);
	ZVAL_UNDEF(&_24$$12);
	ZVAL_UNDEF(&_26$$13);
	ZVAL_UNDEF(&_28$$14);
	ZVAL_UNDEF(&_32$$15);
	ZVAL_UNDEF(&_34$$15);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &args, &level, &count);

	if (!level) {
		level = &level_sub;
		ZEPHIR_INIT_VAR(level);
		ZVAL_LONG(level, 0);
	}
	if (!count) {
		count = &count_sub;
		ZEPHIR_INIT_VAR(count);
		ZVAL_LONG(count, 0);
	}


	ZEPHIR_INIT_VAR(&result);
	array_init(&result);
	zephir_is_iterable(args, 0, "zim/debug/flattenexception.zep", 278);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(args), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&key, _2);
		} else {
			ZVAL_LONG(&key, _1);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _0);
		if (ZEPHIR_GT_LONG(count, 10000)) {
			zephir_create_array(return_value, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_3$$4);
			ZVAL_STRING(&_3$$4, "array");
			zephir_array_fast_append(return_value, &_3$$4);
			ZEPHIR_INIT_NVAR(&_3$$4);
			ZVAL_STRING(&_3$$4, "*SKIPPED over 10000 entries*");
			zephir_array_fast_append(return_value, &_3$$4);
			RETURN_MM();
		}
		ZEPHIR_CALL_FUNCTION(&_4$$3, "is_float", &_5, 67, &value);
		zephir_check_call_status();
		if (zephir_instance_of_ev(&value, zephir_get_internal_ce(SL("__php_incomplete_class")) TSRMLS_CC)) {
			ZEPHIR_INIT_NVAR(&_6$$5);
			zephir_create_array(&_6$$5, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_7$$5);
			ZVAL_STRING(&_7$$5, "incomplete-object");
			zephir_array_fast_append(&_6$$5, &_7$$5);
			ZEPHIR_CALL_METHOD(&_8$$5, this_ptr, "getclassnamefromincomplete", &_9, 0, &value);
			zephir_check_call_status();
			zephir_array_fast_append(&_6$$5, &_8$$5);
			zephir_array_update_zval(&result, &key, &_6$$5, PH_COPY | PH_SEPARATE);
		} else if (Z_TYPE_P(&value) == IS_OBJECT) {
			ZEPHIR_INIT_NVAR(&_10$$6);
			zephir_create_array(&_10$$6, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_11$$6);
			ZVAL_STRING(&_11$$6, "object");
			zephir_array_fast_append(&_10$$6, &_11$$6);
			ZEPHIR_INIT_NVAR(&_11$$6);
			zephir_get_class(&_11$$6, &value, 0 TSRMLS_CC);
			zephir_array_fast_append(&_10$$6, &_11$$6);
			zephir_array_update_zval(&result, &key, &_10$$6, PH_COPY | PH_SEPARATE);
		} else if (Z_TYPE_P(&value) == IS_ARRAY) {
			if (ZEPHIR_GT_LONG(level, 10)) {
				ZEPHIR_INIT_NVAR(&_12$$8);
				zephir_create_array(&_12$$8, 2, 0 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&_13$$8);
				ZVAL_STRING(&_13$$8, "array");
				zephir_array_fast_append(&_12$$8, &_13$$8);
				ZEPHIR_INIT_NVAR(&_13$$8);
				ZVAL_STRING(&_13$$8, "*DEEP NESTED ARRAY*");
				zephir_array_fast_append(&_12$$8, &_13$$8);
				zephir_array_update_zval(&result, &key, &_12$$8, PH_COPY | PH_SEPARATE);
			} else {
				ZEPHIR_INIT_NVAR(&_14$$9);
				zephir_create_array(&_14$$9, 2, 0 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&_15$$9);
				ZVAL_STRING(&_15$$9, "array");
				zephir_array_fast_append(&_14$$9, &_15$$9);
				ZVAL_LONG(&_17$$9, (zephir_get_numberval(level) + 1));
				ZVAL_LONG(&_18$$9, (zephir_get_numberval(count) + 1));
				ZEPHIR_CALL_METHOD(&_16$$9, this_ptr, "flattenargs", &_19, 68, &value, &_17$$9, &_18$$9);
				zephir_check_call_status();
				zephir_array_fast_append(&_14$$9, &_16$$9);
				zephir_array_update_zval(&result, &key, &_14$$9, PH_COPY | PH_SEPARATE);
			}
		} else if (Z_TYPE_P(&value) == IS_NULL) {
			ZEPHIR_INIT_NVAR(&_20$$10);
			zephir_create_array(&_20$$10, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_21$$10);
			ZVAL_STRING(&_21$$10, "null");
			zephir_array_fast_append(&_20$$10, &_21$$10);
			zephir_array_fast_append(&_20$$10, &__$null);
			zephir_array_update_zval(&result, &key, &_20$$10, PH_COPY | PH_SEPARATE);
		} else if ((Z_TYPE_P(&value) == IS_TRUE || Z_TYPE_P(&value) == IS_FALSE)) {
			ZEPHIR_INIT_NVAR(&_22$$11);
			zephir_create_array(&_22$$11, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_23$$11);
			ZVAL_STRING(&_23$$11, "boolean");
			zephir_array_fast_append(&_22$$11, &_23$$11);
			zephir_array_fast_append(&_22$$11, &value);
			zephir_array_update_zval(&result, &key, &_22$$11, PH_COPY | PH_SEPARATE);
		} else if (Z_TYPE_P(&value) == IS_LONG) {
			ZEPHIR_INIT_NVAR(&_24$$12);
			zephir_create_array(&_24$$12, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_25$$12);
			ZVAL_STRING(&_25$$12, "integer");
			zephir_array_fast_append(&_24$$12, &_25$$12);
			zephir_array_fast_append(&_24$$12, &value);
			zephir_array_update_zval(&result, &key, &_24$$12, PH_COPY | PH_SEPARATE);
		} else if (zephir_is_true(&_4$$3)) {
			ZEPHIR_INIT_NVAR(&_26$$13);
			zephir_create_array(&_26$$13, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_27$$13);
			ZVAL_STRING(&_27$$13, "float");
			zephir_array_fast_append(&_26$$13, &_27$$13);
			zephir_array_fast_append(&_26$$13, &value);
			zephir_array_update_zval(&result, &key, &_26$$13, PH_COPY | PH_SEPARATE);
		} else if (Z_TYPE_P(&value) == IS_RESOURCE) {
			ZEPHIR_INIT_NVAR(&_28$$14);
			zephir_create_array(&_28$$14, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_29$$14);
			ZVAL_STRING(&_29$$14, "resource");
			zephir_array_fast_append(&_28$$14, &_29$$14);
			ZEPHIR_CALL_FUNCTION(&_30$$14, "get_resource_type", &_31, 69, &value);
			zephir_check_call_status();
			zephir_array_fast_append(&_28$$14, &_30$$14);
			zephir_array_update_zval(&result, &key, &_28$$14, PH_COPY | PH_SEPARATE);
		} else {
			ZEPHIR_INIT_NVAR(&_32$$15);
			zephir_create_array(&_32$$15, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_33$$15);
			ZVAL_STRING(&_33$$15, "string");
			zephir_array_fast_append(&_32$$15, &_33$$15);
			zephir_get_strval(&_34$$15, &value);
			zephir_array_fast_append(&_32$$15, &_34$$15);
			zephir_array_update_zval(&result, &key, &_32$$15, PH_COPY | PH_SEPARATE);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	RETURN_CCTOR(&result);

}

PHP_METHOD(Zim_Debug_FlattenException, getClassNameFromIncomplete) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *value, value_sub, myArray, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&myArray);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value);



	ZEPHIR_INIT_VAR(&myArray);
	object_init_ex(&myArray, spl_ce_ArrayObject);
	ZEPHIR_CALL_METHOD(NULL, &myArray, "__construct", NULL, 70, value);
	zephir_check_call_status();
	zephir_array_fetch_string(&_0, &myArray, SL("__PHP_Incomplete_Class_Name"), PH_NOISY | PH_READONLY, "zim/debug/flattenexception.zep", 286 TSRMLS_CC);
	RETURN_CTOR(&_0);

}

