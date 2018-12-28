
extern zend_class_entry *zim_debug_handler_ce;

ZEPHIR_INIT_CLASS(Zim_Debug_Handler);

PHP_METHOD(Zim_Debug_Handler, __construct);
PHP_METHOD(Zim_Debug_Handler, getInstance);
PHP_METHOD(Zim_Debug_Handler, register);
PHP_METHOD(Zim_Debug_Handler, handleShutdown);
PHP_METHOD(Zim_Debug_Handler, isFatal);
PHP_METHOD(Zim_Debug_Handler, handleError);
PHP_METHOD(Zim_Debug_Handler, handleException);
PHP_METHOD(Zim_Debug_Handler, sendPhpResponse);
PHP_METHOD(Zim_Debug_Handler, getHtml);
PHP_METHOD(Zim_Debug_Handler, getContent);
PHP_METHOD(Zim_Debug_Handler, getStylesheet);
PHP_METHOD(Zim_Debug_Handler, decorate);
PHP_METHOD(Zim_Debug_Handler, formatClass);
PHP_METHOD(Zim_Debug_Handler, formatPath);
PHP_METHOD(Zim_Debug_Handler, formatArgs);
PHP_METHOD(Zim_Debug_Handler, escapeHtml);
zend_object *zephir_init_properties_Zim_Debug_Handler(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_handler___construct, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, debug, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, debug)
#endif
	ZEND_ARG_INFO(0, fileLinkFormat)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_debug_handler_register, 0, 0, Zim\\Debug\\ExceptionHandler, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_handler_register, 0, 0, IS_OBJECT, "Zim\\Debug\\ExceptionHandler", 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, debug, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, debug)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, fileLinkFormat, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, fileLinkFormat)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_handler_isfatal, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, type)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_handler_handleerror, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, level)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, message, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, message)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 1)
#else
	ZEND_ARG_INFO(0, file)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, line, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, line)
#endif
	ZEND_ARG_ARRAY_INFO(0, context, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_handler_handleexception, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, exception, Throwable, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_handler_sendphpresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, exception)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_handler_gethtml, 0, 0, 1)
	ZEND_ARG_INFO(0, exception)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_handler_getcontent, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_handler_getcontent, 0, 1, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_OBJ_INFO(0, exception, Zim\\Debug\\FlattenException, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_handler_getstylesheet, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_handler_getstylesheet, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_handler_decorate, 0, 2, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_handler_decorate, 0, 2, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, content, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, content)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, css, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, css)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_handler_formatclass, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, classs, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, classs)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_handler_formatpath, 0, 0, 2)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, line)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_handler_formatargs, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_handler_formatargs, 0, 1, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_ARRAY_INFO(0, args, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_handler_escapehtml, 0, 0, 1)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_debug_handler_method_entry) {
	PHP_ME(Zim_Debug_Handler, __construct, arginfo_zim_debug_handler___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Debug_Handler, getInstance, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Debug_Handler, register, arginfo_zim_debug_handler_register, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Debug_Handler, handleShutdown, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_Handler, isFatal, arginfo_zim_debug_handler_isfatal, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Debug_Handler, handleError, arginfo_zim_debug_handler_handleerror, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_Handler, handleException, arginfo_zim_debug_handler_handleexception, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_Handler, sendPhpResponse, arginfo_zim_debug_handler_sendphpresponse, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_Handler, getHtml, arginfo_zim_debug_handler_gethtml, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_Handler, getContent, arginfo_zim_debug_handler_getcontent, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_Handler, getStylesheet, arginfo_zim_debug_handler_getstylesheet, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_Handler, decorate, arginfo_zim_debug_handler_decorate, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Debug_Handler, formatClass, arginfo_zim_debug_handler_formatclass, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Debug_Handler, formatPath, arginfo_zim_debug_handler_formatpath, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Debug_Handler, formatArgs, arginfo_zim_debug_handler_formatargs, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Debug_Handler, escapeHtml, arginfo_zim_debug_handler_escapehtml, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
