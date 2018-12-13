
extern zend_class_entry *zim_routing_route_ce;

ZEPHIR_INIT_CLASS(Zim_Routing_Route);

PHP_METHOD(Zim_Routing_Route, __construct);
PHP_METHOD(Zim_Routing_Route, setParameters);
PHP_METHOD(Zim_Routing_Route, getParameters);
PHP_METHOD(Zim_Routing_Route, mergeDefaults);
PHP_METHOD(Zim_Routing_Route, getPath);
PHP_METHOD(Zim_Routing_Route, setPath);
PHP_METHOD(Zim_Routing_Route, setPathCallback);
PHP_METHOD(Zim_Routing_Route, getMethods);
PHP_METHOD(Zim_Routing_Route, setMethods);
PHP_METHOD(Zim_Routing_Route, getOptions);
PHP_METHOD(Zim_Routing_Route, addOptions);
PHP_METHOD(Zim_Routing_Route, setOption);
PHP_METHOD(Zim_Routing_Route, getOption);
PHP_METHOD(Zim_Routing_Route, hasOption);
PHP_METHOD(Zim_Routing_Route, getDefaults);
PHP_METHOD(Zim_Routing_Route, setDefaults);
PHP_METHOD(Zim_Routing_Route, addDefaults);
PHP_METHOD(Zim_Routing_Route, getDefault);
PHP_METHOD(Zim_Routing_Route, hasDefault);
PHP_METHOD(Zim_Routing_Route, setDefault);
PHP_METHOD(Zim_Routing_Route, getRequirements);
PHP_METHOD(Zim_Routing_Route, setRequirements);
PHP_METHOD(Zim_Routing_Route, addRequirements);
PHP_METHOD(Zim_Routing_Route, getRequirement);
PHP_METHOD(Zim_Routing_Route, hasRequirement);
PHP_METHOD(Zim_Routing_Route, setRequirement);
PHP_METHOD(Zim_Routing_Route, compile);
PHP_METHOD(Zim_Routing_Route, sanitizeRequirement);
PHP_METHOD(Zim_Routing_Route, __callStatic);
zend_object *zephir_init_properties_Zim_Routing_Route(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route___construct, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, path)
#endif
	ZEND_ARG_ARRAY_INFO(0, defaults, 0)
	ZEND_ARG_INFO(0, methods)
	ZEND_ARG_ARRAY_INFO(0, requirements, 0)
	ZEND_ARG_ARRAY_INFO(0, options, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_setparameters, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_mergedefaults, 0, 1, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_mergedefaults, 0, 1, IS_ARRAY, NULL, 0)
#endif
	ZEND_ARG_ARRAY_INFO(0, params, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_getpath, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_getpath, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_setpath, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, pattern, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, pattern)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_setpathcallback, 0, 0, 1)
	ZEND_ARG_INFO(0, m)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_getmethods, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_getmethods, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_setmethods, 0, 0, 1)
	ZEND_ARG_INFO(0, methods)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_getoptions, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_getoptions, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_addoptions, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, options, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_setoption, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_getoption, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_hasoption, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_hasoption, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_getdefaults, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_getdefaults, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_setdefaults, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, defaults, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_adddefaults, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, defaults, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_getdefault, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_hasdefault, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_hasdefault, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_setdefault, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, name)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_getrequirements, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_getrequirements, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_setrequirements, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, requirements, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_addrequirements, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, requirements, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_getrequirement, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_hasrequirement, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_hasrequirement, 0, 1, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_setrequirement, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, regex, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, regex)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_routing_route_compile, 0, 0, Zim\\Routing\\CompiledRoute, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_route_compile, 0, 0, IS_OBJECT, "Zim\\Routing\\CompiledRoute", 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route_sanitizerequirement, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, regex)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_route___callstatic, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, method, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, method)
#endif
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_routing_route_method_entry) {
	PHP_ME(Zim_Routing_Route, __construct, arginfo_zim_routing_route___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Routing_Route, setParameters, arginfo_zim_routing_route_setparameters, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, getParameters, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, mergeDefaults, arginfo_zim_routing_route_mergedefaults, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Routing_Route, getPath, arginfo_zim_routing_route_getpath, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, setPath, arginfo_zim_routing_route_setpath, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, setPathCallback, arginfo_zim_routing_route_setpathcallback, ZEND_ACC_PRIVATE)
	PHP_ME(Zim_Routing_Route, getMethods, arginfo_zim_routing_route_getmethods, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, setMethods, arginfo_zim_routing_route_setmethods, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, getOptions, arginfo_zim_routing_route_getoptions, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, addOptions, arginfo_zim_routing_route_addoptions, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, setOption, arginfo_zim_routing_route_setoption, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, getOption, arginfo_zim_routing_route_getoption, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, hasOption, arginfo_zim_routing_route_hasoption, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, getDefaults, arginfo_zim_routing_route_getdefaults, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, setDefaults, arginfo_zim_routing_route_setdefaults, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, addDefaults, arginfo_zim_routing_route_adddefaults, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, getDefault, arginfo_zim_routing_route_getdefault, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, hasDefault, arginfo_zim_routing_route_hasdefault, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, setDefault, arginfo_zim_routing_route_setdefault, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, getRequirements, arginfo_zim_routing_route_getrequirements, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, setRequirements, arginfo_zim_routing_route_setrequirements, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, addRequirements, arginfo_zim_routing_route_addrequirements, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, getRequirement, arginfo_zim_routing_route_getrequirement, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, hasRequirement, arginfo_zim_routing_route_hasrequirement, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, setRequirement, arginfo_zim_routing_route_setrequirement, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, compile, arginfo_zim_routing_route_compile, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_Route, sanitizeRequirement, arginfo_zim_routing_route_sanitizerequirement, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Routing_Route, __callStatic, arginfo_zim_routing_route___callstatic, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
