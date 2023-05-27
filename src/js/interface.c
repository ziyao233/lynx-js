/*
 *	lynx-js
 *	/src/js/interface.c
 *	By GPLv2 License.
 *	Copyright (c) 2023 Yao Zi. All rights reserved.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<HTAlert.h>

#include<js/interface.h>

void
js_interface_alert(const char *msg)
{
	HTAlert(msg);
	return;
}
