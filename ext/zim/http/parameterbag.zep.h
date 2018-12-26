
extern zend_class_entry *zim_http_parameterbag_ce;

ZEPHIR_INIT_CLASS(Zim_Http_ParameterBag);

PHP_METHOD(Zim_Http_ParameterBag, __construct);
PHP_METHOD(Zim_Http_ParameterBag, all);
PHP_METHOD(Zim_Http_ParameterBag, keys);
PHP_METHOD(Zim_Http_ParameterBag, replace);
PHP_METHOD(Zim_Http_ParameterBag, add);
PHP_METHOD(Zim_Http_ParameterBag, get);
PHP_METHOD(Zim_Http_ParameterBag, set);
PHP_METHOD(Zim_Http_ParameterBag, has);
PHP_METHOD(Zim_Http_ParameterBag, remove);
PHP_METHOD(Zim_Http_ParameterBag, getAlpha);
PHP_METHOD(Zim_Http_ParameterBag, getAlnum);
PHP_METHOD(Zim_Http_ParameterBag, getDigits);
PHP_METHOD(Zim_Http_ParameterBag, getInt);
PHP_METHOD(Zim_Http_ParameterBag, getBoolean);
PHP_METHOD(Zim_Http_ParameterBag, filter);
PHP_METHOD(Zim_Http_ParameterBag, getIterator);
PHP_METHOD(Zim_Http_ParameterBag, count);
zend_object *zephir_init_properties_Zim_Http_ParameterBag(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_parameterbag_all, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_parameterbag_all, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_parameterbag_keys, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_parameterbag_keys, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_replace, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_add, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_get, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_set, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_parameterbag_has, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_parameterbag_has, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_remove, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_getalpha, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_getalnum, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_getdigits, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_getint, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_getboolean, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_parameterbag_filter, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, filter, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, filter)
#endif
	ZEND_ARG_INFO(0, options)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_parameterbag_getiterator, 0, 0, ArrayIterator, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_parameterbag_getiterator, 0, 0, IS_OBJECT, "ArrayIterator", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_parameterbag_count, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_parameterbag_count, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_parameterbag_method_entry) {
	PHP_ME(Zim_Http_ParameterBag, __construct, arginfo_zim_http_parameterbag___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Http_ParameterBag, all, arginfo_zim_http_parameterbag_all, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, keys, arginfo_zim_http_parameterbag_keys, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, replace, arginfo_zim_http_parameterbag_replace, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, add, arginfo_zim_http_parameterbag_add, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, get, arginfo_zim_http_parameterbag_get, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, set, arginfo_zim_http_parameterbag_set, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, has, arginfo_zim_http_parameterbag_has, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, remove, arginfo_zim_http_parameterbag_remove, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, getAlpha, arginfo_zim_http_parameterbag_getalpha, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, getAlnum, arginfo_zim_http_parameterbag_getalnum, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, getDigits, arginfo_zim_http_parameterbag_getdigits, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, getInt, arginfo_zim_http_parameterbag_getint, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, getBoolean, arginfo_zim_http_parameterbag_getboolean, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, filter, arginfo_zim_http_parameterbag_filter, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, getIterator, arginfo_zim_http_parameterbag_getiterator, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_ParameterBag, count, arginfo_zim_http_parameterbag_count, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
