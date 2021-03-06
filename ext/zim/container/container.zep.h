
extern zend_class_entry *zim_container_container_ce;

ZEPHIR_INIT_CLASS(Zim_Container_Container);

PHP_METHOD(Zim_Container_Container, bound);
PHP_METHOD(Zim_Container_Container, has);
PHP_METHOD(Zim_Container_Container, isShared);
PHP_METHOD(Zim_Container_Container, isAlias);
PHP_METHOD(Zim_Container_Container, bind);
PHP_METHOD(Zim_Container_Container, getClosure);
PHP_METHOD(Zim_Container_Container, singleton);
PHP_METHOD(Zim_Container_Container, extend);
PHP_METHOD(Zim_Container_Container, instance);
PHP_METHOD(Zim_Container_Container, alias);
PHP_METHOD(Zim_Container_Container, get);
PHP_METHOD(Zim_Container_Container, make);
PHP_METHOD(Zim_Container_Container, getConcrete);
PHP_METHOD(Zim_Container_Container, isBuildable);
PHP_METHOD(Zim_Container_Container, build);
PHP_METHOD(Zim_Container_Container, notInstantiable);
PHP_METHOD(Zim_Container_Container, getBindings);
PHP_METHOD(Zim_Container_Container, getAlias);
PHP_METHOD(Zim_Container_Container, getExtenders);
PHP_METHOD(Zim_Container_Container, forgetExtenders);
PHP_METHOD(Zim_Container_Container, dropStaleInstances);
PHP_METHOD(Zim_Container_Container, forgetInstance);
PHP_METHOD(Zim_Container_Container, forgetInstances);
PHP_METHOD(Zim_Container_Container, flush);
PHP_METHOD(Zim_Container_Container, getInstance);
PHP_METHOD(Zim_Container_Container, setInstance);
PHP_METHOD(Zim_Container_Container, set);
PHP_METHOD(Zim_Container_Container, remove);
PHP_METHOD(Zim_Container_Container, call);
PHP_METHOD(Zim_Container_Container, buildObject);
PHP_METHOD(Zim_Container_Container, getDependencies);
PHP_METHOD(Zim_Container_Container, reflectionParams);
zend_object *zephir_init_properties_Zim_Container_Container(zend_class_entry *class_type TSRMLS_DC);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_bound, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_bound, 0, 1, _IS_BOOL, NULL, 0)
#endif
	ZEND_ARG_INFO(0, abstractt)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_has, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_isshared, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_isshared, 0, 1, _IS_BOOL, NULL, 0)
#endif
	ZEND_ARG_INFO(0, abstractt)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_isalias, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_isalias, 0, 1, _IS_BOOL, NULL, 0)
#endif
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_bind, 0, 0, 1)
	ZEND_ARG_INFO(0, abstractt)
	ZEND_ARG_INFO(0, concrete)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, shared, _IS_BOOL, 0)
#else
	ZEND_ARG_INFO(0, shared)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_container_container_getclosure, 0, 2, Zim\\Container\\ContainergetClosureClosureZero, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_getclosure, 0, 2, IS_OBJECT, "Zim\\Container\\ContainergetClosureClosureZero", 0)
#endif
	ZEND_ARG_INFO(0, abstractt)
	ZEND_ARG_INFO(0, concrete)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_singleton, 0, 0, 1)
	ZEND_ARG_INFO(0, abstractt)
	ZEND_ARG_INFO(0, concrete)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_extend, 0, 0, 2)
	ZEND_ARG_INFO(0, abstractt)
	ZEND_ARG_OBJ_INFO(0, closure, Closure, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_instance, 0, 0, 2)
	ZEND_ARG_INFO(0, abstractt)
	ZEND_ARG_INFO(0, instance)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_alias, 0, 0, 2)
	ZEND_ARG_INFO(0, abstractt)
	ZEND_ARG_INFO(0, alias)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_get, 0, 0, 1)
	ZEND_ARG_INFO(0, id)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_make, 0, 0, 1)
	ZEND_ARG_INFO(0, abstractt)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_getconcrete, 0, 0, 1)
	ZEND_ARG_INFO(0, abstractt)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_isbuildable, 0, 2, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_isbuildable, 0, 2, _IS_BOOL, NULL, 0)
