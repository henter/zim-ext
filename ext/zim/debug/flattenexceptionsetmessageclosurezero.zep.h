
extern zend_class_entry *zim_debug_flattenexceptionsetmessageclosurezero_ce;

ZEPHIR_INIT_CLASS(Zim_Debug_FlattenExceptionsetMessageClosureZero);

PHP_METHOD(Zim_Debug_FlattenExceptionsetMessageClosureZero, __construct);
PHP_METHOD(Zim_Debug_FlattenExceptionsetMessageClosureZero, __invoke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexceptionsetmessageclosurezero___invoke, 0, 0, 1)
	ZEND_ARG_INFO(0, m)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_debug_flattenexceptionsetmessageclosurezero_method_entry) {
	PHP_ME(Zim_Debug_FlattenExceptionsetMessageClosureZero, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Debug_FlattenExceptionsetMessageClosureZero, __invoke, arginfo_zim_debug_flattenexceptionsetmessageclosurezero___invoke, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
