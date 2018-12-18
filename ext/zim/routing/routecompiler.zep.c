
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
#include "kernel/string.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"


/**
 * RouteCompiler compiles Route instances to CompiledRoute instances.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 * @author Tobias Schultze <http://tobion.de>
 */
ZEPHIR_INIT_CLASS(Zim_Routing_RouteCompiler) {

	ZEPHIR_REGISTER_CLASS(Zim\\Routing, RouteCompiler, zim, routing_routecompiler, zim_routing_routecompiler_method_entry, 0);

	zephir_declare_class_constant_string(zim_routing_routecompiler_ce, SL("REGEX_PATTERN_START"), "#^\\{\\w+\\}#");

	zephir_declare_class_constant_string(zim_routing_routecompiler_ce, SL("REGEX_PATTERN"), "#\\{\\w+\\}#");

	zephir_declare_class_constant_string(zim_routing_routecompiler_ce, SL("REGEX_UTF8"), "/[\\x80-\\xFF]/");

	zephir_declare_class_constant_string(zim_routing_routecompiler_ce, SL("REGEX_UTF8_FULL"), "/[\\x80-\\xFF]|(?<!\\\\)\\\\(?:\\\\\\\\)*+(?-i:X|[pP][\\{CLMNPSZ]|x\\{[A-Fa-f0-9]{3})/");

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

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *route, route_sub, variables, path, result, pathVariables, _0, _1, _2, _3, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&route_sub);
	ZVAL_UNDEF(&variables);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&pathVariables);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &route);



	ZEPHIR_INIT_VAR(&variables);
	array_init(&variables);
	ZEPHIR_CALL_METHOD(&path, route, "getpath", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_SELF(&result, "compilepattern", NULL, 0, route, &path);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&pathVariables);
	zephir_array_fetch_string(&pathVariables, &result, SL("variables"), PH_NOISY, "zim/routing/routecompiler.zep", 55 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_array_merge(&_0, &variables, &pathVariables TSRMLS_CC);
	ZEPHIR_CPY_WRT(&variables, &_0);
	object_init_ex(return_value, zim_routing_compiledroute_ce);
	zephir_array_fetch_string(&_1, &result, SL("staticPrefix"), PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 58 TSRMLS_CC);
	zephir_array_fetch_string(&_2, &result, SL("regex"), PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 59 TSRMLS_CC);
	zephir_array_fetch_string(&_3, &result, SL("tokens"), PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 60 TSRMLS_CC);
	ZEPHIR_CALL_FUNCTION(&_4, "array_unique", NULL, 103, &variables);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 104, &_1, &_2, &_3, &pathVariables, &_4);
	zephir_check_call_status();
	RETURN_MM();

}

