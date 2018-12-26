
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/concat.h"


ZEPHIR_INIT_CLASS(Zim_Support_Str) {

	ZEPHIR_REGISTER_CLASS(Zim\\Support, Str, zim, support_str, zim_support_str_method_entry, 0);

	/**
	 * The cache of snake-cased words.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_support_str_ce, SL("snakeCache"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * The cache of camel-cased words.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_support_str_ce, SL("camelCache"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * The cache of studly-cased words.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_support_str_ce, SL("studlyCache"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	return SUCCESS;

}

/**
 * Return the remainder of a string after a given value.
 *
 * @param  string  $subject
 * @param  string  $search
 * @return string
 */
PHP_METHOD(Zim_Support_Str, after) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *subject_param = NULL, *search_param = NULL, _0, _1, _2;
	zval subject, search;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&subject);
	ZVAL_UNDEF(&search);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &subject_param, &search_param);

	zephir_get_strval(&subject, subject_param);
	zephir_get_strval(&search, search_param);


	ZEPHIR_INIT_VAR(&_0);
	if (ZEPHIR_IS_STRING_IDENTICAL(&search, "")) {
		ZEPHIR_CPY_WRT(&_0, &subject);
	} else {
		ZEPHIR_INIT_VAR(&_1);
		zephir_fast_explode(&_1, &search, &subject, 2  TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_2, "array_reverse", NULL, 107, &_1);
		zephir_check_call_status();
		zephir_array_fetch_long(&_0, &_2, 0, PH_NOISY, "zim/support/str.zep", 32 TSRMLS_CC);
	}
	RETURN_CCTOR(&_0);

}

/**
 * Get the portion of a string before a given value.
 *
 * @param  string  $subject
 * @param  string  $search
 * @return string
 */
PHP_METHOD(Zim_Support_Str, before) {

	zval *subject_param = NULL, *search_param = NULL, _0, _1;
	zval subject, search;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&subject);
	ZVAL_UNDEF(&search);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &subject_param, &search_param);

	zephir_get_strval(&subject, subject_param);
	zephir_get_strval(&search, search_param);


	ZEPHIR_INIT_VAR(&_0);
	if (ZEPHIR_IS_STRING_IDENTICAL(&search, "")) {
		ZEPHIR_CPY_WRT(&_0, &subject);
	} else {
		ZEPHIR_INIT_VAR(&_1);
		zephir_fast_explode(&_1, &search, &subject, LONG_MAX TSRMLS_CC);
		zephir_array_fetch_long(&_0, &_1, 0, PH_NOISY, "zim/support/str.zep", 44 TSRMLS_CC);
	}
	RETURN_CCTOR(&_0);

}

/**
 * Convert a value to camel case.
 *
 * @param  string  $value
 * @return string
 */
PHP_METHOD(Zim_Support_Str, camel) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, _0, _3, _4, _5, _6, _1$$3, _2$$3;
	zval value;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	zephir_get_strval(&value, value_param);


	zephir_read_static_property_ce(&_0, zim_support_str_ce, SL("camelCache"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_0, &value)) {
		zephir_read_static_property_ce(&_1$$3, zim_support_str_ce, SL("camelCache"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_2$$3, &_1$$3, &value, PH_NOISY | PH_READONLY, "zim/support/str.zep", 56 TSRMLS_CC);
		RETURN_CTOR(&_2$$3);
	}
	ZEPHIR_CALL_SELF(&_3, "studly", NULL, 0, &value);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_4, "lcfirst", NULL, 125, &_3);
	zephir_check_call_status();
	zephir_update_static_property_array_multi_ce(zim_support_str_ce, SL("camelCache"), &_4 TSRMLS_CC, SL("z"), 1, &value);
	zephir_read_static_property_ce(&_5, zim_support_str_ce, SL("camelCache"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_6, &_5, &value, PH_NOISY | PH_READONLY, "zim/support/str.zep", 59 TSRMLS_CC);
	RETURN_CTOR(&_6);

}

/**
 * Determine if a given string contains a given substring.
 *
 * @param  string  $haystack
 * @param  string|array  $needles
 * @return bool
 */
