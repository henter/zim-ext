
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
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "kernel/file.h"
#include "kernel/array.h"
#include "ext/spl/spl_array.h"


/**
 * File Kernel.php
 * @henter
 * Time: 2018-11-26 16:07
 */
ZEPHIR_INIT_CLASS(Zim_Http_Kernel) {

	ZEPHIR_REGISTER_CLASS(Zim\\Http, Kernel, zim, http_kernel, zim_http_kernel_method_entry, 0);

	/**
	 * @var Zim
	 */
	zend_declare_property_null(zim_http_kernel_ce, SL("zim"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * @var Router
	 */
	zend_declare_property_null(zim_http_kernel_ce, SL("router"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Create a new HTTP kernel instance.
 *
 * @param  Zim    $zim
 * @param  Router $router
 * @return void
 */
PHP_METHOD(Zim_Http_Kernel, __construct) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *zim, zim_sub, *router, router_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&zim_sub);
	ZVAL_UNDEF(&router_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &zim, &router);



	zephir_update_property_zval(this_ptr, SL("zim"), zim);
	zephir_update_property_zval(this_ptr, SL("router"), router);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "bootstraproutes", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Zim_Http_Kernel, bootstrapRoutes) {

	zend_string *_4;
	zend_ulong _3;
	zval configs, pattern, to, _1, *_2, _5$$4, _6$$4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&configs);
	ZVAL_UNDEF(&pattern);
	ZVAL_UNDEF(&to);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "routes");
	ZEPHIR_CALL_CE_STATIC(&configs, zim_zim_ce, "config", &_0, 0, &_1);
	zephir_check_call_status();
	if (Z_TYPE_P(&configs) != IS_ARRAY) {
		RETURN_MM_BOOL(0);
	}
	zephir_is_iterable(&configs, 0, "zim/http/kernel.zep", 57);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&configs), _3, _4, _2)
	{
		ZEPHIR_INIT_NVAR(&pattern);
		if (_4 != NULL) { 
			ZVAL_STR_COPY(&pattern, _4);
		} else {
			ZVAL_LONG(&pattern, _3);
		}
		ZEPHIR_INIT_NVAR(&to);
		ZVAL_COPY(&to, _2);
		zephir_read_property(&_5$$4, this_ptr, SL("router"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_NVAR(&_6$$4);
		array_init(&_6$$4);
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "addroute", NULL, 0, &_6$$4, &pattern, &to);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&to);
	ZEPHIR_INIT_NVAR(&pattern);
	RETURN_MM_BOOL(1);

}

/**
 * @param Request $request
 * @return Response
 * @throws \Throwable
 */
PHP_METHOD(Zim_Http_Kernel, handle) {

	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *request, request_sub, requestEvent, resp, response, e, respEvent, _0, _1, _2, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&request_sub);
	ZVAL_UNDEF(&requestEvent);
	ZVAL_UNDEF(&resp);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&respEvent);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	zephir_read_property(&_0, this_ptr, SL("zim"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "request");
	ZEPHIR_CALL_METHOD(NULL, &_0, "instance", NULL, 0, &_1, request);
	zephir_check_call_status();
	zephir_read_property(&_2, this_ptr, SL("zim"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, &_2, "boot", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&requestEvent);
	object_init_ex(&requestEvent, zim_event_requestevent_ce);
	ZEPHIR_CALL_METHOD(NULL, &requestEvent, "__construct", NULL, 83, request);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(NULL, zim_event_event_ce, "fire", &_3, 0, &requestEvent);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&resp, &requestEvent, "getresponse", NULL, 84);
	zephir_check_call_status();
	if (zephir_is_true(&resp)) {
		ZEPHIR_RETURN_CALL_METHOD(&resp, "prepare", NULL, 0, request);
		zephir_check_call_status();
		RETURN_MM();
	}

	/* try_start_1: */

		ZEPHIR_CALL_METHOD(&response, this_ptr, "dispatchtorouter", NULL, 0, request);
		zephir_check_call_status_or_jump(try_end_1);
		RETURN_MM_NULL();

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_NVAR(&_1);
		ZVAL_OBJ(&_1, EG(exception));
		Z_ADDREF_P(&_1);
		if (zephir_instance_of_ev(&_1, zim_http_exception_notfoundexception_ce TSRMLS_CC)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CPY_WRT(&e, &_1);
			ZEPHIR_CALL_METHOD(&response, this_ptr, "dispatchtodefault", NULL, 0, request);
			zephir_check_call_status();
		} else {
			if (zephir_is_instance_of(&_1, SL("Throwable") TSRMLS_CC)) {
				zend_clear_exception(TSRMLS_C);
				ZEPHIR_CPY_WRT(&e, &_1);
				zephir_throw_exception_debug(&e, "zim/http/kernel.zep", 83 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
		}
	}
	ZEPHIR_INIT_VAR(&respEvent);
	object_init_ex(&respEvent, zim_event_responseevent_ce);
	ZEPHIR_CALL_METHOD(NULL, &respEvent, "__construct", NULL, 83, request, &response);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(NULL, zim_event_event_ce, "fire", &_3, 0, &respEvent);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_4, &respEvent, "getresponse", NULL, 84);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_4, "prepare", NULL, 0, request);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * 根据 uri 猜测 controller 类名
 * @param string $uri
 * @return string|bool
 */
