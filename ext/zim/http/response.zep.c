
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
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "ext/spl/spl_array.h"


/**
 * File Response.php
 * @henter
 * Time: 2018-11-24 19:53
 *
 */
/**
 * Response represents an HTTP response.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 */
ZEPHIR_INIT_CLASS(Zim_Http_Response) {

	ZEPHIR_REGISTER_CLASS(Zim\\Http, Response, zim, http_response, zim_http_response_method_entry, 0);

	/**
	 * @var ResponseHeaderBag
	 */
	zend_declare_property_null(zim_http_response_ce, SL("headers"), ZEND_ACC_PUBLIC TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(zim_http_response_ce, SL("content"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(zim_http_response_ce, SL("version"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var int
	 */
	zend_declare_property_null(zim_http_response_ce, SL("statusCode"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(zim_http_response_ce, SL("statusText"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var string
	 */
	zend_declare_property_null(zim_http_response_ce, SL("charset"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Status codes translation table.
	 *
	 * The list of codes is complete according to the
	 * {@link http://www.iana.org/assignments/http-status-codes/ Hypertext Transfer Protocol (HTTP) Status Code Registry}
	 * (last updated 2016-03-01).
	 *
	 * Unless otherwise noted, the status code is defined in RFC2616.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_http_response_ce, SL("statusTexts"), ZEND_ACC_PUBLIC|ZEND_ACC_STATIC TSRMLS_CC);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_CONTINUE"), 100);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_SWITCHING_PROTOCOLS"), 101);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_PROCESSING"), 102);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_EARLY_HINTS"), 103);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_OK"), 200);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_CREATED"), 201);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_ACCEPTED"), 202);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_NON_AUTHORITATIVE_INFORMATION"), 203);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_NO_CONTENT"), 204);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_RESET_CONTENT"), 205);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_PARTIAL_CONTENT"), 206);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_MULTI_STATUS"), 207);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_ALREADY_REPORTED"), 208);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_IM_USED"), 226);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_MULTIPLE_CHOICES"), 300);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_MOVED_PERMANENTLY"), 301);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_FOUND"), 302);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_SEE_OTHER"), 303);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_NOT_MODIFIED"), 304);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_USE_PROXY"), 305);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_RESERVED"), 306);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_TEMPORARY_REDIRECT"), 307);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_PERMANENTLY_REDIRECT"), 308);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_BAD_REQUEST"), 400);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_UNAUTHORIZED"), 401);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_PAYMENT_REQUIRED"), 402);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_FORBIDDEN"), 403);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_NOT_FOUND"), 404);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_METHOD_NOT_ALLOWED"), 405);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_NOT_ACCEPTABLE"), 406);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_PROXY_AUTHENTICATION_REQUIRED"), 407);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_REQUEST_TIMEOUT"), 408);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_CONFLICT"), 409);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_GONE"), 410);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_LENGTH_REQUIRED"), 411);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_PRECONDITION_FAILED"), 412);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_REQUEST_ENTITY_TOO_LARGE"), 413);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_REQUEST_URI_TOO_LONG"), 414);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_UNSUPPORTED_MEDIA_TYPE"), 415);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_REQUESTED_RANGE_NOT_SATISFIABLE"), 416);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_EXPECTATION_FAILED"), 417);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_I_AM_A_TEAPOT"), 418);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_MISDIRECTED_REQUEST"), 421);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_UNPROCESSABLE_ENTITY"), 422);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_LOCKED"), 423);

	zephir_declare_class_constant_long(zim_http_response_ce, SL("HTTP_FAILED_DEPENDENCY"), 424);

	zend_class_implements(zim_http_response_ce TSRMLS_CC, 1, zim_contract_response_ce);
	return SUCCESS;

}

/**
 * Response constructor.
 * @param string $content
 * @param int $status
 * @param array $headers
 */
PHP_METHOD(Zim_Http_Response, __construct) {

	zval headers;
	zend_long status, ZEPHIR_LAST_CALL_STATUS;
	zval *content = NULL, content_sub, *status_param = NULL, *headers_param = NULL, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&headers);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 3, &content, &status_param, &headers_param);

	if (!content) {
		content = &content_sub;
		ZEPHIR_INIT_VAR(content);
		ZVAL_STRING(content, "");
	}
	if (!status_param) {
		status = 200;
	} else {
		status = zephir_get_intval(status_param);
	}
	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	object_init_ex(&_0, zim_http_responseheaderbag_ce);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 19, &headers);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("headers"), &_0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcontent", NULL, 0, content);
	zephir_check_call_status();
	ZVAL_LONG(&_1, status);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setstatuscode", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "1.0");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setprotocolversion", NULL, 0, &_2);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Factory method for chainability.
 *
 * @param mixed $content The response content, see setContent()
 * @param int   $status  The response status code
 * @param array $headers An array of response headers
 *
 * @return static
 */
