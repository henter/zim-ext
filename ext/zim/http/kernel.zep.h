
extern zend_class_entry *zim_http_kernel_ce;

ZEPHIR_INIT_CLASS(Zim_Http_Kernel);

PHP_METHOD(Zim_Http_Kernel, __construct);
PHP_METHOD(Zim_Http_Kernel, bootstrapRoutes);
PHP_METHOD(Zim_Http_Kernel, handle);
PHP_METHOD(Zim_Http_Kernel, handleException);
PHP_METHOD(Zim_Http_Kernel, guessController);
PHP_METHOD(Zim_Http_Kernel, getDefaultRoute);
PHP_METHOD(Zim_Http_Kernel, dispatchToDefault);
PHP_METHOD(Zim_Http_Kernel, dispatchToRouter);
PHP_METHOD(Zim_Http_Kernel, doDispatch);
PHP_METHOD(Zim_Http_Kernel, toResponse);
PHP_METHOD(Zim_Http_Kernel, shouldBeJson);
PHP_METHOD(Zim_Http_Kernel, terminate);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_kernel___construct, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, zim, Zim\\Zim, 0)
	ZEND_ARG_OBJ_INFO(0, router, Zim\\Routing\\Router, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_kernel_handle, 0, 1, Zim\\Http\\Response, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_kernel_handle, 0, 1, IS_OBJECT, "Zim\\Http\\Response", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Http\\Request, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_kernel_handleexception, 0, 2, Zim\\Http\\Response, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_kernel_handleexception, 0, 2, IS_OBJECT, "Zim\\Http\\Response", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, e, Throwable, 0)
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Http\\Request, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_kernel_guesscontroller, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, uri, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, uri)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_kernel_getdefaultroute, 0, 1, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_kernel_getdefaultroute, 0, 1, IS_ARRAY, NULL, 0)
#endif
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Http\\Request, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_kernel_dispatchtodefault, 0, 1, Zim\\Http\\Response, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_kernel_dispatchtodefault, 0, 1, IS_OBJECT, "Zim\\Http\\Response", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Http\\Request, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_kernel_dispatchtorouter, 0, 1, Zim\\Http\\Response, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_kernel_dispatchtorouter, 0, 1, IS_OBJECT, "Zim\\Http\\Response", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Http\\Request, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_http_kernel_dodispatch, 0, 2, Zim\\Http\\Response, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_http_kernel_dodispatch, 0, 2, IS_OBJECT, "Zim\\Http\\Response", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Http\\Request, 0)
	ZEND_ARG_INFO(0, call)
	ZEND_ARG_ARRAY_INFO(0, params, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_kernel_toresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, resp)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_kernel_shouldbejson, 0, 0, 1)
	ZEND_ARG_INFO(0, content)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_http_kernel_terminate, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Http\\Request, 0)
	ZEND_ARG_OBJ_INFO(0, response, Zim\\Http\\Response, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_http_kernel_method_entry) {
	PHP_ME(Zim_Http_Kernel, __construct, arginfo_zim_http_kernel___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Http_Kernel, bootstrapRoutes, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_Kernel, handle, arginfo_zim_http_kernel_handle, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Kernel, handleException, arginfo_zim_http_kernel_handleexception, ZEND_ACC_PRIVATE)
	PHP_ME(Zim_Http_Kernel, guessController, arginfo_zim_http_kernel_guesscontroller, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_Kernel, getDefaultRoute, arginfo_zim_http_kernel_getdefaultroute, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_Kernel, dispatchToDefault, arginfo_zim_http_kernel_dispatchtodefault, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Kernel, dispatchToRouter, arginfo_zim_http_kernel_dispatchtorouter, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Http_Kernel, doDispatch, arginfo_zim_http_kernel_dodispatch, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_Kernel, toResponse, arginfo_zim_http_kernel_toresponse, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_Kernel, shouldBeJson, arginfo_zim_http_kernel_shouldbejson, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Http_Kernel, terminate, arginfo_zim_http_kernel_terminate, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
