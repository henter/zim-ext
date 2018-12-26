
extern zend_class_entry *zim_contract_arrayable_ce;

ZEPHIR_INIT_CLASS(Zim_Contract_Arrayable);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_arrayable_toarray, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_arrayable_toarray, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_contract_arrayable_method_entry) {
	PHP_ABSTRACT_ME(Zim_Contract_Arrayable, toArray, arginfo_zim_contract_arrayable_toarray)
	PHP_FE_END
};