PHP_METHOD(Zim_Routing_RouteCompiler, compilePattern) {

	zval _68$$14;
	zval _98$$5, _60$$12, _64$$13, _101$$20;
	zend_bool isSeparator = 0, _4, _5, _14, _112, _40$$5, _58$$5, _59$$5, _74$$14, _75$$14, _79$$14, _84$$16, _92$$16, _108$$21, _118$$25;
	zephir_fcall_cache_entry *_13 = NULL, *_50 = NULL, *_66 = NULL, *_69 = NULL, *_72 = NULL, *_97 = NULL, *_105 = NULL, *_111 = NULL, *_116 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, _113, _114, _119$$25, _120$$25;
	zval *route, route_sub, *pattern, pattern_sub, __$true, tokens, variables, matches, pos, defaultSeparator, useUtf8, needsUtf8, match, varName, precedingText, precedingChar, regexp, followingPattern, nextSeparator, firstOptional, i, token, _0, _1, _2, _3, _6, _7, _8, _18, _19, _20, _21, _22, *_23, aa, _103, _104, *_106, _117, _123, _9$$3, _10$$3, _11$$3, _12$$3, _15$$4, _16$$4, _17$$4, _24$$5, _25$$5, _26$$5, _27$$5, _28$$5, _29$$5, _30$$5, _31$$5, _32$$5, _33$$5, _39$$5, _41$$5, _42$$5, _43$$5, _44$$5, _45$$5, _46$$5, _99$$5, _100$$5, _34$$7, _35$$7, _36$$7, _37$$7, _38$$8, _47$$9, _48$$9, _49$$9, _51$$10, _52$$10, _53$$10, _54$$11, _55$$11, _56$$11, _57$$11, _61$$12, _62$$12, _63$$12, _65$$13, _67$$14, _70$$14, _71$$14, _73$$14, _76$$14, _77$$14, _78$$14, _80$$16, _81$$16, _82$$16, _83$$16, _85$$16, _86$$16, _87$$16, _88$$16, _96$$16, _89$$18, _90$$18, _91$$18, _93$$19, _94$$19, _95$$19, _102$$20, _107$$21, _109$$21, _110$$21, _115$$24, _121$$26, _122$$26;
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
	ZVAL_UNDEF(&aa);
	ZVAL_UNDEF(&_103);
	ZVAL_UNDEF(&_104);
	ZVAL_UNDEF(&_117);
	ZVAL_UNDEF(&_123);
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
	ZVAL_UNDEF(&_39$$5);
	ZVAL_UNDEF(&_41$$5);
	ZVAL_UNDEF(&_42$$5);
	ZVAL_UNDEF(&_43$$5);
	ZVAL_UNDEF(&_44$$5);
	ZVAL_UNDEF(&_45$$5);
	ZVAL_UNDEF(&_46$$5);
	ZVAL_UNDEF(&_99$$5);
	ZVAL_UNDEF(&_100$$5);
	ZVAL_UNDEF(&_34$$7);
	ZVAL_UNDEF(&_35$$7);
	ZVAL_UNDEF(&_36$$7);
	ZVAL_UNDEF(&_37$$7);
	ZVAL_UNDEF(&_38$$8);
	ZVAL_UNDEF(&_47$$9);
	ZVAL_UNDEF(&_48$$9);
	ZVAL_UNDEF(&_49$$9);
	ZVAL_UNDEF(&_51$$10);
	ZVAL_UNDEF(&_52$$10);
	ZVAL_UNDEF(&_53$$10);
	ZVAL_UNDEF(&_54$$11);
	ZVAL_UNDEF(&_55$$11);
	ZVAL_UNDEF(&_56$$11);
	ZVAL_UNDEF(&_57$$11);
	ZVAL_UNDEF(&_61$$12);
	ZVAL_UNDEF(&_62$$12);
	ZVAL_UNDEF(&_63$$12);
	ZVAL_UNDEF(&_65$$13);
	ZVAL_UNDEF(&_67$$14);
	ZVAL_UNDEF(&_70$$14);
	ZVAL_UNDEF(&_71$$14);
	ZVAL_UNDEF(&_73$$14);
	ZVAL_UNDEF(&_76$$14);
	ZVAL_UNDEF(&_77$$14);
	ZVAL_UNDEF(&_78$$14);
	ZVAL_UNDEF(&_80$$16);
	ZVAL_UNDEF(&_81$$16);
	ZVAL_UNDEF(&_82$$16);
	ZVAL_UNDEF(&_83$$16);
	ZVAL_UNDEF(&_85$$16);
	ZVAL_UNDEF(&_86$$16);
	ZVAL_UNDEF(&_87$$16);
	ZVAL_UNDEF(&_88$$16);
	ZVAL_UNDEF(&_96$$16);
	ZVAL_UNDEF(&_89$$18);
	ZVAL_UNDEF(&_90$$18);
	ZVAL_UNDEF(&_91$$18);
	ZVAL_UNDEF(&_93$$19);
	ZVAL_UNDEF(&_94$$19);
	ZVAL_UNDEF(&_95$$19);
	ZVAL_UNDEF(&_102$$20);
	ZVAL_UNDEF(&_107$$21);
	ZVAL_UNDEF(&_109$$21);
	ZVAL_UNDEF(&_110$$21);
	ZVAL_UNDEF(&_115$$24);
	ZVAL_UNDEF(&_121$$26);
	ZVAL_UNDEF(&_122$$26);
	ZVAL_UNDEF(&_98$$5);
	ZVAL_UNDEF(&_60$$12);
	ZVAL_UNDEF(&_64$$13);
	ZVAL_UNDEF(&_101$$20);
	ZVAL_UNDEF(&_68$$14);

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
		ZEPHIR_CALL_METHOD(NULL, &_9$$3, "__construct", NULL, 11, &_12$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_9$$3, "zim/routing/routecompiler.zep", 78 TSRMLS_CC);
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
		ZEPHIR_CALL_METHOD(NULL, &_15$$4, "__construct", NULL, 11, &_17$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_15$$4, "zim/routing/routecompiler.zep", 81 TSRMLS_CC);
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
	zephir_is_iterable(&matches, 0, "zim/routing/routecompiler.zep", 144);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&matches), _23)
	{
		ZEPHIR_INIT_NVAR(&match);
		ZVAL_COPY(&match, _23);
		zephir_array_fetch_long(&_24$$5, &match, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 87 TSRMLS_CC);
		zephir_array_fetch_long(&_25$$5, &_24$$5, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 87 TSRMLS_CC);
		ZVAL_LONG(&_26$$5, 1);
		ZVAL_LONG(&_27$$5, -1);
		ZEPHIR_INIT_NVAR(&varName);
		zephir_substr(&varName, &_25$$5, 1 , -1 , 0);
		zephir_array_fetch_long(&_28$$5, &match, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 89 TSRMLS_CC);
		zephir_array_fetch_long(&_29$$5, &_28$$5, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 89 TSRMLS_CC);
		ZEPHIR_SINIT_NVAR(_30$$5);
		zephir_sub_function(&_30$$5, &_29$$5, &pos);
		ZEPHIR_INIT_NVAR(&precedingText);
		zephir_substr(&precedingText, pattern, zephir_get_intval(&pos), zephir_get_intval(&_30$$5), 0);
		zephir_array_fetch_long(&_29$$5, &match, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 90 TSRMLS_CC);
		zephir_array_fetch_long(&_31$$5, &_29$$5, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 90 TSRMLS_CC);
		zephir_array_fetch_long(&_32$$5, &match, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 90 TSRMLS_CC);
		zephir_array_fetch_long(&_33$$5, &_32$$5, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 90 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&pos);
		ZVAL_LONG(&pos, (zephir_get_numberval(&_31$$5) + zephir_fast_strlen_ev(&_33$$5)));
		if (zephir_fast_strlen_ev(&precedingText) == 0) {
			ZEPHIR_INIT_NVAR(&precedingChar);
			ZVAL_STRING(&precedingChar, "");
		} else if (zephir_is_true(&useUtf8)) {
			ZEPHIR_INIT_NVAR(&_34$$7);
			ZVAL_STRING(&_34$$7, "/.$/u");
			ZEPHIR_INIT_NVAR(&_35$$7);
			ZEPHIR_INIT_NVAR(&_36$$7);
			ZVAL_STRING(&_36$$7, "/.$/u");
			zephir_preg_match(&_35$$7, &_36$$7, &precedingText, &precedingChar, 0, 0 , 0  TSRMLS_CC);
			zephir_array_fetch_long(&_37$$7, &precedingChar, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 95 TSRMLS_CC);
			ZEPHIR_CPY_WRT(&precedingChar, &_37$$7);
		} else {
			ZVAL_LONG(&_38$$8, -1);
			ZEPHIR_INIT_NVAR(&precedingChar);
			zephir_substr(&precedingChar, &precedingText, -1 , 0, ZEPHIR_SUBSTR_NO_LENGTH);
		}
		ZEPHIR_SINIT_NVAR(_39$$5);
		ZVAL_STRING(&_39$$5, "");
		_40$$5 = !ZEPHIR_IS_IDENTICAL(&_39$$5, &precedingChar);
		if (_40$$5) {
			ZEPHIR_INIT_NVAR(&_41$$5);
			ZVAL_STRING(&_41$$5, "/,;.:-_~+*=@|");
			ZEPHIR_INIT_NVAR(&_42$$5);
			zephir_fast_strpos(&_42$$5, &_41$$5, &precedingChar, 0 );
			_40$$5 = !ZEPHIR_IS_FALSE_IDENTICAL(&_42$$5);
		}
		isSeparator = _40$$5;
		ZEPHIR_INIT_NVAR(&_43$$5);
		ZEPHIR_INIT_NVAR(&_44$$5);
		ZVAL_STRING(&_44$$5, "/^\\d/");
		ZEPHIR_INIT_NVAR(&_45$$5);
		ZEPHIR_INIT_NVAR(&_46$$5);
		ZVAL_STRING(&_46$$5, "/^\\d/");
		zephir_preg_match(&_45$$5, &_46$$5, &varName, &_43$$5, 0, 0 , 0  TSRMLS_CC);
		if (zephir_is_true(&_45$$5)) {
			ZEPHIR_INIT_NVAR(&_47$$9);
			object_init_ex(&_47$$9, spl_ce_DomainException);
			ZEPHIR_INIT_NVAR(&_48$$9);
			ZVAL_STRING(&_48$$9, "Variable name \"%s\" cannot start with a digit in route pattern \"%s\". Please use a different name.");
			ZEPHIR_CALL_FUNCTION(&_49$$9, "sprintf", &_13, 22, &_48$$9, &varName, pattern);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &_47$$9, "__construct", &_50, 105, &_49$$9);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_47$$9, "zim/routing/routecompiler.zep", 103 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		if (zephir_fast_in_array(&varName, &variables TSRMLS_CC)) {
			ZEPHIR_INIT_NVAR(&_51$$10);
			object_init_ex(&_51$$10, spl_ce_LogicException);
			ZEPHIR_INIT_NVAR(&_52$$10);
			ZVAL_STRING(&_52$$10, "Route pattern \"%s\" cannot reference variable name \"%s\" more than once.");
			ZEPHIR_CALL_FUNCTION(&_53$$10, "sprintf", &_13, 22, &_52$$10, pattern, &varName);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &_51$$10, "__construct", NULL, 11, &_53$$10);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_51$$10, "zim/routing/routecompiler.zep", 106 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		if (zephir_fast_strlen_ev(&varName) > 32) {
			ZEPHIR_INIT_NVAR(&_54$$11);
			object_init_ex(&_54$$11, spl_ce_DomainException);
			ZEPHIR_INIT_NVAR(&_55$$11);
			ZVAL_STRING(&_55$$11, "Variable name \"%s\" cannot be longer than %s characters in route pattern \"%s\". Please use a shorter name.");
			ZVAL_LONG(&_56$$11, 32);
			ZEPHIR_CALL_FUNCTION(&_57$$11, "sprintf", &_13, 22, &_55$$11, &varName, &_56$$11, pattern);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(NULL, &_54$$11, "__construct", &_50, 105, &_57$$11);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_54$$11, "zim/routing/routecompiler.zep", 109 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		_58$$5 = isSeparator;
		if (_58$$5) {
			_58$$5 = !ZEPHIR_IS_IDENTICAL(&precedingText, &precedingChar);
		}
		_59$$5 = !isSeparator;
		if (_59$$5) {
			_59$$5 = zephir_fast_strlen_ev(&precedingText) > 0;
		}
		if (_58$$5) {
			ZEPHIR_INIT_NVAR(&_60$$12);
			zephir_create_array(&_60$$12, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_61$$12);
			ZVAL_STRING(&_61$$12, "text");
			zephir_array_fast_append(&_60$$12, &_61$$12);
			ZVAL_LONG(&_62$$12, 0);
			ZVAL_LONG(&_63$$12, -zephir_fast_strlen_ev(&precedingChar));
			ZEPHIR_INIT_NVAR(&_61$$12);
			zephir_substr(&_61$$12, &precedingText, 0 , zephir_get_intval(&_63$$12), 0);
			zephir_array_fast_append(&_60$$12, &_61$$12);
			zephir_array_append(&tokens, &_60$$12, PH_SEPARATE, "zim/routing/routecompiler.zep", 112);
		} else if (_59$$5) {
			ZEPHIR_INIT_NVAR(&_64$$13);
			zephir_create_array(&_64$$13, 2, 0 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_65$$13);
			ZVAL_STRING(&_65$$13, "text");
			zephir_array_fast_append(&_64$$13, &_65$$13);
			zephir_array_fast_append(&_64$$13, &precedingText);
			zephir_array_append(&tokens, &_64$$13, PH_SEPARATE, "zim/routing/routecompiler.zep", 114);
		}
		ZEPHIR_CALL_METHOD(&regexp, route, "getrequirement", &_66, 0, &varName);
		zephir_check_call_status();
		if (Z_TYPE_P(&regexp) == IS_NULL) {
			ZEPHIR_INIT_NVAR(&_67$$14);
			zephir_substr(&_67$$14, pattern, zephir_get_intval(&pos), 0, ZEPHIR_SUBSTR_NO_LENGTH);
			zephir_get_strval(&_68$$14, &_67$$14);
			ZEPHIR_CPY_WRT(&followingPattern, &_68$$14);
			ZEPHIR_CALL_SELF(&nextSeparator, "findnextseparator", &_69, 0, &followingPattern, &useUtf8);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_70$$14);
			ZVAL_STRING(&_70$$14, "#");
			ZEPHIR_CALL_FUNCTION(&_71$$14, "preg_quote", &_72, 76, &defaultSeparator, &_70$$14);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_73$$14);
			_74$$14 = !ZEPHIR_IS_IDENTICAL(&defaultSeparator, &nextSeparator);
			if (_74$$14) {
				_74$$14 = !ZEPHIR_IS_STRING_IDENTICAL(&nextSeparator, "");
			}
			if (_74$$14) {
				ZEPHIR_INIT_NVAR(&_70$$14);
				ZVAL_STRING(&_70$$14, "#");
				ZEPHIR_CALL_FUNCTION(&_73$$14, "preg_quote", &_72, 76, &nextSeparator, &_70$$14);
				zephir_check_call_status();
			} else {
				ZEPHIR_INIT_NVAR(&_73$$14);
				ZVAL_STRING(&_73$$14, "");
			}
			ZEPHIR_INIT_NVAR(&_70$$14);
			ZVAL_STRING(&_70$$14, "[^%s%s]+");
			ZEPHIR_CALL_FUNCTION(&regexp, "sprintf", &_13, 22, &_70$$14, &_71$$14, &_73$$14);
			zephir_check_call_status();
			_75$$14 = !ZEPHIR_IS_STRING_IDENTICAL(&nextSeparator, "");
			if (_75$$14) {
				ZEPHIR_INIT_NVAR(&_76$$14);
				ZEPHIR_INIT_NVAR(&_70$$14);
				ZVAL_STRING(&_70$$14, "#^\\{\\w+\\}#");
				ZEPHIR_INIT_NVAR(&_77$$14);
				ZEPHIR_INIT_NVAR(&_78$$14);
				ZVAL_STRING(&_78$$14, "#^\\{\\w+\\}#");
				zephir_preg_match(&_77$$14, &_78$$14, &followingPattern, &_76$$14, 0, 0 , 0  TSRMLS_CC);
				_75$$14 = !zephir_is_true(&_77$$14);
			}
			_79$$14 = _75$$14;
			if (!(_79$$14)) {
				_79$$14 = ZEPHIR_IS_STRING_IDENTICAL(&followingPattern, "");
			}
			if (_79$$14) {
				zephir_concat_self_str(&regexp, SL("+") TSRMLS_CC);
			}
		} else {
			ZEPHIR_INIT_NVAR(&_80$$16);
			ZEPHIR_INIT_NVAR(&_81$$16);
			ZVAL_STRING(&_81$$16, "//u");
			ZEPHIR_INIT_NVAR(&_82$$16);
			ZEPHIR_INIT_NVAR(&_83$$16);
			ZVAL_STRING(&_83$$16, "//u");
			zephir_preg_match(&_82$$16, &_83$$16, &regexp, &_80$$16, 0, 0 , 0  TSRMLS_CC);
			_84$$16 = !zephir_is_true(&needsUtf8);
			if (_84$$16) {
				ZEPHIR_INIT_NVAR(&_85$$16);
				ZEPHIR_INIT_NVAR(&_86$$16);
				ZVAL_STRING(&_86$$16, "/[\\x80-\\xFF]|(?<!\\\\)\\\\(?:\\\\\\\\)*+(?-i:X|[pP][\\{CLMNPSZ]|x\\{[A-Fa-f0-9]{3})/");
				ZEPHIR_INIT_NVAR(&_87$$16);
				ZEPHIR_INIT_NVAR(&_88$$16);
				ZVAL_STRING(&_88$$16, "/[\\x80-\\xFF]|(?<!\\\\)\\\\(?:\\\\\\\\)*+(?-i:X|[pP][\\{CLMNPSZ]|x\\{[A-Fa-f0-9]{3})/");
				zephir_preg_match(&_87$$16, &_88$$16, &regexp, &_85$$16, 0, 0 , 0  TSRMLS_CC);
				_84$$16 = zephir_is_true(&_87$$16);
			}
			if (!(zephir_is_true(&_82$$16))) {
				ZEPHIR_INIT_NVAR(&useUtf8);
				ZVAL_BOOL(&useUtf8, 0);
			} else if (_84$$16) {
				ZEPHIR_INIT_NVAR(&_89$$18);
				object_init_ex(&_89$$18, spl_ce_LogicException);
				ZEPHIR_INIT_NVAR(&_90$$18);
				ZVAL_STRING(&_90$$18, "Cannot use UTF-8 route requirements without setting the \"utf8\" option for variable \"%s\" in pattern \"%s\".");
				ZEPHIR_CALL_FUNCTION(&_91$$18, "sprintf", &_13, 22, &_90$$18, &varName, pattern);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, &_89$$18, "__construct", NULL, 11, &_91$$18);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_89$$18, "zim/routing/routecompiler.zep", 134 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			_92$$16 = !zephir_is_true(&useUtf8);
			if (_92$$16) {
				_92$$16 = zephir_is_true(&needsUtf8);
			}
			if (_92$$16) {
				ZEPHIR_INIT_NVAR(&_93$$19);
				object_init_ex(&_93$$19, spl_ce_LogicException);
				ZEPHIR_INIT_NVAR(&_94$$19);
				ZVAL_STRING(&_94$$19, "Cannot mix UTF-8 requirement with non-UTF-8 charset for variable \"%s\" in pattern \"%s\".");
				ZEPHIR_CALL_FUNCTION(&_95$$19, "sprintf", &_13, 22, &_94$$19, &varName, pattern);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, &_93$$19, "__construct", NULL, 11, &_95$$19);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_93$$19, "zim/routing/routecompiler.zep", 137 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_SELF(&_96$$16, "transformcapturinggroupstononcapturings", &_97, 0, &regexp);
			zephir_check_call_status();
			ZEPHIR_CPY_WRT(&regexp, &_96$$16);
		}
		ZEPHIR_INIT_NVAR(&_98$$5);
		zephir_create_array(&_98$$5, 4, 0 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&_99$$5);
		ZVAL_STRING(&_99$$5, "variable");
		zephir_array_fast_append(&_98$$5, &_99$$5);
		ZEPHIR_INIT_LNVAR(_100$$5);
		if (isSeparator) {
			ZEPHIR_CPY_WRT(&_100$$5, &precedingChar);
		} else {
			ZEPHIR_INIT_NVAR(&_100$$5);
			ZVAL_STRING(&_100$$5, "");
		}
		zephir_array_fast_append(&_98$$5, &_100$$5);
		zephir_array_fast_append(&_98$$5, &regexp);
		zephir_array_fast_append(&_98$$5, &varName);
		zephir_array_append(&tokens, &_98$$5, PH_SEPARATE, "zim/routing/routecompiler.zep", 141);
		zephir_array_append(&variables, &varName, PH_SEPARATE, "zim/routing/routecompiler.zep", 142);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&match);
	if (ZEPHIR_LT_LONG(&pos, zephir_fast_strlen_ev(pattern))) {
		ZEPHIR_INIT_VAR(&_101$$20);
		zephir_create_array(&_101$$20, 2, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_102$$20);
		ZVAL_STRING(&_102$$20, "text");
		zephir_array_fast_append(&_101$$20, &_102$$20);
		ZEPHIR_INIT_NVAR(&_102$$20);
		zephir_substr(&_102$$20, pattern, zephir_get_intval(&pos), 0, ZEPHIR_SUBSTR_NO_LENGTH);
		zephir_array_fast_append(&_101$$20, &_102$$20);
		zephir_array_append(&tokens, &_101$$20, PH_SEPARATE, "zim/routing/routecompiler.zep", 145);
	}
	ZEPHIR_INIT_VAR(&firstOptional);
	ZEPHIR_GET_CONSTANT(&firstOptional, "PHP_INT_MAX");
	ZEPHIR_INIT_VAR(&i);
	ZVAL_LONG(&i, 0);
	ZVAL_LONG(&_103, (zephir_fast_count_int(&tokens TSRMLS_CC) - 1));
	ZVAL_LONG(&_104, 0);
	ZEPHIR_CALL_FUNCTION(&aa, "range", &_105, 106, &_103, &_104);
	zephir_check_call_status();
	zephir_is_iterable(&aa, 0, "zim/routing/routecompiler.zep", 163);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&aa), _106)
	{
		ZEPHIR_INIT_NVAR(&i);
		ZVAL_COPY(&i, _106);
		ZEPHIR_OBS_NVAR(&token);
		zephir_array_fetch(&token, &tokens, &i, PH_NOISY, "zim/routing/routecompiler.zep", 155 TSRMLS_CC);
		zephir_array_fetch_long(&_107$$21, &token, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 156 TSRMLS_CC);
		_108$$21 = ZEPHIR_IS_STRING_IDENTICAL(&_107$$21, "variable");
		if (_108$$21) {
			zephir_array_fetch_long(&_110$$21, &token, 3, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 156 TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&_109$$21, route, "hasdefault", &_111, 0, &_110$$21);
			zephir_check_call_status();
			_108$$21 = zephir_is_true(&_109$$21);
		}
		if (_108$$21) {
			ZEPHIR_CPY_WRT(&firstOptional, &i);
		} else {
			break;
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_INIT_NVAR(&regexp);
	ZVAL_STRING(&regexp, "");
	ZEPHIR_INIT_NVAR(&i);
	ZVAL_LONG(&i, 0);
	_114 = (zephir_fast_count_int(&tokens TSRMLS_CC) - 1);
	_113 = 0;
	_112 = 0;
	if (_113 <= _114) {
		while (1) {
			if (_112) {
				_113++;
				if (!(_113 <= _114)) {
					break;
				}
			} else {
				_112 = 1;
			}
			ZEPHIR_INIT_NVAR(&i);
			ZVAL_LONG(&i, _113);
			ZEPHIR_CALL_SELF(&_115$$24, "computeregexp", &_116, 0, &tokens, &i, &firstOptional);
			zephir_check_call_status();
			zephir_concat_self(&regexp, &_115$$24 TSRMLS_CC);
		}
	}
	ZEPHIR_INIT_VAR(&_117);
	ZEPHIR_CONCAT_SSVSSS(&_117, "#", "^", &regexp, "$", "#", "sD");
	ZEPHIR_CPY_WRT(&regexp, &_117);
	if (zephir_is_true(&needsUtf8)) {
		zephir_concat_self_str(&regexp, SL("u") TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&i);
		ZVAL_LONG(&i, 0);
		_120$$25 = (zephir_fast_count_int(&tokens TSRMLS_CC) - 1);
		_119$$25 = 0;
		_118$$25 = 0;
		if (_119$$25 <= _120$$25) {
			while (1) {
				if (_118$$25) {
					_119$$25++;
					if (!(_119$$25 <= _120$$25)) {
						break;
					}
				} else {
					_118$$25 = 1;
				}
				ZEPHIR_INIT_NVAR(&i);
				ZVAL_LONG(&i, _119$$25);
				zephir_array_fetch(&_121$$26, &tokens, &i, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 174 TSRMLS_CC);
				zephir_array_fetch_long(&_122$$26, &_121$$26, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 174 TSRMLS_CC);
				if (ZEPHIR_IS_STRING_IDENTICAL(&_122$$26, "variable")) {
					zephir_array_update_multi(&tokens, &__$true TSRMLS_CC, SL("za"), 2, &i);
				}
			}
		}
	}
	zephir_create_array(return_value, 4, 0 TSRMLS_CC);
	ZEPHIR_CALL_SELF(&_123, "determinestaticprefix", NULL, 0, route, &tokens);
	zephir_check_call_status();
	zephir_array_update_string(return_value, SL("staticPrefix"), &_123, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("regex"), &regexp, PH_COPY | PH_SEPARATE);
	ZEPHIR_CALL_FUNCTION(&_123, "array_reverse", NULL, 107, &tokens);
	zephir_check_call_status();
	zephir_array_update_string(return_value, SL("tokens"), &_123, PH_COPY | PH_SEPARATE);
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
	zval *route, route_sub, *tokens_param = NULL, _0, _1, prefix, _10, _11, _13, _14, _16, _17, _18, _2$$3, _3$$3, _4$$3, _5$$3, _7$$3, _8$$3, _9$$3, _19$$4, _20$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&route_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&prefix);
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


	zephir_array_fetch_long(&_0, &tokens, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 192 TSRMLS_CC);
	zephir_array_fetch_long(&_1, &_0, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 192 TSRMLS_CC);
	if (!ZEPHIR_IS_STRING_IDENTICAL(&_1, "text")) {
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_array_fetch_long(&_4$$3, &tokens, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 193 TSRMLS_CC);
		zephir_array_fetch_long(&_5$$3, &_4$$3, 3, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 193 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_3$$3, route, "hasdefault", NULL, 0, &_5$$3);
		zephir_check_call_status();
		_6$$3 = zephir_is_true(&_3$$3);
		if (!(_6$$3)) {
			zephir_array_fetch_long(&_7$$3, &tokens, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 193 TSRMLS_CC);
			zephir_array_fetch_long(&_8$$3, &_7$$3, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 193 TSRMLS_CC);
			_6$$3 = ZEPHIR_IS_STRING_IDENTICAL(&_8$$3, "/");
		}
		if (_6$$3) {
			ZVAL_STRING(&_2$$3, "");
		} else {
			zephir_array_fetch_long(&_9$$3, &tokens, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 193 TSRMLS_CC);
			zephir_array_fetch_long(&_2$$3, &_9$$3, 1, PH_NOISY, "zim/routing/routecompiler.zep", 193 TSRMLS_CC);
		}
		RETURN_CCTOR(&_2$$3);
	}
	zephir_array_fetch_long(&_10, &tokens, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 197 TSRMLS_CC);
	ZEPHIR_OBS_VAR(&prefix);
	zephir_array_fetch_long(&prefix, &_10, 1, PH_NOISY, "zim/routing/routecompiler.zep", 197 TSRMLS_CC);
	zephir_array_fetch_long(&_11, &tokens, 1, PH_READONLY, "zim/routing/routecompiler.zep", 198 TSRMLS_CC);
	_12 = zephir_array_isset_long(&_11, 1);
	if (_12) {
		zephir_array_fetch_long(&_13, &tokens, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 198 TSRMLS_CC);
		zephir_array_fetch_long(&_14, &_13, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 198 TSRMLS_CC);
		_12 = !ZEPHIR_IS_STRING_IDENTICAL(&_14, "/");
	}
	_15 = _12;
	if (_15) {
		zephir_array_fetch_long(&_17, &tokens, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 198 TSRMLS_CC);
		zephir_array_fetch_long(&_18, &_17, 3, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 198 TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_16, route, "hasdefault", NULL, 0, &_18);
		zephir_check_call_status();
		_15 = ZEPHIR_IS_FALSE_IDENTICAL(&_16);
	}
	if (_15) {
		zephir_array_fetch_long(&_19$$4, &tokens, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 199 TSRMLS_CC);
		zephir_array_fetch_long(&_20$$4, &_19$$4, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 199 TSRMLS_CC);
		zephir_concat_self(&prefix, &_20$$4 TSRMLS_CC);
	}
	RETURN_CCTOR(&prefix);

}

