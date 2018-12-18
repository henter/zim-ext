
extern zend_class_entry *zim_zim_ce;

ZEPHIR_INIT_CLASS(Zim_Zim);

PHP_METHOD(Zim_Zim, __construct);
PHP_METHOD(Zim_Zim, getInstance);
PHP_METHOD(Zim_Zim, bootstrapContainer);
PHP_METHOD(Zim_Zim, bootstrapConfig);
PHP_METHOD(Zim_Zim, registerServices);
PHP_METHOD(Zim_Zim, version);
PHP_METHOD(Zim_Zim, register);
PHP_METHOD(Zim_Zim, boot);
PHP_METHOD(Zim_Zim, bootService);
PHP_METHOD(Zim_Zim, inConsole);
PHP_METHOD(Zim_Zim, basePath);
PHP_METHOD(Zim_Zim, configure);
PHP_METHOD(Zim_Zim, getConfigPath);
PHP_METHOD(Zim_Zim, env);
PHP_METHOD(Zim_Zim, registerErrorHandling);
PHP_METHOD(Zim_Zim, getEvent);
PHP_METHOD(Zim_Zim, fire);
PHP_METHOD(Zim_Zim, app);
PHP_METHOD(Zim_Zim, config);
zend_object *zephir_init_properties_Zim_Zim(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_zim___construct, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, path)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_zim_getinstance, 0, 0, Zim\\Container\\Container, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_zim_getinstance, 0, 0, IS_OBJECT, "Zim\\Container\\Container", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_zim_version, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_zim_version, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_zim_register, 0, 0, 1)
	ZEND_ARG_INFO(0, service)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_zim_bootservice, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, service, Zim\\Service\\Service, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_zim_inconsole, 0, 0, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_zim_inconsole, 0, 0, _IS_BOOL, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_zim_basepath, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_zim_basepath, 0, 0, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_zim_configure, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_zim_getconfigpath, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_zim_getconfigpath, 0, 0, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_zim_fire, 0, 0, 1)
	ZEND_ARG_INFO(0, event)
	ZEND_ARG_ARRAY_INFO(0, payload, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, halt, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, halt)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_zim_app, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_zim_config, 0, 0, 0)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_zim_method_entry) {
	PHP_ME(Zim_Zim, __construct, arginfo_zim_zim___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Zim, getInstance, arginfo_zim_zim_getinstance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Zim, bootstrapContainer, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Zim, bootstrapConfig, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Zim, registerServices, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Zim, version, arginfo_zim_zim_version, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Zim, register, arginfo_zim_zim_register, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Zim, boot, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Zim, bootService, arginfo_zim_zim_bootservice, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Zim, inConsole, arginfo_zim_zim_inconsole, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Zim, basePath, arginfo_zim_zim_basepath, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Zim, configure, arginfo_zim_zim_configure, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Zim, getConfigPath, arginfo_zim_zim_getconfigpath, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Zim, env, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Zim, registerErrorHandling, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Zim, getEvent, NULL, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Zim, fire, arginfo_zim_zim_fire, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Zim, app, arginfo_zim_zim_app, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Zim, config, arginfo_zim_zim_config, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
