
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
#include "kernel/fcall.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/operators.h"
#include "kernel/array.h"


/**
 * HTTP header utility functions.
 *
 * @author Christian Schmidt <github@chsc.dk>
 */
ZEPHIR_INIT_CLASS(Zim_Http_HeaderUtils) {

	ZEPHIR_REGISTER_CLASS(Zim\\Http, HeaderUtils, zim, http_headerutils, zim_http_headerutils_method_entry, 0);

	return SUCCESS;

}

/**
 * This class should not be instantiated.
 */
PHP_METHOD(Zim_Http_HeaderUtils, __construct) {

	zval *this_ptr = getThis();



}

/**
 * Splits an HTTP header by one or more separators.
 *
 * Example:
 *
 *     HeaderUtils::split("da, en-gb;q=0.8", ",;")
 *     // => array(array('da'), array('en-gb', 'q=0.8'))
 *
 * @param string $header     HTTP header value
 * @param string $separators List of characters to split on, ordered by
 *                           precedence, e.g. ",", ";=", or ",;="
 *
 * @return array Nested array with as many levels as there are characters in
 *               $separators
 */
PHP_METHOD(Zim_Http_HeaderUtils, split) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *header_param = NULL, *separators_param = NULL, quotedSeparators, matches, _0, _1, _2, _3, _4;
	zval header, separators;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&header);
	ZVAL_UNDEF(&separators);
	ZVAL_UNDEF(&quotedSeparators);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &header_param, &separators_param);

	zephir_get_strval(&header, header_param);
	zephir_get_strval(&separators, separators_param);


	ZEPHIR_INIT_VAR(&matches);
	array_init(&matches);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "/");
	ZEPHIR_CALL_FUNCTION(&quotedSeparators, "preg_quote", NULL, 76, &separators, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SVSVS(&_1, "\n            /\n                (?!\\s)\n                    (?:\n                        # quoted-string\n                        \"(?:[^\"\\\\]|\\\\.)*(?:\"|\\\\|$)\n                    |\n                        # token\n                        [^\"", &quotedSeparators, "]+\n                    )+\n                (?<!\\s)\n            |\n                # separator\n                \\s*\n                (?<separator>[", &quotedSeparators, "])\n                \\s*\n            /x");
	ZEPHIR_INIT_NVAR(&_0);
	zephir_fast_trim(&_0, &header, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	ZVAL_LONG(&_2, 2);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_LONG(&_4, 2);
	zephir_preg_match(&_3, &_1, &_0, &matches, 1, zephir_get_intval(&_2) , 0  TSRMLS_CC);
	ZEPHIR_RETURN_CALL_SELF("groupparts", NULL, 0, &matches, &separators);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Combines an array of arrays into one associative array.
 *
 * Each of the nested arrays should have one or two elements. The first
 * value will be used as the keys in the associative array, and the second
 * will be used as the values, or true if the nested array only contains one
 * element. Array keys are lowercased.
 *
 * Example:
 *
 *     HeaderUtils::combine(array(array("foo", "abc"), array("bar")))
 *     // => array("foo" => "abc", "bar" => true)
 */
PHP_METHOD(Zim_Http_HeaderUtils, combine) {

	zval *parts_param = NULL, assoc, part, name, value, *_0, _1$$3;
	zval parts;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&assoc);
	ZVAL_UNDEF(&part);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parts_param);

	zephir_get_arrval(&parts, parts_param);


	ZEPHIR_INIT_VAR(&assoc);
	array_init(&assoc);
	zephir_is_iterable(&parts, 0, "zim/http/headerutils.zep", 73);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&parts), _0)
	{
		ZEPHIR_INIT_NVAR(&part);
		ZVAL_COPY(&part, _0);
		zephir_array_fetch_long(&_1$$3, &part, 0, PH_NOISY | PH_READONLY, "zim/http/headerutils.zep", 69 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&name);
		zephir_fast_strtolower(&name, &_1$$3);
		if (zephir_array_isset_long(&part, 1)) {
			ZEPHIR_OBS_NVAR(&value);
			zephir_array_fetch_long(&value, &part, 1, PH_NOISY, "zim/http/headerutils.zep", 70 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_BOOL(&value, 1);
		}
		zephir_array_update_zval(&assoc, &name, &value, PH_COPY | PH_SEPARATE);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&part);
	RETURN_CCTOR(&assoc);

}

