
extern zend_class_entry *zim_event_httpevent_ce;

ZEPHIR_INIT_CLASS(Zim_Event_HttpEvent);

PHP_METHOD(Zim_Event_HttpEvent, __construct);
PHP_METHOD(Zim_Event_HttpEvent, getResponse);
PHP_METHOD(Zim_Event_HttpEvent, setResponse);
PHP_METHOD(Zim_Event_HttpEvent, getRequest);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_httpevent___construct, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Contract\\Request, 0)
	ZEND_ARG_OBJ_INFO(0, response, Zim\\Contract\\Response, 1)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_event_httpevent_getresponse, 0, 0, Zim\\Contract\\Response, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_httpevent_getresponse, 0, 0, IS_OBJECT, "Zim\\Contract\\Response", 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_httpevent_setresponse, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, response, Zim\\Contract\\Response, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_event_httpevent_getrequest, 0, 0, Zim\\Contract\\Request, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_httpevent_getrequest, 0, 0, IS_OBJECT, "Zim\\Contract\\Request", 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_event_httpevent_method_entry) {
	PHP_ME(Zim_Event_HttpEvent, __construct, arginfo_zim_event_httpevent___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Event_HttpEvent, getResponse, arginfo_zim_event_httpevent_getresponse, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Event_HttpEvent, setResponse, arginfo_zim_event_httpevent_setresponse, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Event_HttpEvent, getRequest, arginfo_zim_event_httpevent_getrequest, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
