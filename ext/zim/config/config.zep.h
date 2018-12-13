
extern zend_class_entry *zim_config_config_ce;

ZEPHIR_INIT_CLASS(Zim_Config_Config);

PHP_METHOD(Zim_Config_Config, __construct);
PHP_METHOD(Zim_Config_Config, has);
PHP_METHOD(Zim_Config_Config, get);
PHP_METHOD(Zim_Config_Config, getMany);
PHP_METHOD(Zim_Config_Config, set);
PHP_METHOD(Zim_Config_Config, prepend);
PHP_METHOD(Zim_Config_Config, push);
PHP_METHOD(Zim_Config_Config, all);
PHP_METHOD(Zim_Config_Config, offsetExists);
PHP_METHOD(Zim_Config_Config, offsetGet);
PHP_METHOD(Zim_Config_Config, offsetSet);
PHP_METHOD(Zim_Config_Config, offsetUnset);
zend_object *zephir_init_properties_Zim_Config_Config(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_config_config___construct, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, items, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_config_config_has, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_config_config_has, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_config_config_get, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_config_config_getmany, 0, 1, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_config_config_getmany, 0, 1, IS_ARRAY, NULL, 0)
#endif
	ZEND_ARG_ARRAY_INFO(0, keys, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_config_config_set, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_config_config_prepend, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_config_config_push, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_config_config_all, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_config_config_all, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_config_config_offsetexists, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_config_config_offsetexists, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_config_config_offsetget, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_config_config_offsetset, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_config_config_offsetunset, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_config_config_method_entry) {
	PHP_ME(Zim_Config_Config, __construct, arginfo_zim_config_config___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Config_Config, has, arginfo_zim_config_config_has, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Config_Config, get, arginfo_zim_config_config_get, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Config_Config, getMany, arginfo_zim_config_config_getmany, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Config_Config, set, arginfo_zim_config_config_set, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Config_Config, prepend, arginfo_zim_config_config_prepend, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Config_Config, push, arginfo_zim_config_config_push, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Config_Config, all, arginfo_zim_config_config_all, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Config_Config, offsetExists, arginfo_zim_config_config_offsetexists, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Config_Config, offsetGet, arginfo_zim_config_config_offsetget, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Config_Config, offsetSet, arginfo_zim_config_config_offsetset, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Config_Config, offsetUnset, arginfo_zim_config_config_offsetunset, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
