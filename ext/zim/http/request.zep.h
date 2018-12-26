
extern zend_class_entry *zim_http_request_ce;

ZEPHIR_INIT_CLASS(Zim_Http_Request);

PHP_METHOD(Zim_Http_Request, __construct);
PHP_METHOD(Zim_Http_Request, getForwardedFor);
PHP_METHOD(Zim_Http_Request, initialize);
PHP_METHOD(Zim_Http_Request, createFromGlobals);
PHP_METHOD(Zim_Http_Request, create);
PHP_METHOD(Zim_Http_Request, duplicate);
PHP_METHOD(Zim_Http_Request, getUser);
PHP_METHOD(Zim_Http_Request, getPassword);
PHP_METHOD(Zim_Http_Request, getUserInfo);
PHP_METHOD(Zim_Http_Request, isNoCache);
PHP_METHOD(Zim_Http_Request, setFormat);
PHP_METHOD(Zim_Http_Request, getRequestFormat);
PHP_METHOD(Zim_Http_Request, setRequestFormat);
PHP_METHOD(Zim_Http_Request, getContentType);
PHP_METHOD(Zim_Http_Request, getMimeType);
PHP_METHOD(Zim_Http_Request, getMimeTypes);
PHP_METHOD(Zim_Http_Request, getFormat);
PHP_METHOD(Zim_Http_Request, initializeFormats);
PHP_METHOD(Zim_Http_Request, __clone);
PHP_METHOD(Zim_Http_Request, __toString);
PHP_METHOD(Zim_Http_Request, overrideGlobals);
PHP_METHOD(Zim_Http_Request, enableHttpMethodParameterOverride);
PHP_METHOD(Zim_Http_Request, getHttpMethodParameterOverride);
PHP_METHOD(Zim_Http_Request, normalizeQueryString);
PHP_METHOD(Zim_Http_Request, get);
PHP_METHOD(Zim_Http_Request, getPathInfo);
PHP_METHOD(Zim_Http_Request, getScheme);
PHP_METHOD(Zim_Http_Request, isSecure);
PHP_METHOD(Zim_Http_Request, getPort);
PHP_METHOD(Zim_Http_Request, getHttpHost);
PHP_METHOD(Zim_Http_Request, getRequestUri);
PHP_METHOD(Zim_Http_Request, getSchemeAndHttpHost);
PHP_METHOD(Zim_Http_Request, getUri);
PHP_METHOD(Zim_Http_Request, getQueryString);
PHP_METHOD(Zim_Http_Request, getHost);
PHP_METHOD(Zim_Http_Request, getMethod);
PHP_METHOD(Zim_Http_Request, setMethod);
PHP_METHOD(Zim_Http_Request, getRealMethod);
PHP_METHOD(Zim_Http_Request, isMethod);
PHP_METHOD(Zim_Http_Request, getContent);
PHP_METHOD(Zim_Http_Request, prepareRequestUri);
PHP_METHOD(Zim_Http_Request, preparePathInfo);
PHP_METHOD(Zim_Http_Request, getBasePath);
PHP_METHOD(Zim_Http_Request, prepareBasePath);
PHP_METHOD(Zim_Http_Request, getBaseUrl);
PHP_METHOD(Zim_Http_Request, prepareBaseUrl);
PHP_METHOD(Zim_Http_Request, getUrlencodedPrefix);
void zephir_init_static_properties_Zim_Http_Request(TSRMLS_D);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_request___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, query, 0)
	ZEND_ARG_ARRAY_INFO(0, request, 0)
	ZEND_ARG_ARRAY_INFO(0, attributes, 0)
	ZEND_ARG_ARRAY_INFO(0, server, 0)
	ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getforwardedfor, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getforwardedfor, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_request_initialize, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, query, 0)
	ZEND_ARG_ARRAY_INFO(0, request, 0)
	ZEND_ARG_ARRAY_INFO(0, attributes, 0)
	ZEND_ARG_ARRAY_INFO(0, server, 0)
	ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_request_createfromglobals, 0, 0, Zim\\Http\\Request, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_createfromglobals, 0, 0, IS_OBJECT, "Zim\\Http\\Request", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_request_create, 0, 1, Zim\\Http\\Request, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_create, 0, 1, IS_OBJECT, "Zim\\Http\\Request", 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, uri, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, uri)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, method, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, method)
