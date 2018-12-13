
extern zend_class_entry *zim_support_str_ce;

ZEPHIR_INIT_CLASS(Zim_Support_Str);

PHP_METHOD(Zim_Support_Str, after);
PHP_METHOD(Zim_Support_Str, before);
PHP_METHOD(Zim_Support_Str, camel);
PHP_METHOD(Zim_Support_Str, contains);
PHP_METHOD(Zim_Support_Str, endsWith);
PHP_METHOD(Zim_Support_Str, finish);
PHP_METHOD(Zim_Support_Str, kebab);
PHP_METHOD(Zim_Support_Str, length);
PHP_METHOD(Zim_Support_Str, limit);
PHP_METHOD(Zim_Support_Str, lower);
PHP_METHOD(Zim_Support_Str, words);
PHP_METHOD(Zim_Support_Str, random);
PHP_METHOD(Zim_Support_Str, replaceArray);
PHP_METHOD(Zim_Support_Str, replaceFirst);
PHP_METHOD(Zim_Support_Str, replaceLast);
PHP_METHOD(Zim_Support_Str, start);
PHP_METHOD(Zim_Support_Str, upper);
PHP_METHOD(Zim_Support_Str, title);
PHP_METHOD(Zim_Support_Str, snake);
PHP_METHOD(Zim_Support_Str, startsWith);
PHP_METHOD(Zim_Support_Str, studly);
PHP_METHOD(Zim_Support_Str, substr);
PHP_METHOD(Zim_Support_Str, ucfirst);
void zephir_init_static_properties_Zim_Support_Str(TSRMLS_D);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_after, 0, 2, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_after, 0, 2, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, subject, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, subject)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, search, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, search)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_before, 0, 2, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_before, 0, 2, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, subject, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, subject)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, search, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, search)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_camel, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_camel, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_contains, 0, 2, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_contains, 0, 2, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, haystack, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, haystack)
#endif
	ZEND_ARG_INFO(0, needles)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_endswith, 0, 2, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_endswith, 0, 2, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, haystack, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, haystack)
#endif
	ZEND_ARG_INFO(0, needles)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_finish, 0, 2, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_finish, 0, 2, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, cap, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, cap)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_kebab, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_kebab, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_length, 0, 1, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_length, 0, 1, IS_LONG, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, encoding, IS_STRING, 1)
#else
	ZEND_ARG_INFO(0, encoding)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_limit, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_limit, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, limit, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, limit)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, end, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, end)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_lower, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_lower, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_words, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_words, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, words, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, words)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, end, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, end)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_random, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_random, 0, 0, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, length)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_replacearray, 0, 3, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_replacearray, 0, 3, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, search, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, search)
#endif
	ZEND_ARG_ARRAY_INFO(0, replace, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, subject, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, subject)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_replacefirst, 0, 3, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_replacefirst, 0, 3, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, search, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, search)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, replace, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, replace)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, subject, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, subject)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_replacelast, 0, 3, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_replacelast, 0, 3, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, search, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, search)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, replace, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, replace)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, subject, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, subject)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_start, 0, 2, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_start, 0, 2, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, prefix, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, prefix)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_upper, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_upper, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_title, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_title, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_snake, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_snake, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, delimiter, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, delimiter)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_startswith, 0, 2, _IS_BOOL, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_startswith, 0, 2, _IS_BOOL, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, haystack, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, haystack)
#endif
	ZEND_ARG_INFO(0, needles)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_studly, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_studly, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, value)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_substr, 0, 2, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_substr, 0, 2, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, stringg, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, stringg)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, start, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, start)
#endif
	ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_ucfirst, 0, 1, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_zim_support_str_ucfirst, 0, 1, IS_STRING, NULL, 0)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, stringg, IS_STRING, 0)
#else
	ZEND_ARG_INFO(0, stringg)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_support_str_method_entry) {
	PHP_ME(Zim_Support_Str, after, arginfo_zim_support_str_after, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, before, arginfo_zim_support_str_before, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, camel, arginfo_zim_support_str_camel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, contains, arginfo_zim_support_str_contains, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, endsWith, arginfo_zim_support_str_endswith, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, finish, arginfo_zim_support_str_finish, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, kebab, arginfo_zim_support_str_kebab, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, length, arginfo_zim_support_str_length, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, limit, arginfo_zim_support_str_limit, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, lower, arginfo_zim_support_str_lower, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, words, arginfo_zim_support_str_words, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, random, arginfo_zim_support_str_random, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, replaceArray, arginfo_zim_support_str_replacearray, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, replaceFirst, arginfo_zim_support_str_replacefirst, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, replaceLast, arginfo_zim_support_str_replacelast, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, start, arginfo_zim_support_str_start, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, upper, arginfo_zim_support_str_upper, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, title, arginfo_zim_support_str_title, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, snake, arginfo_zim_support_str_snake, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, startsWith, arginfo_zim_support_str_startswith, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, studly, arginfo_zim_support_str_studly, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, substr, arginfo_zim_support_str_substr, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Support_Str, ucfirst, arginfo_zim_support_str_ucfirst, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
