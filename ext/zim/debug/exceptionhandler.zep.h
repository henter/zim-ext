
extern zend_class_entry *zim_debug_exceptionhandler_ce;

ZEPHIR_INIT_CLASS(Zim_Debug_ExceptionHandler);

PHP_METHOD(Zim_Debug_ExceptionHandler, __construct);
PHP_METHOD(Zim_Debug_ExceptionHandler, register);
PHP_METHOD(Zim_Debug_ExceptionHandler, handle);
PHP_METHOD(Zim_Debug_ExceptionHandler, sendPhpResponse);
PHP_METHOD(Zim_Debug_ExceptionHandler, getContent);
PHP_METHOD(Zim_Debug_ExceptionHandler, getStylesheet);
PHP_METHOD(Zim_Debug_ExceptionHandler, decorate);
PHP_METHOD(Zim_Debug_ExceptionHandler, formatClass);
PHP_METHOD(Zim_Debug_ExceptionHandler, formatPath);
PHP_METHOD(Zim_Debug_ExceptionHandler, formatArgs);
PHP_METHOD(Zim_Debug_ExceptionHandler, escapeHtml);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_exceptionhandler___construct, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, debug, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, debug)
#endif
	ZEND_ARG_INFO(0, fileLinkFormat)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_debug_exceptionhandler_register, 0, 0, Zim\\Debug\\ExceptionHandler, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_exceptionhandler_register, 0, 0, IS_OBJECT, "Zim\\Debug\\ExceptionHandler", 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, debug, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, debug)
#endif
	ZEND_ARG_INFO(0, fileLinkFormat)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_exceptionhandler_handle, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, exception, Zim\\Debug\\Exception, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_exceptionhandler_sendphpresponse, 0, 0, 1)
	ZEND_ARG_INFO(0, exception)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_exceptionhandler_getcontent, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_exceptionhandler_getcontent, 0, 1, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_OBJ_INFO(0, exception, Zim\\Debug\\FlattenException, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_exceptionhandler_getstylesheet, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_exceptionhandler_getstylesheet, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_exceptionhandler_decorate, 0, 0, 2)
	ZEND_ARG_INFO(0, content)
	ZEND_ARG_INFO(0, css)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_exceptionhandler_formatclass, 0, 0, 1)
	ZEND_ARG_INFO(0, classs)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_exceptionhandler_formatpath, 0, 0, 2)
	ZEND_ARG_INFO(0, path)
	ZEND_ARG_INFO(0, line)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_exceptionhandler_formatargs, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_debug_exceptionhandler_formatargs, 0, 1, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_ARRAY_INFO(0, args, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_exceptionhandler_escapehtml, 0, 0, 1)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_debug_exceptionhandler_method_entry) {
	PHP_ME(Zim_Debug_ExceptionHandler, __construct, arginfo_zim_debug_exceptionhandler___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Debug_ExceptionHandler, register, arginfo_zim_debug_exceptionhandler_register, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Debug_ExceptionHandler, handle, arginfo_zim_debug_exceptionhandler_handle, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_ExceptionHandler, sendPhpResponse, arginfo_zim_debug_exceptionhandler_sendphpresponse, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_ExceptionHandler, getContent, arginfo_zim_debug_exceptionhandler_getcontent, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_ExceptionHandler, getStylesheet, arginfo_zim_debug_exceptionhandler_getstylesheet, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_ExceptionHandler, decorate, arginfo_zim_debug_exceptionhandler_decorate, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Debug_ExceptionHandler, formatClass, arginfo_zim_debug_exceptionhandler_formatclass, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Debug_ExceptionHandler, formatPath, arginfo_zim_debug_exceptionhandler_formatpath, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Debug_ExceptionHandler, formatArgs, arginfo_zim_debug_exceptionhandler_formatargs, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Debug_ExceptionHandler, escapeHtml, arginfo_zim_debug_exceptionhandler_escapehtml, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
