
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "zim.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *zim_http_exception_exceptioninterface_ce;
zend_class_entry *zim_contract_response_ce;
zend_class_entry *zim_contract_action_ce;
zend_class_entry *zim_contract_config_ce;
zend_class_entry *zim_contract_request_ce;
zend_class_entry *zim_event_httpevent_ce;
zend_class_entry *zim_http_exception_exception_ce;
zend_class_entry *zim_container_container_ce;
zend_class_entry *zim_http_controller_ce;
zend_class_entry *zim_http_headerbag_ce;
zend_class_entry *zim_http_parameterbag_ce;
zend_class_entry *zim_http_response_ce;
zend_class_entry *zim_service_service_ce;
zend_class_entry *zim_config_config_ce;
zend_class_entry *zim_container_bindingresolutionexception_ce;
zend_class_entry *zim_container_boundmethod_ce;
zend_class_entry *zim_container_boundmethodcallclosurezero_ce;
zend_class_entry *zim_container_containergetclosureclosurezero_ce;
zend_class_entry *zim_container_containersetclosureone_ce;
zend_class_entry *zim_container_contextualbindingbuilder_ce;
zend_class_entry *zim_container_entrynotfoundexception_ce;
zend_class_entry *zim_debug_errorhandler_ce;
zend_class_entry *zim_debug_exceptionhandler_ce;
zend_class_entry *zim_debug_fatalerrorexception_ce;
zend_class_entry *zim_debug_flattenexception_ce;
zend_class_entry *zim_debug_flattenexceptionsetmessageclosurezero_ce;
zend_class_entry *zim_event_dispatcher_ce;
zend_class_entry *zim_event_dispatchevent_ce;
zend_class_entry *zim_event_event_ce;
zend_class_entry *zim_event_listener_ce;
zend_class_entry *zim_event_listeneron_ce;
zend_class_entry *zim_event_requestevent_ce;
zend_class_entry *zim_event_responseevent_ce;
zend_class_entry *zim_event_terminateevent_ce;
zend_class_entry *zim_http_action_ce;
zend_class_entry *zim_http_exception_methodnotallowedexception_ce;
zend_class_entry *zim_http_exception_notfoundexception_ce;
zend_class_entry *zim_http_exception_responseexception_ce;
zend_class_entry *zim_http_headerutils_ce;
zend_class_entry *zim_http_jsonresponse_ce;
zend_class_entry *zim_http_kernel_ce;
zend_class_entry *zim_http_request_ce;
zend_class_entry *zim_http_responseheaderbag_ce;
zend_class_entry *zim_http_serverbag_ce;
zend_class_entry *zim_routing_compiledroute_ce;
zend_class_entry *zim_routing_registrar_ce;
zend_class_entry *zim_routing_route_ce;
zend_class_entry *zim_routing_routecollection_ce;
zend_class_entry *zim_routing_routecompiler_ce;
zend_class_entry *zim_routing_router_ce;
zend_class_entry *zim_service_logservice_ce;
zend_class_entry *zim_support_arr_ce;
zend_class_entry *zim_support_str_ce;
zend_class_entry *zim_zim_ce;