PHP_METHOD(Zim_Http_Kernel, guessController) {

	zephir_fcall_cache_entry *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *uri_param = NULL, _0, _1, suffix, files, file, name, _2, _3, _4, *_5, _7$$5, _8$$5;
	zval uri;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&uri);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&suffix);
	ZVAL_UNDEF(&files);
	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &uri_param);

	zephir_get_strval(&uri, uri_param);


	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "APP_PATH");
	ZEPHIR_CALL_FUNCTION(&_1, "defined", NULL, 85, &_0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_1))) {
		RETURN_MM_BOOL(0);
	}
	ZEPHIR_INIT_NVAR(&_0);
	zephir_ucfirst(&_0, &uri);
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_CONCAT_SVS(&_2, "App\\Controller\\", &_0, "Controller");
	if (zephir_class_exists(&_2, 1 TSRMLS_CC)) {
		zephir_ucfirst(return_value, &uri);
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&suffix);
	ZVAL_STRING(&suffix, "Controller.php");
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_GET_CONSTANT(&_3, "APP_PATH");
	ZEPHIR_INIT_VAR(&_4);
	ZEPHIR_CONCAT_VSV(&_4, &_3, "/Controller/*", &suffix);
	ZEPHIR_CALL_FUNCTION(&files, "glob", NULL, 86, &_4);
	zephir_check_call_status();
	zephir_is_iterable(&files, 0, "zim/http/kernel.zep", 113);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&files), _5)
	{
		ZEPHIR_INIT_NVAR(&file);
		ZVAL_COPY(&file, _5);
		ZEPHIR_INIT_NVAR(&_7$$5);
		zephir_basename(&_7$$5, &file TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&_8$$5);
		ZVAL_STRING(&_8$$5, "");
		ZEPHIR_CALL_CE_STATIC(&name, zim_support_str_ce, "replacelast", &_6, 0, &suffix, &_8$$5, &_7$$5);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_8$$5);
		zephir_fast_strtolower(&_8$$5, &name);
		if (ZEPHIR_IS_IDENTICAL(&uri, &_8$$5)) {
			RETURN_CCTOR(&name);
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&file);
	RETURN_MM_BOOL(0);

}

/**
 * default IndexController indexAction, same as yaf
 *
 * rules:
 * /            => Index@index
 * /foo         => Foo@index or Index@foo
 * /foo/bar     => Foo@bar
 *
 * @param Request $request
 * @return array
 */
