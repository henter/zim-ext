
extern zend_class_entry *zim_contract_action_ce;

ZEPHIR_INIT_CLASS(Zim_Contract_Action);

ZEPHIR_INIT_FUNCS(zim_contract_action_method_entry) {
	PHP_ABSTRACT_ME(Zim_Contract_Action, execute, NULL)
	PHP_FE_END
};
