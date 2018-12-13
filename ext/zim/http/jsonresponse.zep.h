
extern zend_class_entry *zim_http_jsonresponse_ce;

ZEPHIR_INIT_CLASS(Zim_Http_JsonResponse);

PHP_METHOD(Zim_Http_JsonResponse, __construct);
PHP_METHOD(Zim_Http_JsonResponse, create);
PHP_METHOD(Zim_Http_JsonResponse, fromJsonString);
PHP_METHOD(Zim_Http_JsonResponse, setCallback);
PHP_METHOD(Zim_Http_JsonResponse, setJson);
PHP_METHOD(Zim_Http_JsonResponse, setData);
PHP_METHOD(Zim_Http_JsonResponse, getEncodingOptions);
PHP_METHOD(Zim_Http_JsonResponse, setEncodingOptions);
PHP_METHOD(Zim_Http_JsonResponse, update);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_jsonresponse___construct, 0, 0, 0)
	ZEND_ARG_INFO(0, data)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, status, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, status)
#endif
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, json, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, json)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_jsonresponse_create, 0, 0, 0)
	ZEND_ARG_INFO(0, data)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, status, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, status)
#endif
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_jsonresponse_fromjsonstring, 0, 0, 0)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, status)
	ZEND_ARG_INFO(0, headers)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_jsonresponse_setcallback, 0, 0, 0)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_jsonresponse_setjson, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, json, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, json)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_jsonresponse_setdata, 0, 0, 0)
	ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_jsonresponse_getencodingoptions, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_jsonresponse_getencodingoptions, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_jsonresponse_setencodingoptions, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, encodingOptions, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, encodingOptions)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_jsonresponse_method_entry) {
	PHP_ME(Zim_Http_JsonResponse, __construct, arginfo_zim_http_jsonresponse___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Http_JsonResponse, create, arginfo_zim_http_jsonresponse_create, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_JsonResponse, fromJsonString, arginfo_zim_http_jsonresponse_fromjsonstring, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Http_JsonResponse, setCallback, arginfo_zim_http_jsonresponse_setcallback, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_JsonResponse, setJson, arginfo_zim_http_jsonresponse_setjson, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_JsonResponse, setData, arginfo_zim_http_jsonresponse_setdata, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_JsonResponse, getEncodingOptions, arginfo_zim_http_jsonresponse_getencodingoptions, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_JsonResponse, setEncodingOptions, arginfo_zim_http_jsonresponse_setencodingoptions, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_JsonResponse, update, NULL, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
