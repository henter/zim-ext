
extern zend_class_entry *zim_routing_routecollection_ce;

ZEPHIR_INIT_CLASS(Zim_Routing_RouteCollection);

PHP_METHOD(Zim_Routing_RouteCollection, __clone);
PHP_METHOD(Zim_Routing_RouteCollection, getIterator);
PHP_METHOD(Zim_Routing_RouteCollection, count);
PHP_METHOD(Zim_Routing_RouteCollection, add);
PHP_METHOD(Zim_Routing_RouteCollection, all);
PHP_METHOD(Zim_Routing_RouteCollection, get);
PHP_METHOD(Zim_Routing_RouteCollection, remove);
PHP_METHOD(Zim_Routing_RouteCollection, addCollection);
PHP_METHOD(Zim_Routing_RouteCollection, addPrefix);
PHP_METHOD(Zim_Routing_RouteCollection, addNamePrefix);
PHP_METHOD(Zim_Routing_RouteCollection, addDefaults);
PHP_METHOD(Zim_Routing_RouteCollection, addRequirements);
PHP_METHOD(Zim_Routing_RouteCollection, addOptions);
PHP_METHOD(Zim_Routing_RouteCollection, setMethods);
zend_object *zephir_init_properties_Zim_Routing_RouteCollection(zend_class_entry *class_type TSRMLS_DC);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_routecollection_count, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_routecollection_count, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecollection_add, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
	ZEND_ARG_OBJ_INFO(0, route, Zim\\Routing\\Route, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_routecollection_all, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_routecollection_all, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecollection_get, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecollection_remove, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecollection_addcollection, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, collection, Zim\\Routing\\RouteCollection, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecollection_addprefix, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, prefix, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, prefix)
#endif
	ZEND_ARG_ARRAY_INFO(0, defaults, 0)
	ZEND_ARG_ARRAY_INFO(0, requirements, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecollection_addnameprefix, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, prefix, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, prefix)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecollection_adddefaults, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, defaults, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecollection_addrequirements, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, requirements, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecollection_addoptions, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, options, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecollection_setmethods, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, methods, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_routing_routecollection_method_entry) {
	PHP_ME(Zim_Routing_RouteCollection, __clone, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, getIterator, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, count, arginfo_zim_routing_routecollection_count, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, add, arginfo_zim_routing_routecollection_add, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, all, arginfo_zim_routing_routecollection_all, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, get, arginfo_zim_routing_routecollection_get, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, remove, arginfo_zim_routing_routecollection_remove, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, addCollection, arginfo_zim_routing_routecollection_addcollection, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, addPrefix, arginfo_zim_routing_routecollection_addprefix, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, addNamePrefix, arginfo_zim_routing_routecollection_addnameprefix, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, addDefaults, arginfo_zim_routing_routecollection_adddefaults, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, addRequirements, arginfo_zim_routing_routecollection_addrequirements, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, addOptions, arginfo_zim_routing_routecollection_addoptions, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_RouteCollection, setMethods, arginfo_zim_routing_routecollection_setmethods, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
