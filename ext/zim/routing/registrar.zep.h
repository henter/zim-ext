
extern zend_class_entry *zim_routing_registrar_ce;

ZEPHIR_INIT_CLASS(Zim_Routing_Registrar);

PHP_METHOD(Zim_Routing_Registrar, __construct);
PHP_METHOD(Zim_Routing_Registrar, registrarRoute);
PHP_METHOD(Zim_Routing_Registrar, doMatch);
PHP_METHOD(Zim_Routing_Registrar, __call);
zend_object *zephir_init_properties_Zim_Routing_Registrar(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_registrar___construct, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, router, Zim\\Routing\\Router, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_routing_registrar_registrarroute, 0, 2, Zim\\Routing\\Route, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_registrar_registrarroute, 0, 2, IS_OBJECT, "Zim\\Routing\\Route", 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, method, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, method)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, uri, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, uri)
#endif
	ZEND_ARG_INFO(0, info)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_routing_registrar_domatch, 0, 2, Zim\\Routing\\Route, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_registrar_domatch, 0, 2, IS_OBJECT, "Zim\\Routing\\Route", 0)
#endif
	ZEND_ARG_INFO(0, methods)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, uri, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, uri)
#endif
	ZEND_ARG_INFO(0, info)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_registrar___call, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, method, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, method)
#endif
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_routing_registrar_method_entry) {
	PHP_ME(Zim_Routing_Registrar, __construct, arginfo_zim_routing_registrar___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Routing_Registrar, registrarRoute, arginfo_zim_routing_registrar_registrarroute, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Routing_Registrar, doMatch, arginfo_zim_routing_registrar_domatch, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Registrar, __call, arginfo_zim_routing_registrar___call, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