PHP_METHOD(Zim_Support_Str, contains) {

	zend_bool _1$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_3 = NULL;
	zval *haystack_param = NULL, *needles, needles_sub, needle, arr, *_0, _2$$3;
	zval haystack;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&haystack);
	ZVAL_UNDEF(&needles_sub);
	ZVAL_UNDEF(&needle);
	ZVAL_UNDEF(&arr);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &haystack_param, &needles);

	zephir_get_strval(&haystack, haystack_param);


	if (Z_TYPE_P(needles) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&arr, needles);
	} else {
		ZEPHIR_INIT_NVAR(&arr);
		zephir_create_array(&arr, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&arr, needles);
	}
	zephir_is_iterable(&arr, 0, "zim/support/str.zep", 79);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&arr), _0)
	{
		ZEPHIR_INIT_NVAR(&needle);
		ZVAL_COPY(&needle, _0);
		_1$$3 = !ZEPHIR_IS_STRING_IDENTICAL(&needle, "");
		if (_1$$3) {
			ZEPHIR_CALL_FUNCTION(&_2$$3, "mb_strpos", &_3, 126, &haystack, &needle);
			zephir_check_call_status();
			_1$$3 = !ZEPHIR_IS_FALSE_IDENTICAL(&_2$$3);
		}
		if (_1$$3) {
			RETURN_MM_BOOL(1);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&needle);
	RETURN_MM_BOOL(0);

}

/**
 * Determine if a given string ends with a given substring.
 *
 * @param  string  $haystack
 * @param  string|array  $needles
 * @return bool
 */
PHP_METHOD(Zim_Support_Str, endsWith) {

	zval *haystack_param = NULL, *needles, needles_sub, needle, arr, *_0, _1$$3, _2$$3;
	zval haystack, _3$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&haystack);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&needles_sub);
	ZVAL_UNDEF(&needle);
	ZVAL_UNDEF(&arr);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &haystack_param, &needles);

	zephir_get_strval(&haystack, haystack_param);


	if (Z_TYPE_P(needles) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&arr, needles);
	} else {
		ZEPHIR_INIT_NVAR(&arr);
		zephir_create_array(&arr, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&arr, needles);
	}
	zephir_is_iterable(&arr, 0, "zim/support/str.zep", 99);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&arr), _0)
	{
		ZEPHIR_INIT_NVAR(&needle);
		ZVAL_COPY(&needle, _0);
		ZVAL_LONG(&_1$$3, -zephir_fast_strlen_ev(&needle));
		ZEPHIR_INIT_NVAR(&_2$$3);
		zephir_substr(&_2$$3, &haystack, zephir_get_intval(&_1$$3), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_get_strval(&_3$$3, &needle);
		if (ZEPHIR_IS_IDENTICAL(&_2$$3, &_3$$3)) {
			RETURN_MM_BOOL(1);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&needle);
	RETURN_MM_BOOL(0);

}

/**
 * Cap a string with a single instance of a given value.
 *
 * @param  string  $value
 * @param  string  $cap
 * @return string
 */
PHP_METHOD(Zim_Support_Str, finish) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, *cap_param = NULL, quoted, _0, _1, _2;
	zval value, cap;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&cap);
	ZVAL_UNDEF(&quoted);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &value_param, &cap_param);

	zephir_get_strval(&value, value_param);
	zephir_get_strval(&cap, cap_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "/");
	ZEPHIR_CALL_FUNCTION(&quoted, "preg_quote", NULL, 79, &cap, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SVS(&_1, "/(?:", &quoted, ")+$/u");
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "");
	ZEPHIR_CALL_FUNCTION(&_2, "preg_replace", NULL, 23, &_1, &_0, &value);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VV(return_value, &_2, &cap);
	RETURN_MM();

}

/**
 * Convert a string to kebab case.
 *
 * @param  string  $value
 * @return string
 */
