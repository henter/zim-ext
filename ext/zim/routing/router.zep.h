
extern zend_class_entry *zim_routing_router_ce;

ZEPHIR_INIT_CLASS(Zim_Routing_Router);

PHP_METHOD(Zim_Routing_Router, __construct);
PHP_METHOD(Zim_Routing_Router, getRoutes);
PHP_METHOD(Zim_Routing_Router, addRoute);
PHP_METHOD(Zim_Routing_Router, createRoute);
PHP_METHOD(Zim_Routing_Router, matchRequest);
PHP_METHOD(Zim_Routing_Router, match);
PHP_METHOD(Zim_Routing_Router, matchCollection);
zend_object *zephir_init_properties_Zim_Routing_Router(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_router___construct, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, routes, Zim\\Routing\\RouteCollection, 1)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_routing_router_getroutes, 0, 0, Zim\\Routing\\RouteCollection, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_router_getroutes, 0, 0, IS_OBJECT, "Zim\\Routing\\RouteCollection", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_routing_router_addroute, 0, 3, Zim\\Routing\\Route, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_router_addroute, 0, 3, IS_OBJECT, "Zim\\Routing\\Route", 0)
#endif
	ZEND_ARG_INFO(0, methods)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, uri, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, uri)
#endif
	ZEND_ARG_INFO(0, info)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_routing_router_createroute, 0, 3, Zim\\Routing\\Route, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_router_createroute, 0, 3, IS_OBJECT, "Zim\\Routing\\Route", 0)
#endif
	ZEND_ARG_INFO(0, methods)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, uri, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, uri)
#endif
	ZEND_ARG_INFO(0, info)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_routing_router_matchrequest, 0, 1, Zim\\Routing\\Route, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_router_matchrequest, 0, 1, IS_OBJECT, "Zim\\Routing\\Route", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, request, Zim\\Http\\Request, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_routing_router_match, 0, 1, Zim\\Routing\\Route, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_router_match, 0, 1, IS_OBJECT, "Zim\\Routing\\Route", 0)
#endif
	ZEND_ARG_INFO(0, path)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, method, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, method)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_router_matchcollection, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, path)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_routing_router_method_entry) {
	PHP_ME(Zim_Routing_Router, __construct, arginfo_zim_routing_router___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Routing_Router, getRoutes, arginfo_zim_routing_router_getroutes, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Router, addRoute, arginfo_zim_routing_router_addroute, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Router, createRoute, arginfo_zim_routing_router_createroute, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Routing_Router, matchRequest, arginfo_zim_routing_router_matchrequest, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Router, match, arginfo_zim_routing_router_match, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Router, matchCollection, arginfo_zim_routing_router_matchcollection, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
