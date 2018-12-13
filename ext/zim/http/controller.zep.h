
extern zend_class_entry *zim_http_controller_ce;

ZEPHIR_INIT_CLASS(Zim_Http_Controller);

PHP_METHOD(Zim_Http_Controller, __get);
PHP_METHOD(Zim_Http_Controller, app);
PHP_METHOD(Zim_Http_Controller, bind);
PHP_METHOD(Zim_Http_Controller, getRequest);
PHP_METHOD(Zim_Http_Controller, getActionClass);
PHP_METHOD(Zim_Http_Controller, getAction);
PHP_METHOD(Zim_Http_Controller, getActions);
zend_object *zephir_init_properties_Zim_Http_Controller(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_controller___get, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_controller_app, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_controller_bind, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_controller_getactionclass, 0, 0, 1)
	ZEND_ARG_INFO(0, uri)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_controller_getaction, 0, 1, IS_NULL, 1)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_controller_getaction, 0, 1, IS_NULL, NULL, 1)
#endif
	ZEND_ARG_INFO(0, uri)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_controller_method_entry) {
	PHP_ME(Zim_Http_Controller, __get, arginfo_zim_http_controller___get, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Controller, app, arginfo_zim_http_controller_app, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Controller, bind, arginfo_zim_http_controller_bind, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Controller, getRequest, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Controller, getActionClass, arginfo_zim_http_controller_getactionclass, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Controller, getAction, arginfo_zim_http_controller_getaction, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Controller, getActions, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
