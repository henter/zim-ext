
extern zend_class_entry *zim_container_containergetclosureclosurezero_ce;

ZEPHIR_INIT_CLASS(Zim_Container_ContainergetClosureClosureZero);

PHP_METHOD(Zim_Container_ContainergetClosureClosureZero, __construct);
PHP_METHOD(Zim_Container_ContainergetClosureClosureZero, __invoke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_containergetclosureclosurezero___construct, 0, 0, 2)
	ZEND_ARG_INFO(0, abstractt)
	ZEND_ARG_INFO(0, concrete)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_containergetclosureclosurezero___invoke, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, container, Zim\\Container\\Container, 0)
	ZEND_ARG_INFO(0, parameters)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_container_containergetclosureclosurezero_method_entry) {
	PHP_ME(Zim_Container_ContainergetClosureClosureZero, __construct, arginfo_zim_container_containergetclosureclosurezero___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Container_ContainergetClosureClosureZero, __invoke, arginfo_zim_container_containergetclosureclosurezero___invoke, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
