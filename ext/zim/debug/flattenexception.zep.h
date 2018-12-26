
extern zend_class_entry *zim_debug_flattenexception_ce;

ZEPHIR_INIT_CLASS(Zim_Debug_FlattenException);

PHP_METHOD(Zim_Debug_FlattenException, create);
PHP_METHOD(Zim_Debug_FlattenException, createFromThrowable);
PHP_METHOD(Zim_Debug_FlattenException, toArray);
PHP_METHOD(Zim_Debug_FlattenException, getStatusCode);
PHP_METHOD(Zim_Debug_FlattenException, setStatusCode);
PHP_METHOD(Zim_Debug_FlattenException, getHeaders);
PHP_METHOD(Zim_Debug_FlattenException, setHeaders);
PHP_METHOD(Zim_Debug_FlattenException, getClass);
PHP_METHOD(Zim_Debug_FlattenException, setClass);
PHP_METHOD(Zim_Debug_FlattenException, getFile);
PHP_METHOD(Zim_Debug_FlattenException, setFile);
PHP_METHOD(Zim_Debug_FlattenException, getLine);
PHP_METHOD(Zim_Debug_FlattenException, setLine);
PHP_METHOD(Zim_Debug_FlattenException, getMessage);
PHP_METHOD(Zim_Debug_FlattenException, setMessage);
PHP_METHOD(Zim_Debug_FlattenException, getCode);
PHP_METHOD(Zim_Debug_FlattenException, setCode);
PHP_METHOD(Zim_Debug_FlattenException, getPrevious);
PHP_METHOD(Zim_Debug_FlattenException, setPrevious);
PHP_METHOD(Zim_Debug_FlattenException, getAllPrevious);
PHP_METHOD(Zim_Debug_FlattenException, getTrace);
PHP_METHOD(Zim_Debug_FlattenException, setTraceFromThrowable);
PHP_METHOD(Zim_Debug_FlattenException, setTrace);
PHP_METHOD(Zim_Debug_FlattenException, flattenArgs);
PHP_METHOD(Zim_Debug_FlattenException, getClassNameFromIncomplete);

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_create, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, exception, Zim\\Debug\\Exception, 0)
	ZEND_ARG_INFO(0, statusCode)
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_createfromthrowable, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, exception, Zim\\Debug\\Throwable, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, _statusCode, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, _statusCode)
#endif
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_setstatuscode, 0, 0, 1)
	ZEND_ARG_INFO(0, code)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_setheaders, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, headers, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_setclass, 0, 0, 1)
	ZEND_ARG_INFO(0, c)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_setfile, 0, 0, 1)
	ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_setline, 0, 0, 1)
	ZEND_ARG_INFO(0, line)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_setmessage, 0, 0, 1)
	ZEND_ARG_INFO(0, message)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_setcode, 0, 0, 1)
	ZEND_ARG_INFO(0, code)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_setprevious, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, previous, Zim\\Debug\\self, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_settracefromthrowable, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, throwable, Zim\\Debug\\Throwable, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_settrace, 0, 0, 3)
	ZEND_ARG_INFO(0, trace)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, line)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_flattenargs, 0, 0, 1)
	ZEND_ARG_INFO(0, args)
	ZEND_ARG_INFO(0, level)
	ZEND_ARG_INFO(0, count)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_zim_debug_flattenexception_getclassnamefromincomplete, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, value, Zim\\Debug\\__PHP_Incomplete_Class, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(zim_debug_flattenexception_method_entry) {
	PHP_ME(Zim_Debug_FlattenException, create, arginfo_zim_debug_flattenexception_create, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Debug_FlattenException, createFromThrowable, arginfo_zim_debug_flattenexception_createfromthrowable, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Zim_Debug_FlattenException, toArray, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, getStatusCode, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, setStatusCode, arginfo_zim_debug_flattenexception_setstatuscode, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, getHeaders, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, setHeaders, arginfo_zim_debug_flattenexception_setheaders, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, getClass, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, setClass, arginfo_zim_debug_flattenexception_setclass, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, getFile, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, setFile, arginfo_zim_debug_flattenexception_setfile, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, getLine, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, setLine, arginfo_zim_debug_flattenexception_setline, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, getMessage, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, setMessage, arginfo_zim_debug_flattenexception_setmessage, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, getCode, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, setCode, arginfo_zim_debug_flattenexception_setcode, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, getPrevious, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, setPrevious, arginfo_zim_debug_flattenexception_setprevious, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, getAllPrevious, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, getTrace, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, setTraceFromThrowable, arginfo_zim_debug_flattenexception_settracefromthrowable, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, setTrace, arginfo_zim_debug_flattenexception_settrace, ZEND_ACC_PUBLIC)
	PHP_ME(Zim_Debug_FlattenException, flattenArgs, arginfo_zim_debug_flattenexception_flattenargs, ZEND_ACC_PROTECTED)
	PHP_ME(Zim_Debug_FlattenException, getClassNameFromIncomplete, arginfo_zim_debug_flattenexception_getclassnamefromincomplete, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
