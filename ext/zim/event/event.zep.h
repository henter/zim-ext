
extern zend_class_entry *zim_event_event_ce;

ZEPHIR_INIT_CLASS(Zim_Event_Event);

PHP_METHOD(Zim_Event_Event, fire);
PHP_METHOD(Zim_Event_Event, listen);
PHP_METHOD(Zim_Event_Event, on);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_event_fire, 0, 0, 1)
	ZEND_ARG_INFO(0, event)
	ZEND_ARG_ARRAY_INFO(0, payload, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, halt, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, halt)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_event_listen, 0, 0, 1)
	ZEND_ARG_INFO(0, event)
	ZEND_ARG_ARRAY_INFO(0, payload, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_event_on, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_event_event_method_entry) {
	PHP_ME(Zim_Event_Event, fire, arginfo_zim_event_event_fire, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Event_Event, listen, arginfo_zim_event_event_listen, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Event_Event, on, arginfo_zim_event_event_on, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
