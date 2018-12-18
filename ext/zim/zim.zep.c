
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/require.h"
#include "kernel/file.h"


/**
 * File App.php
 * @henter
 * Time: 2018-11-24 19:29
 *
 */
/**
 * Class Zim
 * @package Zim
 */
ZEPHIR_INIT_CLASS(Zim_Zim) {

	ZEPHIR_REGISTER_CLASS_EX(Zim, Zim, zim, zim, zim_container_container_ce, zim_zim_method_entry, 0);

	/**
	 * The current globally available container (if any).
	 *
	 * @var static
	 */
	zend_declare_property_null(zim_zim_ce, SL("instance"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * All of the loaded configuration files.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_zim_ce, SL("loadedConfigs"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * Indicates if the application has "booted".
	 *
	 * @var bool
	 */
	zend_declare_property_bool(zim_zim_ce, SL("booted"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The loaded services.
	 *
	 * @var array
	 */
	zend_declare_property_null(zim_zim_ce, SL("loadedServices"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The base path of the application installation.
	 *
	 * /           => basePath
	 * /app        => APP_PATH
	 * /config
	 * /vendor
	 *
	 * @var string
	 */
	zend_declare_property_null(zim_zim_ce, SL("basePath"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zim_zim_ce->create_object = zephir_init_properties_Zim_Zim;
	zephir_declare_class_constant_string(zim_zim_ce, SL("VERSION"), "Zim (1.0.0)");

	return SUCCESS;

}

PHP_METHOD(Zim_Zim, __construct) {

	zval _0, _1, _2;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_GET_CONSTANT(&_0, "APP_PATH");
	ZEPHIR_CALL_FUNCTION(&_1, "dirname", NULL, 126, &_0);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("basePath"), &_1);
	ZVAL_LONG(&_2, 32767);
	ZEPHIR_CALL_FUNCTION(NULL, "error_reporting", NULL, 39, &_2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "bootstrapcontainer", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "bootstrapconfig", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "registerservices", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Set the globally available instance of the container.
 *
 * @return self
 */
PHP_METHOD(Zim_Zim, getInstance) {

	zval _0, _2, _1$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();

	zephir_read_static_property_ce(&_0, zim_zim_ce, SL("instance"), PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, zim_zim_ce);
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 127);
		zephir_check_call_status();
		zend_update_static_property(zim_zim_ce, ZEND_STRL("instance"), &_1$$3);
	}
	zephir_read_static_property_ce(&_2, zim_zim_ce, SL("instance"), PH_NOISY_CC | PH_READONLY);
	RETURN_CTOR(&_2);

}

/**
 * Set the shared instance of the container.
 *
 * @param  self $container
 * @return self
 */
PHP_METHOD(Zim_Zim, setInstance) {

	zval *container = NULL, container_sub, __$null, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&container_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 0, 1, &container);

	if (!container) {
		container = &container_sub;
		container = &__$null;
	}


	zend_update_static_property(zim_zim_ce, ZEND_STRL("instance"), container);
	zephir_read_static_property_ce(&_0, zim_zim_ce, SL("instance"), PH_NOISY_CC | PH_READONLY);
	RETURN_CTORW(&_0);

}

/**
 * Bootstrap the application container.
 *
 * @return void
 */
PHP_METHOD(Zim_Zim, bootstrapContainer) {

	zval _5;
	zval _0, _1, _2, _3, _4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();

	zend_update_static_property(zim_zim_ce, ZEND_STRL("instance"), this_ptr);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "zim");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "instance", NULL, 0, &_0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_0);
	object_init_ex(&_0, zim_config_config_ce);
	ZEPHIR_CALL_METHOD(NULL, &_0, "__construct", NULL, 128);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "config");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "instance", NULL, 0, &_1, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_1);
	object_init_ex(&_1, zim_event_dispatcher_ce);
	if (zephir_has_constructor(&_1 TSRMLS_CC)) {
		ZEPHIR_CALL_METHOD(NULL, &_1, "__construct", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "event");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "instance", NULL, 0, &_2, &_1);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_2);
	object_init_ex(&_2, zim_routing_router_ce);
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 129);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "router");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "instance", NULL, 0, &_3, &_2);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "env", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_3);
	ZVAL_STRING(&_3, "env");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "instance", NULL, 0, &_3, &_4);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_5);
	zephir_create_array(&_5, 9, 0 TSRMLS_CC);
	add_assoc_stringl_ex(&_5, SL("Zim\\Zim"), SL("zim"));
	add_assoc_stringl_ex(&_5, SL("Zim\\Container\\Container"), SL("zim"));
	add_assoc_stringl_ex(&_5, SL("Zim\\Config\\Config"), SL("config"));
	add_assoc_stringl_ex(&_5, SL("Zim\\Contract\\Config"), SL("config"));
	add_assoc_stringl_ex(&_5, SL("Zim\\Event\\Event"), SL("event"));
	add_assoc_stringl_ex(&_5, SL("Zim\\Event\\Dispatcher"), SL("event"));
	add_assoc_stringl_ex(&_5, SL("Zim\\Contract\\Request"), SL("request"));
	add_assoc_stringl_ex(&_5, SL("Zim\\Http\\Request"), SL("request"));
	add_assoc_stringl_ex(&_5, SL("Zim\\Routing\\Router"), SL("router"));
	zephir_update_property_zval(this_ptr, SL("aliases"), &_5);
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Zim_Zim, bootstrapConfig) {

	zval _0;
	zephir_fcall_cache_entry *_1 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "app");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "configure", &_1, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "routes");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "configure", &_1, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