PHP_METHOD(Zim_Support_Str, kebab) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, _0;
	zval value;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	zephir_get_strval(&value, value_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "-");
	ZEPHIR_RETURN_CALL_STATIC("snake", NULL, 0, &value, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the length of the given string.
 *
 * @param  string  $value
 * @param  string  $encoding
 * @return int
 */
PHP_METHOD(Zim_Support_Str, length) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *value_param = NULL, *encoding_param = NULL;
	zval value, encoding;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&encoding);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &value_param, &encoding_param);

	zephir_get_strval(&value, value_param);
	if (!encoding_param) {
		ZEPHIR_INIT_VAR(&encoding);
		ZVAL_STRING(&encoding, "");
	} else {
		zephir_get_strval(&encoding, encoding_param);
	}


	if (!(Z_TYPE_P(&encoding) == IS_UNDEF) && Z_STRLEN_P(&encoding)) {
		ZEPHIR_RETURN_CALL_FUNCTION("mb_strlen", &_0, 127, &value, &encoding);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_RETURN_CALL_FUNCTION("mb_strlen", &_0, 127, &value);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Limit the number of characters in a string.
 *
 * @param  string  $value
 * @param  int     $limit
 * @param  string  $end
 * @return string
 */
PHP_METHOD(Zim_Support_Str, limit) {

	zend_long limit, ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, *limit_param = NULL, *end_param = NULL, _0, _1, _2, _3, _4, _5, _6;
	zval value, end;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&end);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &value_param, &limit_param, &end_param);

	zephir_get_strval(&value, value_param);
	if (!limit_param) {
		limit = 100;
	} else {
		limit = zephir_get_intval(limit_param);
	}
	if (!end_param) {
		ZEPHIR_INIT_VAR(&end);
		ZVAL_STRING(&end, "...");
	} else {
		zephir_get_strval(&end, end_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "UTF-8");
	ZEPHIR_CALL_FUNCTION(&_1, "mb_strwidth", NULL, 128, &value, &_0);
	zephir_check_call_status();
	if (ZEPHIR_LE_LONG(&_1, limit)) {
		RETURN_CTOR(&value);
	}
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_2, 0);
	ZVAL_LONG(&_3, limit);
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "");
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "UTF-8");
	ZEPHIR_CALL_FUNCTION(&_6, "mb_strimwidth", NULL, 129, &value, &_2, &_3, &_4, &_5);
	zephir_check_call_status();
	zephir_fast_trim(&_0, &_6, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	ZEPHIR_CONCAT_VV(return_value, &_0, &end);
	RETURN_MM();

}

/**
 * Convert the given string to lower-case.
 *
 * @param  string  $value
 * @return string
 */
PHP_METHOD(Zim_Support_Str, lower) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, _0;
	zval value;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	zephir_get_strval(&value, value_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "UTF-8");
	ZEPHIR_RETURN_CALL_FUNCTION("mb_strtolower", NULL, 130, &value, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Limit the number of words in a string.
 *
 * @param  string  $value
 * @param  int     $words
 * @param  string  $end
 * @return string
 */
PHP_METHOD(Zim_Support_Str, words) {

	zend_bool _3;
	zval matches;
	zend_long words, ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, *words_param = NULL, *end_param = NULL, _0, _2, _4, _5, _6, _7, _8;
	zval value, end, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&end);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&matches);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &value_param, &words_param, &end_param);

	zephir_get_strval(&value, value_param);
	if (!words_param) {
		words = 100;
	} else {
		words = zephir_get_intval(words_param);
	}
	if (!end_param) {
		ZEPHIR_INIT_VAR(&end);
		ZVAL_STRING(&end, "...");
	} else {
		zephir_get_strval(&end, end_param);
	}


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, words);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SVS(&_1, "/^\\s*+(?:\\S++\\s*+){1,", &_0, "}/u");
	ZEPHIR_INIT_VAR(&_2);
	zephir_preg_match(&_2, &_1, &value, &matches, 0, 0 , 0  TSRMLS_CC);
	_3 = !(zephir_array_isset_long(&matches, 0));
	if (!(_3)) {
		ZEPHIR_CALL_STATIC(&_4, "length", NULL, 0, &value);
		zephir_check_call_status();
		zephir_array_fetch_long(&_6, &matches, 0, PH_NOISY | PH_READONLY, "zim/support/str.zep", 182 TSRMLS_CC);
		ZEPHIR_CALL_STATIC(&_5, "length", NULL, 0, &_6);
		zephir_check_call_status();
		_3 = ZEPHIR_IS_IDENTICAL(&_4, &_5);
	}
	if (_3) {
		RETURN_CTOR(&value);
	}
	ZEPHIR_INIT_VAR(&_7);
	zephir_array_fetch_long(&_8, &matches, 0, PH_NOISY | PH_READONLY, "zim/support/str.zep", 185 TSRMLS_CC);
	zephir_fast_trim(&_7, &_8, NULL , ZEPHIR_TRIM_RIGHT TSRMLS_CC);
	ZEPHIR_CONCAT_VV(return_value, &_7, &end);
	RETURN_MM();

}

/**
 * Generate a more truly "random" alpha-numeric string.
 *
 * @param  int  $length
 * @return string
 */
