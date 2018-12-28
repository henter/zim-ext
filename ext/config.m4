PHP_ARG_ENABLE(zim, whether to enable zim, [ --enable-zim   Enable Zim])

if test "$PHP_ZIM" = "yes"; then

	

	if ! test "x" = "x"; then
		PHP_EVAL_LIBLINE(, ZIM_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_ZIM, 1, [Whether you have Zim])
	zim_sources="zim.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c zim/event/httpevent.zep.c
	zim/http/exception/exceptioninterface.zep.c
	zim/contract/response.zep.c
	zim/http/exception/exception.zep.c
	zim/container/container.zep.c
	zim/contract/action.zep.c
	zim/contract/config.zep.c
	zim/contract/request.zep.c
	zim/http/controller.zep.c
	zim/http/headerbag.zep.c
	zim/http/parameterbag.zep.c
	zim/http/response.zep.c
	zim/config/config.zep.c
	zim/container/bindingresolutionexception.zep.c
	zim/container/containergetclosureclosurezero.zep.c
	zim/container/containersetclosureone.zep.c
	zim/container/entrynotfoundexception.zep.c
	zim/contract/arrayable.zep.c
	zim/contract/jsonable.zep.c
	zim/debug/fatalerrorexception.zep.c
	zim/debug/flattenexception.zep.c
	zim/debug/flattenexceptionsetmessageclosurezero.zep.c
	zim/debug/handler.zep.c
	zim/event/dispatcher.zep.c
	zim/event/dispatchevent.zep.c
	zim/event/event.zep.c
	zim/event/exceptionevent.zep.c
	zim/event/listener.zep.c
	zim/event/listeneron.zep.c
	zim/event/requestevent.zep.c
	zim/event/responseevent.zep.c
	zim/event/terminateevent.zep.c
	zim/http/action.zep.c
	zim/http/exception/methodnotallowedexception.zep.c
	zim/http/exception/notfoundexception.zep.c
	zim/http/exception/responseexception.zep.c
	zim/http/headerutils.zep.c
	zim/http/jsonresponse.zep.c
	zim/http/kernel.zep.c
	zim/http/request.zep.c
	zim/http/responseheaderbag.zep.c
	zim/http/serverbag.zep.c
	zim/routing/compiledroute.zep.c
	zim/routing/registrar.zep.c
	zim/routing/route.zep.c
	zim/routing/routecollection.zep.c
	zim/routing/routecompiler.zep.c
	zim/routing/router.zep.c
	zim/service/service.zep.c
	zim/support/arr.zep.c
	zim/support/str.zep.c
	zim/zim.zep.c "
	PHP_NEW_EXTENSION(zim, $zim_sources, $ext_shared,, )
	PHP_SUBST(ZIM_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([zim], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([zim], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/zim], [php_ZIM.h])

fi
