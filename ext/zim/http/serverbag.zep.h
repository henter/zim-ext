
extern zend_class_entry *zim_http_serverbag_ce;

ZEPHIR_INIT_CLASS(Zim_Http_ServerBag);

PHP_METHOD(Zim_Http_ServerBag, getHeaders);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_serverbag_getheaders, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_serverbag_getheaders, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_serverbag_method_entry) {
	PHP_ME(Zim_Http_ServerBag, getHeaders, arginfo_zim_http_serverbag_getheaders, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