PHP_METHOD(Zim_Support_Str, random) {

	zval _2$$3;
	zephir_fcall_cache_entry *_0 = NULL, *_5 = NULL;
	zval *length_param = NULL, stringg, len, size, bytes, _1$$3, _3$$3, _4$$3, _6$$3, _7$$3, _8$$3;
	zend_long length, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&stringg);
	ZVAL_UNDEF(&len);
	ZVAL_UNDEF(&size);
	ZVAL_UNDEF(&bytes);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &length_param);

	if (!length_param) {
		length = 16;
	} else {
		length = zephir_get_intval(length_param);
	}


	ZEPHIR_INIT_VAR(&stringg);
	ZVAL_STRING(&stringg, "");
	ZEPHIR_INIT_VAR(&len);
	ZVAL_LONG(&len, zephir_fast_strlen_ev(&stringg));
	while (1) {
		if (!(ZEPHIR_LT_LONG(&len, length))) {
			break;
		}
		ZEPHIR_INIT_NVAR(&size);
		ZVAL_LONG(&size, (length - zephir_get_numberval(&len)));
		ZEPHIR_CALL_FUNCTION(&bytes, "random_bytes", &_0, 131, &size);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_1$$3);
		ZEPHIR_INIT_NVAR(&_2$$3);
		zephir_create_array(&_2$$3, 3, 0 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "/");
		zephir_array_fast_append(&_2$$3, &_3$$3);
		ZEPHIR_INIT_NVAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "+");
		zephir_array_fast_append(&_2$$3, &_3$$3);
		ZEPHIR_INIT_NVAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "=");
		zephir_array_fast_append(&_2$$3, &_3$$3);
		ZEPHIR_CALL_FUNCTION(&_4$$3, "base64_encode", &_5, 111, &bytes);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_3$$3);
		ZVAL_STRING(&_3$$3, "");
		zephir_fast_str_replace(&_1$$3, &_2$$3, &_3$$3, &_4$$3 TSRMLS_CC);
		ZVAL_LONG(&_6$$3, 0);
		ZEPHIR_INIT_NVAR(&_7$$3);
		zephir_substr(&_7$$3, &_1$$3, 0 , zephir_get_intval(&size), 0);
		ZEPHIR_INIT_LNVAR(_8$$3);
		ZEPHIR_CONCAT_VV(&_8$$3, &stringg, &_7$$3);
		ZEPHIR_CPY_WRT(&stringg, &_8$$3);
		ZEPHIR_INIT_NVAR(&len);
		ZVAL_LONG(&len, zephir_fast_strlen_ev(&stringg));
	}
	RETURN_CCTOR(&stringg);

}

/**
 * Replace a given value in the string sequentially with an array.
 *
 * @param  string  $search
 * @param  array   $replace
 * @param  string  $subject
 * @return string
 */
PHP_METHOD(Zim_Support_Str, replaceArray) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_2 = NULL;
	zval replace;
	zval *search_param = NULL, *replace_param = NULL, *subject_param = NULL, value, *_0, _1$$3;
	zval search, subject;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&search);
	ZVAL_UNDEF(&subject);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&replace);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &search_param, &replace_param, &subject_param);

	zephir_get_strval(&search, search_param);
	zephir_get_arrval(&replace, replace_param);
	zephir_get_strval(&subject, subject_param);


	zephir_is_iterable(&replace, 0, "zim/support/str.zep", 224);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&replace), _0)
	{
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _0);
		ZEPHIR_CALL_STATIC(&_1$$3, "replacefirst", &_2, 0, &search, &value, &subject);
		zephir_check_call_status();
		zephir_get_strval(&subject, &_1$$3);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	RETURN_CTOR(&subject);

}

/**
 * Replace the first occurrence of a given value in the string.
 *
 * @param  string  $search
 * @param  string  $replace
 * @param  string  $subject
 * @return string
 */
PHP_METHOD(Zim_Support_Str, replaceFirst) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *search_param = NULL, *replace_param = NULL, *subject_param = NULL, position, _0$$4;
	zval search, replace, subject;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&search);
	ZVAL_UNDEF(&replace);
	ZVAL_UNDEF(&subject);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&_0$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &search_param, &replace_param, &subject_param);

	zephir_get_strval(&search, search_param);
	zephir_get_strval(&replace, replace_param);
	zephir_get_strval(&subject, subject_param);


	if (ZEPHIR_IS_STRING(&search, "")) {
		RETURN_CTOR(&subject);
	}
	ZEPHIR_INIT_VAR(&position);
	zephir_fast_strpos(&position, &subject, &search, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&position)) {
		ZVAL_LONG(&_0$$4, zephir_fast_strlen_ev(&search));
		ZEPHIR_RETURN_CALL_FUNCTION("substr_replace", NULL, 52, &subject, &replace, &position, &_0$$4);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_CTOR(&subject);

}