/**
 * Joins an associative array into a string for use in an HTTP header.
 *
 * The key and value of each entry are joined with "=", and all entries
 * are joined with the specified separator and an additional space (for
 * readability). Values are quoted if necessary.
 *
 * Example:
 *
 *     HeaderUtils::toString(array("foo" => "abc", "bar" => true, "baz" => "a b c"), ",")
 *     // => 'foo=abc, bar, baz="a b c"'
 */
PHP_METHOD(Zim_Http_HeaderUtils, toString) {

	zend_string *_2;
	zend_ulong _1;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_4 = NULL;
	zval separator, _6;
	zval *assoc_param = NULL, *separator_param = NULL, parts, name, value, *_0, _3$$5, _5$$5;
	zval assoc;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&assoc);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&separator);
	ZVAL_UNDEF(&_6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &assoc_param, &separator_param);

	zephir_get_arrval(&assoc, assoc_param);
	zephir_get_strval(&separator, separator_param);


	ZEPHIR_INIT_VAR(&parts);
	array_init(&parts);
	zephir_is_iterable(&assoc, 0, "zim/http/headerutils.zep", 100);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&assoc), _1, _2, _0)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_2 != NULL) { 
			ZVAL_STR_COPY(&name, _2);
		} else {
			ZVAL_LONG(&name, _1);
		}
		ZEPHIR_INIT_NVAR(&value);
		ZVAL_COPY(&value, _0);
		if (ZEPHIR_IS_TRUE_IDENTICAL(&value)) {
			zephir_array_append(&parts, &name, PH_SEPARATE, "zim/http/headerutils.zep", 95);
		} else {
			ZEPHIR_CALL_SELF(&_3$$5, "quote", &_4, 0, &value);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_5$$5);
			ZEPHIR_CONCAT_VSV(&_5$$5, &name, "=", &_3$$5);
			zephir_array_append(&parts, &_5$$5, PH_SEPARATE, "zim/http/headerutils.zep", 97);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&name);
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CONCAT_VS(&_6, &separator, " ");
	zephir_fast_join(return_value, &_6, &parts TSRMLS_CC);
	RETURN_MM();

}

/**
 * Encodes a string as a quoted string, if necessary.
 *
 * If a string contains characters not allowed by the "token" construct in
 * the HTTP specification, it is backslash-escaped and enclosed in quotes
 * to match the "quoted-string" construct.
 */
PHP_METHOD(Zim_Http_HeaderUtils, quote) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *s_param = NULL, _0, _1, _2, _3, _4, _5;
	zval s;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&s);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &s_param);

	zephir_get_strval(&s, s_param);


	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "/^[a-z0-9!#$%&'*.^_`|~-]+$/i");
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "/^[a-z0-9!#$%&'*.^_`|~-]+$/i");
	zephir_preg_match(&_2, &_3, &s, &_0, 0, 0 , 0  TSRMLS_CC);
	if (zephir_is_true(&_2)) {
		RETURN_CTOR(&s);
	}
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "\"\\\"");
	ZEPHIR_CALL_FUNCTION(&_5, "addcslashes", NULL, 77, &s, &_4);
	zephir_check_call_status();
	ZEPHIR_CONCAT_SVS(return_value, "\"", &_5, "\"");
	RETURN_MM();

}

/**
 * Decodes a quoted string.
 *
 * If passed an unquoted string that matches the "token" construct (as
 * defined in the HTTP specification), it is passed through verbatimly.
 */