PHP_METHOD(Zim_Http_Kernel, getDefaultRoute) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *request, request_sub, segments, c, a, tmpListCA, _0, _1, _2, _3, _5, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&request_sub);
	ZVAL_UNDEF(&segments);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&tmpListCA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CALL_METHOD(&_2, request, "getpathinfo", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "/");
	zephir_fast_trim(&_1, &_2, &_3, ZEPHIR_TRIM_BOTH TSRMLS_CC);
	zephir_fast_explode_str(&_0, SL("/"), &_1, LONG_MAX TSRMLS_CC);
	ZEPHIR_CALL_FUNCTION(&segments, "array_filter", NULL, 87, &_0);
	zephir_check_call_status();
	if (!(zephir_is_true(&segments))) {
		zephir_create_array(return_value, 2, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "Index");
		zephir_array_fast_append(return_value, &_4$$3);
		ZEPHIR_INIT_NVAR(&_4$$3);
		ZVAL_STRING(&_4$$3, "index");
		zephir_array_fast_append(return_value, &_4$$3);
		RETURN_MM();
	}
	if (zephir_array_isset_long(&segments, 1)) {
		ZEPHIR_CPY_WRT(&tmpListCA, &segments);
		ZEPHIR_OBS_VAR(&c);
		zephir_array_fetch_long(&c, &tmpListCA, 0, PH_NOISY, "zim/http/kernel.zep", 139 TSRMLS_CC);
		ZEPHIR_OBS_VAR(&a);
		zephir_array_fetch_long(&a, &tmpListCA, 1, PH_NOISY, "zim/http/kernel.zep", 140 TSRMLS_CC);
	} else {
		ZEPHIR_OBS_NVAR(&c);
		zephir_array_fetch_long(&c, &segments, 0, PH_NOISY, "zim/http/kernel.zep", 142 TSRMLS_CC);
		ZEPHIR_INIT_NVAR(&a);
		ZVAL_STRING(&a, "index");
	}
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "guesscontroller", NULL, 0, &c);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&c, &_5);
	if (!(zephir_is_true(&c))) {
		ZEPHIR_INIT_NVAR(&c);
		ZVAL_STRING(&c, "Index");
		ZEPHIR_OBS_NVAR(&a);
		zephir_array_fetch_long(&a, &segments, 0, PH_NOISY, "zim/http/kernel.zep", 149 TSRMLS_CC);
	}
	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(return_value, &c);
	zephir_array_fast_append(return_value, &a);
	RETURN_MM();

}

/**
 * 默认路由规则
 * 即：
 *      如果存在 FooController
 *      /foo     => App\Controller\FooController::indexAction
 *      /foo/bar => App\Controller\FooController::barAction
 *      /foo/bar => App\Controller\FooController::$actions[bar]::execute
 *
 *      否则
 *      /foo     => App\Controller\IndexController::fooAction
 *      /foo/bar => App\Controller\IndexController::fooAction
 *
 * @param Request $request
 * @return Response
 * @throws \Throwable
 */
