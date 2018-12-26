
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"


/**
 * File NotFoundException.php
 * @henter
 * Time: 2018-11-25 23:30
 *
 */
ZEPHIR_INIT_CLASS(Zim_Http_Exception_NotFoundException) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Http\\Exception, NotFoundException, zim, http_exception_notfoundexception, zim_http_exception_exception_ce, zim_http_exception_notfoundexception_method_entry, 0);

	return SUCCESS;

}

/**
 * @param string     $message  The internal exception message
 * @param \Exception $previous The previous exception
 * @param int        $code     The internal exception code
 * @param array      $headers
 */
PHP_METHOD(Zim_Http_Exception_NotFoundException, __construct) {

	zephir_fcall_cache_entry *_0 = NULL;
	zval headers;
	zend_long code, ZEPHIR_LAST_CALL_STATUS;
	zval *message_param = NULL, *previous = NULL, previous_sub, *code_param = NULL, *headers_param = NULL, __$null, _1, _2;
	zval message;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&previous_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&headers);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 4, &message_param, &previous, &code_param, &headers_param);

	if (!message_param) {
		ZEPHIR_INIT_VAR(&message);
		ZVAL_STRING(&message, "");
	} else {
		zephir_get_strval(&message, message_param);
	}
	if (!previous) {
		previous = &previous_sub;
		previous = &__$null;
	}
	if (!code_param) {
		code = 0;
	} else {
		code = zephir_get_intval(code_param);
	}
	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}


	ZVAL_LONG(&_1, 404);
	ZVAL_LONG(&_2, code);
	ZEPHIR_CALL_PARENT(NULL, zim_http_exception_notfoundexception_ce, getThis(), "__construct", &_0, 0, &_1, &message, previous, &headers, &_2);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

