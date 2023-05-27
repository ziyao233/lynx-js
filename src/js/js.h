/*
 *	lynx-js
 *	/src/js/js.h
 *	By GPL v2 License.
 *	Copyright (c) 2023 Yao Zi. All rights reserved.
 */

#ifndef __JS_H_INC__
#define __JS_H_INC__

int js_init(void);
void js_destroy(void);
int js_reset(void);
int js_do(const char *code);

#endif	// __JS_H_INC__
