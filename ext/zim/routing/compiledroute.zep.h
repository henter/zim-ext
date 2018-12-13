
extern zend_class_entry *zim_routing_compiledroute_ce;

ZEPHIR_INIT_CLASS(Zim_Routing_CompiledRoute);

PHP_METHOD(Zim_Routing_CompiledRoute, __construct);
PHP_METHOD(Zim_Routing_CompiledRoute, getStaticPrefix);
PHP_METHOD(Zim_Routing_CompiledRoute, getRegex);
PHP_METHOD(Zim_Routing_CompiledRoute, getTokens);
PHP_METHOD(Zim_Routing_CompiledRoute, getVariables);
PHP_METHOD(Zim_Routing_CompiledRoute, getPathVariables);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_compiledroute___construct, 0, 0, 4)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, staticPrefix, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, staticPrefix)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, regex, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, regex)
#endif
	ZEND_ARG_ARRAY_INFO(0, tokens, 0)
	ZEND_ARG_ARRAY_INFO(0, pathVariables, 0)
	ZEND_ARG_ARRAY_INFO(0, variables, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_compiledroute_getstaticprefix, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_compiledroute_getstaticprefix, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_compiledroute_getregex, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_compiledroute_getregex, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_compiledroute_gettokens, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_compiledroute_gettokens, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_compiledroute_getvariables, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_compiledroute_getvariables, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_compiledroute_getpathvariables, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_compiledroute_getpathvariables, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_routing_compiledroute_method_entry) {
	PHP_ME(Zim_Routing_CompiledRoute, __construct, arginfo_zim_routing_compiledroute___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Zim_Routing_CompiledRoute, getStaticPrefix, arginfo_zim_routing_compiledroute_getstaticprefix, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_CompiledRoute, getRegex, arginfo_zim_routing_compiledroute_getregex, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_CompiledRoute, getTokens, arginfo_zim_routing_compiledroute_gettokens, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_CompiledRoute, getVariables, arginfo_zim_routing_compiledroute_getvariables, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Routing_CompiledRoute, getPathVariables, arginfo_zim_routing_compiledroute_getpathvariables, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
