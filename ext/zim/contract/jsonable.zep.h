
extern zend_class_entry *zim_contract_jsonable_ce;

ZEPHIR_INIT_CLASS(Zim_Contract_Jsonable);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_jsonable_tojson, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_contract_jsonable_tojson, 0, 0, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, options, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, options)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_contract_jsonable_method_entry) {
	PHP_ABSTRACT_ME(Zim_Contract_Jsonable, toJson, arginfo_zim_contract_jsonable_tojson)
	PHP_FE_END
};
