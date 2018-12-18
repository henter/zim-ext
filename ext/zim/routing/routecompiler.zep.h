
extern zend_class_entry *zim_routing_routecompiler_ce;

ZEPHIR_INIT_CLASS(Zim_Routing_RouteCompiler);

PHP_METHOD(Zim_Routing_RouteCompiler, compile);
PHP_METHOD(Zim_Routing_RouteCompiler, compilePattern);
PHP_METHOD(Zim_Routing_RouteCompiler, determineStaticPrefix);
PHP_METHOD(Zim_Routing_RouteCompiler, findNextSeparator);
PHP_METHOD(Zim_Routing_RouteCompiler, computeRegexp);
PHP_METHOD(Zim_Routing_RouteCompiler, transformCapturingGroupsToNonCapturings);
PHP_METHOD(Zim_Routing_RouteCompiler, strat);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecompiler_compile, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, route, Zim\\Routing\\Route, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecompiler_compilepattern, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, route, Zim\\Routing\\Route, 0)
	ZEND_ARG_INFO(0, pattern)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecompiler_determinestaticprefix, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, route, Zim\\Routing\\Route, 0)
	ZEND_ARG_ARRAY_INFO(0, tokens, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_routecompiler_findnextseparator, 0, 2, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_routecompiler_findnextseparator, 0, 2, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, pattern, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, pattern)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, useUtf8, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, useUtf8)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_routecompiler_computeregexp, 0, 3, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_routecompiler_computeregexp, 0, 3, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_ARRAY_INFO(0, tokens, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, index)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, firstOptional, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, firstOptional)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_routing_routecompiler_transformcapturinggroupstononcapturings, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, regexp, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, regexp)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_routecompiler_strat, 0, 2, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_routing_routecompiler_strat, 0, 2, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_INFO(0, s)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, i, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, i)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_routing_routecompiler_method_entry) {
	PHP_ME(Zim_Routing_RouteCompiler, compile, arginfo_zim_routing_routecompiler_compile, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Routing_RouteCompiler, compilePattern, arginfo_zim_routing_routecompiler_compilepattern, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Routing_RouteCompiler, determineStaticPrefix, arginfo_zim_routing_routecompiler_determinestaticprefix, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Routing_RouteCompiler, findNextSeparator, arginfo_zim_routing_routecompiler_findnextseparator, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Routing_RouteCompiler, computeRegexp, arginfo_zim_routing_routecompiler_computeregexp, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Routing_RouteCompiler, transformCapturingGroupsToNonCapturings, arginfo_zim_routing_routecompiler_transformcapturinggroupstononcapturings, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Routing_RouteCompiler, strat, arginfo_zim_routing_routecompiler_strat, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_FE_END
};
