
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
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/**
 * RouteCompiler compiles Route instances to CompiledRoute instances.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 * @author Tobias Schultze <http://tobion.de>
 */
ZEPHIR_INIT_CLASS(Zim_Routing_RouteCompiler) {

	ZEPHIR_REGISTER_CLASS(Zim\\Routing, RouteCompiler, zim, routing_routecompiler, zim_routing_routecompiler_method_entry, 0);

	zephir_declare_class_constant_string(zim_routing_routecompiler_ce, SL("REGEX_DELIMITER"), "#");

	/**
	 * This string defines the characters that are automatically considered separators in front of
	 * optional placeholders (with default and no static text following). Such a single separator
	 * can be left out together with the optional placeholder from matching and generating URLs.
	 */
	zephir_declare_class_constant_string(zim_routing_routecompiler_ce, SL("SEPARATORS"), "/,;.:-_~+*=@|");

	/**
	 * The maximum supported length of a PCRE subpattern name
	 * http://pcre.org/current/doc/html/pcre2pattern.html#SEC16.
	 *
	 * @internal
	 */
	zephir_declare_class_constant_long(zim_routing_routecompiler_ce, SL("VARIABLE_MAXIMUM_LENGTH"), 32);

	return SUCCESS;

}

/**
 * {@inheritdoc}
 *
 * @throws \InvalidArgumentException if a path variable is named _fragment
 * @throws \LogicException           if a variable is referenced more than once
 * @throws \DomainException          if a variable name starts with a digit or if it is too long to be successfully used as
 *                                   a PCRE subpattern
 */
