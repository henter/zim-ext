
extern zend_class_entry *zim_debug_fatalerrorexception_ce;

ZEPHIR_INIT_CLASS(Zim_Debug_FatalErrorException);

PHP_METHOD(Zim_Debug_FatalErrorException, __construct);
PHP_METHOD(Zim_Debug_FatalErrorException, getOriginalClassName);
PHP_METHOD(Zim_Debug_FatalErrorException, setTrace);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_fatalerrorexception___construct, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, e, Zim\\Debug\\Throwable, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_fatalerrorexception_settrace, 0, 0, 1)
	ZEND_ARG_INFO(0, trace)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_debug_fatalerrorexception_method_entry) {
	PHP_ME(Zim_Debug_FatalErrorException, __construct, arginfo_zim_debug_fatalerrorexception___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Debug_FatalErrorException, getOriginalClassName, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FatalErrorException, setTrace, arginfo_zim_debug_fatalerrorexception_settrace, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
