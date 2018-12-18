
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
#include "ext/spl/spl_iterators.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/**
 * A RouteCollection represents a set of Route instances.
 *
 * When adding a route at the end of the collection, an existing route
 * with the same name is removed first. So there can only be one route
 * with a given name.
 *
 * @author Fabien Potencier <fabien@symfony.com>
 * @author Tobias Schultze <http://tobion.de>
 */
ZEPHIR_INIT_CLASS(Zim_Routing_RouteCollection) {

	ZEPHIR_REGISTER_CLASS(Zim\\Routing, RouteCollection, zim, routing_routecollection, zim_routing_routecollection_method_entry, 0);

	/**
	 * @var Route[]
	 */
	zend_declare_property_null(zim_routing_routecollection_ce, SL("routes"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_routing_routecollection_ce->create_object = zephir_init_properties_Zim_Routing_RouteCollection;

	zend_class_implements(zim_routing_routecollection_ce TSRMLS_CC, 1, zend_ce_aggregate);
	zend_class_implements(zim_routing_routecollection_ce TSRMLS_CC, 1, spl_ce_Countable);
	return SUCCESS;

}

PHP_METHOD(Zim_Routing_RouteCollection, __clone) {

	zend_string *_3;
	zend_ulong _2;
	zval name, route, _0, *_1, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "zim/routing/routecollection.zep", 34);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_0), _2, _3, _1)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_3 != NULL) { 
			ZVAL_STR_COPY(&name, _3);
		} else {
			ZVAL_LONG(&name, _2);
		}
		ZEPHIR_INIT_NVAR(&route);
		ZVAL_COPY(&route, _1);
		ZEPHIR_INIT_LNVAR(_4$$3);
		if (zephir_clone(&_4$$3, &route TSRMLS_CC) == FAILURE) {
			RETURN_MM();
		}
		zephir_update_property_array(this_ptr, SL("routes"), &name, &_4$$3 TSRMLS_CC);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&route);
	ZEPHIR_INIT_NVAR(&name);
	ZEPHIR_MM_RESTORE();

}

/**
 * Gets the current RouteCollection as an Iterator that includes all routes.
 *
 * It implements \IteratorAggregate.
 *
 * @see all()
 *
 * @return \ArrayIterator|Route[] An \ArrayIterator object for iterating over routes
 */
PHP_METHOD(Zim_Routing_RouteCollection, getIterator) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, zephir_get_internal_ce(SL("arrayiterator")));
	zephir_read_property(&_0, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 18, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Gets the number of Routes in this collection.
 *
 * @return int The number of routes
 */
PHP_METHOD(Zim_Routing_RouteCollection, count) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	RETURN_LONG(zephir_fast_count_int(&_0 TSRMLS_CC));

}

/**
 * Adds a route.
 *
 * @param string $name  The route name
 * @param Route  $route A Route instance
 */
PHP_METHOD(Zim_Routing_RouteCollection, add) {

	zval *name_param = NULL, *route, route_sub, _0;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&route_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &name_param, &route);

	zephir_get_strval(&name, name_param);


	zephir_read_property(&_0, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, &name, PH_SEPARATE);
	zephir_update_property_array(this_ptr, SL("routes"), &name, route TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Returns all routes in this collection.
 *
 * @return Route[] An array of routes
 */
PHP_METHOD(Zim_Routing_RouteCollection, all) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "routes");

}

/**
 * Gets a route by name.
 *
 * @param string $name The route name
 *
 * @return Route|null A Route instance or null when not found
 */
PHP_METHOD(Zim_Routing_RouteCollection, get) {

	zval *name_param = NULL, _0, _1, _2;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_1, &name)) {
		zephir_read_property(&_2, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
		zephir_array_fetch(&_0, &_2, &name, PH_NOISY, "zim/routing/routecollection.zep", 92 TSRMLS_CC);
	} else {
		ZVAL_NULL(&_0);
	}
	RETURN_CCTOR(&_0);

}

/**
 * Removes a route or an array of routes by name from the collection.
 *
 * @param string $name The route name or an array of route names
 */