PHP_METHOD(Zim_Routing_RouteCompiler, compile) {

	zephir_fcall_cache_entry *_5 = NULL, *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *route, route_sub, variables, path, result, staticPrefix, pathVariables, pathParam, tokens, regex, *_0, _7, _8, _1$$4, _2$$4, _3$$4, _4$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&route_sub);
	ZVAL_UNDEF(&variables);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&staticPrefix);
	ZVAL_UNDEF(&pathVariables);
	ZVAL_UNDEF(&pathParam);
	ZVAL_UNDEF(&tokens);
	ZVAL_UNDEF(&regex);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &route);



	ZEPHIR_INIT_VAR(&variables);
	array_init(&variables);
	ZEPHIR_CALL_METHOD(&path, route, "getpath", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_SELF(&result, "compilepattern", NULL, 0, route, &path);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&staticPrefix);
	zephir_array_fetch_string(&staticPrefix, &result, SL("staticPrefix"), PH_NOISY, "zim/routing/routecompiler.zep", 48 TSRMLS_CC);
	ZEPHIR_OBS_VAR(&pathVariables);
	zephir_array_fetch_string(&pathVariables, &result, SL("variables"), PH_NOISY, "zim/routing/routecompiler.zep", 49 TSRMLS_CC);
	zephir_is_iterable(&pathVariables, 0, "zim/routing/routecompiler.zep", 55);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&pathVariables), _0)
	{
		ZEPHIR_INIT_NVAR(&pathParam);
		ZVAL_COPY(&pathParam, _0);
		if (ZEPHIR_IS_STRING_IDENTICAL(&pathParam, "_fragment")) {
			ZEPHIR_INIT_NVAR(&_1$$4);
			object_init_ex(&_1$$4, spl_ce_InvalidArgumentException);
			ZEPHIR_CALL_METHOD(&_2$$4, route, "getpath", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_3$$4);
			ZVAL_STRING(&_3$$4, "Route pattern \"%s\" cannot contain \"_fragment\" as a path parameter.");
			ZEPHIR_CALL_FUNCTION(&_4$$4, "sprintf", &_5, 22, &_3$$4, &_2$$4);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &_1$$4, "__construct", &_6, 28, &_4$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_1$$4, "zim/routing/routecompiler.zep", 52 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&pathParam);
	ZEPHIR_INIT_VAR(&_7);
	zephir_fast_array_merge(&_7, &variables, &pathVariables TSRMLS_CC);
	ZEPHIR_CPY_WRT(&variables, &_7);
	ZEPHIR_OBS_VAR(&tokens);
	zephir_array_fetch_string(&tokens, &result, SL("tokens"), PH_NOISY, "zim/routing/routecompiler.zep", 56 TSRMLS_CC);
	ZEPHIR_OBS_VAR(&regex);
	zephir_array_fetch_string(&regex, &result, SL("regex"), PH_NOISY, "zim/routing/routecompiler.zep", 57 TSRMLS_CC);
	object_init_ex(return_value, zim_routing_compiledroute_ce);
	ZEPHIR_CALL_FUNCTION(&_8, "array_unique", NULL, 107, &variables);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 108, &staticPrefix, &regex, &tokens, &pathVariables, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Zim_Routing_RouteCompiler, compilePattern) {

	zval _71$$14;
	zval _101$$5, _63$$12, _67$$13, _105$$20;
	zend_bool isSeparator = 0, _4, _5, _14, _107, _115, _42$$5, _60$$5, _61$$5, _77$$14, _78$$14, _82$$14, _87$$16, _95$$16, _111$$21, _121$$25;
	zephir_fcall_cache_entry *_13 = NULL, *_35 = NULL, *_52 = NULL, *_69 = NULL, *_72 = NULL, *_75 = NULL, *_100 = NULL, *_114 = NULL, *_119 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, _108, _109, _116, _122$$25;
	zval *route, route_sub, *pattern, pattern_sub, __$true, tokens, variables, matches, pos, defaultSeparator, useUtf8, needsUtf8, match, varName, precedingText, precedingChar, regexp, followingPattern, nextSeparator, firstOptional, i, token, nbToken, _0, _1, _2, _3, _6, _7, _8, _18, _19, _20, _21, _22, *_23, _104, _117, _120, _126, _9$$3, _10$$3, _11$$3, _12$$3, _15$$4, _16$$4, _17$$4, _24$$5, _25$$5, _26$$5, _27$$5, _28$$5, _29$$5, _30$$5, _31$$5, _32$$5, _33$$5, _34$$5, _41$$5, _43$$5, _44$$5, _45$$5, _46$$5, _47$$5, _48$$5, _62$$5, _102$$5, _103$$5, _36$$7, _37$$7, _38$$7, _39$$7, _40$$8, _49$$9, _50$$9, _51$$9, _53$$10, _54$$10, _55$$10, _56$$11, _57$$11, _58$$11, _59$$11, _64$$12, _65$$12, _66$$12, _68$$13, _70$$14, _73$$14, _74$$14, _76$$14, _79$$14, _80$$14, _81$$14, _83$$16, _84$$16, _85$$16, _86$$16, _88$$16, _89$$16, _90$$16, _91$$16, _99$$16, _92$$18, _93$$18, _94$$18, _96$$19, _97$$19, _98$$19, _106$$20, _110$$21, _112$$21, _113$$21, _118$$24, _123$$25, _124$$26, _125$$26;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&route_sub);
	ZVAL_UNDEF(&pattern_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&tokens);
	ZVAL_UNDEF(&variables);
	ZVAL_UNDEF(&matches);
	ZVAL_UNDEF(&pos);
	ZVAL_UNDEF(&defaultSeparator);
	ZVAL_UNDEF(&useUtf8);
	ZVAL_UNDEF(&needsUtf8);
	ZVAL_UNDEF(&match);
	ZVAL_UNDEF(&varName);
	ZVAL_UNDEF(&precedingText);
	ZVAL_UNDEF(&precedingChar);
	ZVAL_UNDEF(&regexp);
	ZVAL_UNDEF(&followingPattern);
	ZVAL_UNDEF(&nextSeparator);
	ZVAL_UNDEF(&firstOptional);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&token);
	ZVAL_UNDEF(&nbToken);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_19);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_21);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_104);
	ZVAL_UNDEF(&_117);
	ZVAL_UNDEF(&_120);
	ZVAL_UNDEF(&_126);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);
	ZVAL_UNDEF(&_12$$3);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_17$$4);
	ZVAL_UNDEF(&_24$$5);
	ZVAL_UNDEF(&_25$$5);
	ZVAL_UNDEF(&_26$$5);
	ZVAL_UNDEF(&_27$$5);
	ZVAL_UNDEF(&_28$$5);
	ZVAL_UNDEF(&_29$$5);
	ZVAL_UNDEF(&_30$$5);
	ZVAL_UNDEF(&_31$$5);
	ZVAL_UNDEF(&_32$$5);
	ZVAL_UNDEF(&_33$$5);
	ZVAL_UNDEF(&_34$$5);
	ZVAL_UNDEF(&_41$$5);
	ZVAL_UNDEF(&_43$$5);
	ZVAL_UNDEF(&_44$$5);
	ZVAL_UNDEF(&_45$$5);
	ZVAL_UNDEF(&_46$$5);
	ZVAL_UNDEF(&_47$$5);
	ZVAL_UNDEF(&_48$$5);
	ZVAL_UNDEF(&_62$$5);
	ZVAL_UNDEF(&_102$$5);
	ZVAL_UNDEF(&_103$$5);
	ZVAL_UNDEF(&_36$$7);
	ZVAL_UNDEF(&_37$$7);
	ZVAL_UNDEF(&_38$$7);
	ZVAL_UNDEF(&_39$$7);
	ZVAL_UNDEF(&_40$$8);
	ZVAL_UNDEF(&_49$$9);
	ZVAL_UNDEF(&_50$$9);
	ZVAL_UNDEF(&_51$$9);
	ZVAL_UNDEF(&_53$$10);
	ZVAL_UNDEF(&_54$$10);
	ZVAL_UNDEF(&_55$$10);
	ZVAL_UNDEF(&_56$$11);
	ZVAL_UNDEF(&_57$$11);
	ZVAL_UNDEF(&_58$$11);
	ZVAL_UNDEF(&_59$$11);
	ZVAL_UNDEF(&_64$$12);
	ZVAL_UNDEF(&_65$$12);
	ZVAL_UNDEF(&_66$$12);
	ZVAL_UNDEF(&_68$$13);
	ZVAL_UNDEF(&_70$$14);
	ZVAL_UNDEF(&_73$$14);
	ZVAL_UNDEF(&_74$$14);
	ZVAL_UNDEF(&_76$$14);
	ZVAL_UNDEF(&_79$$14);
	ZVAL_UNDEF(&_80$$14);
	ZVAL_UNDEF(&_81$$14);
	ZVAL_UNDEF(&_83$$16);
	ZVAL_UNDEF(&_84$$16);
	ZVAL_UNDEF(&_85$$16);
	ZVAL_UNDEF(&_86$$16);
	ZVAL_UNDEF(&_88$$16);
	ZVAL_UNDEF(&_89$$16);
	ZVAL_UNDEF(&_90$$16);
	ZVAL_UNDEF(&_91$$16);
	ZVAL_UNDEF(&_99$$16);
	ZVAL_UNDEF(&_92$$18);
	ZVAL_UNDEF(&_93$$18);
	ZVAL_UNDEF(&_94$$18);
	ZVAL_UNDEF(&_96$$19);
	ZVAL_UNDEF(&_97$$19);
	ZVAL_UNDEF(&_98$$19);
	ZVAL_UNDEF(&_106$$20);
	ZVAL_UNDEF(&_110$$21);
	ZVAL_UNDEF(&_112$$21);
	ZVAL_UNDEF(&_113$$21);
	ZVAL_UNDEF(&_118$$24);
	ZVAL_UNDEF(&_123$$25);
	ZVAL_UNDEF(&_124$$26);
	ZVAL_UNDEF(&_125$$26);
	ZVAL_UNDEF(&_101$$5);
	ZVAL_UNDEF(&_63$$12);
	ZVAL_UNDEF(&_67$$13);
	ZVAL_UNDEF(&_105$$20);
	ZVAL_UNDEF(&_71$$14);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &route, &pattern);



	ZEPHIR_INIT_VAR(&tokens);
	array_init(&tokens);
	ZEPHIR_INIT_VAR(&variables);
	array_init(&variables);
	ZEPHIR_INIT_VAR(&matches);
	array_init(&matches);
	ZEPHIR_INIT_VAR(&pos);
	ZVAL_LONG(&pos, 0);
	ZEPHIR_INIT_VAR(&defaultSeparator);
	ZVAL_STRING(&defaultSeparator, "/");
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "//u");
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "//u");
	ZEPHIR_INIT_VAR(&useUtf8);
	zephir_preg_match(&useUtf8, &_2, pattern, &_0, 0, 0 , 0  TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "utf8");
	ZEPHIR_CALL_METHOD(&needsUtf8, route, "getoption", NULL, 0, &_3);
	zephir_check_call_status();
	_4 = !zephir_is_true(&needsUtf8);
	if (_4) {
		_4 = zephir_is_true(&useUtf8);
	}
	_5 = _4;
	if (_5) {
		ZEPHIR_INIT_VAR(&_6);
		ZEPHIR_INIT_NVAR(&_3);
		ZVAL_STRING(&_3, "/[\\x80-\\xFF]/");
		ZEPHIR_INIT_VAR(&_7);
		ZEPHIR_INIT_VAR(&_8);
		ZVAL_STRING(&_8, "/[\\x80-\\xFF]/");
		zephir_preg_match(&_7, &_8, pattern, &_6, 0, 0 , 0  TSRMLS_CC);
		_5 = zephir_is_true(&_7);
	}
	if (_5) {
		ZEPHIR_INIT_VAR(&_9$$3);
		object_init_ex(&_9$$3, spl_ce_LogicException);
		ZEPHIR_CALL_METHOD(&_10$$3, route, "getpath", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_11$$3);
		ZVAL_STRING(&_11$$3, "Cannot use UTF-8 route patterns without setting the \"utf8\" option for route \"%s\".");
		ZEPHIR_CALL_FUNCTION(&_12$$3, "sprintf", &_13, 22, &_11$$3, &_10$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_9$$3, "__construct", NULL, 109, &_12$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_9$$3, "zim/routing/routecompiler.zep", 73 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_14 = !zephir_is_true(&useUtf8);
	if (_14) {
		_14 = zephir_is_true(&needsUtf8);
	}
	if (_14) {
		ZEPHIR_INIT_VAR(&_15$$4);
		object_init_ex(&_15$$4, spl_ce_LogicException);
		ZEPHIR_INIT_VAR(&_16$$4);
		ZVAL_STRING(&_16$$4, "Cannot mix UTF-8 requirements with non-UTF-8 pattern \"%s\".");
		ZEPHIR_CALL_FUNCTION(&_17$$4, "sprintf", &_13, 22, &_16$$4, pattern);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &_15$$4, "__construct", NULL, 109, &_17$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_15$$4, "zim/routing/routecompiler.zep", 76 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_18);
	ZVAL_STRING(&_18, "#\\{\\w+\\}#");
	ZVAL_LONG(&_19, (2 | 256));
	ZEPHIR_INIT_VAR(&_20);
	ZEPHIR_INIT_VAR(&_21);
	ZVAL_STRING(&_21, "#\\{\\w+\\}#");
	ZVAL_LONG(&_22, (2 | 256));
	zephir_preg_match(&_20, &_21, pattern, &matches, 1, zephir_get_intval(&_19) , 0  TSRMLS_CC);
	zephir_is_iterable(&matches, 0, "zim/routing/routecompiler.zep", 145);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&matches), _23)
	{
		ZEPHIR_INIT_NVAR(&match);
		ZVAL_COPY(&match, _23);
		zephir_array_fetch_long(&_24$$5, &match, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 82 TSRMLS_CC);
		zephir_array_fetch_long(&_25$$5, &_24$$5, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 82 TSRMLS_CC);
		ZVAL_LONG(&_26$$5, 1);
		ZVAL_LONG(&_27$$5, -1);
		ZEPHIR_INIT_NVAR(&varName);
		zephir_substr(&varName, &_25$$5, 1 , -1 , 0);
		zephir_array_fetch_long(&_28$$5, &match, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 84 TSRMLS_CC);
		zephir_array_fetch_long(&_29$$5, &_28$$5, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 84 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_30$$5);
		zephir_sub_function(&_30$$5, &_29$$5, &pos);
		ZEPHIR_INIT_NVAR(&precedingText);
		zephir_substr(&precedingText, pattern, zephir_get_intval(&pos), zephir_get_intval(&_30$$5), 0);
		zephir_array_fetch_long(&_29$$5, &match, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 85 TSRMLS_CC);
		zephir_array_fetch_long(&_31$$5, &_29$$5, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 85 TSRMLS_CC);
		zephir_array_fetch_long(&_32$$5, &match, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 85 TSRMLS_CC);
		zephir_array_fetch_long(&_33$$5, &_32$$5, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 85 TSRMLS_CC);
		ZEPHIR_CALL_FUNCTION(&_34$$5, "\strlen", &_35, 50, &_33$$5);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&pos);
		zephir_add_function(&pos, &_31$$5, &_34$$5);
		ZEPHIR_CALL_FUNCTION(&_34$$5, "\strlen", &_35, 50, &precedingText);
		zephir_check_call_status();
		if (!(zephir_is_true(&_34$$5))) {
			ZEPHIR_INIT_NVAR(&precedingChar);
			ZVAL_STRING(&precedingChar, "");
		} else if (zephir_is_true(&useUtf8)) {
			ZEPHIR_INIT_NVAR(&_36$$7);
			ZVAL_STRING(&_36$$7, "/.$/u");
			ZEPHIR_INIT_NVAR(&_37$$7);
			ZEPHIR_INIT_NVAR(&_38$$7);
			ZVAL_STRING(&_38$$7, "/.$/u");
			zephir_preg_match(&_37$$7, &_38$$7, &precedingText, &precedingChar, 0, 0 , 0  TSRMLS_CC);
			zephir_array_fetch_long(&_39$$7, &precedingChar, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 90 TSRMLS_CC);
			ZEPHIR_CPY_WRT(&precedingChar, &_39$$7);
		} else {
			ZVAL_LONG(&_40$$8, -1);
			ZEPHIR_INIT_NVAR(&precedingChar);
			zephir_substr(&precedingChar, &precedingText, -1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		}
		ZEPHIR_SINIT_NVAR(_41$$5);
		ZVAL_STRING(&_41$$5, "");
		_42$$5 = !ZEPHIR_IS_IDENTICAL(&_41$$5, &precedingChar);
		if (_42$$5) {
			ZEPHIR_INIT_NVAR(&_43$$5);
			ZVAL_STRING(&_43$$5, "/,;.:-_~+*=@|");
			ZEPHIR_INIT_NVAR(&_44$$5);
			zephir_fast_strpos(&_44$$5, &_43$$5, &precedingChar, 0 );
			_42$$5 = !ZEPHIR_IS_FALSE_IDENTICAL(&_44$$5);
		}
		isSeparator = _42$$5;
		ZEPHIR_INIT_NVAR(&_45$$5);
		ZEPHIR_INIT_NVAR(&_46$$5);
		ZVAL_STRING(&_46$$5, "/^\\d/");
		ZEPHIR_INIT_NVAR(&_47$$5);
		ZEPHIR_INIT_NVAR(&_48$$5);
		ZVAL_STRING(&_48$$5, "/^\\d/");
		zephir_preg_match(&_47$$5, &_48$$5, &varName, &_45$$5, 0, 0 , 0  TSRMLS_CC);
		if (zephir_is_true(&_47$$5)) {
			ZEPHIR_INIT_NVAR(&_49$$9);
			object_init_ex(&_49$$9, spl_ce_DomainException);
			ZEPHIR_INIT_NVAR(&_50$$9);
			ZVAL_STRING(&_50$$9, "Variable name \"%s\" cannot start with a digit in route pattern \"%s\". Please use a different name.");
			ZEPHIR_CALL_FUNCTION(&_51$$9, "sprintf", &_13, 22, &_50$$9, &varName, pattern);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &_49$$9, "__construct", &_52, 110, &_51$$9);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_49$$9, "zim/routing/routecompiler.zep", 98 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		if (zephir_fast_in_array(&varName, &variables TSRMLS_CC)) {
			ZEPHIR_INIT_NVAR(&_53$$10);
			object_init_ex(&_53$$10, spl_ce_LogicException);
			ZEPHIR_INIT_NVAR(&_54$$10);
			ZVAL_STRING(&_54$$10, "Route pattern \"%s\" cannot reference variable name \"%s\" more than once.");
			ZEPHIR_CALL_FUNCTION(&_55$$10, "sprintf", &_13, 22, &_54$$10, pattern, &varName);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &_53$$10, "__construct", NULL, 109, &_55$$10);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_53$$10, "zim/routing/routecompiler.zep", 101 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		if (zephir_fast_strlen_ev(&varName) > 32) {
			ZEPHIR_INIT_NVAR(&_56$$11);
			object_init_ex(&_56$$11, spl_ce_DomainException);
			ZEPHIR_INIT_NVAR(&_57$$11);
			ZVAL_STRING(&_57$$11, "Variable name \"%s\" cannot be longer than %s characters in route pattern \"%s\". Please use a shorter name.");
			ZVAL_LONG(&_58$$11, 32);
			ZEPHIR_CALL_FUNCTION(&_59$$11, "sprintf", &_13, 22, &_57$$11, &varName, &_58$$11, pattern);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &_56$$11, "__construct", &_52, 110, &_59$$11);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_56$$11, "zim/routing/routecompiler.zep", 104 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		_60$$5 = isSeparator;
		if (_60$$5) {
			_60$$5 = !ZEPHIR_IS_IDENTICAL(&precedingText, &precedingChar);
		}
		_61$$5 = !isSeparator;
		if (_61$$5) {
			ZEPHIR_CALL_FUNCTION(&_62$$5, "\strlen", &_35, 50, &precedingText);
			zephir_check_call_status();
			_61$$5 = ZEPHIR_GT_LONG(&_62$$5, 0);
		}
		if (_60$$5) {
			ZEPHIR_INIT_NVAR(&_63$$12);
			zephir_create_array(&_63$$12, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_64$$12);
			ZVAL_STRING(&_64$$12, "text");
			zephir_array_fast_append(&_63$$12, &_64$$12);
			ZEPHIR_CALL_FUNCTION(&_65$$12, "\strlen", &_35, 50, &precedingChar);
			zephir_check_call_status();
			zephir_negate(&_65$$12 TSRMLS_CC);
			ZVAL_LONG(&_66$$12, 0);
			ZEPHIR_INIT_NVAR(&_64$$12);
			zephir_substr(&_64$$12, &precedingText, 0 , zephir_get_intval(&_65$$12), 0);
			zephir_array_fast_append(&_63$$12, &_64$$12);
			zephir_array_append(&tokens, &_63$$12, PH_SEPARATE, "zim/routing/routecompiler.zep", 107);
		} else if (_61$$5) {
			ZEPHIR_INIT_NVAR(&_67$$13);
			zephir_create_array(&_67$$13, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_68$$13);
			ZVAL_STRING(&_68$$13, "text");
			zephir_array_fast_append(&_67$$13, &_68$$13);
			zephir_array_fast_append(&_67$$13, &precedingText);
			zephir_array_append(&tokens, &_67$$13, PH_SEPARATE, "zim/routing/routecompiler.zep", 109);
		}
		ZEPHIR_CALL_METHOD(&regexp, route, "getrequirement", &_69, 0, &varName);
		zephir_check_call_status();
		if (Z_TYPE_P(&regexp) == IS_NULL) {
			ZEPHIR_INIT_NVAR(&_70$$14);
			zephir_substr(&_70$$14, pattern, zephir_get_intval(&pos), 0, ZEPHIR_SUBSTR_NO_LENGTH);
			zephir_get_strval(&_71$$14, &_70$$14);
			ZEPHIR_CPY_WRT(&followingPattern, &_71$$14);
			ZEPHIR_CALL_SELF(&nextSeparator, "findnextseparator", &_72, 0, &followingPattern, &useUtf8);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_73$$14);
			ZVAL_STRING(&_73$$14, "#");
			ZEPHIR_CALL_FUNCTION(&_74$$14, "preg_quote", &_75, 79, &defaultSeparator, &_73$$14);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_76$$14);
			_77$$14 = !ZEPHIR_IS_IDENTICAL(&defaultSeparator, &nextSeparator);
			if (_77$$14) {
				_77$$14 = !ZEPHIR_IS_STRING_IDENTICAL(&nextSeparator, "");
			}
			if (_77$$14) {
				ZEPHIR_INIT_NVAR(&_73$$14);
				ZVAL_STRING(&_73$$14, "#");
				ZEPHIR_CALL_FUNCTION(&_76$$14, "preg_quote", &_75, 79, &nextSeparator, &_73$$14);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&_76$$14);
				ZVAL_STRING(&_76$$14, "");
			}
			ZEPHIR_INIT_NVAR(&_73$$14);
			ZVAL_STRING(&_73$$14, "[^%s%s]+");
			ZEPHIR_CALL_FUNCTION(&regexp, "sprintf", &_13, 22, &_73$$14, &_74$$14, &_76$$14);
			zephir_check_call_status();
			_78$$14 = !ZEPHIR_IS_STRING_IDENTICAL(&nextSeparator, "");
			if (_78$$14) {
				ZEPHIR_INIT_NVAR(&_79$$14);
				ZEPHIR_INIT_NVAR(&_73$$14);
				ZVAL_STRING(&_73$$14, "#^\\{\\w+\\}#");
				ZEPHIR_INIT_NVAR(&_80$$14);
				ZEPHIR_INIT_NVAR(&_81$$14);
				ZVAL_STRING(&_81$$14, "#^\\{\\w+\\}#");
				zephir_preg_match(&_80$$14, &_81$$14, &followingPattern, &_79$$14, 0, 0 , 0  TSRMLS_CC);
				_78$$14 = !zephir_is_true(&_80$$14);
			}
			_82$$14 = _78$$14;
			if (!(_82$$14)) {
				_82$$14 = ZEPHIR_IS_STRING_IDENTICAL(&followingPattern, "");
			}
			if (_82$$14) {
				zephir_concat_self_str(&regexp, SL("+") TSRMLS_CC);
			}
		} else {
			ZEPHIR_INIT_NVAR(&_83$$16);
			ZEPHIR_INIT_NVAR(&_84$$16);
			ZVAL_STRING(&_84$$16, "//u");
			ZEPHIR_INIT_NVAR(&_85$$16);
			ZEPHIR_INIT_NVAR(&_86$$16);
			ZVAL_STRING(&_86$$16, "//u");
			zephir_preg_match(&_85$$16, &_86$$16, &regexp, &_83$$16, 0, 0 , 0  TSRMLS_CC);
			_87$$16 = !zephir_is_true(&needsUtf8);
			if (_87$$16) {
				ZEPHIR_INIT_NVAR(&_88$$16);
				ZEPHIR_INIT_NVAR(&_89$$16);
				ZVAL_STRING(&_89$$16, "/[\\x80-\\xFF]|(?<!\\\\)\\\\(?:\\\\\\\\)*+(?-i:X|[pP][\\{CLMNPSZ]|x\\{[A-Fa-f0-9]{3})/");
				ZEPHIR_INIT_NVAR(&_90$$16);
				ZEPHIR_INIT_NVAR(&_91$$16);
				ZVAL_STRING(&_91$$16, "/[\\x80-\\xFF]|(?<!\\\\)\\\\(?:\\\\\\\\)*+(?-i:X|[pP][\\{CLMNPSZ]|x\\{[A-Fa-f0-9]{3})/");
				zephir_preg_match(&_90$$16, &_91$$16, &regexp, &_88$$16, 0, 0 , 0  TSRMLS_CC);
				_87$$16 = zephir_is_true(&_90$$16);
			}
			if (!(zephir_is_true(&_85$$16))) {
				ZEPHIR_INIT_NVAR(&useUtf8);
				ZVAL_BOOL(&useUtf8, 0);
			} else if (_87$$16) {
				ZEPHIR_INIT_NVAR(&_92$$18);
				object_init_ex(&_92$$18, spl_ce_LogicException);
				ZEPHIR_INIT_NVAR(&_93$$18);
				ZVAL_STRING(&_93$$18, "Cannot use UTF-8 route requirements without setting the \"utf8\" option for variable \"%s\" in pattern \"%s\".");
				ZEPHIR_CALL_FUNCTION(&_94$$18, "sprintf", &_13, 22, &_93$$18, &varName, pattern);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, &_92$$18, "__construct", NULL, 109, &_94$$18);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_92$$18, "zim/routing/routecompiler.zep", 135 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			_95$$16 = !zephir_is_true(&useUtf8);
			if (_95$$16) {
				_95$$16 = zephir_is_true(&needsUtf8);
			}
			if (_95$$16) {
				ZEPHIR_INIT_NVAR(&_96$$19);
				object_init_ex(&_96$$19, spl_ce_LogicException);
				ZEPHIR_INIT_NVAR(&_97$$19);
				ZVAL_STRING(&_97$$19, "Cannot mix UTF-8 requirement with non-UTF-8 charset for variable \"%s\" in pattern \"%s\".");
				ZEPHIR_CALL_FUNCTION(&_98$$19, "sprintf", &_13, 22, &_97$$19, &varName, pattern);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, &_96$$19, "__construct", NULL, 109, &_98$$19);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_96$$19, "zim/routing/routecompiler.zep", 138 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_SELF(&_99$$16, "transformcapturinggroupstononcapturings", &_100, 0, &regexp);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&regexp, &_99$$16);
		}
		ZEPHIR_INIT_NVAR(&_101$$5);
		zephir_create_array(&_101$$5, 4, 0 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&_102$$5);
		ZVAL_STRING(&_102$$5, "variable");
		zephir_array_fast_append(&_101$$5, &_102$$5);
		ZEPHIR_INIT_LNVAR(_103$$5);
		if (isSeparator) {
			ZEPHIR_CPY_WRT(&_103$$5, &precedingChar);
		} else {
			ZEPHIR_INIT_NVAR(&_103$$5);
			ZVAL_STRING(&_103$$5, "");
		}
		zephir_array_fast_append(&_101$$5, &_103$$5);
		zephir_array_fast_append(&_101$$5, &regexp);
		zephir_array_fast_append(&_101$$5, &varName);
		zephir_array_append(&tokens, &_101$$5, PH_SEPARATE, "zim/routing/routecompiler.zep", 142);
		zephir_array_append(&variables, &varName, PH_SEPARATE, "zim/routing/routecompiler.zep", 143);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&match);
	ZEPHIR_CALL_FUNCTION(&_104, "\strlen", &_35, 50, pattern);
	zephir_check_call_status();
	if (ZEPHIR_LT(&pos, &_104)) {
		ZEPHIR_INIT_VAR(&_105$$20);
		zephir_create_array(&_105$$20, 2, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_106$$20);
		ZVAL_STRING(&_106$$20, "text");
		zephir_array_fast_append(&_105$$20, &_106$$20);
		ZEPHIR_INIT_NVAR(&_106$$20);
		zephir_substr(&_106$$20, pattern, zephir_get_intval(&pos), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_array_fast_append(&_105$$20, &_106$$20);
		zephir_array_append(&tokens, &_105$$20, PH_SEPARATE, "zim/routing/routecompiler.zep", 146);
	}
	ZEPHIR_INIT_VAR(&firstOptional);
	ZEPHIR_GET_CONSTANT(&firstOptional, "PHP_INT_MAX");
	ZEPHIR_INIT_VAR(&i);
	ZVAL_LONG(&i, (zephir_fast_count_int(&tokens TSRMLS_CC) - 1));
	_109 = 0;
	_108 = (zephir_fast_count_int(&tokens TSRMLS_CC) - 1);
	_107 = 0;
	if (_108 <= _109) {
		while (1) {
			if (_107) {
				_108++;
				if (!(_108 <= _109)) {
					break;
				}
			} else {
				_107 = 1;
			}
			ZEPHIR_INIT_NVAR(&i);
			ZVAL_LONG(&i, _108);
			ZEPHIR_OBS_NVAR(&token);
			zephir_array_fetch(&token, &tokens, &i, PH_NOISY, "zim/routing/routecompiler.zep", 152 TSRMLS_CC);
			zephir_array_fetch_long(&_110$$21, &token, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 153 TSRMLS_CC);
			_111$$21 = ZEPHIR_IS_STRING_IDENTICAL(&_110$$21, "variable");
			if (_111$$21) {
				zephir_array_fetch_long(&_113$$21, &token, 3, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 153 TSRMLS_CC);
				ZEPHIR_CALL_METHOD(&_112$$21, route, "hasdefault", &_114, 0, &_113$$21);
				zephir_check_call_status();
				_111$$21 = zephir_is_true(&_112$$21);
			}
			if (_111$$21) {
				ZEPHIR_CPY_WRT(&firstOptional, &i);
			} else {
				break;
			}
		}
	}
	ZEPHIR_INIT_NVAR(&regexp);
	ZVAL_STRING(&regexp, "");
	ZEPHIR_INIT_NVAR(&i);
	ZVAL_LONG(&i, 0);
	ZEPHIR_INIT_VAR(&nbToken);
	ZVAL_LONG(&nbToken, zephir_fast_count_int(&tokens TSRMLS_CC));
	ZEPHIR_CPY_WRT(&_117, &nbToken);
	_116 = 0;
	_115 = 0;
	if (ZEPHIR_GE_LONG(&_117, _116)) {
		while (1) {
			if (_115) {
				_116++;
				if (!(ZEPHIR_GE_LONG(&_117, _116))) {
					break;
				}
			} else {
				_115 = 1;
			}
			ZEPHIR_INIT_NVAR(&i);
			ZVAL_LONG(&i, _116);
			ZEPHIR_CALL_SELF(&_118$$24, "computeregexp", &_119, 0, &tokens, &i, &firstOptional);
			zephir_check_call_status();
			zephir_concat_self(&regexp, &_118$$24 TSRMLS_CC);
		}
	}
	ZEPHIR_INIT_VAR(&_120);
	ZEPHIR_CONCAT_SSVSSS(&_120, "#", "^", &regexp, "$", "#", "sD");
	ZEPHIR_CPY_WRT(&regexp, &_120);
	if (zephir_is_true(&needsUtf8)) {
		zephir_concat_self_str(&regexp, SL("u") TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&i);
		ZVAL_LONG(&i, 0);
		ZEPHIR_INIT_NVAR(&nbToken);
		ZVAL_LONG(&nbToken, zephir_fast_count_int(&tokens TSRMLS_CC));
		ZEPHIR_CPY_WRT(&_123$$25, &nbToken);
		_122$$25 = 0;
		_121$$25 = 0;
		if (ZEPHIR_GE_LONG(&_123$$25, _122$$25)) {
			while (1) {
				if (_121$$25) {
					_122$$25++;
					if (!(ZEPHIR_GE_LONG(&_123$$25, _122$$25))) {
						break;
					}
				} else {
					_121$$25 = 1;
				}
				ZEPHIR_INIT_NVAR(&i);
				ZVAL_LONG(&i, _122$$25);
				zephir_array_fetch(&_124$$26, &tokens, &i, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 173 TSRMLS_CC);
				zephir_array_fetch_long(&_125$$26, &_124$$26, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 173 TSRMLS_CC);
				if (ZEPHIR_IS_STRING_IDENTICAL(&_125$$26, "variable")) {
					zephir_array_update_multi(&tokens, &__$true TSRMLS_CC, SL("za"), 2, &i);
				}
			}
		}
	}
	zephir_create_array(return_value, 4, 0 TSRMLS_CC);
	ZEPHIR_CALL_SELF(&_126, "determinestaticprefix", NULL, 0, route, &tokens);
	zephir_check_call_status();
	zephir_array_update_string(return_value, SL("staticPrefix"), &_126, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("regex"), &regexp, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_FUNCTION(&_126, "array_reverse", NULL, 111, &tokens);
	zephir_check_call_status();
	zephir_array_update_string(return_value, SL("tokens"), &_126, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("variables"), &variables, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}

/**
 * Determines the longest static prefix possible for a route.
 */
PHP_METHOD(Zim_Routing_RouteCompiler, determineStaticPrefix) {

	zend_bool _12, _15, _6$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval tokens;
	zval *route, route_sub, *tokens_param = NULL, prefix, _0, _1, _10, _11, _13, _14, _16, _17, _18, _2$$3, _3$$3, _4$$3, _5$$3, _7$$3, _8$$3, _9$$3, _19$$4, _20$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&route_sub);
	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_20$$4);
	ZVAL_UNDEF(&tokens);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &route, &tokens_param);

	zephir_get_arrval(&tokens, tokens_param);


	zephir_array_fetch_long(&_0, &tokens, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 193 TSRMLS_CC);
	zephir_array_fetch_long(&_1, &_0, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 193 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING_IDENTICAL(&_1, "text")) {
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_array_fetch_long(&_4$$3, &tokens, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 194 TSRMLS_CC);
		zephir_array_fetch_long(&_5$$3, &_4$$3, 3, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 194 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_3$$3, route, "hasdefault", NULL, 0, &_5$$3);
		zephir_check_call_status();
		_6$$3 = zephir_is_true(&_3$$3);
		if (!(_6$$3)) {
			zephir_array_fetch_long(&_7$$3, &tokens, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 194 TSRMLS_CC);
			zephir_array_fetch_long(&_8$$3, &_7$$3, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 194 TSRMLS_CC);
			_6$$3 = ZEPHIR_IS_STRING_IDENTICAL(&_8$$3, "/");
		}
		if (_6$$3) {
			ZVAL_STRING(&_2$$3, "");
		} else {
			zephir_array_fetch_long(&_9$$3, &tokens, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 194 TSRMLS_CC);
			zephir_array_fetch_long(&_2$$3, &_9$$3, 1, PH_NOISY, "zim/routing/routecompiler.zep", 194 TSRMLS_CC);
		}
		RETURN_CCTOR(&_2$$3);
	}
	zephir_array_fetch_long(&_10, &tokens, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 196 TSRMLS_CC);
	ZEPHIR_OBS_VAR(&prefix);
	zephir_array_fetch_long(&prefix, &_10, 1, PH_NOISY, "zim/routing/routecompiler.zep", 196 TSRMLS_CC);
	zephir_array_fetch_long(&_11, &tokens, 1, PH_READONLY, "zim/routing/routecompiler.zep", 197 TSRMLS_CC);
	_12 = zephir_array_isset_long(&_11, 1);
	if (_12) {
		zephir_array_fetch_long(&_13, &tokens, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 197 TSRMLS_CC);
		zephir_array_fetch_long(&_14, &_13, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 197 TSRMLS_CC);
		_12 = !ZEPHIR_IS_STRING_IDENTICAL(&_14, "/");
	}
	_15 = _12;
	if (_15) {
		zephir_array_fetch_long(&_17, &tokens, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 197 TSRMLS_CC);
		zephir_array_fetch_long(&_18, &_17, 3, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 197 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_16, route, "hasdefault", NULL, 0, &_18);
		zephir_check_call_status();
		_15 = ZEPHIR_IS_FALSE_IDENTICAL(&_16);
	}
	if (_15) {
		zephir_array_fetch_long(&_19$$4, &tokens, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 198 TSRMLS_CC);
		zephir_array_fetch_long(&_20$$4, &_19$$4, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 198 TSRMLS_CC);
		zephir_concat_self(&prefix, &_20$$4 TSRMLS_CC);
	}
	RETURN_CCTOR(&prefix);

}

