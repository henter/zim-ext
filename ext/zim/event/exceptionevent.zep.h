
extern zend_class_entry *zim_event_exceptionevent_ce;

ZEPHIR_INIT_CLASS(Zim_Event_ExceptionEvent);

PHP_METHOD(Zim_Event_ExceptionEvent, __construct);
PHP_METHOD(Zim_Event_ExceptionEvent, getThrowable);
PHP_METHOD(Zim_Event_ExceptionEvent, getResponse);
PHP_METHOD(Zim_Event_ExceptionEvent, setResponse);
PHP_METHOD(Zim_Event_ExceptionEvent, getRequest);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_exceptionevent___construct, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, e, Throwable, 0)
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Http\\Request, 0)
	ZEND_ARG_OBJ_INFO(0, response, Zim\\Http\\Response, 1)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_event_exceptionevent_getthrowable, 0, 0, Throable, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_exceptionevent_getthrowable, 0, 0, IS_OBJECT, "Throable", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_event_exceptionevent_getresponse, 0, 0, Zim\\Http\\Response, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_exceptionevent_getresponse, 0, 0, IS_OBJECT, "Zim\\Http\\Response", 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_event_exceptionevent_setresponse, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, response, Zim\\Http\\Response, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_event_exceptionevent_getrequest, 0, 0, Zim\\Http\\Request, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_event_exceptionevent_getrequest, 0, 0, IS_OBJECT, "Zim\\Http\\Request", 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_event_exceptionevent_method_entry) {
	PHP_ME(Zim_Event_ExceptionEvent, __construct, arginfo_zim_event_exceptionevent___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Event_ExceptionEvent, getThrowable, arginfo_zim_event_exceptionevent_getthrowable, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Event_ExceptionEvent, getResponse, arginfo_zim_event_exceptionevent_getresponse, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Event_ExceptionEvent, setResponse, arginfo_zim_event_exceptionevent_setresponse, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Event_ExceptionEvent, getRequest, arginfo_zim_event_exceptionevent_getrequest, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
