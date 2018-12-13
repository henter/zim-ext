
extern zend_class_entry *zim_contract_request_ce;

ZEPHIR_INIT_CLASS(Zim_Contract_Request);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getrequestformat, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getrequestformat, 0, 0, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_contract_request_getmimetype, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, format)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getmimetypes, 0, 1, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getmimetypes, 0, 1, IS_ARRAY, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, format)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_contract_request_get, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getpathinfo, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getpathinfo, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getscheme, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getscheme, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getrequesturi, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getrequesturi, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_geturi, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_geturi, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_gethost, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_gethost, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getmethod, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_getmethod, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_ismethod, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_request_ismethod, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, method, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, method)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_contract_request_getcontent, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, asResource, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, asResource)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_contract_request_method_entry) {
	PHP_ABSTRACT_ME(Zim_Contract_Request, getRequestFormat, arginfo_zim_contract_request_getrequestformat)
	PHP_ABSTRACT_ME(Zim_Contract_Request, getMimeType, arginfo_zim_contract_request_getmimetype)
	ZEND_FENTRY(getMimeTypes, NULL, arginfo_zim_contract_request_getmimetypes, ZEND_ACC_STATIC|ZEND_ACC_ABSTRACT|ZEND_ACC_PUBLIC)
	PHP_ABSTRACT_ME(Zim_Contract_Request, get, arginfo_zim_contract_request_get)
	PHP_ABSTRACT_ME(Zim_Contract_Request, getPathInfo, arginfo_zim_contract_request_getpathinfo)
	PHP_ABSTRACT_ME(Zim_Contract_Request, getScheme, arginfo_zim_contract_request_getscheme)
	PHP_ABSTRACT_ME(Zim_Contract_Request, isSecure, NULL)
	PHP_ABSTRACT_ME(Zim_Contract_Request, getRequestUri, arginfo_zim_contract_request_getrequesturi)
	PHP_ABSTRACT_ME(Zim_Contract_Request, getUri, arginfo_zim_contract_request_geturi)
	PHP_ABSTRACT_ME(Zim_Contract_Request, getQueryString, NULL)
	PHP_ABSTRACT_ME(Zim_Contract_Request, getHost, arginfo_zim_contract_request_gethost)
	PHP_ABSTRACT_ME(Zim_Contract_Request, getMethod, arginfo_zim_contract_request_getmethod)
	PHP_ABSTRACT_ME(Zim_Contract_Request, isMethod, arginfo_zim_contract_request_ismethod)
	PHP_ABSTRACT_ME(Zim_Contract_Request, getContent, arginfo_zim_contract_request_getcontent)
	PHP_FE_END
};