/**
 * Replace the last occurrence of a given value in the string.
 *
 * @param  string  $search
 * @param  string  $replace
 * @param  string  $subject
 * @return string
 */
PHP_METHOD(Zim_Support_Str, replaceLast) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *search_param = NULL, *replace_param = NULL, *subject_param = NULL, position, _0$$3;
	zval search, replace, subject;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&search);
	ZVAL_UNDEF(&replace);
	ZVAL_UNDEF(&subject);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &search_param, &replace_param, &subject_param);

	zephir_get_strval(&search, search_param);
	zephir_get_strval(&replace, replace_param);
	zephir_get_strval(&subject, subject_param);


	ZEPHIR_CALL_FUNCTION(&position, "strrpos", NULL, 49, &subject, &search);
	zephir_check_call_status();
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&position)) {
		ZVAL_LONG(&_0$$3, zephir_fast_strlen_ev(&search));
		ZEPHIR_RETURN_CALL_FUNCTION("substr_replace", NULL, 52, &subject, &replace, &position, &_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_CTOR(&subject);

}

/**
 * Begin a string with a single instance of a given value.
 *
 * @param  string  $value
 * @param  string  $prefix
 * @return string
 */
PHP_METHOD(Zim_Support_Str, start) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, *prefix_param = NULL, quoted, _0, _1, _2;
	zval value, prefix;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&quoted);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &value_param, &prefix_param);

	zephir_get_strval(&value, value_param);
	zephir_get_strval(&prefix, prefix_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "/");
	ZEPHIR_CALL_FUNCTION(&quoted, "preg_quote", NULL, 79, &prefix, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SVS(&_1, "/^(?:", &quoted, ")+/u");
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "");
	ZEPHIR_CALL_FUNCTION(&_2, "preg_replace", NULL, 23, &_1, &_0, &value);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VV(return_value, &prefix, &_2);
	RETURN_MM();

}

/**
 * Convert the given string to upper-case.
 *
 * @param  string  $value
 * @return string
 */
