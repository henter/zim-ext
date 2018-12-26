
extern zend_class_entry *zim_http_exception_methodnotallowedexception_ce;

ZEPHIR_INIT_CLASS(Zim_Http_Exception_MethodNotAllowedException);

PHP_METHOD(Zim_Http_Exception_MethodNotAllowedException, __construct);
PHP_METHOD(Zim_Http_Exception_MethodNotAllowedException, getAllowedMethods);
zend_object *zephir_init_properties_Zim_Http_Exception_MethodNotAllowedException(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_exception_methodnotallowedexception___construct, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, allowedMethods, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, code, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, code)
#endif
	ZEND_ARG_OBJ_INFO(0, previous, Zim\\Http\\Exception\\Exception, 1)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_exception_methodnotallowedexception_getallowedmethods, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_exception_methodnotallowedexception_getallowedmethods, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_exception_methodnotallowedexception_method_entry) {
	PHP_ME(Zim_Http_Exception_MethodNotAllowedException, __construct, arginfo_zim_http_exception_methodnotallowedexception___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Http_Exception_MethodNotAllowedException, getAllowedMethods, arginfo_zim_http_exception_methodnotallowedexception_getallowedmethods, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