PHP_METHOD(Zim_Zim, registerServices) {

	zval services, service, _0, _2, *_3;
	zephir_fcall_cache_entry *_1 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&services);
	ZVAL_UNDEF(&service);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "Zim\\Service\\LogService");
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "register", &_1, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_STRING(&_0, "app.services");
	ZEPHIR_CALL_SELF(&_2, "config", NULL, 0, &_0);
	zephir_check_call_status();
	if (zephir_is_true(&_2)) {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_STRING(&_0, "app.services");
		ZEPHIR_CALL_SELF(&services, "config", NULL, 0, &_0);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(&services);
		array_init(&services);
	}
	zephir_is_iterable(&services, 0, "zim/zim.zep", 142);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&services), _3)
	{
		ZEPHIR_INIT_NVAR(&service);
		ZVAL_COPY(&service, _3);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "register", &_1, 0, &service);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&service);
	ZEPHIR_MM_RESTORE();

}

/**
 * Get the version number of the application.
 *
 * @return string
 */
PHP_METHOD(Zim_Zim, version) {

	zval *this_ptr = getThis();


	RETURN_STRING("Zim (1.0.0)");

}

/**
 * Register a service provider with the application.
 *
 * @param  \Zim\Service\Service|string $service
 */
PHP_METHOD(Zim_Zim, register) {

	zend_bool _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *service = NULL, service_sub, name, _2, _3, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&service_sub);
	ZVAL_UNDEF(&name);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &service);

	ZEPHIR_SEPARATE_PARAM(service);


	_0 = Z_TYPE_P(service) == IS_OBJECT;
	if (_0) {
		_0 = zephir_instance_of_ev(service, zim_service_service_ce TSRMLS_CC);
	}
	if (!(_0)) {
		ZEPHIR_CALL_METHOD(&_1$$3, this_ptr, "make", NULL, 0, service);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(service, &_1$$3);
	}
	ZEPHIR_INIT_VAR(&name);
	zephir_get_class(&name, service, 0 TSRMLS_CC);
	zephir_read_property(&_2, this_ptr, SL("loadedServices"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_key_exists(&_2, &name TSRMLS_CC)) {
		RETURN_MM_NULL();
	}
	zephir_update_property_array(this_ptr, SL("loadedServices"), &name, service TSRMLS_CC);
	if ((zephir_method_exists_ex(service, SL("register") TSRMLS_CC) == SUCCESS)) {
		ZEPHIR_CALL_METHOD(NULL, service, "register", NULL, 0);
		zephir_check_call_status();
	}
	zephir_read_property(&_3, this_ptr, SL("booted"), PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_3)) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "bootservice", NULL, 0, service);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Boots the registered providers, for every incoming request
 */
PHP_METHOD(Zim_Zim, boot) {

	zval __$true, __$false, _0, s, _1, *_2;
	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&s);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("booted"), PH_NOISY_CC | PH_READONLY);
	if (zephir_is_true(&_0)) {
		RETURN_MM_NULL();
	}
	zephir_read_property(&_1, this_ptr, SL("loadedServices"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_1, 0, "zim/zim.zep", 191);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_1), _2)
	{
		ZEPHIR_INIT_NVAR(&s);
		ZVAL_COPY(&s, _2);
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "bootservice", &_3, 0, &s);
		zephir_check_call_status();
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&s);
	if (1) {
		zephir_update_property_zval(this_ptr, SL("booted"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("booted"), &__$false);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Boot the given service provider.
 *
 * @param  \Zim\Service\Service $service
 * @return mixed
 */
PHP_METHOD(Zim_Zim, bootService) {

	zval _0$$3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *service, service_sub, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&service_sub);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &service);



	if ((zephir_method_exists_ex(service, SL("boot") TSRMLS_CC) == SUCCESS)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(&_0$$3, service);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "boot");
		zephir_array_fast_append(&_0$$3, &_1$$3);
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "call", NULL, 0, &_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	RETURN_MM_BOOL(0);

}

