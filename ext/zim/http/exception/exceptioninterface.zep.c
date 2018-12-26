
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


/**
 * File ExceptionInterface.php
 * @henter
 * Time: 2018-11-26 14:30
 *
 */
/**
 * Interface for HTTP error exceptions.
 *
 * @author Kris Wallsmith <kris@symfony.com>
 */
ZEPHIR_INIT_CLASS(Zim_Http_Exception_ExceptionInterface) {

	ZEPHIR_REGISTER_INTERFACE(Zim\\Http\\Exception, ExceptionInterface, zim, http_exception_exceptioninterface, zim_http_exception_exceptioninterface_method_entry);

	return SUCCESS;

}

/**
 * Returns the status code.
 *
 * @return int An HTTP response status code
 */
ZEPHIR_DOC_METHOD(Zim_Http_Exception_ExceptionInterface, getStatusCode);

/**
 * Returns response headers.
 *
 * @return array Response headers
 */
ZEPHIR_DOC_METHOD(Zim_Http_Exception_ExceptionInterface, getHeaders);

