
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
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/string.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/concat.h"


/**
 * ServerBag is a container for HTTP headers from the $_SERVER variable.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 * @author Bulat Shakirzyanov <mallluhuct@gmail.com>
 * @author Robert Kiss <kepten@gmail.com>
 */
ZEPHIR_INIT_CLASS(Zim_Http_ServerBag) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Http, ServerBag, zim, http_serverbag, zim_http_parameterbag_ce, zim_http_serverbag_method_entry, 0);

	return SUCCESS;

}

/**
 * Gets the HTTP headers.
 *
 * @return array
 */
PHP_METHOD(Zim_Http_ServerBag, getHeaders) {

	zend_bool _22$$10;
	zend_string *_3;
	zend_ulong _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval __$true, headers, contentHeaders, key, value, authorizationHeader, exploded, tmpListHeadersPHP_AUTH_USERHeadersPHP_AUTH_PW, _0, *_1, _8, _4$$3, _5$$3, _6$$4, _7$$4, _9$$6, _10$$6, _11$$6, _12$$6, _13$$6, _14$$7, _15$$7, _16$$8, _17$$9, _18$$10, _19$$10, _20$$10, _21$$10, _23$$10, _24$$10, _25$$11, _26$$11, _27$$11, _28$$12, _29$$12, _30$$13, _31$$16, _32$$16, _33$$16, _34$$16, _35$$16, _36$$17;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&headers);
	ZVAL_UNDEF(&contentHeaders);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&authorizationHeader);
	ZVAL_UNDEF(&exploded);
	ZVAL_UNDEF(&tmpListHeadersPHP_AUTH_USERHeadersPHP_AUTH_PW);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_19$$10);
	ZVAL_UNDEF(&_20$$10);
	ZVAL_UNDEF(&_21$$10);
	ZVAL_UNDEF(&_23$$10);
	ZVAL_UNDEF(&_24$$10);
	ZVAL_UNDEF(&_25$$11);
	ZVAL_UNDEF(&_26$$11);
	ZVAL_UNDEF(&_27$$11);
	ZVAL_UNDEF(&_28$$12);
	ZVAL_UNDEF(&_29$$12);
	ZVAL_UNDEF(&_30$$13);
	ZVAL_UNDEF(&_31$$16);
	ZVAL_UNDEF(&_32$$16);
	ZVAL_UNDEF(&_33$$16);
	ZVAL_UNDEF(&_34$$16);
	ZVAL_UNDEF(&_35$$16);
	ZVAL_UNDEF(&_36$$17);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&headers);
	array_init(&headers);
	ZEPHIR_INIT_VAR(&contentHeaders);
	zephir_create_array(&contentHeaders, 3, 0 TSRMLS_CC);
	zephir_array_update_string(&contentHeaders, SL("CONTENT_LENGTH"), &__$true, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&contentHeaders, SL("CONTENT_MD5"), &__$true, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&contentHeaders, SL("CONTENT_TYPE"), &__$true, PH_COPY | PH_SEPARATE);
	zephir_read_property(&_0, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "zim/http/serverbag.zep", 41);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_0), _2, _3, _1)
	{
		ZEPHIR_INIT_NVAR(&key);
		if (_3 != NULL) { 
			ZVAL_STR_COPY(&key, _3);
		} else {
			ZVAL_LONG(&key, _2);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _1);
		ZEPHIR_INIT_NVAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "HTTP_");
		ZEPHIR_INIT_NVAR(&_5$$3);
		zephir_fast_strpos(&_5$$3, &key, &_4$$3, 0 );
		if (ZEPHIR_IS_LONG_IDENTICAL(&_5$$3, 0)) {
			ZVAL_LONG(&_6$$4, 5);
			ZEPHIR_INIT_NVAR(&_7$$4);
			zephir_substr(&_7$$4, &key, 5 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
			ZEPHIR_CPY_WRT(&key, &_7$$4);
			zephir_array_update_zval(&headers, &key, &value, PH_COPY | PH_SEPARATE);
		} else if (zephir_array_isset(&contentHeaders, &key)) {
			zephir_array_update_zval(&headers, &key, &value, PH_COPY | PH_SEPARATE);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&key);
	zephir_read_property(&_8, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_string(&_8, SL("PHP_AUTH_USER"))) {
		zephir_read_property(&_9$$6, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch_string(&_10$$6, &_9$$6, SL("PHP_AUTH_USER"), PH_NOISY | PH_READONLY, "zim/http/serverbag.zep", 42 TSRMLS_CC);
		zephir_array_update_string(&headers, SL("PHP_AUTH_USER"), &_10$$6, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(&_11$$6);
		zephir_read_property(&_12$$6, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
		if (zephir_array_isset_string(&_12$$6, SL("PHP_AUTH_PW"))) {
			zephir_read_property(&_13$$6, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_11$$6);
			zephir_array_fetch_string(&_11$$6, &_13$$6, SL("PHP_AUTH_PW"), PH_NOISY, "zim/http/serverbag.zep", 43 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(&_11$$6);
			ZVAL_STRING(&_11$$6, "");
		}
		zephir_array_update_string(&headers, SL("PHP_AUTH_PW"), &_11$$6, PH_COPY | PH_SEPARATE);
	} else {
		ZEPHIR_INIT_VAR(&authorizationHeader);
		ZVAL_NULL(&authorizationHeader);
		zephir_read_property(&_14$$7, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
		zephir_read_property(&_15$$7, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
		if (zephir_array_isset_string(&_14$$7, SL("HTTP_AUTHORIZATION"))) {
			zephir_read_property(&_16$$8, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&authorizationHeader);
			zephir_array_fetch_string(&authorizationHeader, &_16$$8, SL("HTTP_AUTHORIZATION"), PH_NOISY, "zim/http/serverbag.zep", 60 TSRMLS_CC);
		} else if (zephir_array_isset_string(&_15$$7, SL("REDIRECT_HTTP_AUTHORIZATION"))) {
			zephir_read_property(&_17$$9, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&authorizationHeader);
			zephir_array_fetch_string(&authorizationHeader, &_17$$9, SL("REDIRECT_HTTP_AUTHORIZATION"), PH_NOISY, "zim/http/serverbag.zep", 62 TSRMLS_CC);
		}
		if (Z_TYPE_P(&authorizationHeader) != IS_NULL) {
			ZEPHIR_INIT_VAR(&_18$$10);
			ZVAL_STRING(&_18$$10, "basic ");
			ZEPHIR_CALL_FUNCTION(&_19$$10, "stripos", NULL, 23, &authorizationHeader, &_18$$10);
			zephir_check_call_status();
			zephir_read_property(&_20$$10, this_ptr, SL("parameters"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_VAR(&_21$$10);
			zephir_array_fetch_string(&_21$$10, &_20$$10, SL("PHP_AUTH_DIGEST"), PH_NOISY, "zim/http/serverbag.zep", 73 TSRMLS_CC);
			_22$$10 = ZEPHIR_IS_EMPTY(&_21$$10);
			if (_22$$10) {
				ZEPHIR_INIT_NVAR(&_18$$10);
				ZVAL_STRING(&_18$$10, "digest ");
				ZEPHIR_CALL_FUNCTION(&_23$$10, "stripos", NULL, 23, &authorizationHeader, &_18$$10);
				zephir_check_call_status();
				_22$$10 = ZEPHIR_IS_LONG_IDENTICAL(&_23$$10, 0);
			}
			ZEPHIR_INIT_NVAR(&_18$$10);
			ZVAL_STRING(&_18$$10, "bearer ");
			ZEPHIR_CALL_FUNCTION(&_24$$10, "stripos", NULL, 23, &authorizationHeader, &_18$$10);
			zephir_check_call_status();
			if (ZEPHIR_IS_LONG_IDENTICAL(&_19$$10, 0)) {
				ZVAL_LONG(&_25$$11, 6);
				ZEPHIR_INIT_VAR(&_26$$11);
				zephir_substr(&_26$$11, &authorizationHeader, 6 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
				ZEPHIR_CALL_FUNCTION(&_27$$11, "base64_decode", NULL, 99, &_26$$11);
				zephir_check_call_status();
				ZEPHIR_INIT_VAR(&exploded);
				zephir_fast_explode_str(&exploded, SL(":"), &_27$$11, 2  TSRMLS_CC);
				if (2 == zephir_fast_count_int(&exploded TSRMLS_CC)) {
					ZEPHIR_CPY_WRT(&tmpListHeadersPHP_AUTH_USERHeadersPHP_AUTH_PW, &exploded);
					zephir_array_fetch_long(&_28$$12, &tmpListHeadersPHP_AUTH_USERHeadersPHP_AUTH_PW, 0, PH_NOISY | PH_READONLY, "zim/http/serverbag.zep", 70 TSRMLS_CC);
					zephir_array_update_string(&headers, SL("PHP_AUTH_USER"), &_28$$12, PH_COPY | PH_SEPARATE);
					zephir_array_fetch_long(&_29$$12, &tmpListHeadersPHP_AUTH_USERHeadersPHP_AUTH_PW, 1, PH_NOISY | PH_READONLY, "zim/http/serverbag.zep", 71 TSRMLS_CC);
					zephir_array_update_string(&headers, SL("PHP_AUTH_PW"), &_29$$12, PH_COPY | PH_SEPARATE);
				}
			} else if (_22$$10) {
				zephir_array_update_string(&headers, SL("PHP_AUTH_DIGEST"), &authorizationHeader, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_VAR(&_30$$13);
				ZVAL_STRING(&_30$$13, "PHP_AUTH_DIGEST");
				zephir_update_property_array(this_ptr, SL("parameters"), &_30$$13, &authorizationHeader TSRMLS_CC);
			} else if (ZEPHIR_IS_LONG_IDENTICAL(&_24$$10, 0)) {
				zephir_array_update_string(&headers, SL("AUTHORIZATION"), &authorizationHeader, PH_COPY | PH_SEPARATE);
			}
		}
	}
	if (zephir_array_isset_string(&headers, SL("AUTHORIZATION"))) {
		RETURN_CCTOR(&headers);
	}
	if (zephir_array_isset_string(&headers, SL("PHP_AUTH_USER"))) {
		zephir_array_fetch_string(&_31$$16, &headers, SL("PHP_AUTH_USER"), PH_NOISY | PH_READONLY, "zim/http/serverbag.zep", 92 TSRMLS_CC);
		zephir_array_fetch_string(&_32$$16, &headers, SL("PHP_AUTH_PW"), PH_NOISY | PH_READONLY, "zim/http/serverbag.zep", 92 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_33$$16);
		ZEPHIR_CONCAT_VSV(&_33$$16, &_31$$16, ":", &_32$$16);
		ZEPHIR_CALL_FUNCTION(&_34$$16, "base64_encode", NULL, 100, &_33$$16);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_35$$16);
		ZEPHIR_CONCAT_SV(&_35$$16, "Basic ", &_34$$16);
		zephir_array_update_string(&headers, SL("AUTHORIZATION"), &_35$$16, PH_COPY | PH_SEPARATE);
	} else if (zephir_array_isset_string(&headers, SL("PHP_AUTH_DIGEST"))) {
		zephir_array_fetch_string(&_36$$17, &headers, SL("PHP_AUTH_DIGEST"), PH_NOISY | PH_READONLY, "zim/http/serverbag.zep", 94 TSRMLS_CC);
		zephir_array_update_string(&headers, SL("AUTHORIZATION"), &_36$$17, PH_COPY | PH_SEPARATE);
	}
	RETURN_CCTOR(&headers);

}

