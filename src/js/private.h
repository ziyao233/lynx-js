/*
 *	lynx-js
 *	/src/js/private.h
 *	By GPLv2 License.
 *	Copyright (c) 2023 Yao Zi. All rights reserved.
 */

#ifndef __JS_PRIVATE_H_INC__
#define __JS_PRIVATE_H_INC__

#include<js/interface.h>

#include<js/modules.h>

#define js_register_list(ctx, obj, list) \
	JS_SetPropertyFunctionList((ctx), (obj), (list),	\
				   sizeof(list) / sizeof(JSCFunctionListEntry))
#endif	// __JS_PRIVATE_H_INC__
