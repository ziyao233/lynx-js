/*
 *	lynx-js
 *	/src/js/module_globals.c
 *	By GPLv2 License.
 *	Copyright (c) 2023 Yao Zi. All right reserved.
 */

#include<stdio.h>

#include<quickjs/quickjs.h>

#include<js/js.h>
#include<js/private.h>
#include<js/modules.h>

static
JSValue
js_globals_alert(JSContext *ctx, JSValueConst this, int argc,
		 JSValueConst *arg)
{
	if (argc != 1)
		return JS_EXCEPTION;
	js_interface_alert(JS_ToCString(ctx, arg[0]));
	return JS_UNDEFINED;
}

static const JSCFunctionListEntry globalsMembers[] = {
	JS_CFUNC_DEF("alert", 1, js_globals_alert),
};

int
js_module_globals(JSContext *ctx)
{
	js_register_list(ctx, JS_GetGlobalObject(ctx), globalsMembers);
	return 0;
}
