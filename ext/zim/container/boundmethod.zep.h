
extern zend_class_entry *zim_container_boundmethod_ce;

ZEPHIR_INIT_CLASS(Zim_Container_BoundMethod);

PHP_METHOD(Zim_Container_BoundMethod, call);
PHP_METHOD(Zim_Container_BoundMethod, callClass);
PHP_METHOD(Zim_Container_BoundMethod, callBoundMethod);
PHP_METHOD(Zim_Container_BoundMethod, normalizeMethod);
PHP_METHOD(Zim_Container_BoundMethod, getMethodDependencies);
PHP_METHOD(Zim_Container_BoundMethod, getCallReflector);
PHP_METHOD(Zim_Container_BoundMethod, addDependencyForCallParameter);
PHP_METHOD(Zim_Container_BoundMethod, isCallableWithAtSign);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_boundmethod_call, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, container, Zim\\Container\\Container, 0)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
	ZEND_ARG_INFO(0, defaultMethod)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_boundmethod_callclass, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, container, Zim\\Container\\Container, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, target, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, target)
#endif
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
	ZEND_ARG_INFO(0, defaultMethod)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_boundmethod_callboundmethod, 0, 0, 3)
	ZEND_ARG_OBJ_INFO(0, container, Zim\\Container\\Container, 0)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_boundmethod_normalizemethod, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_boundmethod_normalizemethod, 0, 1, IS_STRING, NULL, 0)
#endif
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_boundmethod_getmethoddependencies, 0, 2, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_boundmethod_getmethoddependencies, 0, 2, IS_ARRAY, NULL, 0)
#endif
	ZEND_ARG_OBJ_INFO(0, container, Zim\\Container\\Container, 0)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_container_boundmethod_getcallreflector, 0, 1, ReflectionFunctionAbstract, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_boundmethod_getcallreflector, 0, 1, IS_OBJECT, "ReflectionFunctionAbstract", 0)
#endif
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_boundmethod_adddependencyforcallparameter, 0, 0, 4)
	ZEND_ARG_OBJ_INFO(0, container, Zim\\Container\\Container, 0)
	ZEND_ARG_OBJ_INFO(0, parameter, ReflectionParameter, 0)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
	ZEND_ARG_ARRAY_INFO(0, dependencies, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_boundmethod_iscallablewithatsign, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_boundmethod_iscallablewithatsign, 0, 1, _IS_BOOL, NULL, 0)
#endif
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_container_boundmethod_method_entry) {
	PHP_ME(Zim_Container_BoundMethod, call, arginfo_zim_container_boundmethod_call, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Container_BoundMethod, callClass, arginfo_zim_container_boundmethod_callclass, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Container_BoundMethod, callBoundMethod, arginfo_zim_container_boundmethod_callboundmethod, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Container_BoundMethod, normalizeMethod, arginfo_zim_container_boundmethod_normalizemethod, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Container_BoundMethod, getMethodDependencies, arginfo_zim_container_boundmethod_getmethoddependencies, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Container_BoundMethod, getCallReflector, arginfo_zim_container_boundmethod_getcallreflector, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Container_BoundMethod, addDependencyForCallParameter, arginfo_zim_container_boundmethod_adddependencyforcallparameter, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Container_BoundMethod, isCallableWithAtSign, arginfo_zim_container_boundmethod_iscallablewithatsign, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_FE_END
};
