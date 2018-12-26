
extern zend_class_entry *zim_http_responseheaderbag_ce;

ZEPHIR_INIT_CLASS(Zim_Http_ResponseHeaderBag);

PHP_METHOD(Zim_Http_ResponseHeaderBag, __construct);
PHP_METHOD(Zim_Http_ResponseHeaderBag, allPreserveCase);
PHP_METHOD(Zim_Http_ResponseHeaderBag, replace);
PHP_METHOD(Zim_Http_ResponseHeaderBag, set);
PHP_METHOD(Zim_Http_ResponseHeaderBag, remove);
PHP_METHOD(Zim_Http_ResponseHeaderBag, hasCacheControlDirective);
PHP_METHOD(Zim_Http_ResponseHeaderBag, getCacheControlDirective);
PHP_METHOD(Zim_Http_ResponseHeaderBag, computeCacheControlValue);
PHP_METHOD(Zim_Http_ResponseHeaderBag, initDate);
zend_object *zephir_init_properties_Zim_Http_ResponseHeaderBag(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_responseheaderbag___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_responseheaderbag_allpreservecase, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_responseheaderbag_allpreservecase, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_responseheaderbag_replace, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_responseheaderbag_set, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, values)
	ZEND_ARG_INFO(0, replace)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_responseheaderbag_remove, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_responseheaderbag_hascachecontroldirective, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_responseheaderbag_getcachecontroldirective, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_responseheaderbag_computecachecontrolvalue, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_responseheaderbag_computecachecontrolvalue, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_responseheaderbag_method_entry) {
	PHP_ME(Zim_Http_ResponseHeaderBag, __construct, arginfo_zim_http_responseheaderbag___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Http_ResponseHeaderBag, allPreserveCase, arginfo_zim_http_responseheaderbag_allpreservecase, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ResponseHeaderBag, replace, arginfo_zim_http_responseheaderbag_replace, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ResponseHeaderBag, set, arginfo_zim_http_responseheaderbag_set, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ResponseHeaderBag, remove, arginfo_zim_http_responseheaderbag_remove, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ResponseHeaderBag, hasCacheControlDirective, arginfo_zim_http_responseheaderbag_hascachecontroldirective, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ResponseHeaderBag, getCacheControlDirective, arginfo_zim_http_responseheaderbag_getcachecontroldirective, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ResponseHeaderBag, computeCacheControlValue, arginfo_zim_http_responseheaderbag_computecachecontrolvalue, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_ResponseHeaderBag, initDate, NULL, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
