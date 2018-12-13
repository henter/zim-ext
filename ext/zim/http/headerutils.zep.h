
extern zend_class_entry *zim_http_headerutils_ce;

ZEPHIR_INIT_CLASS(Zim_Http_HeaderUtils);

PHP_METHOD(Zim_Http_HeaderUtils, __construct);
PHP_METHOD(Zim_Http_HeaderUtils, split);
PHP_METHOD(Zim_Http_HeaderUtils, combine);
PHP_METHOD(Zim_Http_HeaderUtils, toString);
PHP_METHOD(Zim_Http_HeaderUtils, quote);
PHP_METHOD(Zim_Http_HeaderUtils, unquote);
PHP_METHOD(Zim_Http_HeaderUtils, groupParts);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerutils_split, 0, 2, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_headerutils_split, 0, 2, IS_ARRAY, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, header, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, header)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, separators, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, separators)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerutils_combine, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, parts, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerutils_tostring, 0, 0, 2)
	ZEND_ARG_ARRAY_INFO(0, assoc, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, separator, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, separator)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerutils_quote, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, s, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, s)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerutils_unquote, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, s, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, s)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_headerutils_groupparts, 0, 0, 2)
	ZEND_ARG_ARRAY_INFO(0, tmpmatches, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, separators, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, separators)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_headerutils_method_entry) {
	PHP_ME(Zim_Http_HeaderUtils, __construct, NULL, ZEND_ACC_PROTECTED|ZEND_ACC_CTOR)
	PHP_ME(Zim_Http_HeaderUtils, split, arginfo_zim_http_headerutils_split, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_HeaderUtils, combine, arginfo_zim_http_headerutils_combine, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_HeaderUtils, toString, arginfo_zim_http_headerutils_tostring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_HeaderUtils, quote, arginfo_zim_http_headerutils_quote, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_HeaderUtils, unquote, arginfo_zim_http_headerutils_unquote, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_HeaderUtils, groupParts, arginfo_zim_http_headerutils_groupparts, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_FE_END
};
