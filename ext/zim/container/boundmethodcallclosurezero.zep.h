
extern zend_class_entry *zim_container_boundmethodcallclosurezero_ce;

ZEPHIR_INIT_CLASS(Zim_Container_BoundMethodcallClosureZero);

PHP_METHOD(Zim_Container_BoundMethodcallClosureZero, __construct);
PHP_METHOD(Zim_Container_BoundMethodcallClosureZero, __invoke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_boundmethodcallclosurezero___construct, 0, 0, 3)
	ZEND_ARG_INFO(0, container)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, parameters)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_container_boundmethodcallclosurezero_method_entry) {
	PHP_ME(Zim_Container_BoundMethodcallClosureZero, __construct, arginfo_zim_container_boundmethodcallclosurezero___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Container_BoundMethodcallClosureZero, __invoke, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