/**
 * Determine if the application is running in the console.
 *
 * @return bool
 */
PHP_METHOD(Zim_Zim, inConsole) {

	zend_bool _2;
	zval _0, _3;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_FUNCTION(&_0, "php_sapi_name", &_1, 130);
	zephir_check_call_status();
	_2 = ZEPHIR_IS_STRING_IDENTICAL(&_0, "cli");
	if (!(_2)) {
		ZEPHIR_CALL_FUNCTION(&_3, "php_sapi_name", &_1, 130);
		zephir_check_call_status();
		_2 = ZEPHIR_IS_STRING_IDENTICAL(&_3, "phpdbg");
	}
	RETURN_MM_BOOL(_2);

}

/**
 * Get the base path for the application.
 *
 * @param  string|null $path
 * @return string
 */
PHP_METHOD(Zim_Zim, basePath) {

	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *path = NULL, path_sub, __$null, _0$$3, _1$$3, _2, _3$$4, _5$$5, _6$$5, _7$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &path);

	if (!path) {
		path = &path_sub;
		path = &__$null;
	}


	if (zephir_isset_property(this_ptr, SL("basePath"))) {
		zephir_read_property(&_0$$3, this_ptr, SL("basePath"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_1$$3);
		if (zephir_is_true(path)) {
			ZEPHIR_INIT_NVAR(&_1$$3);
			ZEPHIR_CONCAT_SV(&_1$$3, "/", path);
		} else {
			ZEPHIR_CPY_WRT(&_1$$3, path);
		}
		ZEPHIR_CONCAT_VV(return_value, &_0$$3, &_1$$3);
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(&_2, this_ptr, "inconsole", NULL, 0);
	zephir_check_call_status();
	if (zephir_is_true(&_2)) {
		ZEPHIR_CALL_FUNCTION(&_3$$4, "getcwd", &_4, 131);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("basePath"), &_3$$4);
	} else {
		ZEPHIR_CALL_FUNCTION(&_5$$5, "getcwd", &_4, 131);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_6$$5);
		ZEPHIR_CONCAT_VS(&_6$$5, &_5$$5, "/../");
		ZEPHIR_CALL_FUNCTION(&_7$$5, "realpath", NULL, 132, &_6$$5);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("basePath"), &_7$$5);
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "basepath", NULL, 133, path);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Load a configuration file into the application.
 *
 * @param  string $name
 * @return void
 */