PHP_METHOD(Zim_Http_Response, create) {

	zval headers;
	zend_long status, ZEPHIR_LAST_CALL_STATUS;
	zval *content = NULL, content_sub, *status_param = NULL, *headers_param = NULL, __$null, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&headers);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 3, &content, &status_param, &headers_param);

	if (!content) {
		content = &content_sub;
		content = &__$null;
	}
	if (!status_param) {
		status = 200;
	} else {
		status = zephir_get_intval(status_param);
	}
	if (!headers_param) {
		ZEPHIR_INIT_VAR(&headers);
		array_init(&headers);
	} else {
		zephir_get_arrval(&headers, headers_param);
	}


	object_init_ex(return_value, zim_http_response_ce);
	ZVAL_LONG(&_0, status);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 20, content, &_0, &headers);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns the Response as an HTTP string.
 *
 * The string representation of the Response is the same as the
 * one that will be sent to the client only if the prepare() method
 * has been called before.
 *
 * @return string The Response as an HTTP string
 *
 * @see prepare()
 */
PHP_METHOD(Zim_Http_Response, __toString) {

	zval _0, _1, _2, _3, _4, _5, _6;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("version"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_1, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_2, this_ptr, SL("statusText"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "HTTP/%s %s %s");
	ZEPHIR_CALL_FUNCTION(&_4, "sprintf", NULL, 21, &_3, &_0, &_1, &_2);
	zephir_check_call_status();
	zephir_read_property(&_5, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_6, this_ptr, "getcontent", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VSVSV(return_value, &_4, "\n", &_5, "\n", &_6);
	RETURN_MM();

}

/**
 * Clones the current Response instance.
 */
PHP_METHOD(Zim_Http_Response, __clone) {

	zval _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	if (zephir_clone(&_1, &_0 TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	zephir_update_property_zval(this_ptr, SL("headers"), &_1);
	ZEPHIR_MM_RESTORE();

}

/**
 * Prepares the Response before it is sent to the client.
 *
 * This method tweaks the Response to ensure that it is
 * compliant with RFC 2616. Most of the changes are based on
 * the Request that is "associated" with this Response.
 *
 * @return $this
 */
PHP_METHOD(Zim_Http_Response, prepare) {

	zend_bool _2, _34, _16$$4, _9$$5;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *request, request_sub, headers, format, mimeType, charset, length, _0, _1, _3, _30, _31, _33, _35, _36, _37, _4$$3, _6$$3, _7$$4, _8$$4, _11$$4, _12$$4, _13$$4, _14$$4, _15$$4, _17$$4, _18$$4, _24$$4, _26$$4, _10$$6, _19$$7, _20$$7, _21$$8, _22$$8, _23$$8, _25$$9, _27$$10, _28$$10, _29$$11, _32$$12, _38$$13, _39$$13, _40$$13, _41$$13, _42$$13;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&request_sub);
	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&format);
	ZVAL_UNDEF(&mimeType);
	ZVAL_UNDEF(&charset);
	ZVAL_UNDEF(&length);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_36);
	ZVAL_UNDEF(&_37);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_17$$4);
	ZVAL_UNDEF(&_18$$4);
	ZVAL_UNDEF(&_24$$4);
	ZVAL_UNDEF(&_26$$4);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$8);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_27$$10);
	ZVAL_UNDEF(&_28$$10);
	ZVAL_UNDEF(&_29$$11);
	ZVAL_UNDEF(&_32$$12);
	ZVAL_UNDEF(&_38$$13);
	ZVAL_UNDEF(&_39$$13);
	ZVAL_UNDEF(&_40$$13);
	ZVAL_UNDEF(&_41$$13);
	ZVAL_UNDEF(&_42$$13);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	zephir_read_property(&_0, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&headers, &_0);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "isinformational", NULL, 0);
	zephir_check_call_status();
	_2 = zephir_is_true(&_1);
	if (!(_2)) {
		ZEPHIR_CALL_METHOD(&_3, this_ptr, "isempty", NULL, 0);
		zephir_check_call_status();
		_2 = zephir_is_true(&_3);
	}
	if (_2) {
		ZVAL_NULL(&_4$$3);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcontent", &_5, 0, &_4$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_6$$3);
		ZVAL_STRING(&_6$$3, "Content-Type");
		ZEPHIR_CALL_METHOD(NULL, &headers, "remove", NULL, 0, &_6$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_6$$3);
		ZVAL_STRING(&_6$$3, "Content-Length");
		ZEPHIR_CALL_METHOD(NULL, &headers, "remove", NULL, 0, &_6$$3);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_VAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "Content-Type");
		ZEPHIR_CALL_METHOD(&_7$$4, &headers, "has", NULL, 0, &_8$$4);
		zephir_check_call_status();
		if (!(zephir_is_true(&_7$$4))) {
			ZEPHIR_CALL_METHOD(&format, request, "getrequestformat", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&mimeType, request, "getmimetype", NULL, 0, &format);
			zephir_check_call_status();
			_9$$5 = Z_TYPE_P(&format) != IS_NULL;
			if (_9$$5) {
				_9$$5 = zephir_is_true(&mimeType);
			}
			if (_9$$5) {
				ZEPHIR_INIT_VAR(&_10$$6);
				ZVAL_STRING(&_10$$6, "Content-Type");
				ZEPHIR_CALL_METHOD(NULL, &headers, "set", NULL, 0, &_10$$6, &mimeType);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_VAR(&_11$$4);
		zephir_read_property(&_12$$4, this_ptr, SL("charset"), PH_NOISY_CC | PH_READONLY);
		if (zephir_is_true(&_12$$4)) {
			ZEPHIR_OBS_NVAR(&_11$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("charset"), PH_NOISY_CC);
		} else {
			ZEPHIR_INIT_NVAR(&_11$$4);
			ZVAL_STRING(&_11$$4, "UTF-8");
		}
		ZEPHIR_CPY_WRT(&charset, &_11$$4);
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "Content-Type");
		ZEPHIR_CALL_METHOD(&_13$$4, &headers, "has", NULL, 0, &_8$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "Content-Type");
		ZEPHIR_CALL_METHOD(&_14$$4, &headers, "get", NULL, 0, &_8$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "text/");
		ZEPHIR_CALL_FUNCTION(&_15$$4, "stripos", NULL, 22, &_14$$4, &_8$$4);
		zephir_check_call_status();
		_16$$4 = ZEPHIR_IS_LONG_IDENTICAL(&_15$$4, 0);
		if (_16$$4) {
			ZEPHIR_INIT_NVAR(&_8$$4);
			ZVAL_STRING(&_8$$4, "Content-Type");
			ZEPHIR_CALL_METHOD(&_17$$4, &headers, "get", NULL, 0, &_8$$4);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_8$$4);
			ZVAL_STRING(&_8$$4, "charset");
			ZEPHIR_CALL_FUNCTION(&_18$$4, "stripos", NULL, 22, &_17$$4, &_8$$4);
			zephir_check_call_status();
			_16$$4 = ZEPHIR_IS_FALSE_IDENTICAL(&_18$$4);
		}
		if (!(zephir_is_true(&_13$$4))) {
			ZEPHIR_INIT_VAR(&_19$$7);
			ZEPHIR_CONCAT_SV(&_19$$7, "text/html; charset=", &charset);
			ZEPHIR_INIT_VAR(&_20$$7);
			ZVAL_STRING(&_20$$7, "Content-Type");
			ZEPHIR_CALL_METHOD(NULL, &headers, "set", NULL, 0, &_20$$7, &_19$$7);
			zephir_check_call_status();
		} else if (_16$$4) {
			ZEPHIR_INIT_VAR(&_22$$8);
			ZVAL_STRING(&_22$$8, "Content-Type");
			ZEPHIR_CALL_METHOD(&_21$$8, &headers, "get", NULL, 0, &_22$$8);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(&_23$$8);
			ZEPHIR_CONCAT_VSV(&_23$$8, &_21$$8, "; charset=", &charset);
			ZEPHIR_INIT_NVAR(&_22$$8);
			ZVAL_STRING(&_22$$8, "Content-Type");
			ZEPHIR_CALL_METHOD(NULL, &headers, "set", NULL, 0, &_22$$8, &_23$$8);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "Transfer-Encoding");
		ZEPHIR_CALL_METHOD(&_24$$4, &headers, "has", NULL, 0, &_8$$4);
		zephir_check_call_status();
		if (zephir_is_true(&_24$$4)) {
			ZEPHIR_INIT_VAR(&_25$$9);
			ZVAL_STRING(&_25$$9, "Content-Length");
			ZEPHIR_CALL_METHOD(NULL, &headers, "remove", NULL, 0, &_25$$9);
			zephir_check_call_status();
		}
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "HEAD");
		ZEPHIR_CALL_METHOD(&_26$$4, request, "ismethod", NULL, 0, &_8$$4);
		zephir_check_call_status();
		if (zephir_is_true(&_26$$4)) {
			ZEPHIR_INIT_VAR(&_27$$10);
			ZVAL_STRING(&_27$$10, "Content-Length");
			ZEPHIR_CALL_METHOD(&length, &headers, "get", NULL, 0, &_27$$10);
			zephir_check_call_status();
			ZVAL_NULL(&_28$$10);
			ZEPHIR_CALL_METHOD(NULL, this_ptr, "setcontent", &_5, 0, &_28$$10);
			zephir_check_call_status();
			if (zephir_is_true(&length)) {
				ZEPHIR_INIT_VAR(&_29$$11);
				ZVAL_STRING(&_29$$11, "Content-Length");
				ZEPHIR_CALL_METHOD(NULL, &headers, "set", NULL, 0, &_29$$11, &length);
				zephir_check_call_status();
			}
		}
	}
	zephir_read_property(&_0, request, SL("server"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_31);
	ZVAL_STRING(&_31, "SERVER_PROTOCOL");
	ZEPHIR_CALL_METHOD(&_30, &_0, "get", NULL, 0, &_31);
	zephir_check_call_status();
	if (!ZEPHIR_IS_STRING(&_30, "HTTP/1.0")) {
		ZEPHIR_INIT_VAR(&_32$$12);
		ZVAL_STRING(&_32$$12, "1.1");
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setprotocolversion", NULL, 0, &_32$$12);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_33, this_ptr, "getprotocolversion", NULL, 0);
	zephir_check_call_status();
	_34 = ZEPHIR_IS_STRING(&_33, "1.0");
	if (_34) {
		zephir_read_property(&_35, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_31);
		ZVAL_STRING(&_31, "Cache-Control");
		ZEPHIR_CALL_METHOD(&_36, &_35, "get", NULL, 0, &_31);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_31);
		ZVAL_STRING(&_31, "no-cache");
		ZEPHIR_INIT_VAR(&_37);
		zephir_fast_strpos(&_37, &_36, &_31, 0 );
		_34 = !ZEPHIR_IS_FALSE_IDENTICAL(&_37);
	}
	if (_34) {
		zephir_read_property(&_38$$13, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_39$$13);
		ZVAL_STRING(&_39$$13, "pragma");
		ZEPHIR_INIT_VAR(&_40$$13);
		ZVAL_STRING(&_40$$13, "no-cache");
		ZEPHIR_CALL_METHOD(NULL, &_38$$13, "set", NULL, 0, &_39$$13, &_40$$13);
		zephir_check_call_status();
		zephir_read_property(&_41$$13, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_39$$13);
		ZVAL_STRING(&_39$$13, "expires");
		ZVAL_LONG(&_42$$13, -1);
		ZEPHIR_CALL_METHOD(NULL, &_41$$13, "set", NULL, 0, &_39$$13, &_42$$13);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

/**
 * Sends HTTP headers.
 *
 * @return $this
 */
PHP_METHOD(Zim_Http_Response, sendHeaders) {

	zend_string *_5;
	zend_ulong _4;
	zephir_fcall_cache_entry *_9 = NULL;
	zval __$false, __$true, name, values, value, _0, _1, _2, *_3, _10, _11, _12, _13, _14, _15, *_6$$4, _7$$5, _8$$5;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$false, 0);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&values);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_FUNCTION(&_0, "headers_sent", NULL, 23);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		RETURN_THIS();
	}
	zephir_read_property(&_1, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_2, &_1, "allpreservecase", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_2, 0, "zim/http/response.zep", 246);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_2), _4, _5, _3)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_5 != NULL) { 
			ZVAL_STR_COPY(&name, _5);
		} else {
			ZVAL_LONG(&name, _4);
		}
		ZEPHIR_INIT_NVAR(&values);
		ZVAL_COPY(&values, _3);
		zephir_is_iterable(&values, 0, "zim/http/response.zep", 244);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&values), _6$$4)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6$$4);
			ZEPHIR_INIT_LNVAR(_7$$5);
			ZEPHIR_CONCAT_VSV(&_7$$5, &name, ": ", &value);
			zephir_read_property(&_8$$5, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_CALL_FUNCTION(NULL, "header", &_9, 24, &_7$$5, &__$false, &_8$$5);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&value);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&values);
	ZEPHIR_INIT_NVAR(&name);
	zephir_read_property(&_10, this_ptr, SL("version"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_11, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_12, this_ptr, SL("statusText"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_13);
	ZVAL_STRING(&_13, "HTTP/%s %s %s");
	ZEPHIR_CALL_FUNCTION(&_14, "sprintf", NULL, 21, &_13, &_10, &_11, &_12);
	zephir_check_call_status();
	zephir_read_property(&_15, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(NULL, "header", &_9, 24, &_14, &__$true, &_15);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Sends content for the current web response.
 *
 * @return $this
 */
PHP_METHOD(Zim_Http_Response, sendContent) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("content"), PH_NOISY_CC | PH_READONLY);
	zend_print_zval(&_0, 0);
	RETURN_THISW();

}

/**
 * Sends HTTP headers and content.
 *
 * @return $this
 */
PHP_METHOD(Zim_Http_Response, send) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();


	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(NULL, this_ptr, "sendheaders", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "sendcontent", NULL, 0);
	zephir_check_call_status();
	if ((zephir_function_exists_ex(SL("fastcgi_finish_request") TSRMLS_CC) == SUCCESS)) {
		ZEPHIR_CALL_FUNCTION(NULL, "fastcgi_finish_request", NULL, 25);
		zephir_check_call_status();
	}
	RETURN_THIS();

}

