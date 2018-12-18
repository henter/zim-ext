
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
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"


/**
 * File Dispatcher.php
 * @henter
 * Time: 2018-11-24 19:56
 *
 */
ZEPHIR_INIT_CLASS(Zim_Event_Dispatcher) {

	ZEPHIR_REGISTER_CLASS(Zim\\Event, Dispatcher, zim, event_dispatcher, zim_event_dispatcher_method_entry, 0);

	/**
	 * The registered event listeners.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_event_dispatcher_ce, SL("listeners"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_event_dispatcher_ce->create_object = zephir_init_properties_Zim_Event_Dispatcher;
	return SUCCESS;

}

/**
 * Register an event listener with the dispatcher.
 *
 * @param  string|array  $events
 * @param  mixed  $listener
 * @return void
 */
PHP_METHOD(Zim_Event_Dispatcher, listen) {

	zephir_fcall_cache_entry *_2 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *events, events_sub, *listener, listener_sub, event, arr, *_0, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&events_sub);
	ZVAL_UNDEF(&listener_sub);
	ZVAL_UNDEF(&event);
	ZVAL_UNDEF(&arr);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &events, &listener);



	if (Z_TYPE_P(events) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&arr, events);
	} else {
		ZEPHIR_INIT_NVAR(&arr);
		zephir_create_array(&arr, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&arr, events);
	}
	zephir_is_iterable(&arr, 0, "zim/event/dispatcher.zep", 34);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&arr), _0)
	{
		ZEPHIR_INIT_NVAR(&event);
		ZVAL_COPY(&event, _0);
		ZEPHIR_INIT_NVAR(&_1$$3);
		object_init_ex(&_1$$3, zim_event_listener_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", &_2, 71, listener);
		zephir_check_call_status();
		zephir_update_property_array_multi(this_ptr, SL("listeners"), &_1$$3 TSRMLS_CC, SL("za"), 2, &event);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&event);
	ZEPHIR_MM_RESTORE();

}

/**
 * sugar method to listen and callback specific event object
 *
 * @param callable $callback
 */
PHP_METHOD(Zim_Event_Dispatcher, on) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *callback, callback_sub, r, params, eventClass, _4, _5, _6, _1$$3, _2$$3, _3$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&r);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&eventClass);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &callback);



	ZEPHIR_CALL_CE_STATIC(&r, zim_container_boundmethod_ce, "getcallreflector", &_0, 0, callback);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&params, &r, "getparameters", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&params))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_2$$3, &r, "getname", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SVS(&_3$$3, "event callback [", &_2$$3, "] parameter empty");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 28, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "zim/event/dispatcher.zep", 48 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_FUNCTION(&_4, "current", NULL, 72, &params);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, &_4, "getclass", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&eventClass, &_5, "getname", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_6);
	object_init_ex(&_6, zim_event_listeneron_ce);
	ZEPHIR_CALL_METHOD(NULL, &_6, "__construct", NULL, 73, callback);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "listen", NULL, 0, &eventClass, &_6);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Fire an event and call the listeners.
 *
 * @param  string|object  $event
 * @param  mixed  $payload
 * @param  bool  $halt
 * @return array|null
 */
