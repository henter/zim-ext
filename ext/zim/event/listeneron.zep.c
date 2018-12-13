
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


/**
 * File Event.php
 * @henter
 * Time: 2018-11-24 19:56
 *
 */
ZEPHIR_INIT_CLASS(Zim_Event_ListenerOn) {

	ZEPHIR_REGISTER_CLASS(Zim\\Event, ListenerOn, zim, event_listeneron, zim_event_listeneron_method_entry, 0);

	zend_declare_property_null(zim_event_listeneron_ce, SL("callback"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Zim_Event_ListenerOn, __construct) {

	zval *callback, callback_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);

	zephir_fetch_params(0, 1, 0, &callback);



	zephir_update_property_zval(this_ptr, SL("callback"), callback);

}

PHP_METHOD(Zim_Event_ListenerOn, __invoke) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *event, event_sub, *payload, payload_sub, callback, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&event_sub);
	ZVAL_UNDEF(&payload_sub);
	ZVAL_UNDEF(&callback);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &event, &payload);



	zephir_read_property(&_0, this_ptr, SL("callback"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&callback, &_0);
	ZEPHIR_RETURN_CALL_ZVAL_FUNCTION(&callback, NULL, 0, event, payload);
	zephir_check_call_status();
	RETURN_MM();

}