/**
 * Sets the response content.
 *
 * Valid types are strings, numbers, null, and objects that implement a __toString() method.
 *
 * @param mixed $content Content that can be cast to string
 *
 * @return $this
 *
 * @throws \UnexpectedValueException
 */
PHP_METHOD(Zim_Http_Response, setContent) {

	zval _14;
	zval _8;
	zend_bool _5, _6, _7;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *content = NULL, content_sub, _0, _9, _1$$3, _2$$3, _3$$3, _4$$3, _10$$4, _11$$4, _12$$4, _13$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_14);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &content);

	ZEPHIR_SEPARATE_PARAM(content);


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "shouldbejson", NULL, 0, content);
	zephir_check_call_status();
	if (zephir_is_true(&_0)) {
		zephir_read_property(&_1$$3, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "Content-Type");
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "application/json");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "set", NULL, 0, &_2$$3, &_3$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, this_ptr, "morphtojson", NULL, 0, content);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(content, &_4$$3);
	}
	_5 = Z_TYPE_P(content) != IS_NULL;
	if (_5) {
		_5 = !((Z_TYPE_P(content) == IS_STRING));
	}
	_6 = _5;
	if (_6) {
		_6 = !(zephir_is_numeric(content));
	}
	_7 = _6;
	if (_7) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_create_array(&_8, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&_8, content);
		ZEPHIR_INIT_VAR(&_9);
		ZVAL_STRING(&_9, "__toString");
		zephir_array_fast_append(&_8, &_9);
		_7 = !(zephir_is_callable(&_8 TSRMLS_CC));
	}
	if (_7) {
		ZEPHIR_INIT_VAR(&_10$$4);
		object_init_ex(&_10$$4, spl_ce_UnexpectedValueException);
		ZEPHIR_INIT_VAR(&_11$$4);
		zephir_gettype(&_11$$4, content TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_12$$4);
		ZVAL_STRING(&_12$$4, "The Response content must be a string or object implementing __toString(), \"%s\" given.");
		ZEPHIR_CALL_FUNCTION(&_13$$4, "sprintf", NULL, 21, &_12$$4, &_11$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_10$$4, "__construct", NULL, 26, &_13$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_10$$4, "zim/http/response.zep", 298 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_get_strval(&_14, content);
	zephir_update_property_zval(this_ptr, SL("content"), &_14);
	RETURN_THIS();

}

/**
 * Determine if the given content should be turned into JSON.
 *
 * @param  mixed  $content
 * @return bool
 */
PHP_METHOD(Zim_Http_Response, shouldBeJson) {

	zend_bool _0, _1, _2, _3, _4;
	zval *content, content_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_sub);

	zephir_fetch_params(0, 1, 0, &content);



	_0 = Z_TYPE_P(content) == IS_ARRAY;
	if (!(_0)) {
		_1 = Z_TYPE_P(content) == IS_OBJECT;
		if (_1) {
			_2 = zephir_instance_of_ev(content, zim_contract_arrayable_ce TSRMLS_CC);
			if (!(_2)) {
				_2 = zephir_instance_of_ev(content, zim_contract_jsonable_ce TSRMLS_CC);
			}
			_3 = _2;
			if (!(_3)) {
				_3 = zephir_instance_of_ev(content, spl_ce_ArrayObject TSRMLS_CC);
			}
			_4 = _3;
			if (!(_4)) {
				_4 = zephir_is_instance_of(content, SL("JsonSerializable") TSRMLS_CC);
			}
			_1 = _4;
		}
		_0 = _1;
	}
	RETURN_BOOL(_0);

}

