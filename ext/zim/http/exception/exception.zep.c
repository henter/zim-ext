
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"


/**
 * File Exception.php
 * @henter
 * Time: 2018-11-26 14:32
 *
 */
/**
 * HttpException.
 *
 * @author Kris Wallsmith <kris@symfony.com>
 */
ZEPHIR_INIT_CLASS(Zim_Http_Exception_Exception) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Http\\Exception, Exception, zim, http_exception_exception, spl_ce_RuntimeException, zim_http_exception_exception_method_entry, 0);

	zend_declare_property_null(zim_http_exception_exception_ce, SL("statusCode"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(zim_http_exception_exception_ce, SL("headers"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(zim_http_exception_exception_ce TSRMLS_CC, 1, zim_http_exception_exceptioninterface_ce);
	return SUCCESS;

}

PHP_METHOD(Zim_Http_Exception_Exception, __construct) {

	zval headers;
	zval message;
	zval *statusCode_param = NULL, *message_param = NULL, *previous = NULL, previous_sub, *headers_param = NULL, *code_param = NULL, __$null, _0;
	zend_long statusCode, code, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&previous_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&headers);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 4, &statusCode_param, &message_param, &previous, &headers_param, &code_param);

	statusCode = zephir_get_intval(statusCode_param);
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
	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}
	if (!code_param) {
		code = 0;
	} else {
		code = zephir_get_intval(code_param);
	}


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, statusCode);
	zephir_update_property_zval(this_ptr, SL("statusCode"), &_0);
	zephir_update_property_zval(this_ptr, SL("headers"), &headers);
	ZVAL_LONG(&_0, code);
	ZEPHIR_CALL_PARENT(NULL, zim_http_exception_exception_ce, getThis(), "__construct", NULL, 0, &message, &_0, previous);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Zim_Http_Exception_Exception, getStatusCode) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "statusCode");

}

PHP_METHOD(Zim_Http_Exception_Exception, getHeaders) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "headers");

}

/**
 * Set response headers.
 *
 * @param array $headers Response headers
 */
PHP_METHOD(Zim_Http_Exception_Exception, setHeaders) {

	zval *headers_param = NULL;
	zval headers;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&headers);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &headers_param);

	zephir_get_arrval(&headers, headers_param);


	zephir_update_property_zval(this_ptr, SL("headers"), &headers);
	ZEPHIR_MM_RESTORE();

}

