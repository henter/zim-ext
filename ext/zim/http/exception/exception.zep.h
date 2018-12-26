
extern zend_class_entry *zim_http_exception_exception_ce;

ZEPHIR_INIT_CLASS(Zim_Http_Exception_Exception);

PHP_METHOD(Zim_Http_Exception_Exception, __construct);
PHP_METHOD(Zim_Http_Exception_Exception, getStatusCode);
PHP_METHOD(Zim_Http_Exception_Exception, getHeaders);
PHP_METHOD(Zim_Http_Exception_Exception, setHeaders);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_exception_exception___construct, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, statusCode, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, statusCode)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, message, IS_STRING, 1)
#else
	ZEND_ARG_INFO(0, message)
#endif
	ZEND_ARG_OBJ_INFO(0, previous, Zim\\Http\\Exception\\Exception, 1)
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, code, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, code)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_exception_exception_getstatuscode, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_exception_exception_getstatuscode, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_exception_exception_getheaders, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_exception_exception_getheaders, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_exception_exception_setheaders, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_exception_exception_method_entry) {
	PHP_ME(Zim_Http_Exception_Exception, __construct, arginfo_zim_http_exception_exception___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Http_Exception_Exception, getStatusCode, arginfo_zim_http_exception_exception_getstatuscode, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Exception_Exception, getHeaders, arginfo_zim_http_exception_exception_getheaders, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Exception_Exception, setHeaders, arginfo_zim_http_exception_exception_setheaders, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