/**
 * Morph the given content into JSON.
 *
 * @param  mixed   $content
 * @return string
 */
PHP_METHOD(Zim_Http_Response, morphToJson) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *content, content_sub, _0$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_sub);
	ZVAL_UNDEF(&_0$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &content);



	if (Z_TYPE_P(content) == IS_OBJECT) {
		if (zephir_instance_of_ev(content, zim_contract_jsonable_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(content, "tojson", NULL, 0);
			zephir_check_call_status();
			RETURN_MM();
		} else if (zephir_instance_of_ev(content, zim_contract_arrayable_ce TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(&_0$$5, content, "toarray", NULL, 0);
			zephir_check_call_status();
			zephir_json_encode(return_value, &_0$$5, 0 );
			RETURN_MM();
		}
	}
	zephir_json_encode(return_value, content, 0 );
	RETURN_MM();

}

/**
 * Gets the current response content.
 *
 * @return string Content
 */
PHP_METHOD(Zim_Http_Response, getContent) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "content");

}

/**
 * Sets the HTTP protocol version (1.0 or 1.1).
 *
 * @return $this
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, setProtocolVersion) {

	zval *version_param = NULL;
	zval version;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&version);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &version_param);

	zephir_get_strval(&version, version_param);


	zephir_update_property_zval(this_ptr, SL("version"), &version);
	RETURN_THIS();

}

/**
 * Gets the HTTP protocol version.
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, getProtocolVersion) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "version");

}

/**
 * Sets the response status code.
 *
 * If the status text is null it will be automatically populated for the known
 * status codes and left empty otherwise.
 *
 * @return $this
 *
 * @throws \InvalidArgumentException When the HTTP status code is not valid
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, setStatusCode) {

	zval *code_param = NULL, *text = NULL, text_sub, __$null, _0, _1, _2$$3, _3$$3, _4$$3, _5$$3, _6$$4, _7$$4, _8$$4, _9$$5;
	zend_long code, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&text_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &code_param, &text);

	code = zephir_get_intval(code_param);
	if (!text) {
		text = &text_sub;
		text = &__$null;
	}


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, code);
	zephir_update_property_zval(this_ptr, SL("statusCode"), &_0);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "isinvalid", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "The HTTP status code \"%s\" is not valid.");
		ZVAL_LONG(&_4$$3, code);
		ZEPHIR_CALL_FUNCTION(&_5$$3, "sprintf", NULL, 21, &_3$$3, &_4$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 27, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "zim/http/response.zep", 390 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (Z_TYPE_P(text) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_6$$4);
		zephir_read_static_property_ce(&_7$$4, zim_http_response_ce, SL("statusTexts"), PH_NOISY_CC | PH_READONLY);
		if (zephir_array_isset_long(&_7$$4, code)) {
			zephir_read_static_property_ce(&_8$$4, zim_http_response_ce, SL("statusTexts"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_6$$4);
			zephir_array_fetch_long(&_6$$4, &_8$$4, code, PH_NOISY, "zim/http/response.zep", 393 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(&_6$$4);
			ZVAL_STRING(&_6$$4, "unknown status");
		}
		zephir_update_property_zval(this_ptr, SL("statusText"), &_6$$4);
		RETURN_THIS();
	}
	if (ZEPHIR_IS_FALSE_IDENTICAL(text)) {
		ZEPHIR_INIT_VAR(&_9$$5);
		ZEPHIR_INIT_NVAR(&_9$$5);
		ZVAL_STRING(&_9$$5, "");
		zephir_update_property_zval(this_ptr, SL("statusText"), &_9$$5);
		RETURN_THIS();
	}
	zephir_update_property_zval(this_ptr, SL("statusText"), text);
	RETURN_THIS();

}

/**
 * Retrieves the status code for the current web response.
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, getStatusCode) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "statusCode");

}

/**
 * Sets the response charset.
 *
 * @return $this
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, setCharset) {

	zval *charset_param = NULL;
	zval charset;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&charset);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &charset_param);

	zephir_get_strval(&charset, charset_param);


	zephir_update_property_zval(this_ptr, SL("charset"), &charset);
	RETURN_THIS();

}

/**
 * Retrieves the response charset.
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, getCharset) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "charset");

}

/**
 * Is response invalid?
 *
 * @see http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isInvalid) {

	zend_bool _1;
	zval _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);


	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_LT_LONG(&_0, 100);
	if (!(_1)) {
		zephir_read_property(&_2, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
		_1 = ZEPHIR_GE_LONG(&_2, 600);
	}
	RETURN_BOOL(_1);

}

/**
 * Is response informative?
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isInformational) {

	zend_bool _1;
	zval _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);


	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GE_LONG(&_0, 100);
	if (_1) {
		zephir_read_property(&_2, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
		_1 = ZEPHIR_LT_LONG(&_2, 200);
	}
	RETURN_BOOL(_1);

}

/**
 * Is response successful?
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isSuccessful) {

	zend_bool _1;
	zval _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);


	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GE_LONG(&_0, 200);
	if (_1) {
		zephir_read_property(&_2, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
		_1 = ZEPHIR_LT_LONG(&_2, 300);
	}
	RETURN_BOOL(_1);

}

/**
 * Is the response a redirect?
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isRedirection) {

	zend_bool _1;
	zval _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);


	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GE_LONG(&_0, 300);
	if (_1) {
		zephir_read_property(&_2, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
		_1 = ZEPHIR_LT_LONG(&_2, 400);
	}
	RETURN_BOOL(_1);

}

/**
 * Is there a client error?
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isClientError) {

	zend_bool _1;
	zval _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);


	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GE_LONG(&_0, 400);
	if (_1) {
		zephir_read_property(&_2, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
		_1 = ZEPHIR_LT_LONG(&_2, 500);
	}
	RETURN_BOOL(_1);

}

/**
 * Was there a server side error?
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isServerError) {

	zend_bool _1;
	zval _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);


	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GE_LONG(&_0, 500);
	if (_1) {
		zephir_read_property(&_2, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
		_1 = ZEPHIR_LT_LONG(&_2, 600);
	}
	RETURN_BOOL(_1);

}

/**
 * Is the response OK?
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isOk) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(ZEPHIR_IS_LONG_IDENTICAL(&_0, 200));

}

/**
 * Is the response forbidden?
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isForbidden) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(ZEPHIR_IS_LONG_IDENTICAL(&_0, 403));

}

/**
 * Is the response a not found error?
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isNotFound) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(ZEPHIR_IS_LONG_IDENTICAL(&_0, 404));

}

/**
 * Is the response a redirect of some form?
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isRedirect) {

	zend_bool _3;
	zval _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *location_param = NULL, _0, _2, _4, _5, _6;
	zval location;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&location);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &location_param);

	if (!location_param) {
		ZEPHIR_INIT_VAR(&location);
		ZVAL_STRING(&location, "");
	} else {
		zephir_get_strval(&location, location_param);
	}


	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 6, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_LONG(&_2, 201);
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_LONG(&_2, 301);
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_LONG(&_2, 302);
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_LONG(&_2, 303);
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_LONG(&_2, 307);
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_LONG(&_2, 308);
	zephir_array_fast_append(&_1, &_2);
	_3 = zephir_fast_in_array(&_0, &_1 TSRMLS_CC);
	if (_3) {
		ZEPHIR_INIT_VAR(&_4);
		if (ZEPHIR_IS_STRING_IDENTICAL(&location, "")) {
			ZEPHIR_INIT_NVAR(&_4);
			ZVAL_BOOL(&_4, ZEPHIR_IS_STRING_IDENTICAL(&location, ""));
		} else {
			zephir_read_property(&_5, this_ptr, SL("headers"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_INIT_NVAR(&_2);
			ZVAL_STRING(&_2, "Location");
			ZEPHIR_CALL_METHOD(&_6, &_5, "get", NULL, 0, &_2);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_4);
			ZVAL_BOOL(&_4, ZEPHIR_IS_EQUAL(&location, &_6));
		}
		_3 = zephir_is_true(&_4);
	}
	RETURN_MM_BOOL(_3);

}

/**
 * Is the response empty?
 *
 * @final
 */