PHP_METHOD(Zim_Routing_RouteCollection, remove) {

	zval *name_param = NULL, _0;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	zephir_read_property(&_0, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	zephir_array_unset(&_0, &name, PH_SEPARATE);
	ZEPHIR_MM_RESTORE();

}

/**
 * Adds a route collection at the end of the current set by appending all
 * routes of the added collection.
 */
PHP_METHOD(Zim_Routing_RouteCollection, addCollection) {

	zend_string *_3;
	zend_ulong _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *collection, collection_sub, name, route, _0, *_1, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&collection_sub);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &collection);



	ZEPHIR_CALL_METHOD(&_0, collection, "all", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_0, 0, "zim/routing/routecollection.zep", 120);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_0), _2, _3, _1)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_3 != NULL) { 
			ZVAL_STR_COPY(&name, _3);
		} else {
			ZVAL_LONG(&name, _2);
		}
		ZEPHIR_INIT_NVAR(&route);
		ZVAL_COPY(&route, _1);
		zephir_read_property(&_4$$3, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
		zephir_array_unset(&_4$$3, &name, PH_SEPARATE);
		zephir_update_property_array(this_ptr, SL("routes"), &name, &route TSRMLS_CC);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&route);
	ZEPHIR_INIT_NVAR(&name);
	ZEPHIR_MM_RESTORE();

}

/**
 * Adds a prefix to the path of all child routes.
 *
 * @param string $prefix       An optional prefix to add before each pattern of the route collection
 * @param array  $defaults     An array of default values
 * @param array  $requirements An array of requirements
 */
PHP_METHOD(Zim_Routing_RouteCollection, addPrefix) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval defaults, requirements;
	zval *prefix_param = NULL, *defaults_param = NULL, *requirements_param = NULL, route, _0, _1, _2, *_3, _4$$4, _5$$4;
	zval prefix;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&defaults);
	ZVAL_UNDEF(&requirements);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &prefix_param, &defaults_param, &requirements_param);

	zephir_get_strval(&prefix, prefix_param);
	if (!defaults_param) {
		ZEPHIR_INIT_VAR(&defaults);
		array_init(&defaults);
	} else {
		zephir_get_arrval(&defaults, defaults_param);
	}
	if (!requirements_param) {
		ZEPHIR_INIT_VAR(&requirements);
		array_init(&requirements);
	} else {
		zephir_get_arrval(&requirements, requirements_param);
	}


	ZEPHIR_INIT_VAR(&_0);
	zephir_fast_trim(&_0, &prefix, NULL , ZEPHIR_TRIM_BOTH TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "/");
	ZEPHIR_INIT_NVAR(&prefix);
	zephir_fast_trim(&prefix, &_0, &_1, ZEPHIR_TRIM_BOTH TSRMLS_CC);
	if (ZEPHIR_IS_STRING_IDENTICAL(&prefix, "")) {
		RETURN_MM_NULL();
	}
	zephir_read_property(&_2, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_2, 0, "zim/routing/routecollection.zep", 142);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_2), _3)
	{
		ZEPHIR_INIT_NVAR(&route);
		ZVAL_COPY(&route, _3);
		ZEPHIR_CALL_METHOD(&_4$$4, &route, "getpath", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_LNVAR(_5$$4);
		ZEPHIR_CONCAT_SVV(&_5$$4, "/", &prefix, &_4$$4);
		ZEPHIR_CALL_METHOD(NULL, &route, "setpath", NULL, 0, &_5$$4);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &route, "adddefaults", NULL, 0, &defaults);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(NULL, &route, "addrequirements", NULL, 0, &requirements);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&route);
	ZEPHIR_MM_RESTORE();

}

/**
 * Adds a prefix to the name of all the routes within in the collection.
 */