/**
 * Returns the next static character in the Route pattern that will serve as a separator (or the empty string when none available).
 */
PHP_METHOD(Zim_Routing_RouteCompiler, findNextSeparator) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool useUtf8;
	zval *pattern_param = NULL, *useUtf8_param = NULL, _0, _1, _2, first, _10, _11, m$$5, _3$$5, _4$$5, _5$$5, _6$$5, _7$$5, _8$$5, _9$$5;
	zval pattern;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&pattern);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&first);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&m$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);

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
	ZEPHIR_CALL_FUNCTION(&_2, "preg_replace", NULL, 78, &_0, &_1, &pattern);
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
		zephir_preg_match(&_4$$5, &_5$$5, &pattern, &m$$5, 0, 0 , 0  TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_6$$5);
		zephir_array_fetch_long(&_7$$5, &m$$5, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 221 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_8$$5);
		ZVAL_STRING(&_8$$5, "/,;.:-_~+*=@|");
		ZEPHIR_INIT_VAR(&_9$$5);
		zephir_fast_strpos(&_9$$5, &_8$$5, &_7$$5, 0 );
		if (!ZEPHIR_IS_FALSE_IDENTICAL(&_9$$5)) {
			zephir_array_fetch_long(&_6$$5, &m$$5, 0, PH_NOISY, "zim/routing/routecompiler.zep", 221 TSRMLS_CC);
		} else {
			ZVAL_STRING(&_6$$5, "");
		}
		RETURN_CCTOR(&_6$$5);
	}
	ZVAL_LONG(&_10, 0);
	ZEPHIR_CALL_SELF(&first, "at", NULL, 0, &pattern, &_10);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_0);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "/,;.:-_~+*=@|");
	ZEPHIR_INIT_VAR(&_11);
	zephir_fast_strpos(&_11, &_1, &first, 0 );
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&_11)) {
		ZEPHIR_CPY_WRT(&_0, &first);
	} else {
		ZVAL_STRING(&_0, "");
	}
	RETURN_CCTOR(&_0);

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
	zval *tokens_param = NULL, *index_param = NULL, *firstOptional_param = NULL, token, regexp, nbTokens, _0, _1$$3, _2$$3, _5$$5, _6$$5, _7$$5, _8$$5, _9$$5, _11$$6, _12$$6, _13$$6, _14$$6, _15$$6, _16$$7, _17$$8, _18$$8, _19$$8, _20$$8;
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
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&_19$$8);
	ZVAL_UNDEF(&_20$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &tokens_param, &index_param, &firstOptional_param);

	zephir_get_arrval(&tokens, tokens_param);
	index = zephir_get_intval(index_param);
	firstOptional = zephir_get_intval(firstOptional_param);


	ZEPHIR_OBS_VAR(&token);
	zephir_array_fetch_long(&token, &tokens, index, PH_NOISY, "zim/routing/routecompiler.zep", 242 TSRMLS_CC);
	zephir_array_fetch_long(&_0, &token, 0, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 244 TSRMLS_CC);
	if (ZEPHIR_IS_STRING_IDENTICAL(&_0, "text")) {
		zephir_array_fetch_long(&_1$$3, &token, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 245 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "#");
		ZEPHIR_RETURN_CALL_FUNCTION("preg_quote", &_3, 76, &_1$$3, &_2$$3);
		zephir_check_call_status();
		RETURN_MM();
	} else {
		_4$$4 = 0 == index;
		if (_4$$4) {
			_4$$4 = 0 == firstOptional;
		}
		if (_4$$4) {
			zephir_array_fetch_long(&_5$$5, &token, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 250 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_6$$5);
			ZVAL_STRING(&_6$$5, "#");
			ZEPHIR_CALL_FUNCTION(&_7$$5, "preg_quote", &_3, 76, &_5$$5, &_6$$5);
			zephir_check_call_status();
			zephir_array_fetch_long(&_8$$5, &token, 3, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 250 TSRMLS_CC);
			zephir_array_fetch_long(&_9$$5, &token, 2, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 250 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_6$$5);
			ZVAL_STRING(&_6$$5, "%s(?P<%s>%s)?");
			ZEPHIR_RETURN_CALL_FUNCTION("sprintf", &_10, 22, &_6$$5, &_7$$5, &_8$$5, &_9$$5);
			zephir_check_call_status();
			RETURN_MM();
		} else {
			zephir_array_fetch_long(&_11$$6, &token, 1, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 252 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_12$$6);
			ZVAL_STRING(&_12$$6, "#");
			ZEPHIR_CALL_FUNCTION(&_13$$6, "preg_quote", &_3, 76, &_11$$6, &_12$$6);
			zephir_check_call_status();
			zephir_array_fetch_long(&_14$$6, &token, 3, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 252 TSRMLS_CC);
			zephir_array_fetch_long(&_15$$6, &token, 2, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 252 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_12$$6);
			ZVAL_STRING(&_12$$6, "%s(?P<%s>%s)");
			ZEPHIR_CALL_FUNCTION(&regexp, "sprintf", &_10, 22, &_12$$6, &_13$$6, &_14$$6, &_15$$6);
			zephir_check_call_status();
			if (index >= firstOptional) {
				ZEPHIR_INIT_VAR(&_16$$7);
				ZEPHIR_CONCAT_SV(&_16$$7, "(?:", &regexp);
				ZEPHIR_CPY_WRT(&regexp, &_16$$7);
				ZEPHIR_INIT_VAR(&nbTokens);
				ZVAL_LONG(&nbTokens, zephir_fast_count_int(&tokens TSRMLS_CC));
				if ((zephir_get_numberval(&nbTokens) - 1) == index) {
					ZEPHIR_INIT_VAR(&_17$$8);
					if (0 == firstOptional) {
						ZEPHIR_INIT_NVAR(&_17$$8);
						ZVAL_LONG(&_17$$8, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_17$$8);
						ZVAL_LONG(&_17$$8, 0);
					}
					ZEPHIR_INIT_VAR(&_18$$8);
					ZVAL_STRING(&_18$$8, ")?");
					ZVAL_LONG(&_19$$8, ((zephir_get_numberval(&nbTokens) - firstOptional) - zephir_get_numberval(&_17$$8)));
					ZEPHIR_CALL_FUNCTION(&_20$$8, "str_repeat", NULL, 108, &_18$$8, &_19$$8);
					zephir_check_call_status();
					zephir_concat_self(&regexp, &_20$$8 TSRMLS_CC);
				}
			}
			RETURN_CCTOR(&regexp);
		}
	}
	RETURN_MM_STRING("");

}

