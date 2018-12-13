
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


/**
 * File RequestEvent.php
 * @henter
 * Time: 2018-11-25 23:15
 *
 */
ZEPHIR_INIT_CLASS(Zim_Event_RequestEvent) {

	ZEPHIR_REGISTER_CLASS_EX(Zim\\Event, RequestEvent, zim, event_requestevent, zim_event_httpevent_ce, NULL, 0);

	return SUCCESS;

}