PHP_METHOD(Zim_Support_Str, upper) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, _0;
	zval value;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	zephir_get_strval(&value, value_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "UTF-8");
	ZEPHIR_RETURN_CALL_FUNCTION("mb_strtoupper", NULL, 132, &value, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Convert the given string to title case.
 *
 * @param  string  $value
 * @return string
 */
PHP_METHOD(Zim_Support_Str, title) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, _0, _1;
	zval value;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	zephir_get_strval(&value, value_param);


	ZVAL_LONG(&_0, 2);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "UTF-8");
	ZEPHIR_RETURN_CALL_FUNCTION("mb_convert_case", NULL, 133, &value, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Convert a string to snake case.
 *
 * @param  string  $value
 * @param  string  $delimiter
 * @return string
 */
PHP_METHOD(Zim_Support_Str, snake) {

	zephir_fcall_cache_entry *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, *delimiter_param = NULL, key, tmpValue, _0, _1, _5, _12, _13, _14, _2$$3, _3$$3, _4$$3, _6$$4, _7$$4, _8$$4, _11$$4;
	zval value, delimiter, _10$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&delimiter);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&tmpValue);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_11$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &value_param, &delimiter_param);

	zephir_get_strval(&value, value_param);
	if (!delimiter_param) {
		ZEPHIR_INIT_VAR(&delimiter);
		ZVAL_STRING(&delimiter, "_");
	} else {
		zephir_get_strval(&delimiter, delimiter_param);
	}


	ZEPHIR_CPY_WRT(&key, &value);
	zephir_read_static_property_ce(&_0, zim_support_str_ce, SL("snakeCache"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_1, &_0, &key, PH_READONLY, "zim/support/str.zep", 317 TSRMLS_CC);
	if (zephir_array_isset(&_1, &delimiter)) {
		zephir_read_static_property_ce(&_2$$3, zim_support_str_ce, SL("snakeCache"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_3$$3, &_2$$3, &key, PH_NOISY | PH_READONLY, "zim/support/str.zep", 318 TSRMLS_CC);
		zephir_array_fetch(&_4$$3, &_3$$3, &delimiter, PH_NOISY | PH_READONLY, "zim/support/str.zep", 318 TSRMLS_CC);
		RETURN_CTOR(&_4$$3);
	}
	ZEPHIR_CALL_FUNCTION(&_5, "ctype_lower", NULL, 134, &value);
	zephir_check_call_status();
	if (!(zephir_is_true(&_5))) {
		ZEPHIR_CALL_FUNCTION(&_6$$4, "ucwords", NULL, 19, &value);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_7$$4);
		ZVAL_STRING(&_7$$4, "/\\s+/u");
		ZEPHIR_INIT_VAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "");
		ZEPHIR_CALL_FUNCTION(&tmpValue, "preg_replace", &_9, 23, &_7$$4, &_8$$4, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_10$$4);
		ZEPHIR_CONCAT_SV(&_10$$4, "$1", &delimiter);
		ZEPHIR_INIT_NVAR(&_7$$4);
		ZVAL_STRING(&_7$$4, "/(.)(?=[A-Z])/u");
		ZEPHIR_CALL_FUNCTION(&_11$$4, "preg_replace", &_9, 23, &_7$$4, &_10$$4, &tmpValue);
		zephir_check_call_status();
		ZEPHIR_CALL_STATIC(&tmpValue, "lower", NULL, 0, &_11$$4);
		zephir_check_call_status();
		zephir_get_strval(&value, &tmpValue);
	}
	zephir_update_static_property_array_multi_ce(zim_support_str_ce, SL("snakeCache"), &value TSRMLS_CC, SL("zz"), 2, &key, &delimiter);
	zephir_read_static_property_ce(&_12, zim_support_str_ce, SL("snakeCache"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_13, &_12, &key, PH_NOISY | PH_READONLY, "zim/support/str.zep", 326 TSRMLS_CC);
	zephir_array_fetch(&_14, &_13, &delimiter, PH_NOISY | PH_READONLY, "zim/support/str.zep", 326 TSRMLS_CC);
	RETURN_CTOR(&_14);

}

/**
 * Determine if a given string starts with a given substring.
 *
 * @param  string  $haystack
 * @param  string|array  $needles
 * @return bool
 */
PHP_METHOD(Zim_Support_Str, startsWith) {

	zend_bool _1$$3;
	zval *haystack_param = NULL, *needles, needles_sub, needle, arr, *_0, _2$$3, _3$$3, _4$$3;
	zval haystack, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&haystack);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&needles_sub);
	ZVAL_UNDEF(&needle);
	ZVAL_UNDEF(&arr);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &haystack_param, &needles);

	zephir_get_strval(&haystack, haystack_param);


	if (Z_TYPE_P(needles) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&arr, needles);
	} else {
		ZEPHIR_INIT_NVAR(&arr);
		zephir_create_array(&arr, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&arr, needles);
	}
	zephir_is_iterable(&arr, 0, "zim/support/str.zep", 346);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&arr), _0)
	{
		ZEPHIR_INIT_NVAR(&needle);
		ZVAL_COPY(&needle, _0);
		_1$$3 = !ZEPHIR_IS_STRING_IDENTICAL(&needle, "");
		if (_1$$3) {
			ZVAL_LONG(&_2$$3, 0);
			ZVAL_LONG(&_3$$3, zephir_fast_strlen_ev(&needle));
			ZEPHIR_INIT_NVAR(&_4$$3);
			zephir_substr(&_4$$3, &haystack, 0 , zephir_get_intval(&_3$$3), 0);
			zephir_get_strval(&_5$$3, &needle);
			_1$$3 = ZEPHIR_IS_IDENTICAL(&_4$$3, &_5$$3);
		}
		if (_1$$3) {
			RETURN_MM_BOOL(1);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&needle);
	RETURN_MM_BOOL(0);

}

/**
 * Convert a value to studly caps case.
 *
 * @param  string  $value
 * @return string
 */