PHP_METHOD(Zim_Routing_RouteCompiler, transformCapturingGroupsToNonCapturings) {

	zend_bool _4$$3, _7$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0;
	zephir_fcall_cache_entry *_1 = NULL, *_12 = NULL;
	zval *regexp_param = NULL, _0$$3, _2$$3, _3$$3, _5$$3, _6$$3, _8$$3, _9$$3, _10$$3, _11$$3;
	zval regexp;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&regexp);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_11$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &regexp_param);

	zephir_get_strval(&regexp, regexp_param);


	i = -1;
	while (1) {
		if (!(i < (zephir_fast_strlen_ev(&regexp) - 1))) {
			break;
		}
		i++;
		ZVAL_LONG(&_2$$3, i);
		ZEPHIR_CALL_SELF(&_0$$3, "at", &_1, 0, &regexp, &_2$$3);
		zephir_check_call_status();
		if (ZEPHIR_IS_STRING_IDENTICAL(&_0$$3, "\\")) {
			i++;
			continue;
		}
		ZVAL_LONG(&_2$$3, i);
		ZEPHIR_CALL_SELF(&_3$$3, "at", &_1, 0, &regexp, &_2$$3);
		zephir_check_call_status();
		_4$$3 = !ZEPHIR_IS_STRING_IDENTICAL(&_3$$3, "(");
		if (!(_4$$3)) {
			ZVAL_LONG(&_2$$3, (i + 2));
			ZEPHIR_CALL_SELF(&_5$$3, "at", &_1, 0, &regexp, &_2$$3);
			zephir_check_call_status();
			_4$$3 = !zephir_is_true(&_5$$3);
		}
		if (_4$$3) {
			continue;
		}
		i++;
		ZVAL_LONG(&_2$$3, i);
		ZEPHIR_CALL_SELF(&_6$$3, "at", &_1, 0, &regexp, &_2$$3);
		zephir_check_call_status();
		_7$$3 = ZEPHIR_IS_STRING_IDENTICAL(&_6$$3, "*");
		if (!(_7$$3)) {
			ZVAL_LONG(&_2$$3, i);
			ZEPHIR_CALL_SELF(&_8$$3, "at", &_1, 0, &regexp, &_2$$3);
			zephir_check_call_status();
			_7$$3 = ZEPHIR_IS_STRING(&_8$$3, "?");
		}
		if (_7$$3) {
			i++;
			continue;
		}
		ZEPHIR_INIT_NVAR(&_9$$3);
		ZVAL_STRING(&_9$$3, "?:");
		ZVAL_LONG(&_2$$3, i);
		ZVAL_LONG(&_10$$3, 0);
		ZEPHIR_CALL_FUNCTION(&_11$$3, "substr_replace", &_12, 50, &regexp, &_9$$3, &_2$$3, &_10$$3);
		zephir_check_call_status();
		zephir_get_strval(&regexp, &_11$$3);
		i++;
	}
	RETURN_CTOR(&regexp);

}

PHP_METHOD(Zim_Routing_RouteCompiler, at) {

	zend_long i;
	zval *s, s_sub, *i_param = NULL, _0$$3, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&s_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	zephir_fetch_params(0, 2, 0, &s, &i_param);

	i = zephir_get_intval(i_param);


	if (Z_TYPE_P(s) == IS_ARRAY) {
		zephir_array_fetch_long(&_0$$3, s, i, PH_NOISY | PH_READONLY, "zim/routing/routecompiler.zep", 296 TSRMLS_CC);
		RETURN_CTORW(&_0$$3);
	}
	ZVAL_LONG(&_1, i);
	ZVAL_LONG(&_2, 1);
	zephir_substr(return_value, s, zephir_get_intval(&_1), 1 , 0);
	return;

}

