
extern zend_class_entry *zim_http_exception_notfoundexception_ce;

ZEPHIR_INIT_CLASS(Zim_Http_Exception_NotFoundException);

PHP_METHOD(Zim_Http_Exception_NotFoundException, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_exception_notfoundexception___construct, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, message, IS_STRING, 1)
#else
	ZEND_ARG_INFO(0, message)
#endif
	ZEND_ARG_OBJ_INFO(0, previous, Zim\\Http\\Exception\\Exception, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, code, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, code)
#endif
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_exception_notfoundexception_method_entry) {
	PHP_ME(Zim_Http_Exception_NotFoundException, __construct, arginfo_zim_http_exception_notfoundexception___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_FE_END
};
