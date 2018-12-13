
extern zend_class_entry *zim_http_action_ce;

ZEPHIR_INIT_CLASS(Zim_Http_Action);

PHP_METHOD(Zim_Http_Action, execute);

ZEPHIR_INIT_FUNCS(zim_http_action_method_entry) {
	PHP_ME(Zim_Http_Action, execute, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