/**
 * Returns the next static character in the Route pattern that will serve as a separator (or the empty string when none available).
 */
PHP_METHOD(Zim_Routing_RouteCompiler, findNextSeparator) {

	unsigned char _6, _8$$6;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool useUtf8;
	zval *pattern_param = NULL, *useUtf8_param = NULL, _0, _1, _2, ret, _7, patternResult$$5, _3$$5, _4$$5, _5$$5;
	zval pattern;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&ret);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&patternResult$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &pattern_param, &useUtf8_param);

	zephir_get_strval(&pattern, pattern_param);
	useUtf8 = zephir_get_boolval(useUtf8_param);


	if (ZEPHIR_IS_STRING(&pattern, "")) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "#\\{\\w+\\}#");
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "");
	ZEPHIR_CALL_FUNCTION(&_2, "preg_replace", NULL, 81, &_0, &_1, &pattern);
	zephir_check_call_status();
	zephir_get_strval(&pattern, &_2);
	if (ZEPHIR_IS_STRING_IDENTICAL(&pattern, "")) {
		RETURN_MM_STRING("");
	}
	if (useUtf8) {
		ZEPHIR_INIT_VAR(&_3$$5);
		ZVAL_STRING(&_3$$5, "/^./u");
		ZEPHIR_INIT_VAR(&_4$$5);
		ZEPHIR_INIT_VAR(&_5$$5);
		ZVAL_STRING(&_5$$5, "/^./u");
		zephir_preg_match(&_4$$5, &_5$$5, &pattern, &patternResult$$5, 0, 0 , 0  TSRMLS_CC);
		zephir_get_strval(&pattern, &patternResult$$5);
	}
	ZEPHIR_INIT_VAR(&ret);
	ZVAL_STRING(&ret, "");
	_6 = ZEPHIR_STRING_OFFSET(&pattern, 0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "/,;.:-_~+*=@|");
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRINGL(&_1, &_6, 1);
	ZEPHIR_INIT_VAR(&_7);
	zephir_fast_strpos(&_7, &_0, &_1, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&_7)) {
		_8$$6 = ZEPHIR_STRING_OFFSET(&pattern, 0);
		ZEPHIR_INIT_NVAR(&ret);
		ZVAL_LONG(&ret, _8$$6);
	}
	RETURN_CCTOR(&ret);

}

