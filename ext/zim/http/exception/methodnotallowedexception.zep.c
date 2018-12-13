
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
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/operators.h"


/**
 * File MethodNotAllowedException.php
 * @henter
 * Time: 2018-11-27 20:27
 *
 */
/**
 * The resource was found but the request method is not allowed.
 *
 * This exception should trigger an HTTP 405 response in your application code.
 *
 * @author Kris Wallsmith <kris@symfony.com>
 */
ZEPHIR_INIT_CLASS(Zim_Http_Exception_MethodNotAllowedException) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Http\\Exception, MethodNotAllowedException, zim, http_exception_methodnotallowedexception, spl_ce_RuntimeException, zim_http_exception_methodnotallowedexception_method_entry, 0);

	zend_declare_property_null(zim_http_exception_methodnotallowedexception_ce, SL("allowedMethods"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_http_exception_methodnotallowedexception_ce->create_object = zephir_init_properties_Zim_Http_Exception_MethodNotAllowedException;
	return SUCCESS;

}

PHP_METHOD(Zim_Http_Exception_MethodNotAllowedException, __construct) {

	zend_long code, ZEPHIR_LAST_CALL_STATUS;
	zval *allowedMethods_param = NULL, *code_param = NULL, *previous = NULL, previous_sub, __$null, message, _0, _1, _2;
	zval allowedMethods;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&allowedMethods);
	ZVAL_UNDEF(&previous_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&message);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &allowedMethods_param, &code_param, &previous);

	zephir_get_arrval(&allowedMethods, allowedMethods_param);
	if (!code_param) {
		code = 0;
	} else {
		code = zephir_get_intval(code_param);
	}
	if (!previous) {
		previous = &previous_sub;
		previous = &__$null;
	}


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "strtoupper");
	ZEPHIR_CALL_FUNCTION(&_1, "array_map", NULL, 78, &_0, &allowedMethods);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("allowedMethods"), &_1);
	ZEPHIR_INIT_NVAR(&_0);
	zephir_fast_join_str(&_0, SL(","), &allowedMethods TSRMLS_CC);
	ZEPHIR_INIT_VAR(&message);
	ZEPHIR_CONCAT_SV(&message, "Allowed methods ", &_0);
	ZVAL_LONG(&_2, code);
	ZEPHIR_CALL_PARENT(NULL, zim_http_exception_methodnotallowedexception_ce, getThis(), "__construct", NULL, 0, &message, &_2, previous);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Gets the allowed HTTP methods.
 *
 * @return array
 */
PHP_METHOD(Zim_Http_Exception_MethodNotAllowedException, getAllowedMethods) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "allowedMethods");

}

zend_object *zephir_init_properties_Zim_Http_Exception_MethodNotAllowedException(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _1$$3;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("allowedMethods"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("allowedMethods"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

