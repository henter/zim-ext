
extern zend_class_entry *zim_service_service_ce;

ZEPHIR_INIT_CLASS(Zim_Service_Service);

PHP_METHOD(Zim_Service_Service, __construct);
PHP_METHOD(Zim_Service_Service, boot);
PHP_METHOD(Zim_Service_Service, register);
PHP_METHOD(Zim_Service_Service, provides);
PHP_METHOD(Zim_Service_Service, when);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_service_service___construct, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, zim, Zim\\Zim, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_service_service_provides, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_service_service_provides, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_service_service_when, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_service_service_when, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_service_service_method_entry) {
	PHP_ME(Zim_Service_Service, __construct, arginfo_zim_service_service___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Service_Service, boot, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Service_Service, register, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Service_Service, provides, arginfo_zim_service_service_provides, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Service_Service, when, arginfo_zim_service_service_when, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