PHP_METHOD(Zim_Zim, configure) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *name_param = NULL, __$true, path, _0, _1$$4, _2$$4, _3$$4;
	zval name;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	zephir_get_strval(&name, name_param);


	zephir_read_property(&_0, this_ptr, SL("loadedConfigs"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset(&_0, &name)) {
		RETURN_MM_NULL();
	}
	zephir_update_property_array(this_ptr, SL("loadedConfigs"), &name, &__$true TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&path, this_ptr, "getconfigpath", NULL, 0, &name);
	zephir_check_call_status();
	if (zephir_is_true(&path)) {
		ZEPHIR_INIT_VAR(&_2$$4);
		ZVAL_STRING(&_2$$4, "config");
		ZEPHIR_CALL_METHOD(&_1$$4, this_ptr, "make", NULL, 0, &_2$$4);
		zephir_check_call_status();
		ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(&_3$$4);
		if (zephir_require_zval_ret(&_3$$4, &path TSRMLS_CC) == FAILURE) {
			RETURN_MM_NULL();
		}
		ZEPHIR_CALL_METHOD(NULL, &_1$$4, "set", NULL, 0, &name, &_3$$4);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Get the path to the given configuration file.
 *
 * If no name is provided, then we'll return the path to the config folder.
 *
 * @param  string|null $name
 * @return string
 */
PHP_METHOD(Zim_Zim, getConfigPath) {

	zephir_fcall_cache_entry *_2 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *name = NULL, name_sub, __$null, appConfigDir, path, appConfigPath, _0$$3, _1$$3, _3$$5, _4$$7, _5$$7, _6$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&appConfigDir);
	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&appConfigPath);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$7);
	ZVAL_UNDEF(&_5$$7);
	ZVAL_UNDEF(&_6$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &name);

	if (!name) {
		name = &name_sub;
		name = &__$null;
	}


	if (!(zephir_is_true(name))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		ZVAL_STRING(&_1$$3, "config");
		ZEPHIR_CALL_METHOD(&_0$$3, this_ptr, "basepath", &_2, 0, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&appConfigDir);
		ZEPHIR_CONCAT_VS(&appConfigDir, &_0$$3, "/");
		if ((zephir_file_exists(&appConfigDir TSRMLS_CC) == SUCCESS)) {
			RETURN_CCTOR(&appConfigDir);
		} else {
			ZEPHIR_INIT_VAR(&_3$$5);
			ZVAL_STRING(&_3$$5, "../config/");
			ZEPHIR_CALL_METHOD(&path, this_ptr, "basepath", &_2, 133, &_3$$5);
			zephir_check_call_status();
			if ((zephir_file_exists(&path TSRMLS_CC) == SUCCESS)) {
				RETURN_CCTOR(&path);
			}
		}
	} else {
		ZEPHIR_INIT_VAR(&_5$$7);
		ZVAL_STRING(&_5$$7, "config");
		ZEPHIR_CALL_METHOD(&_4$$7, this_ptr, "basepath", &_2, 133, &_5$$7);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&appConfigPath);
		ZEPHIR_CONCAT_VSVS(&appConfigPath, &_4$$7, "/", name, ".php");
		if ((zephir_file_exists(&appConfigPath TSRMLS_CC) == SUCCESS)) {
			RETURN_CCTOR(&appConfigPath);
		} else {
			ZEPHIR_INIT_VAR(&_6$$9);
			ZEPHIR_CONCAT_SVS(&_6$$9, "../config/", name, ".php");
			ZEPHIR_CALL_METHOD(&path, this_ptr, "basepath", &_2, 133, &_6$$9);
			zephir_check_call_status();
			if ((zephir_file_exists(&path TSRMLS_CC) == SUCCESS)) {
				RETURN_CCTOR(&path);
			}
		}
	}
	RETURN_MM_STRING("");

}

PHP_METHOD(Zim_Zim, env) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "zim.env");
	ZEPHIR_RETURN_CALL_SELF("config", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Set the error handling for the application.
 *
 * @return void
 */
PHP_METHOD(Zim_Zim, registerErrorHandling) {

	zval _0, _1, _2$$3, _3$$3;
	zephir_fcall_cache_entry *_4 = NULL, *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();

	ZVAL_LONG(&_0, 32767);
	ZEPHIR_CALL_FUNCTION(NULL, "error_reporting", NULL, 39, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "inconsole", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "display_errors");
		ZVAL_LONG(&_3$$3, 0);
		ZEPHIR_CALL_FUNCTION(NULL, "ini_set", NULL, 134, &_2$$3, &_3$$3);
		zephir_check_call_status();
		ZVAL_BOOL(&_3$$3, 1);
		ZEPHIR_INIT_NVAR(&_2$$3);
		ZVAL_STRING(&_2$$3, "phpstorm://open?file=%f&line=%l");
		ZEPHIR_CALL_CE_STATIC(NULL, zim_debug_exceptionhandler_ce, "register", &_4, 0, &_3$$3, &_2$$3);
		zephir_check_call_status();
		ZEPHIR_CALL_CE_STATIC(NULL, zim_debug_errorhandler_ce, "register", &_5, 0);
		zephir_check_call_status();
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * @return Dispatcher
 */
PHP_METHOD(Zim_Zim, getEvent) {

	zval _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "event");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "make", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param       $event
 * @param array $payload
 * @param bool  $halt
 * @return mixed
 */
PHP_METHOD(Zim_Zim, fire) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool halt;
	zval payload;
	zval *event, event_sub, *payload_param = NULL, *halt_param = NULL, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&event_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&payload);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &event, &payload_param, &halt_param);

	if (!payload_param) {
		ZEPHIR_INIT_VAR(&payload);
		array_init(&payload);
	} else {
		zephir_get_arrval(&payload, payload_param);
	}
	if (!halt_param) {
		halt = 0;
	} else {
		halt = zephir_get_boolval(halt_param);
	}


	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getevent", NULL, 0);
	zephir_check_call_status();
	if (halt) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	ZEPHIR_RETURN_CALL_METHOD(&_0, "fire", NULL, 0, event, &payload, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param string $name
 * @return mixed
 */
PHP_METHOD(Zim_Zim, app) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *name = NULL, name_sub, __$null, _0$$3, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&name_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &name);

	if (!name) {
		name = &name_sub;
		name = &__$null;
	}


	if (Z_TYPE_P(name) == IS_NULL) {
		zephir_read_static_property_ce(&_0$$3, zim_zim_ce, SL("instance"), PH_NOISY_CC | PH_READONLY);
		RETURN_CTOR(&_0$$3);
	}
	zephir_read_static_property_ce(&_1, zim_zim_ce, SL("instance"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_1, "make", NULL, 0, name);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Get / set the specified configuration value.
 *
 * If an array is passed as the key, we will assume you want to set an array of values.
 *
 * @param  array|string|null $key
 * @param  mixed             $default
 * @return mixed
 */
PHP_METHOD(Zim_Zim, config) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key = NULL, key_sub, *deft = NULL, deft_sub, __$null, _0$$3, _1$$4, _2$$4, _3, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key_sub);
	ZVAL_UNDEF(&deft_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &key, &deft);

	if (!key) {
		key = &key_sub;
		key = &__$null;
	}
	if (!deft) {
		deft = &deft_sub;
		deft = &__$null;
	}


	if (Z_TYPE_P(key) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "config");
		ZEPHIR_RETURN_CALL_SELF("app", NULL, 0, &_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (Z_TYPE_P(key) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_2$$4);
		ZVAL_STRING(&_2$$4, "config");
		ZEPHIR_CALL_SELF(&_1$$4, "app", NULL, 0, &_2$$4);
		zephir_check_call_status();
		ZEPHIR_RETURN_CALL_METHOD(&_1$$4, "set", NULL, 0, key);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_STRING(&_4, "config");
	ZEPHIR_CALL_SELF(&_3, "app", NULL, 0, &_4);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_3, "get", NULL, 0, key, deft);
	zephir_check_call_status();
	RETURN_MM();

}