PHP_METHOD(Zim_Http_HeaderUtils, unquote) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *s_param = NULL, _0, _1;
	zval s;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&s);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &s_param);

	zephir_get_strval(&s, s_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "/\\\\(.)|\"/");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "$1");
	ZEPHIR_RETURN_CALL_FUNCTION("preg_replace", NULL, 78, &_0, &_1, &s);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Zim_Http_HeaderUtils, groupParts) {

	zend_bool _3$$3;
	unsigned char _0;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0;
	zephir_fcall_cache_entry *_7 = NULL, *_10 = NULL;
	zval separators;
	zval *tmpmatches_param = NULL, *separators_param = NULL, separator, partSeparators, partMatches, match, parts, matches, _1, *_2, _4$$3, *_5$$6, _6$$7, *_8$$8, _9$$9, _11$$9, _12$$9;
	zval tmpmatches;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tmpmatches);
	ZVAL_UNDEF(&separator);
	ZVAL_UNDEF(&partSeparators);
	ZVAL_UNDEF(&partMatches);
	ZVAL_UNDEF(&match);
	ZVAL_UNDEF(&parts);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&separators);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &tmpmatches_param, &separators_param);

	zephir_get_arrval(&tmpmatches, tmpmatches_param);
	zephir_get_strval(&separators, separators_param);


	ZEPHIR_CPY_WRT(&matches, &tmpmatches);
	_0 = ZEPHIR_STRING_OFFSET(&separators, 0);
	ZEPHIR_INIT_VAR(&separator);
	ZVAL_LONG(&separator, _0);
	ZVAL_LONG(&_1, 1);
	ZEPHIR_INIT_VAR(&partSeparators);
	zephir_substr(&partSeparators, &separators, 1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
	i = 0;
	ZEPHIR_INIT_VAR(&partMatches);
	array_init(&partMatches);
	zephir_is_iterable(&matches, 0, "zim/http/headerutils.zep", 146);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&matches), _2)
	{
		ZEPHIR_INIT_NVAR(&match);
		ZVAL_COPY(&match, _2);
		_3$$3 = zephir_array_isset_string(&match, SL("separator"));
		if (_3$$3) {
			zephir_array_fetch_string(&_4$$3, &match, SL("separator"), PH_NOISY | PH_READONLY, "zim/http/headerutils.zep", 140 TSRMLS_CC);
			_3$$3 = ZEPHIR_IS_IDENTICAL(&_4$$3, &separator);
		}
		if (_3$$3) {
			i++;
		} else {
			zephir_array_update_multi(&partMatches, &match TSRMLS_CC, SL("la"), 2, i);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&match);
	ZEPHIR_INIT_VAR(&parts);
	array_init(&parts);
	if (zephir_is_true(&partSeparators)) {
		zephir_is_iterable(&partMatches, 0, "zim/http/headerutils.zep", 151);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&partMatches), _5$$6)
		{
			ZEPHIR_INIT_NVAR(&matches);
			ZVAL_COPY(&matches, _5$$6);
			ZEPHIR_CALL_SELF(&_6$$7, "groupparts", &_7, 0, &matches, &partSeparators);
			zephir_check_call_status();
			zephir_array_append(&parts, &_6$$7, PH_SEPARATE, "zim/http/headerutils.zep", 149);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&matches);
	} else {
		zephir_is_iterable(&partMatches, 0, "zim/http/headerutils.zep", 155);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&partMatches), _8$$8)
		{
			ZEPHIR_INIT_NVAR(&matches);
			ZVAL_COPY(&matches, _8$$8);
			zephir_array_fetch_long(&_11$$9, &matches, 0, PH_NOISY | PH_READONLY, "zim/http/headerutils.zep", 153 TSRMLS_CC);
			zephir_array_fetch_long(&_12$$9, &_11$$9, 0, PH_NOISY | PH_READONLY, "zim/http/headerutils.zep", 153 TSRMLS_CC);
			ZEPHIR_CALL_SELF(&_9$$9, "unquote", &_10, 0, &_12$$9);
			zephir_check_call_status();
			zephir_array_append(&parts, &_9$$9, PH_SEPARATE, "zim/http/headerutils.zep", 153);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&matches);
	}
	RETURN_CCTOR(&parts);

}

