
extern zend_class_entry *zim_event_listener_ce;

ZEPHIR_INIT_CLASS(Zim_Event_Listener);

PHP_METHOD(Zim_Event_Listener, __construct);
PHP_METHOD(Zim_Event_Listener, __invoke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_listener___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_listener___invoke, 0, 0, 2)
	ZEND_ARG_INFO(0, event)
	ZEND_ARG_INFO(0, payload)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_event_listener_method_entry) {
	PHP_ME(Zim_Event_Listener, __construct, arginfo_zim_event_listener___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Event_Listener, __invoke, arginfo_zim_event_listener___invoke, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
