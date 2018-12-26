
extern zend_class_entry *zim_event_dispatcher_ce;

ZEPHIR_INIT_CLASS(Zim_Event_Dispatcher);

PHP_METHOD(Zim_Event_Dispatcher, listen);
PHP_METHOD(Zim_Event_Dispatcher, fire);
PHP_METHOD(Zim_Event_Dispatcher, parseEventAndPayload);
PHP_METHOD(Zim_Event_Dispatcher, getListeners);
PHP_METHOD(Zim_Event_Dispatcher, addInterfaceListeners);
PHP_METHOD(Zim_Event_Dispatcher, hasListeners);
PHP_METHOD(Zim_Event_Dispatcher, remove);
zend_object *zephir_init_properties_Zim_Event_Dispatcher(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_dispatcher_listen, 0, 0, 2)
	ZEND_ARG_INFO(0, events)
	ZEND_ARG_INFO(0, listener)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_dispatcher_fire, 0, 0, 1)
	ZEND_ARG_INFO(0, event)
	ZEND_ARG_INFO(0, payload)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, halt, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, halt)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_dispatcher_parseeventandpayload, 0, 2, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_dispatcher_parseeventandpayload, 0, 2, IS_ARRAY, NULL, 0)
#endif
	ZEND_ARG_INFO(0, event)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_dispatcher_getlisteners, 0, 1, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_dispatcher_getlisteners, 0, 1, IS_ARRAY, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, eventName, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, eventName)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_dispatcher_addinterfacelisteners, 0, 1, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_dispatcher_addinterfacelisteners, 0, 1, IS_ARRAY, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, eventName, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, eventName)
#endif
	ZEND_ARG_ARRAY_INFO(0, listeners, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_dispatcher_haslisteners, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_dispatcher_haslisteners, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, eventName, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, eventName)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_dispatcher_remove, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, event, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, event)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_event_dispatcher_method_entry) {
	PHP_ME(Zim_Event_Dispatcher, listen, arginfo_zim_event_dispatcher_listen, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Event_Dispatcher, fire, arginfo_zim_event_dispatcher_fire, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Event_Dispatcher, parseEventAndPayload, arginfo_zim_event_dispatcher_parseeventandpayload, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Event_Dispatcher, getListeners, arginfo_zim_event_dispatcher_getlisteners, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Event_Dispatcher, addInterfaceListeners, arginfo_zim_event_dispatcher_addinterfacelisteners, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Event_Dispatcher, hasListeners, arginfo_zim_event_dispatcher_haslisteners, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Event_Dispatcher, remove, arginfo_zim_event_dispatcher_remove, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
