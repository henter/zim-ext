
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
#include "kernel/operators.h"


/**
 * File Event.php
 * @henter
 * Time: 2018-11-24 19:56
 *
 */
ZEPHIR_INIT_CLASS(Zim_Event_Event) {

	ZEPHIR_REGISTER_CLASS(Zim\\Event, Event, zim, event_event, zim_event_event_method_entry, 0);

	zephir_declare_class_constant_string(zim_event_event_ce, SL("EXCEPTION"), "zim.exception");

	return SUCCESS;

}

/**
 * @param $event
 * @param array $payload
 * @param bool $halt
 */
PHP_METHOD(Zim_Event_Event, fire) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zend_bool halt;
	zval payload;
	zval *event, event_sub, *payload_param = NULL, *halt_param = NULL, _0, _2, _3, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&event_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&payload);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &event, &payload_param, &halt_param);

	if (!payload_param) {
		ZEPHIR_INIT_VAR(&payload);
		array_init(&payload);
	} else {
		zephir_get_arrval(&payload, payload_param);
	}
	if (!halt_param) {
		halt = 0;
	} else {
		halt = zephir_get_boolval(halt_param);
	}


	ZEPHIR_CALL_CE_STATIC(&_0, zim_zim_ce, "getinstance", &_1, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "event");
	ZEPHIR_CALL_METHOD(&_2, &_0, "make", NULL, 0, &_3);
	zephir_check_call_status();
	if (halt) {
		ZVAL_BOOL(&_4, 1);
	} else {
		ZVAL_BOOL(&_4, 0);
	}
	ZEPHIR_CALL_METHOD(NULL, &_2, "fire", NULL, 0, event, &payload, &_4);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * @param $event
 * @param callable $listener
 */
PHP_METHOD(Zim_Event_Event, listen) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *event, event_sub, *listener, listener_sub, _0, _2, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&event_sub);
	ZVAL_UNDEF(&listener_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &event, &listener);



	ZEPHIR_CALL_CE_STATIC(&_0, zim_zim_ce, "getinstance", &_1, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "event");
	ZEPHIR_CALL_METHOD(&_2, &_0, "make", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_2, "listen", NULL, 0, event, listener);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * @param callable $callback
 */
PHP_METHOD(Zim_Event_Event, on) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *callback, callback_sub, _0, _2, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &callback);



	ZEPHIR_CALL_CE_STATIC(&_0, zim_zim_ce, "getinstance", &_1, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "event");
	ZEPHIR_CALL_METHOD(&_2, &_0, "make", NULL, 0, &_3);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &_2, "on", NULL, 0, callback);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