#endif
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
	ZEND_ARG_ARRAY_INFO(0, server, 0)
	ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_request_duplicate, 0, 0, Zim\\Http\\Request, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_duplicate, 0, 0, IS_OBJECT, "Zim\\Http\\Request", 0)
#endif
	ZEND_ARG_ARRAY_INFO(0, query, 0)
	ZEND_ARG_ARRAY_INFO(0, request, 0)
	ZEND_ARG_ARRAY_INFO(0, attributes, 0)
	ZEND_ARG_ARRAY_INFO(0, server, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_request_setformat, 0, 0, 2)
	ZEND_ARG_INFO(0, format)
	ZEND_ARG_INFO(0, mimeTypes)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getrequestformat, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getrequestformat, 0, 0, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_request_setrequestformat, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, format)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_request_getmimetype, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, format)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getmimetypes, 0, 1, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getmimetypes, 0, 1, IS_ARRAY, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, format, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, format)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_request_getformat, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, mimeType, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, mimeType)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request___tostring, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request___tostring, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_normalizequerystring, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_normalizequerystring, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, qs, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, qs)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_request_get, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getpathinfo, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getpathinfo, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getscheme, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getscheme, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_gethttphost, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_gethttphost, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getrequesturi, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getrequesturi, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getschemeandhttphost, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getschemeandhttphost, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_geturi, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_geturi, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_gethost, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_gethost, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getmethod, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getmethod, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_request_setmethod, 0, 0, 1)
	ZEND_ARG_INFO(0, method)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getrealmethod, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_getrealmethod, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_ismethod, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_ismethod, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, method, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, method)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_request_getcontent, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, asResource, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, asResource)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_preparepathinfo, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_request_preparepathinfo, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_request_geturlencodedprefix, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, str)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, prefix, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, prefix)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_request_method_entry) {
	PHP_ME(Zim_Http_Request, __construct, arginfo_zim_http_request___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Http_Request, getForwardedFor, arginfo_zim_http_request_getforwardedfor, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, initialize, arginfo_zim_http_request_initialize, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, createFromGlobals, arginfo_zim_http_request_createfromglobals, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_Request, create, arginfo_zim_http_request_create, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_Request, duplicate, arginfo_zim_http_request_duplicate, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getUser, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getPassword, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getUserInfo, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, isNoCache, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, setFormat, arginfo_zim_http_request_setformat, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getRequestFormat, arginfo_zim_http_request_getrequestformat, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, setRequestFormat, arginfo_zim_http_request_setrequestformat, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getContentType, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getMimeType, arginfo_zim_http_request_getmimetype, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getMimeTypes, arginfo_zim_http_request_getmimetypes, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_Request, getFormat, arginfo_zim_http_request_getformat, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, initializeFormats, NULL, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_Request, __clone, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, __toString, arginfo_zim_http_request___tostring, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, overrideGlobals, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, enableHttpMethodParameterOverride, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_Request, getHttpMethodParameterOverride, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_Request, normalizeQueryString, arginfo_zim_http_request_normalizequerystring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_Request, get, arginfo_zim_http_request_get, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getPathInfo, arginfo_zim_http_request_getpathinfo, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getScheme, arginfo_zim_http_request_getscheme, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, isSecure, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getPort, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getHttpHost, arginfo_zim_http_request_gethttphost, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getRequestUri, arginfo_zim_http_request_getrequesturi, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getSchemeAndHttpHost, arginfo_zim_http_request_getschemeandhttphost, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getUri, arginfo_zim_http_request_geturi, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getQueryString, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getHost, arginfo_zim_http_request_gethost, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getMethod, arginfo_zim_http_request_getmethod, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, setMethod, arginfo_zim_http_request_setmethod, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getRealMethod, arginfo_zim_http_request_getrealmethod, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, isMethod, arginfo_zim_http_request_ismethod, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, getContent, arginfo_zim_http_request_getcontent, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, prepareRequestUri, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_Request, preparePathInfo, arginfo_zim_http_request_preparepathinfo, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_Request, getBasePath, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, prepareBasePath, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_Request, getBaseUrl, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Request, prepareBaseUrl, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_Request, getUrlencodedPrefix, arginfo_zim_http_request_geturlencodedprefix, ZEND_ACC_PRIVATE)
	PHP_FE_END
};
