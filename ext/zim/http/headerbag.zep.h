
extern zend_class_entry *zim_http_headerbag_ce;

ZEPHIR_INIT_CLASS(Zim_Http_HeaderBag);

PHP_METHOD(Zim_Http_HeaderBag, __construct);
PHP_METHOD(Zim_Http_HeaderBag, addCacheControlDirective);
PHP_METHOD(Zim_Http_HeaderBag, hasCacheControlDirective);
PHP_METHOD(Zim_Http_HeaderBag, getCacheControlDirective);
PHP_METHOD(Zim_Http_HeaderBag, removeCacheControlDirective);
PHP_METHOD(Zim_Http_HeaderBag, parseCacheControl);
PHP_METHOD(Zim_Http_HeaderBag, getCacheControlHeader);
PHP_METHOD(Zim_Http_HeaderBag, getDate);
PHP_METHOD(Zim_Http_HeaderBag, __toString);
PHP_METHOD(Zim_Http_HeaderBag, all);
PHP_METHOD(Zim_Http_HeaderBag, keys);
PHP_METHOD(Zim_Http_HeaderBag, replace);
PHP_METHOD(Zim_Http_HeaderBag, add);
PHP_METHOD(Zim_Http_HeaderBag, get);
PHP_METHOD(Zim_Http_HeaderBag, set);
PHP_METHOD(Zim_Http_HeaderBag, has);
PHP_METHOD(Zim_Http_HeaderBag, contains);
PHP_METHOD(Zim_Http_HeaderBag, remove);
PHP_METHOD(Zim_Http_HeaderBag, getIterator);
PHP_METHOD(Zim_Http_HeaderBag, count);
zend_object *zephir_init_properties_Zim_Http_HeaderBag(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag_addcachecontroldirective, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag_hascachecontroldirective, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag_getcachecontroldirective, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag_removecachecontroldirective, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_parsecachecontrol, 0, 1, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_parsecachecontrol, 0, 1, IS_ARRAY, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, header, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, header)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag_getdate, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_OBJ_INFO(0, deft, DateTime, 1)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag___tostring, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag___tostring, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_all, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_all, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_keys, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_keys, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag_replace, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag_add, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag_get, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, first, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, first)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag_set, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, values)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, replace, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, replace)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_has, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_has, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_contains, 0, 2, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_contains, 0, 2, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerbag_remove, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_headerbag_getiterator, 0, 0, ArrayIterator, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_getiterator, 0, 0, IS_OBJECT, "ArrayIterator", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_count, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerbag_count, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_headerbag_method_entry) {
	PHP_ME(Zim_Http_HeaderBag, __construct, arginfo_zim_http_headerbag___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Http_HeaderBag, addCacheControlDirective, arginfo_zim_http_headerbag_addcachecontroldirective, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, hasCacheControlDirective, arginfo_zim_http_headerbag_hascachecontroldirective, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, getCacheControlDirective, arginfo_zim_http_headerbag_getcachecontroldirective, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, removeCacheControlDirective, arginfo_zim_http_headerbag_removecachecontroldirective, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, parseCacheControl, arginfo_zim_http_headerbag_parsecachecontrol, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_HeaderBag, getCacheControlHeader, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_HeaderBag, getDate, arginfo_zim_http_headerbag_getdate, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, __toString, arginfo_zim_http_headerbag___tostring, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, all, arginfo_zim_http_headerbag_all, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, keys, arginfo_zim_http_headerbag_keys, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, replace, arginfo_zim_http_headerbag_replace, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, add, arginfo_zim_http_headerbag_add, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, get, arginfo_zim_http_headerbag_get, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, set, arginfo_zim_http_headerbag_set, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, has, arginfo_zim_http_headerbag_has, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, contains, arginfo_zim_http_headerbag_contains, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, remove, arginfo_zim_http_headerbag_remove, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, getIterator, arginfo_zim_http_headerbag_getiterator, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_HeaderBag, count, arginfo_zim_http_headerbag_count, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
