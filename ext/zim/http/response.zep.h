
extern zend_class_entry *zim_http_response_ce;

ZEPHIR_INIT_CLASS(Zim_Http_Response);

PHP_METHOD(Zim_Http_Response, __construct);
PHP_METHOD(Zim_Http_Response, create);
PHP_METHOD(Zim_Http_Response, __toString);
PHP_METHOD(Zim_Http_Response, __clone);
PHP_METHOD(Zim_Http_Response, prepare);
PHP_METHOD(Zim_Http_Response, sendHeaders);
PHP_METHOD(Zim_Http_Response, sendContent);
PHP_METHOD(Zim_Http_Response, send);
PHP_METHOD(Zim_Http_Response, setContent);
PHP_METHOD(Zim_Http_Response, getContent);
PHP_METHOD(Zim_Http_Response, setProtocolVersion);
PHP_METHOD(Zim_Http_Response, getProtocolVersion);
PHP_METHOD(Zim_Http_Response, setStatusCode);
PHP_METHOD(Zim_Http_Response, getStatusCode);
PHP_METHOD(Zim_Http_Response, setCharset);
PHP_METHOD(Zim_Http_Response, getCharset);
PHP_METHOD(Zim_Http_Response, isInvalid);
PHP_METHOD(Zim_Http_Response, isInformational);
PHP_METHOD(Zim_Http_Response, isSuccessful);
PHP_METHOD(Zim_Http_Response, isRedirection);
PHP_METHOD(Zim_Http_Response, isClientError);
PHP_METHOD(Zim_Http_Response, isServerError);
PHP_METHOD(Zim_Http_Response, isOk);
PHP_METHOD(Zim_Http_Response, isForbidden);
PHP_METHOD(Zim_Http_Response, isNotFound);
PHP_METHOD(Zim_Http_Response, isRedirect);
PHP_METHOD(Zim_Http_Response, isEmpty);
void zephir_init_static_properties_Zim_Http_Response(TSRMLS_D);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_response___construct, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, content, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, content)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, status, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, status)
#endif
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_response_create, 0, 0, Zim\\Http\\Response, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_response_create, 0, 0, IS_OBJECT, "Zim\\Http\\Response", 0)
#endif
	ZEND_ARG_INFO(0, content)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, status, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, status)
#endif
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_response___tostring, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_response___tostring, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_response_prepare, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Http\\Zim\\Contract\\Request, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_response_setcontent, 0, 0, 1)
	ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_response_getcontent, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_response_getcontent, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_response_setprotocolversion, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, version, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, version)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_response_setstatuscode, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, code, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, code)
#endif
	ZEND_ARG_INFO(0, text)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_response_setcharset, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, charset, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, charset)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_response_isredirect, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, location, IS_STRING, 1)
#else
	ZEND_ARG_INFO(0, location)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_response_method_entry) {
	PHP_ME(Zim_Http_Response, __construct, arginfo_zim_http_response___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Http_Response, create, arginfo_zim_http_response_create, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_Response, __toString, arginfo_zim_http_response___tostring, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, __clone, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, prepare, arginfo_zim_http_response_prepare, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, sendHeaders, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, sendContent, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, send, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, setContent, arginfo_zim_http_response_setcontent, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, getContent, arginfo_zim_http_response_getcontent, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, setProtocolVersion, arginfo_zim_http_response_setprotocolversion, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, getProtocolVersion, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, setStatusCode, arginfo_zim_http_response_setstatuscode, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, getStatusCode, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, setCharset, arginfo_zim_http_response_setcharset, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, getCharset, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isInvalid, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isInformational, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isSuccessful, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isRedirection, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isClientError, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isServerError, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isOk, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isForbidden, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isNotFound, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isRedirect, arginfo_zim_http_response_isredirect, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Response, isEmpty, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
