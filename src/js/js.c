/*
 *	lynx-js
 *	/src/js/js.c
 *	By GPLv2 License.
 *	Copyright (c) 2023 Yao Zi. All rights reserved.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<quickjs/quickjs.h>

#include<js/js.h>
#include<js/private.h>
#include<js/modules.h>

JSRuntime *jsRuntime;
JSContext *jsContext;

static int
load_modules(void)
{
	js_module_globals(jsContext);
	return 0;
}

int
js_init(void)
{
	jsRuntime = JS_NewRuntime();
	if (!jsRuntime)
		goto end;
	jsContext = JS_NewContext(jsRuntime);
	if (!jsContext)
		goto end;
	if (load_modules()) {
		jsRuntime = NULL;
		goto end;
	}
end:
	return !jsRuntime;
}

void
js_destroy(void)
{
	if (jsContext)
		JS_FreeContext(jsContext);
	if (jsRuntime)
		JS_FreeRuntime(jsRuntime);
	return;
}

int
js_reset(void)
{
	js_destroy();
	return js_init();
}

int
js_do(const char *code)
{
	JSValue ret = JS_Eval(jsContext, code, strlen(code), "", 0);
	int err = JS_IsException(ret);
	JS_FreeValue(jsContext, ret);
	return err;
}