/**
 * Computes the regexp used to match a specific token. It can be static text or a subpattern.
 *
 * @param array $tokens        The route tokens
 * @param int   $index         The index of the current token
 * @param int   $firstOptional The index of the first optional token
 *
 * @return string The regexp pattern for a single token
 */
PHP_METHOD(Zim_Routing_RouteCompiler, computeRegexp) {

	zend_bool _4$$4;
	zephir_fcall_cache_entry *_3 = NULL, *_10 = NULL;
	zend_long index, firstOptional, ZEPHIR_LAST_CALL_STATUS;
	zval *tokens_param = NULL, *index_param = NULL, *firstOptional_param = NULL, token, regexp, nbTokens, _0, _1$$3, _2$$3, _5$$5, _6$$5, _7$$5, _8$$5, _9$$5, _11$$6, _12$$6, _13$$6, _14$$6, _15$$6, _16$$8, _17$$8, _18$$8, _19$$8;
	zval tokens;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&tokens);
	ZVAL_UNDEF(&token);
	ZVAL_UNDEF(&regexp);
	ZVAL_UNDEF(&nbTokens);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&_19$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tokens_param, &index_param, &firstOptional_param);

	zephir_get_arrval(&tokens, tokens_param);
	index = zephir_get_intval(index_param);
	firstOptional = zephir_get_intval(firstOptional_param);


	ZEPHIR_OBS_VAR(&token);
	zephir_array_fetch_long(&token, &tokens, index, PH_NOISY, "zim/routing/routecompiler.zep", 245 TSRMLS_CC);
	zephir_array_fetch_long(&_0, &token, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 246 TSRMLS_CC);
	if (ZEPHIR_IS_STRING_IDENTICAL(&_0, "text")) {
		zephir_array_fetch_long(&_1$$3, &token, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 248 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "#");
		ZEPHIR_RETURN_CALL_FUNCTION("preg_quote", &_3, 79, &_1$$3, &_2$$3);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		_4$$4 = 0 == index;
		if (_4$$4) {
			_4$$4 = 0 == firstOptional;
		}
		if (_4$$4) {
			zephir_array_fetch_long(&_5$$5, &token, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 253 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_6$$5);
			ZVAL_STRING(&_6$$5, "#");
			ZEPHIR_CALL_FUNCTION(&_7$$5, "preg_quote", &_3, 79, &_5$$5, &_6$$5);
			zephir_check_call_status();
			zephir_array_fetch_long(&_8$$5, &token, 3, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 253 TSRMLS_CC);
			zephir_array_fetch_long(&_9$$5, &token, 2, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 253 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_6$$5);
			ZVAL_STRING(&_6$$5, "%s(?P<%s>%s)?");
			ZEPHIR_RETURN_CALL_FUNCTION("sprintf", &_10, 22, &_6$$5, &_7$$5, &_8$$5, &_9$$5);
			zephir_check_call_status();
			RETURN_MM();
		} else {
			zephir_array_fetch_long(&_11$$6, &token, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 255 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_12$$6);
			ZVAL_STRING(&_12$$6, "#");
			ZEPHIR_CALL_FUNCTION(&_13$$6, "preg_quote", &_3, 79, &_11$$6, &_12$$6);
			zephir_check_call_status();
			zephir_array_fetch_long(&_14$$6, &token, 3, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 255 TSRMLS_CC);
			zephir_array_fetch_long(&_15$$6, &token, 2, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 255 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_12$$6);
			ZVAL_STRING(&_12$$6, "%s(?P<%s>%s)");
			ZEPHIR_CALL_FUNCTION(&regexp, "sprintf", &_10, 22, &_12$$6, &_13$$6, &_14$$6, &_15$$6);
			zephir_check_call_status();
			if (index >= firstOptional) {
				ZEPHIR_INIT_NVAR(&regexp);
				ZVAL_STRING(&regexp, "(?:{regexp}");
				ZEPHIR_INIT_VAR(&nbTokens);
				ZVAL_LONG(&nbTokens, zephir_fast_count_int(&tokens TSRMLS_CC));
				if ((zephir_get_numberval(&nbTokens) - 1) == index) {
					ZEPHIR_INIT_VAR(&_16$$8);
					if (0 == firstOptional) {
						ZEPHIR_INIT_NVAR(&_16$$8);
						ZVAL_LONG(&_16$$8, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$8);
						ZVAL_LONG(&_16$$8, 0);
					}
					ZEPHIR_INIT_VAR(&_17$$8);
					ZVAL_STRING(&_17$$8, ")?");
					ZVAL_LONG(&_18$$8, ((zephir_get_numberval(&nbTokens) - firstOptional) - zephir_get_numberval(&_16$$8)));
					ZEPHIR_CALL_FUNCTION(&_19$$8, "str_repeat", NULL, 112, &_17$$8, &_18$$8);
					zephir_check_call_status();
					zephir_concat_self(&regexp, &_19$$8 TSRMLS_CC);
				}
			}
			RETURN_CCTOR(&regexp);
		}
	}
	RETURN_MM_STRING("");

}