PHP_METHOD(Zim_Event_Dispatcher, fire) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool halt, _2$$3;
	zval *event = NULL, event_sub, *payload = NULL, payload_sub, *halt_param = NULL, tmpListEventPayload, responses, listener, response, _0, *_1, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&event_sub);
	ZVAL_UNDEF(&payload_sub);
	ZVAL_UNDEF(&tmpListEventPayload);
	ZVAL_UNDEF(&responses);
	ZVAL_UNDEF(&listener);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &event, &payload, &halt_param);

	ZEPHIR_SEPARATE_PARAM(event);
	if (!payload) {
		payload = &payload_sub;
		ZEPHIR_INIT_VAR(payload);
		array_init(payload);
	} else {
		ZEPHIR_SEPARATE_PARAM(payload);
	}
	if (!halt_param) {
		halt = 0;
	} else {
		halt = zephir_get_boolval(halt_param);
	}


	ZEPHIR_CALL_METHOD(&tmpListEventPayload, this_ptr, "parseeventandpayload", NULL, 0, event, payload);
	zephir_check_call_status();
	ZEPHIR_OBS_NVAR(event);
	zephir_array_fetch_long(event, &tmpListEventPayload, 0, PH_NOISY, "zim/event/dispatcher.zep", 70 TSRMLS_CC);
	ZEPHIR_OBS_NVAR(payload);
	zephir_array_fetch_long(payload, &tmpListEventPayload, 1, PH_NOISY, "zim/event/dispatcher.zep", 71 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&responses);
	array_init(&responses);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getlisteners", NULL, 0, event);
	zephir_check_call_status();
	zephir_is_iterable(&_0, 0, "zim/event/dispatcher.zep", 89);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
	{
		ZEPHIR_INIT_NVAR(&listener);
		ZVAL_COPY(&listener, _1);
		ZEPHIR_CALL_ZVAL_FUNCTION(&response, &listener, NULL, 0, event, payload);
		zephir_check_call_status();
		_2$$3 = halt;
		if (_2$$3) {
			_2$$3 = !((Z_TYPE_P(&response) == IS_NULL));
		}
		if (_2$$3) {
			RETURN_CCTOR(&response);
		}
		if (ZEPHIR_IS_FALSE_IDENTICAL(&response)) {
			break;
		}
		zephir_array_append(&responses, &response, PH_SEPARATE, "zim/event/dispatcher.zep", 87);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&listener);
	ZEPHIR_INIT_VAR(&_3);
	if (halt) {
		ZVAL_NULL(&_3);
	} else {
		ZEPHIR_CPY_WRT(&_3, &responses);
	}
	RETURN_CCTOR(&_3);

}

/**
 * Parse the given event and payload and prepare them for dispatching.
 *
 * @param  mixed  $event
 * @param  mixed  $payload
 * @return array
 */
PHP_METHOD(Zim_Event_Dispatcher, parseEventAndPayload) {

	zval *event, event_sub, *payload = NULL, payload_sub, _0$$3, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&event_sub);
	ZVAL_UNDEF(&payload_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &event, &payload);

	ZEPHIR_SEPARATE_PARAM(payload);


	if (Z_TYPE_P(event) == IS_OBJECT) {
		zephir_create_array(return_value, 2, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_get_class(&_0$$3, event, 0 TSRMLS_CC);
		zephir_array_fast_append(return_value, &_0$$3);
		zephir_array_fast_append(return_value, event);
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_1);
	if (Z_TYPE_P(payload) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&_1, payload);
	} else {
		ZEPHIR_INIT_NVAR(&_1);
		zephir_create_array(&_1, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&_1, payload);
	}
	ZEPHIR_CPY_WRT(payload, &_1);
	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(return_value, event);
	zephir_array_fast_append(return_value, payload);
	RETURN_MM();

}

/**
 * Get all of the listeners for a given event name.
 *
 * @param  string  $eventName
 * @return array
 */
