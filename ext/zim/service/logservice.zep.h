
extern zend_class_entry *zim_service_logservice_ce;

ZEPHIR_INIT_CLASS(Zim_Service_LogService);

PHP_METHOD(Zim_Service_LogService, boot);
PHP_METHOD(Zim_Service_LogService, register);

ZEPHIR_INIT_FUNCS(zim_service_logservice_method_entry) {
	PHP_ME(Zim_Service_LogService, boot, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Service_LogService, register, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