PHP_METHOD(Zim_Routing_RouteCompiler, transformCapturingGroupsToNonCapturings) {

	unsigned char _3$$3, _5$$3;
	zend_bool _0, _4$$3, _7$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, i2 = 0, _1, _2;
	zephir_fcall_cache_entry *_12 = NULL;
	zval *regexp_param = NULL, s, _6$$3, _8$$3, _9$$3, _10$$3, _11$$3;
	zval regexp;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&regexp);
	ZVAL_UNDEF(&s);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &regexp_param);

	zephir_get_strval(&regexp, regexp_param);


	i = 0;
	_2 = zephir_fast_strlen_ev(&regexp);
	_1 = 0;
	_0 = 0;
	if (_1 <= _2) {
		while (1) {
			if (_0) {
				_1++;
				if (!(_1 <= _2)) {
					break;
				}
			} else {
				_0 = 1;
			}
			i = _1;
			_3$$3 = ZEPHIR_STRING_OFFSET(&regexp, i);
			ZEPHIR_INIT_NVAR(&s);
			ZVAL_LONG(&s, _3$$3);
			if (ZEPHIR_IS_STRING_IDENTICAL(&s, "\\")) {
				i++;
				continue;
			}
			i2 = ((i + 2));
			_4$$3 = !ZEPHIR_IS_STRING_IDENTICAL(&s, "(");
			if (!(_4$$3)) {
				_5$$3 = ZEPHIR_STRING_OFFSET(&regexp, i2);
				ZEPHIR_INIT_NVAR(&_6$$3);
				ZVAL_STRINGL(&_6$$3, &_5$$3, 1);
				_4$$3 = zephir_fast_strlen_ev(&_6$$3) == 0;
			}
			if (_4$$3) {
				continue;
			}
			i++;
			_7$$3 = ZEPHIR_IS_STRING_IDENTICAL(&s, "*");
			if (!(_7$$3)) {
				_7$$3 = ZEPHIR_IS_STRING_IDENTICAL(&s, "?");
			}
			if (_7$$3) {
				i++;
				continue;
			}
			ZEPHIR_INIT_NVAR(&_8$$3);
			ZVAL_STRING(&_8$$3, "?:");
			ZVAL_LONG(&_9$$3, i);
			ZVAL_LONG(&_10$$3, 0);
			ZEPHIR_CALL_FUNCTION(&_11$$3, "substr_replace", &_12, 52, &regexp, &_8$$3, &_9$$3, &_10$$3);
			zephir_check_call_status();
			zephir_get_strval(&regexp, &_11$$3);
			i++;
		}
	}
	RETURN_CTOR(&regexp);

}

