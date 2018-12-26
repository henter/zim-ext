
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


/**
 * File RequestEvent.php
 * @henter
 * Time: 2018-11-25 23:15
 *
 */
ZEPHIR_INIT_CLASS(Zim_Event_ExceptionEvent) {

	ZEPHIR_REGISTER_CLASS(Zim\\Event, ExceptionEvent, zim, event_exceptionevent, zim_event_exceptionevent_method_entry, 0);

	/**
	 * @var \Throwable
	 */
	zend_declare_property_null(zim_event_exceptionevent_ce, SL("e"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var Request
	 */
	zend_declare_property_null(zim_event_exceptionevent_ce, SL("request"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var Response
	 */
	zend_declare_property_null(zim_event_exceptionevent_ce, SL("response"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Zim_Event_ExceptionEvent, __construct) {

	zval *e, e_sub, *request, request_sub, *response = NULL, response_sub, __$null;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&e_sub);
	ZVAL_UNDEF(&request_sub);
	ZVAL_UNDEF(&response_sub);
	ZVAL_NULL(&__$null);

	zephir_fetch_params(0, 2, 1, &e, &request, &response);

	if (!response) {
		response = &response_sub;
		response = &__$null;
	}


	zephir_update_property_zval(this_ptr, SL("e"), e);
	zephir_update_property_zval(this_ptr, SL("request"), request);
	zephir_update_property_zval(this_ptr, SL("response"), response);

}

/**
 * @return \Throwable
 */
PHP_METHOD(Zim_Event_ExceptionEvent, getThrowable) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "e");

}

/**
 * @return Response
 */
PHP_METHOD(Zim_Event_ExceptionEvent, getResponse) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "response");

}

/**
 * @param Response $response
 * @return $this
 */
PHP_METHOD(Zim_Event_ExceptionEvent, setResponse) {

	zval *response, response_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&response_sub);

	zephir_fetch_params(0, 1, 0, &response);



	zephir_update_property_zval(this_ptr, SL("response"), response);
	RETURN_THISW();

}

/**
 * @return Request
 */
PHP_METHOD(Zim_Event_ExceptionEvent, getRequest) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "request");

}

