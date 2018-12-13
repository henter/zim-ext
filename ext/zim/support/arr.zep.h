
extern zend_class_entry *zim_support_arr_ce;

ZEPHIR_INIT_CLASS(Zim_Support_Arr);

PHP_METHOD(Zim_Support_Arr, value);
PHP_METHOD(Zim_Support_Arr, accessible);
PHP_METHOD(Zim_Support_Arr, exists);
PHP_METHOD(Zim_Support_Arr, get);
PHP_METHOD(Zim_Support_Arr, has);
PHP_METHOD(Zim_Support_Arr, set);
PHP_METHOD(Zim_Support_Arr, _parseIniString);
PHP_METHOD(Zim_Support_Arr, _cast);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_support_arr_value, 0, 0, 1)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_arr_accessible, 0, 1, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_arr_accessible, 0, 1, _IS_BOOL, NULL, 0)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_arr_exists, 0, 2, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_arr_exists, 0, 2, _IS_BOOL, NULL, 0)
#endif
	ZEND_ARG_INFO(0, myArray)
	ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_support_arr_get, 0, 0, 2)
	ZEND_ARG_INFO(0, myArray)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, deft)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_arr_has, 0, 2, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_arr_has, 0, 2, _IS_BOOL, NULL, 0)
#endif
	ZEND_ARG_INFO(0, myArray)
	ZEND_ARG_INFO(0, keys)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_arr_set, 0, 3, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_arr_set, 0, 3, IS_ARRAY, NULL, 0)
#endif
	ZEND_ARG_ARRAY_INFO(0, myArray, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, key)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_support_arr__parseinistring, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, path)
#endif
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_support_arr__cast, 0, 0, 1)
	ZEND_ARG_INFO(0, ini)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_support_arr_method_entry) {
	PHP_ME(Zim_Support_Arr, value, arginfo_zim_support_arr_value, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Arr, accessible, arginfo_zim_support_arr_accessible, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Arr, exists, arginfo_zim_support_arr_exists, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Arr, get, arginfo_zim_support_arr_get, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Arr, has, arginfo_zim_support_arr_has, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Arr, set, arginfo_zim_support_arr_set, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Arr, _parseIniString, arginfo_zim_support_arr__parseinistring, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Arr, _cast, arginfo_zim_support_arr__cast, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC)
	PHP_FE_END
};