PHP_METHOD(Zim_Support_Str, studly) {

	zval _4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, key, tmpValue, _0, _3, _5, _6, _7, _8, _9, _10, _1$$3, _2$$3;
	zval value;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&tmpValue);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &value_param);

	zephir_get_strval(&value, value_param);


	ZEPHIR_CPY_WRT(&key, &value);
	zephir_read_static_property_ce(&_0, zim_support_str_ce, SL("studlyCache"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_0, &key)) {
		zephir_read_static_property_ce(&_1$$3, zim_support_str_ce, SL("studlyCache"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_2$$3, &_1$$3, &key, PH_NOISY | PH_READONLY, "zim/support/str.zep", 361 TSRMLS_CC);
		RETURN_CTOR(&_2$$3);
	}
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_INIT_VAR(&_4);
	zephir_create_array(&_4, 2, 0 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_5);
	ZVAL_STRING(&_5, "-");
	zephir_array_fast_append(&_4, &_5);
	ZEPHIR_INIT_NVAR(&_5);
	ZVAL_STRING(&_5, "_");
	zephir_array_fast_append(&_4, &_5);
	ZEPHIR_INIT_NVAR(&_5);
	ZVAL_STRING(&_5, " ");
	zephir_fast_str_replace(&_3, &_4, &_5, &value TSRMLS_CC);
	ZEPHIR_CALL_FUNCTION(&tmpValue, "ucwords", NULL, 19, &_3);
	zephir_check_call_status();
	zephir_get_strval(&value, &tmpValue);
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_INIT_VAR(&_7);
	ZVAL_STRING(&_7, " ");
	ZEPHIR_INIT_VAR(&_8);
	ZVAL_STRING(&_8, "");
	zephir_fast_str_replace(&_6, &_7, &_8, &value TSRMLS_CC);
	zephir_update_static_property_array_multi_ce(zim_support_str_ce, SL("studlyCache"), &_6 TSRMLS_CC, SL("z"), 1, &key);
	zephir_read_static_property_ce(&_9, zim_support_str_ce, SL("studlyCache"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_10, &_9, &key, PH_NOISY | PH_READONLY, "zim/support/str.zep", 367 TSRMLS_CC);
	RETURN_CTOR(&_10);

}

/**
 * Returns the portion of string specified by the start and length parameters.
 *
 * @param  string  $string
 * @param  int  $start
 * @param  int|null  $length
 * @return string
 */
PHP_METHOD(Zim_Support_Str, substr) {

	zend_long start, ZEPHIR_LAST_CALL_STATUS;
	zval *stringg_param = NULL, *start_param = NULL, *length = NULL, length_sub, __$null, _0, _1;
	zval stringg;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&stringg);
	ZVAL_UNDEF(&length_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &stringg_param, &start_param, &length);

	zephir_get_strval(&stringg, stringg_param);
	start = zephir_get_intval(start_param);
	if (!length) {
		length = &length_sub;
		length = &__$null;
	}


	ZVAL_LONG(&_0, start);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "UTF-8");
	ZEPHIR_RETURN_CALL_FUNCTION("mb_substr", NULL, 135, &stringg, &_0, length, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Make a string's first character uppercase.
 *
 * @param  string  $string
 * @return string
 */
PHP_METHOD(Zim_Support_Str, ucfirst) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *stringg_param = NULL, _0, _1, _2, _3, _4;
	zval stringg;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&stringg);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &stringg_param);

	zephir_get_strval(&stringg, stringg_param);


	ZVAL_LONG(&_2, 0);
	ZVAL_LONG(&_3, 1);
	ZEPHIR_CALL_STATIC(&_1, "substr", NULL, 0, &stringg, &_2, &_3);
	zephir_check_call_status();
	ZEPHIR_CALL_STATIC(&_0, "upper", NULL, 0, &_1);
	zephir_check_call_status();
	ZVAL_LONG(&_2, 1);
	ZEPHIR_CALL_STATIC(&_4, "substr", NULL, 0, &stringg, &_2);
	zephir_check_call_status();
	ZEPHIR_CONCAT_VV(return_value, &_0, &_4);
	RETURN_MM();

}

void zephir_init_static_properties_Zim_Support_Str(TSRMLS_D) {

	zval _0, _1, _2;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zend_update_static_property(zim_support_str_ce, ZEND_STRL("studlyCache"), &_0);
	ZEPHIR_INIT_VAR(&_1);
	array_init(&_1);
	zend_update_static_property(zim_support_str_ce, ZEND_STRL("camelCache"), &_1);
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zend_update_static_property(zim_support_str_ce, ZEND_STRL("snakeCache"), &_2);
	ZEPHIR_MM_RESTORE();

}

