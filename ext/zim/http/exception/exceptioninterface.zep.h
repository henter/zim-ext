
extern zend_class_entry *zim_http_exception_exceptioninterface_ce;

ZEPHIR_INIT_CLASS(Zim_Http_Exception_ExceptionInterface);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_exception_exceptioninterface_getstatuscode, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_exception_exceptioninterface_getstatuscode, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_exception_exceptioninterface_getheaders, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_exception_exceptioninterface_getheaders, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_exception_exceptioninterface_method_entry) {
	PHP_ABSTRACT_ME(Zim_Http_Exception_ExceptionInterface, getStatusCode, arginfo_zim_http_exception_exceptioninterface_getstatuscode)
	PHP_ABSTRACT_ME(Zim_Http_Exception_ExceptionInterface, getHeaders, arginfo_zim_http_exception_exceptioninterface_getheaders)
	PHP_FE_END
};