PHP_METHOD(Zim_Event_Dispatcher, getListeners) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *eventName_param = NULL, __$false, listeners, _0, _1, _2, _3;
	zval eventName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventName);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&listeners);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &eventName_param);

	zephir_get_strval(&eventName, eventName_param);


	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("listeners"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, &eventName)) {
		zephir_read_property(&_2, this_ptr, SL("listeners"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_OBS_NVAR(&_0);
		zephir_array_fetch(&_0, &_2, &eventName, PH_NOISY, "zim/event/dispatcher.zep", 118 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_NVAR(&_0);
		array_init(&_0);
	}
	ZEPHIR_CPY_WRT(&listeners, &_0);
	ZEPHIR_INIT_VAR(&_3);
	if (zephir_class_exists(&eventName, zephir_is_true(&__$false)  TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(&_3, this_ptr, "addinterfacelisteners", NULL, 0, &eventName, &listeners);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&_3, &listeners);
	}
	RETURN_CCTOR(&_3);

}

/**
 * Add the listeners for the event's interfaces to the given array.
 *
 * @param  string  $eventName
 * @param  array  $listeners
 * @return array
 */
PHP_METHOD(Zim_Event_Dispatcher, addInterfaceListeners) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval listeners;
	zval *eventName_param = NULL, *listeners_param = NULL, interfacee, names, _0, *_1, _2$$3, _3$$4, _4$$4, *_5$$4, _6$$5, _7$$5;
	zval eventName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventName);
	ZVAL_UNDEF(&interfacee);
	ZVAL_UNDEF(&names);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&listeners);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &eventName_param, &listeners_param);

	zephir_get_strval(&eventName, eventName_param);
	if (!listeners_param) {
		ZEPHIR_INIT_VAR(&listeners);
		array_init(&listeners);
	} else {
		zephir_get_arrval(&listeners, listeners_param);
	}


	ZEPHIR_CALL_FUNCTION(&_0, "class_implements", NULL, 74, &eventName);
	zephir_check_call_status();
	zephir_is_iterable(&_0, 0, "zim/event/dispatcher.zep", 141);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
	{
		ZEPHIR_INIT_NVAR(&interfacee);
		ZVAL_COPY(&interfacee, _1);
		zephir_read_property(&_2$$3, this_ptr, SL("listeners"), PH_NOISY_CC | PH_READONLY);
		if (zephir_array_isset(&_2$$3, &interfacee)) {
			zephir_read_property(&_3$$4, this_ptr, SL("listeners"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_4$$4, &_3$$4, &interfacee, PH_NOISY | PH_READONLY, "zim/event/dispatcher.zep", 135 TSRMLS_CC);
			zephir_is_iterable(&_4$$4, 0, "zim/event/dispatcher.zep", 139);
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_4$$4), _5$$4)
			{
				ZEPHIR_INIT_NVAR(&names);
				ZVAL_COPY(&names, _5$$4);
				ZEPHIR_INIT_LNVAR(_6$$5);
				if (Z_TYPE_P(&names) == IS_ARRAY) {
					ZEPHIR_CPY_WRT(&_6$$5, &names);
				} else {
					ZEPHIR_INIT_NVAR(&_6$$5);
					zephir_create_array(&_6$$5, 1, 0 TSRMLS_CC);
					zephir_array_fast_append(&_6$$5, &names);
				}
				ZEPHIR_CPY_WRT(&names, &_6$$5);
				ZEPHIR_INIT_NVAR(&_7$$5);
				zephir_fast_array_merge(&_7$$5, &listeners, &names TSRMLS_CC);
				ZEPHIR_CPY_WRT(&listeners, &_7$$5);
			} ZEND_HASH_FOREACH_END();
			ZEPHIR_INIT_NVAR(&names);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&interfacee);
	RETURN_CTOR(&listeners);

}

/**
 * Determine if a given event has listeners.
 *
 * @param  string  $eventName
 * @return bool
 */
PHP_METHOD(Zim_Event_Dispatcher, hasListeners) {

	zval *eventName_param = NULL, _0;
	zval eventName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eventName);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &eventName_param);

	zephir_get_strval(&eventName, eventName_param);


	zephir_read_property(&_0, this_ptr, SL("listeners"), PH_NOISY_CC | PH_READONLY);
	RETURN_MM_BOOL(zephir_array_isset(&_0, &eventName));

}

/**
 * Remove a set of listeners from the dispatcher.
 *
 * @param  string  $event
 * @return void
 */
PHP_METHOD(Zim_Event_Dispatcher, remove) {

	zval *event_param = NULL, _0;
	zval event;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&event);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &event_param);

	zephir_get_strval(&event, event_param);


	zephir_read_property(&_0, this_ptr, SL("listeners"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, &event, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

zend_object *zephir_init_properties_Zim_Event_Dispatcher(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _1$$3;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("listeners"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("listeners"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