ZEND_DECLARE_MODULE_GLOBALS(zim)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(zim)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Zim_Http_Exception_ExceptionInterface);
	ZEPHIR_INIT(Zim_Contract_Response);
	ZEPHIR_INIT(Zim_Contract_Action);
	ZEPHIR_INIT(Zim_Contract_Config);
	ZEPHIR_INIT(Zim_Contract_Request);
	ZEPHIR_INIT(Zim_Event_HttpEvent);
	ZEPHIR_INIT(Zim_Http_Exception_Exception);
	ZEPHIR_INIT(Zim_Container_Container);
	ZEPHIR_INIT(Zim_Http_Controller);
	ZEPHIR_INIT(Zim_Http_HeaderBag);
	ZEPHIR_INIT(Zim_Http_ParameterBag);
	ZEPHIR_INIT(Zim_Http_Response);
	ZEPHIR_INIT(Zim_Service_Service);
	ZEPHIR_INIT(Zim_Config_Config);
	ZEPHIR_INIT(Zim_Container_BindingResolutionException);
	ZEPHIR_INIT(Zim_Container_BoundMethod);
	ZEPHIR_INIT(Zim_Container_BoundMethodcallClosureZero);
	ZEPHIR_INIT(Zim_Container_ContainergetClosureClosureZero);
	ZEPHIR_INIT(Zim_Container_ContainersetClosureOne);
	ZEPHIR_INIT(Zim_Container_ContextualBindingBuilder);
	ZEPHIR_INIT(Zim_Container_EntryNotFoundException);
	ZEPHIR_INIT(Zim_Debug_ErrorHandler);
	ZEPHIR_INIT(Zim_Debug_ExceptionHandler);
	ZEPHIR_INIT(Zim_Debug_FatalErrorException);
	ZEPHIR_INIT(Zim_Debug_FlattenException);
	ZEPHIR_INIT(Zim_Debug_FlattenExceptionsetMessageClosureZero);
	ZEPHIR_INIT(Zim_Event_DispatchEvent);
	ZEPHIR_INIT(Zim_Event_Dispatcher);
	ZEPHIR_INIT(Zim_Event_Event);
	ZEPHIR_INIT(Zim_Event_Listener);
	ZEPHIR_INIT(Zim_Event_ListenerOn);
	ZEPHIR_INIT(Zim_Event_RequestEvent);
	ZEPHIR_INIT(Zim_Event_ResponseEvent);
	ZEPHIR_INIT(Zim_Event_TerminateEvent);
	ZEPHIR_INIT(Zim_Http_Action);
	ZEPHIR_INIT(Zim_Http_Exception_MethodNotAllowedException);
	ZEPHIR_INIT(Zim_Http_Exception_NotFoundException);
	ZEPHIR_INIT(Zim_Http_Exception_ResponseException);
	ZEPHIR_INIT(Zim_Http_HeaderUtils);
	ZEPHIR_INIT(Zim_Http_JsonResponse);
	ZEPHIR_INIT(Zim_Http_Kernel);
	ZEPHIR_INIT(Zim_Http_Request);
	ZEPHIR_INIT(Zim_Http_ResponseHeaderBag);
	ZEPHIR_INIT(Zim_Http_ServerBag);
	ZEPHIR_INIT(Zim_Routing_CompiledRoute);
	ZEPHIR_INIT(Zim_Routing_Registrar);
	ZEPHIR_INIT(Zim_Routing_Route);
	ZEPHIR_INIT(Zim_Routing_RouteCollection);
	ZEPHIR_INIT(Zim_Routing_RouteCompiler);
	ZEPHIR_INIT(Zim_Routing_Router);
	ZEPHIR_INIT(Zim_Service_LogService);
	ZEPHIR_INIT(Zim_Support_Arr);
	ZEPHIR_INIT(Zim_Support_Str);
	ZEPHIR_INIT(Zim_Zim);
	
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(zim)
{
	
	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_zim_globals *zim_globals TSRMLS_DC)
{
	zim_globals->initialized = 0;

	/* Memory options */
	zim_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	zim_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	zim_globals->cache_enabled = 1;

	/* Recursive Lock */
	zim_globals->recursive_lock = 0;

	/* Static cache */
	memset(zim_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);

	
	
}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_zim_globals *zim_globals TSRMLS_DC)
{
	
}

static PHP_RINIT_FUNCTION(zim)
{
	zend_zim_globals *zim_globals_ptr;
#ifdef ZTS
	tsrm_ls = ts_resource(0);
#endif
	zim_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(zim_globals_ptr TSRMLS_CC);
	zephir_initialize_memory(zim_globals_ptr TSRMLS_CC);

		zephir_init_static_properties_Zim_Http_Response(TSRMLS_C);
		zephir_init_static_properties_Zim_Http_Request(TSRMLS_C);
		zephir_init_static_properties_Zim_Support_Str(TSRMLS_C);
	
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(zim)
{
	
	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}



static PHP_MINFO_FUNCTION(zim)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_ZIM_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_ZIM_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_ZIM_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_ZIM_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_ZIM_ZEPVERSION);
	php_info_print_table_end();
	
	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(zim)
{
	php_zephir_init_globals(zim_globals TSRMLS_CC);
	php_zephir_init_module_globals(zim_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(zim)
{
	
}


zend_function_entry php_zim_functions[] = {
	ZEND_FE_END

};

zend_module_entry zim_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_ZIM_EXTNAME,
	php_zim_functions,
	PHP_MINIT(zim),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(zim),
#else
	NULL,
#endif
	PHP_RINIT(zim),
	PHP_RSHUTDOWN(zim),
	PHP_MINFO(zim),
	PHP_ZIM_VERSION,
	ZEND_MODULE_GLOBALS(zim),
	PHP_GINIT(zim),
	PHP_GSHUTDOWN(zim),
#ifdef ZEPHIR_POST_REQUEST
	PHP_PRSHUTDOWN(zim),
#else
	NULL,
#endif
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_ZIM
ZEND_GET_MODULE(zim)
#endif
