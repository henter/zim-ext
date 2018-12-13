
extern zend_class_entry *zim_debug_errorhandler_ce;

ZEPHIR_INIT_CLASS(Zim_Debug_ErrorHandler);

PHP_METHOD(Zim_Debug_ErrorHandler, register);
PHP_METHOD(Zim_Debug_ErrorHandler, __construct);
PHP_METHOD(Zim_Debug_ErrorHandler, setExceptionHandler);
PHP_METHOD(Zim_Debug_ErrorHandler, handleError);
PHP_METHOD(Zim_Debug_ErrorHandler, handleException);
zend_object *zephir_init_properties_Zim_Debug_ErrorHandler(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_errorhandler_register, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, handler, Zim\\Debug\\self, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_errorhandler_setexceptionhandler, 0, 0, 0)
	ZEND_ARG_INFO(0, handler)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_errorhandler_handleerror, 0, 0, 4)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, type)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, message, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, message)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, file)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, line, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, line)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_errorhandler_handleexception, 0, 0, 1)
	ZEND_ARG_INFO(0, exception)
	ZEND_ARG_ARRAY_INFO(0, error, 1)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_debug_errorhandler_method_entry) {
	PHP_ME(Zim_Debug_ErrorHandler, register, arginfo_zim_debug_errorhandler_register, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Debug_ErrorHandler, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Debug_ErrorHandler, setExceptionHandler, arginfo_zim_debug_errorhandler_setexceptionhandler, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_ErrorHandler, handleError, arginfo_zim_debug_errorhandler_handleerror, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_ErrorHandler, handleException, arginfo_zim_debug_errorhandler_handleexception, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
