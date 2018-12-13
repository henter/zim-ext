
extern zend_class_entry *zim_contract_response_ce;

ZEPHIR_INIT_CLASS(Zim_Contract_Response);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_contract_response_prepare, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Contract\\Request, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_contract_response_method_entry) {
	PHP_ABSTRACT_ME(Zim_Contract_Response, prepare, arginfo_zim_contract_response_prepare)
	PHP_FE_END
};