zend_object *zephir_init_properties_Zim_Zim(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _2, _4, _6, _8, _10, _12, _14, _16, _18, _20, _22, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8, _13$$9, _15$$10, _17$$11, _19$$12, _21$$13, _23$$14;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_20);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_15$$10);
	ZVAL_UNDEF(&_17$$11);
	ZVAL_UNDEF(&_19$$12);
	ZVAL_UNDEF(&_21$$13);
	ZVAL_UNDEF(&_23$$14);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("loadedServices"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("loadedServices"), &_1$$3);
		}
		zephir_read_property(&_2, this_ptr, SL("contextual"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval(this_ptr, SL("contextual"), &_3$$4);
		}
		zephir_read_property(&_4, this_ptr, SL("with"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval(this_ptr, SL("with"), &_5$$5);
		}
		zephir_read_property(&_6, this_ptr, SL("buildStack"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval(this_ptr, SL("buildStack"), &_7$$6);
		}
		zephir_read_property(&_8, this_ptr, SL("extenders"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval(this_ptr, SL("extenders"), &_9$$7);
		}
		zephir_read_property(&_10, this_ptr, SL("abstractAliases"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_11$$8);
			array_init(&_11$$8);
			zephir_update_property_zval(this_ptr, SL("abstractAliases"), &_11$$8);
		}
		zephir_read_property(&_12, this_ptr, SL("aliases"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_12) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_13$$9);
			array_init(&_13$$9);
			zephir_update_property_zval(this_ptr, SL("aliases"), &_13$$9);
		}
		zephir_read_property(&_14, this_ptr, SL("instances"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_14) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_15$$10);
			array_init(&_15$$10);
			zephir_update_property_zval(this_ptr, SL("instances"), &_15$$10);
		}
		zephir_read_property(&_16, this_ptr, SL("methodBindings"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_16) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_17$$11);
			array_init(&_17$$11);
			zephir_update_property_zval(this_ptr, SL("methodBindings"), &_17$$11);
		}
		zephir_read_property(&_18, this_ptr, SL("bindings"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_18) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_19$$12);
			array_init(&_19$$12);
			zephir_update_property_zval(this_ptr, SL("bindings"), &_19$$12);
		}
		zephir_read_property(&_20, this_ptr, SL("resolved"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_20) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_21$$13);
			array_init(&_21$$13);
			zephir_update_property_zval(this_ptr, SL("resolved"), &_21$$13);
		}
		zephir_read_property(&_22, this_ptr, SL("loadedConfigs"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_22) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_23$$14);
			array_init(&_23$$14);
			zephir_update_property_zval(this_ptr, SL("loadedConfigs"), &_23$$14);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