PHP_METHOD(Zim_Routing_RouteCollection, addNamePrefix) {

	zend_string *_3;
	zend_ulong _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *prefix_param = NULL, prefixedRoutes, name, route, _0, *_1, _4$$3, _5$$3, _6$$4, _7$$4;
	zval prefix;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&prefix);
	ZVAL_UNDEF(&prefixedRoutes);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &prefix_param);

	zephir_get_strval(&prefix, prefix_param);


	ZEPHIR_INIT_VAR(&prefixedRoutes);
	array_init(&prefixedRoutes);
	zephir_read_property(&_0, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "zim/routing/routecollection.zep", 159);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_0), _2, _3, _1)
	{
		ZEPHIR_INIT_NVAR(&name);
		if (_3 != NULL) { 
			ZVAL_STR_COPY(&name, _3);
		} else {
			ZVAL_LONG(&name, _2);
		}
		ZEPHIR_INIT_NVAR(&route);
		ZVAL_COPY(&route, _1);
		ZEPHIR_INIT_LNVAR(_4$$3);
		ZEPHIR_CONCAT_VV(&_4$$3, &prefix, &name);
		zephir_array_update_zval(&prefixedRoutes, &_4$$3, &route, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_NVAR(&_5$$3);
		ZVAL_STRING(&_5$$3, "_canonical_route");
		ZEPHIR_CALL_METHOD(&name, &route, "getdefault", NULL, 0, &_5$$3);
		zephir_check_call_status();
		if (Z_TYPE_P(&name) != IS_NULL) {
			ZEPHIR_INIT_LNVAR(_6$$4);
			ZEPHIR_CONCAT_VV(&_6$$4, &prefix, &name);
			ZEPHIR_INIT_NVAR(&_7$$4);
			ZVAL_STRING(&_7$$4, "_canonical_route");
			ZEPHIR_CALL_METHOD(NULL, &route, "setdefault", NULL, 0, &_7$$4, &_6$$4);
			zephir_check_call_status();
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&route);
	ZEPHIR_INIT_NVAR(&name);
	zephir_update_property_zval(this_ptr, SL("routes"), &prefixedRoutes);
	ZEPHIR_MM_RESTORE();

}

/**
 * Adds defaults to all routes.
 *
 * An existing default value under the same name in a route will be overridden.
 *
 * @param array $defaults An array of default values
 */
PHP_METHOD(Zim_Routing_RouteCollection, addDefaults) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *defaults_param = NULL, route, _0$$3, *_1$$3;
	zval defaults;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&defaults);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &defaults_param);

	zephir_get_arrval(&defaults, defaults_param);


	if (zephir_fast_count_int(&defaults TSRMLS_CC) > 0) {
		zephir_read_property(&_0$$3, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
		zephir_is_iterable(&_0$$3, 0, "zim/routing/routecollection.zep", 177);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0$$3), _1$$3)
		{
			ZEPHIR_INIT_NVAR(&route);
			ZVAL_COPY(&route, _1$$3);
			ZEPHIR_CALL_METHOD(NULL, &route, "adddefaults", NULL, 0, &defaults);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&route);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Adds requirements to all routes.
 *
 * An existing requirement under the same name in a route will be overridden.
 *
 * @param array $requirements An array of requirements
 */
PHP_METHOD(Zim_Routing_RouteCollection, addRequirements) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *requirements_param = NULL, route, _0$$3, *_1$$3;
	zval requirements;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&requirements);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &requirements_param);

	zephir_get_arrval(&requirements, requirements_param);


	if (zephir_fast_count_int(&requirements TSRMLS_CC) > 0) {
		zephir_read_property(&_0$$3, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
		zephir_is_iterable(&_0$$3, 0, "zim/routing/routecollection.zep", 195);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0$$3), _1$$3)
		{
			ZEPHIR_INIT_NVAR(&route);
			ZVAL_COPY(&route, _1$$3);
			ZEPHIR_CALL_METHOD(NULL, &route, "addrequirements", NULL, 0, &requirements);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&route);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Adds options to all routes.
 *
 * An existing option value under the same name in a route will be overridden.
 *
 * @param array $options An array of options
 */
PHP_METHOD(Zim_Routing_RouteCollection, addOptions) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *options_param = NULL, route, _0$$3, *_1$$3;
	zval options;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&options);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &options_param);

	zephir_get_arrval(&options, options_param);


	if (zephir_fast_count_int(&options TSRMLS_CC) > 0) {
		zephir_read_property(&_0$$3, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
		zephir_is_iterable(&_0$$3, 0, "zim/routing/routecollection.zep", 213);
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0$$3), _1$$3)
		{
			ZEPHIR_INIT_NVAR(&route);
			ZVAL_COPY(&route, _1$$3);
			ZEPHIR_CALL_METHOD(NULL, &route, "addoptions", NULL, 0, &options);
			zephir_check_call_status();
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&route);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Sets the HTTP methods (e.g. 'POST') all child routes are restricted to.
 *
 * @param string[] $methods The method or an array of methods
 */
PHP_METHOD(Zim_Routing_RouteCollection, setMethods) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *methods_param = NULL, route, _0, *_1;
	zval methods;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&methods);
	ZVAL_UNDEF(&route);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &methods_param);

	zephir_get_arrval(&methods, methods_param);


	zephir_read_property(&_0, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "zim/routing/routecollection.zep", 228);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
	{
		ZEPHIR_INIT_NVAR(&route);
		ZVAL_COPY(&route, _1);
		ZEPHIR_CALL_METHOD(NULL, &route, "setmethods", NULL, 0, &methods);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&route);
	ZEPHIR_MM_RESTORE();

}

zend_object *zephir_init_properties_Zim_Routing_RouteCollection(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _1$$3;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("routes"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("routes"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

