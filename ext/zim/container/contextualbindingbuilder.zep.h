
extern zend_class_entry *zim_container_contextualbindingbuilder_ce;

ZEPHIR_INIT_CLASS(Zim_Container_ContextualBindingBuilder);

PHP_METHOD(Zim_Container_ContextualBindingBuilder, __construct);
PHP_METHOD(Zim_Container_ContextualBindingBuilder, needs);
PHP_METHOD(Zim_Container_ContextualBindingBuilder, give);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_contextualbindingbuilder___construct, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, container, Zim\\Container\\Container, 0)
	ZEND_ARG_INFO(0, concrete)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_contextualbindingbuilder_needs, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, abstractt, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, abstractt)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_contextualbindingbuilder_give, 0, 0, 1)
	ZEND_ARG_INFO(0, implementation)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_container_contextualbindingbuilder_method_entry) {
	PHP_ME(Zim_Container_ContextualBindingBuilder, __construct, arginfo_zim_container_contextualbindingbuilder___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Container_ContextualBindingBuilder, needs, arginfo_zim_container_contextualbindingbuilder_needs, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_ContextualBindingBuilder, give, arginfo_zim_container_contextualbindingbuilder_give, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