PHP_METHOD(Zim_Http_Kernel, dispatchToDefault) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *request, request_sub, c, a, tmpListCA, controller, method, callablee, actionClass, _0, _1, _2$$4, _3$$4, _4$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&request_sub);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&tmpListCA);
	ZVAL_UNDEF(&controller);
	ZVAL_UNDEF(&method);
	ZVAL_UNDEF(&callablee);
	ZVAL_UNDEF(&actionClass);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	ZEPHIR_CALL_METHOD(&tmpListCA, this_ptr, "getdefaultroute", NULL, 0, request);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&c);
	zephir_array_fetch_long(&c, &tmpListCA, 0, PH_NOISY, "zim/http/kernel.zep", 176 TSRMLS_CC);
	ZEPHIR_OBS_VAR(&a);
	zephir_array_fetch_long(&a, &tmpListCA, 1, PH_NOISY, "zim/http/kernel.zep", 177 TSRMLS_CC);
	zephir_read_property(&_0, this_ptr, SL("zim"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CONCAT_SVS(&_1, "App\\Controller\\", &c, "Controller");
	ZEPHIR_CALL_METHOD(&controller, &_0, "make", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&method, &controller, "getaction", NULL, 0, &a);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&callablee);
	if (zephir_is_true(&method)) {
		zephir_create_array(&callablee, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&callablee, &controller);
		zephir_array_fast_append(&callablee, &method);
	} else {
		ZEPHIR_CALL_METHOD(&actionClass, &controller, "getactionclass", NULL, 0, &a);
		zephir_check_call_status();
		if (!(zephir_class_exists(&actionClass, 1 TSRMLS_CC))) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zim_http_exception_notfoundexception_ce, "action not found", "zim/http/kernel.zep", 190);
			return;
		}
		zephir_create_array(&callablee, 2, 0 TSRMLS_CC);
		zephir_read_property(&_2$$4, this_ptr, SL("zim"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_METHOD(&_3$$4, &_2$$4, "make", NULL, 0, &actionClass);
		zephir_check_call_status();
		zephir_array_fast_append(&callablee, &_3$$4);
		ZEPHIR_INIT_VAR(&_4$$4);
		ZVAL_STRING(&_4$$4, "execute");
		zephir_array_fast_append(&callablee, &_4$$4);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dodispatch", NULL, 0, request, &callablee);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * 基于路由规则匹配
 *
 * @param Request $request
 * @return Response
 */
PHP_METHOD(Zim_Http_Kernel, dispatchToRouter) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *request, request_sub, route, callablee, _0, _1, _9, _2$$3, _3$$3, _4$$3, _5$$3, _6$$4, _7$$4, _8$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&request_sub);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&callablee);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &request);



	zephir_read_property(&_0, this_ptr, SL("router"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&route, &_0, "matchrequest", NULL, 0, request);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "_callable");
	ZEPHIR_CALL_METHOD(&callablee, &route, "getdefault", NULL, 0, &_1);
	zephir_check_call_status();
	if (!(zephir_is_true(&callablee))) {
		ZEPHIR_INIT_NVAR(&callablee);
		zephir_create_array(&callablee, 2, 0 TSRMLS_CC);
		zephir_read_property(&_2$$3, this_ptr, SL("zim"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_5$$3);
		ZVAL_STRING(&_5$$3, "_controller");
		ZEPHIR_CALL_METHOD(&_4$$3, &route, "getdefault", NULL, 0, &_5$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_3$$3, &_2$$3, "make", NULL, 0, &_4$$3);
		zephir_check_call_status();
		zephir_array_fast_append(&callablee, &_3$$3);
		ZEPHIR_INIT_NVAR(&_5$$3);
		ZVAL_STRING(&_5$$3, "_action");
		ZEPHIR_CALL_METHOD(&_3$$3, &route, "getdefault", NULL, 0, &_5$$3);
		zephir_check_call_status();
		zephir_array_fast_append(&callablee, &_3$$3);
		if (!(zephir_is_callable(&callablee TSRMLS_CC))) {
			ZEPHIR_INIT_VAR(&_6$$4);
			object_init_ex(&_6$$4, zim_http_exception_notfoundexception_ce);
			zephir_array_fetch_long(&_7$$4, &callablee, 1, PH_NOISY | PH_READONLY, "zim/http/kernel.zep", 212 TSRMLS_CC);
			ZEPHIR_INIT_VAR(&_8$$4);
			ZEPHIR_CONCAT_SV(&_8$$4, "action not found ", &_7$$4);
			ZEPHIR_CALL_METHOD(NULL, &_6$$4, "__construct", NULL, 88, &_8$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_6$$4, "zim/http/kernel.zep", 212 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_CALL_METHOD(&_9, &route, "getparameters", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dodispatch", NULL, 0, request, &callablee, &_9);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param Request  $request
 * @param callable $callable
 * @param array    $params
 * @return Response
 */
PHP_METHOD(Zim_Http_Kernel, doDispatch) {

	zephir_fcall_cache_entry *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params, _1$$3, _6$$4;
	zval *request, request_sub, *callablee, callablee_sub, *params_param = NULL, e, resp, _9, _10, _0$$3, _2$$3, _3$$3, _4$$3, _5$$4, _7$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&request_sub);
	ZVAL_UNDEF(&callablee_sub);
	ZVAL_UNDEF(&e);
	ZVAL_UNDEF(&resp);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_6$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &request, &callablee, &params_param);

	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}


	if (Z_TYPE_P(callablee) == IS_ARRAY) {
		zephir_read_property(&_0$$3, request, SL("attributes"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_create_array(&_1$$3, 2, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_array_fetch_long(&_3$$3, callablee, 0, PH_NOISY | PH_READONLY, "zim/http/kernel.zep", 229 TSRMLS_CC);
		zephir_get_class(&_2$$3, &_3$$3, 0 TSRMLS_CC);
		zephir_array_fast_append(&_1$$3, &_2$$3);
		ZEPHIR_OBS_VAR(&_4$$3);
		zephir_array_fetch_long(&_4$$3, callablee, 1, PH_NOISY, "zim/http/kernel.zep", 229 TSRMLS_CC);
		zephir_array_fast_append(&_1$$3, &_4$$3);
		ZEPHIR_INIT_NVAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "callable");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "set", NULL, 0, &_2$$3, &_1$$3);
		zephir_check_call_status();
	} else {
		zephir_read_property(&_5$$4, request, SL("attributes"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_6$$4);
		zephir_create_array(&_6$$4, 2, 0 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_7$$4);
		ZVAL_STRING(&_7$$4, "Closure");
		zephir_array_fast_append(&_6$$4, &_7$$4);
		ZEPHIR_INIT_NVAR(&_7$$4);
		ZVAL_STRING(&_7$$4, "Closure");
		zephir_array_fast_append(&_6$$4, &_7$$4);
		ZEPHIR_INIT_NVAR(&_7$$4);
		ZVAL_STRING(&_7$$4, "callable");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "set", NULL, 0, &_7$$4, &_6$$4);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&e);
	object_init_ex(&e, zim_event_dispatchevent_ce);
	ZEPHIR_CALL_METHOD(NULL, &e, "__construct", NULL, 83, request);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(NULL, zim_event_event_ce, "fire", &_8, 0, &e);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&resp, &e, "getresponse", NULL, 84);
	zephir_check_call_status();
	if (zephir_is_true(&resp)) {
		ZEPHIR_RETURN_CALL_METHOD(&resp, "prepare", NULL, 0, request);
		zephir_check_call_status();
		RETURN_MM();
	}
	zephir_read_property(&_9, this_ptr, SL("zim"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, &_9, "call", NULL, 0, callablee, &params);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "toresponse", NULL, 0, &_10);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param mixed $resp
 * @return Response
 */
PHP_METHOD(Zim_Http_Kernel, toResponse) {

	zend_bool _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *resp, resp_sub, response, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&resp_sub);
	ZVAL_UNDEF(&response);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &resp);



	_0 = Z_TYPE_P(resp) == IS_OBJECT;
	if (_0) {
		_0 = zephir_instance_of_ev(resp, zim_http_response_ce TSRMLS_CC);
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shouldbejson", NULL, 0, resp);
	zephir_check_call_status();
	if (_0) {
		ZEPHIR_CPY_WRT(&response, resp);
	} else if (zephir_is_true(&_1)) {
		ZEPHIR_INIT_NVAR(&response);
		object_init_ex(&response, zim_http_jsonresponse_ce);
		ZEPHIR_CALL_METHOD(NULL, &response, "__construct", NULL, 79, resp);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&response);
		object_init_ex(&response, zim_http_response_ce);
		ZEPHIR_CALL_METHOD(NULL, &response, "__construct", NULL, 21, resp);
		zephir_check_call_status();
	}
	RETURN_CCTOR(&response);

}

/**
 * Determine if the given content should be turned into JSON.
 *
 * @param  mixed  $content
 * @return bool
 */
PHP_METHOD(Zim_Http_Kernel, shouldBeJson) {

	zend_bool _0, _1, _2, _3, _4;
	zval *content, content_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content_sub);

	zephir_fetch_params(0, 1, 0, &content);



	_0 = Z_TYPE_P(content) == IS_ARRAY;
	if (!(_0)) {
		_1 = Z_TYPE_P(content) == IS_OBJECT;
		if (_1) {
			_2 = zephir_instance_of_ev(content, zim_contract_arrayable_ce TSRMLS_CC);
			if (!(_2)) {
				_2 = zephir_instance_of_ev(content, zim_contract_jsonable_ce TSRMLS_CC);
			}
			_3 = _2;
			if (!(_3)) {
				_3 = zephir_instance_of_ev(content, spl_ce_ArrayObject TSRMLS_CC);
			}
			_4 = _3;
			if (!(_4)) {
				_4 = zephir_is_instance_of(content, SL("JsonSerializable") TSRMLS_CC);
			}
			_1 = _4;
		}
		_0 = _1;
	}
	RETURN_BOOL(_0);

}

/**
 * will not return to fastcgi
 *
 * @param Request  $request
 * @param Response $response
 */
PHP_METHOD(Zim_Http_Kernel, terminate) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *request, request_sub, *response, response_sub, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&request_sub);
	ZVAL_UNDEF(&response_sub);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &request, &response);



	ZEPHIR_INIT_VAR(&_1);
	object_init_ex(&_1, zim_event_terminateevent_ce);
	ZEPHIR_CALL_METHOD(NULL, &_1, "__construct", NULL, 83, request, response);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(NULL, zim_event_event_ce, "fire", &_0, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