#endif
	ZEND_ARG_INFO(0, concrete)
	ZEND_ARG_INFO(0, abstractt)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_build, 0, 0, 1)
	ZEND_ARG_INFO(0, concrete)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_notinstantiable, 0, 0, 1)
	ZEND_ARG_INFO(0, concrete)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_getbindings, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_getbindings, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_getalias, 0, 0, 1)
	ZEND_ARG_INFO(0, abstractt)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_getextenders, 0, 1, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_getextenders, 0, 1, IS_ARRAY, NULL, 0)
#endif
	ZEND_ARG_INFO(0, abstractt)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_forgetextenders, 0, 0, 1)
	ZEND_ARG_INFO(0, abstractt)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_dropstaleinstances, 0, 0, 1)
	ZEND_ARG_INFO(0, abstractt)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_forgetinstance, 0, 0, 1)
	ZEND_ARG_INFO(0, abstractt)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_zim_container_container_getinstance, 0, 0, Zim\\Container\\Container, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_container_container_getinstance, 0, 0, IS_OBJECT, "Zim\\Container\\Container", 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_setinstance, 0, 0, 0)
	ZEND_ARG_OBJ_INFO(0, container, Zim\\Container\\Container, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_set, 0, 0, 2)
	ZEND_ARG_INFO(0, key)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_remove, 0, 0, 1)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_call, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_ARRAY_INFO(0, parameters, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_buildobject, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, c, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, c)
#endif
	ZEND_ARG_ARRAY_INFO(0, params, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_getdependencies, 0, 0, 1)
	ZEND_ARG_INFO(0, call)
	ZEND_ARG_ARRAY_INFO(0, params, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_container_container_reflectionparams, 0, 0, 1)
	ZEND_ARG_INFO(0, call)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_container_container_method_entry) {
	PHP_ME(Zim_Container_Container, bound, arginfo_zim_container_container_bound, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, has, arginfo_zim_container_container_has, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, isShared, arginfo_zim_container_container_isshared, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, isAlias, arginfo_zim_container_container_isalias, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, bind, arginfo_zim_container_container_bind, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, getClosure, arginfo_zim_container_container_getclosure, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Container_Container, singleton, arginfo_zim_container_container_singleton, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, extend, arginfo_zim_container_container_extend, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, instance, arginfo_zim_container_container_instance, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, alias, arginfo_zim_container_container_alias, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, get, arginfo_zim_container_container_get, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, make, arginfo_zim_container_container_make, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, getConcrete, arginfo_zim_container_container_getconcrete, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Container_Container, isBuildable, arginfo_zim_container_container_isbuildable, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Container_Container, build, arginfo_zim_container_container_build, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, notInstantiable, arginfo_zim_container_container_notinstantiable, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Container_Container, getBindings, arginfo_zim_container_container_getbindings, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, getAlias, arginfo_zim_container_container_getalias, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, getExtenders, arginfo_zim_container_container_getextenders, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Container_Container, forgetExtenders, arginfo_zim_container_container_forgetextenders, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, dropStaleInstances, arginfo_zim_container_container_dropstaleinstances, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Container_Container, forgetInstance, arginfo_zim_container_container_forgetinstance, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, forgetInstances, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, flush, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, getInstance, arginfo_zim_container_container_getinstance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Container_Container, setInstance, arginfo_zim_container_container_setinstance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Container_Container, set, arginfo_zim_container_container_set, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, remove, arginfo_zim_container_container_remove, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, call, arginfo_zim_container_container_call, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, buildObject, arginfo_zim_container_container_buildobject, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, getDependencies, arginfo_zim_container_container_getdependencies, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Container_Container, reflectionParams, arginfo_zim_container_container_reflectionparams, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
