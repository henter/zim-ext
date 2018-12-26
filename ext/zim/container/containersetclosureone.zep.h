
extern zend_class_entry *zim_container_containersetclosureone_ce;

ZEPHIR_INIT_CLASS(Zim_Container_ContainersetClosureOne);

PHP_METHOD(Zim_Container_ContainersetClosureOne, __construct);
PHP_METHOD(Zim_Container_ContainersetClosureOne, __invoke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_containersetclosureone___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_container_containersetclosureone_method_entry) {
	PHP_ME(Zim_Container_ContainersetClosureOne, __construct, arginfo_zim_container_containersetclosureone___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Container_ContainersetClosureOne, __invoke, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
