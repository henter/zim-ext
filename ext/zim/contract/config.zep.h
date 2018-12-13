
extern zend_class_entry *zim_contract_config_ce;

ZEPHIR_INIT_CLASS(Zim_Contract_Config);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_config_has, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_config_has, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_contract_config_get, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_config_all, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_config_all, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_contract_config_set, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_contract_config_prepend, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_contract_config_push, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_contract_config_method_entry) {
	PHP_ABSTRACT_ME(Zim_Contract_Config, has, arginfo_zim_contract_config_has)
	PHP_ABSTRACT_ME(Zim_Contract_Config, get, arginfo_zim_contract_config_get)
	PHP_ABSTRACT_ME(Zim_Contract_Config, all, arginfo_zim_contract_config_all)
	PHP_ABSTRACT_ME(Zim_Contract_Config, set, arginfo_zim_contract_config_set)
	PHP_ABSTRACT_ME(Zim_Contract_Config, prepend, arginfo_zim_contract_config_prepend)
	PHP_ABSTRACT_ME(Zim_Contract_Config, push, arginfo_zim_contract_config_push)
	PHP_FE_END
};