PHP_METHOD(Zim_Http_Response, isEmpty) {

	zval _1;
	zval _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("statusCode"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 2, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_LONG(&_2, 204);
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_LONG(&_2, 304);
	zephir_array_fast_append(&_1, &_2);
	RETURN_MM_BOOL(zephir_fast_in_array(&_0, &_1 TSRMLS_CC));

}

void zephir_init_static_properties_Zim_Http_Response(TSRMLS_D) {

	zval _0;
		ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 67, 0 TSRMLS_CC);
	add_index_stringl(&_0, 100, SL("Continue"));
	add_index_stringl(&_0, 101, SL("Switching Protocols"));
	add_index_stringl(&_0, 102, SL("Processing"));
	add_index_stringl(&_0, 103, SL("Early Hints"));
	add_index_stringl(&_0, 200, SL("OK"));
	add_index_stringl(&_0, 201, SL("Created"));
	add_index_stringl(&_0, 202, SL("Accepted"));
	add_index_stringl(&_0, 203, SL("Non-Authoritative Information"));
	add_index_stringl(&_0, 204, SL("No Content"));
	add_index_stringl(&_0, 205, SL("Reset Content"));
	add_index_stringl(&_0, 206, SL("Partial Content"));
	add_index_stringl(&_0, 207, SL("Multi-Status"));
	add_index_stringl(&_0, 208, SL("Already Reported"));
	add_index_stringl(&_0, 226, SL("IM Used"));
	add_index_stringl(&_0, 300, SL("Multiple Choices"));
	add_index_stringl(&_0, 301, SL("Moved Permanently"));
	add_index_stringl(&_0, 302, SL("Found"));
	add_index_stringl(&_0, 303, SL("See Other"));
	add_index_stringl(&_0, 304, SL("Not Modified"));
	add_index_stringl(&_0, 305, SL("Use Proxy"));
	add_index_stringl(&_0, 307, SL("Temporary Redirect"));
	add_index_stringl(&_0, 308, SL("Permanent Redirect"));
	add_index_stringl(&_0, 400, SL("Bad Request"));
	add_index_stringl(&_0, 401, SL("Unauthorized"));
	add_index_stringl(&_0, 402, SL("Payment Required"));
	add_index_stringl(&_0, 403, SL("Forbidden"));
	add_index_stringl(&_0, 404, SL("Not Found"));
	add_index_stringl(&_0, 405, SL("Method Not Allowed"));
	add_index_stringl(&_0, 406, SL("Not Acceptable"));
	add_index_stringl(&_0, 407, SL("Proxy Authentication Required"));
	add_index_stringl(&_0, 408, SL("Request Timeout"));
	add_index_stringl(&_0, 409, SL("Conflict"));
	add_index_stringl(&_0, 410, SL("Gone"));
	add_index_stringl(&_0, 411, SL("Length Required"));
	add_index_stringl(&_0, 412, SL("Precondition Failed"));
	add_index_stringl(&_0, 413, SL("Payload Too Large"));
	add_index_stringl(&_0, 414, SL("URI Too Long"));
	add_index_stringl(&_0, 415, SL("Unsupported Media Type"));
	add_index_stringl(&_0, 416, SL("Range Not Satisfiable"));
	add_index_stringl(&_0, 417, SL("Expectation Failed"));
	add_index_stringl(&_0, 418, SL("I'm a teapot"));
	add_index_stringl(&_0, 421, SL("Misdirected Request"));
	add_index_stringl(&_0, 422, SL("Unprocessable Entity"));
	add_index_stringl(&_0, 423, SL("Locked"));
	add_index_stringl(&_0, 424, SL("Failed Dependency"));
	add_index_stringl(&_0, 425, SL("Too Early"));
	add_index_stringl(&_0, 426, SL("Upgrade Required"));
	add_index_stringl(&_0, 428, SL("Precondition Required"));
	add_index_stringl(&_0, 429, SL("Too Many Requests"));
	add_index_stringl(&_0, 431, SL("Request Header Fields Too Large"));
	add_index_stringl(&_0, 451, SL("Unavailable For Legal Reasons"));
	add_index_stringl(&_0, 500, SL("Internal Server Error"));
	add_index_stringl(&_0, 501, SL("Not Implemented"));
	add_index_stringl(&_0, 502, SL("Bad Gateway"));
	add_index_stringl(&_0, 503, SL("Service Unavailable"));
	add_index_stringl(&_0, 504, SL("Gateway Timeout"));
	add_index_stringl(&_0, 505, SL("HTTP Version Not Supported"));
	add_index_stringl(&_0, 506, SL("Variant Also Negotiates"));
	add_index_stringl(&_0, 507, SL("Insufficient Storage"));
	add_index_stringl(&_0, 508, SL("Loop Detected"));
	add_index_stringl(&_0, 510, SL("Not Extended"));
	add_index_stringl(&_0, 511, SL("Network Authentication Required"));
	zend_update_static_property(zim_http_response_ce, ZEND_STRL("statusTexts"), &_0);
	ZEPHIR_MM_RESTORE();

}

