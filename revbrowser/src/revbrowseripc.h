/* Copyright (C) 2003-2013 Runtime Revolution Ltd.

This file is part of LiveCode.

LiveCode is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License v3 as published by the Free
Software Foundation.

LiveCode is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with LiveCode.  If not see <http://www.gnu.org/licenses/>.  */

#ifndef __MC_REVBROWSERIPC_H__
#define __MC_REVBROWSERIPC_H__

#include "ipc.h"
#include "revbrowser.h"

typedef enum _MCRevBrowserIPCMessage
{
	kMCRevBrowserIPCMessageInit,
	kMCRevBrowserIPCMessageShutdown,
	
	// LiveCode -> Browser
	kMCRevBrowserIPCMessageCreateBrowser,
	kMCRevBrowserIPCMessageDestroyBrowser,
	
	kMCRevBrowserIPCMessageGetProperty,
	kMCRevBrowserIPCMessageSetProperty,
	
	kMCRevBrowserIPCMessageExecuteScript,
	kMCRevBrowserIPCMessageCallScript,
	kMCRevBrowserIPCMessageFindString,
	kMCRevBrowserIPCMessageGoBack,
	kMCRevBrowserIPCMessageGoForward,
	kMCRevBrowserIPCMessageFocus,
	kMCRevBrowserIPCMessageUnfocus,
	kMCRevBrowserIPCMessageRefresh,
	kMCRevBrowserIPCMessageStop,
	kMCRevBrowserIPCMessagePrint,
	kMCRevBrowserIPCMessageRedraw,
	kMCRevBrowserIPCMessageMakeTextBigger,
	kMCRevBrowserIPCMessageMakeTextSmaller,
	kMCRevBrowserIPCMessageAddJavaScriptHandler,
	kMCRevBrowserIPCMessageRemoveJavaScriptHandler,
	
	// Callbacks
	kMCRevBrowserIPCMessageCallback,
	
	// Message response
	kMCRevBrowserIPCMessageResult,
} MCRevBrowserIPCMessage;

typedef enum _MCRevBrowserProperty
{
	MCRevBrowserPropertyVisible,
	MCRevBrowserPropertyBrowser,
	MCRevBrowserPropertyMessages,
	MCRevBrowserPropertySelectedText,
	MCRevBrowserPropertyOffline,
	MCRevBrowserPropertyContextMenu,
	MCRevBrowserPropertyNewWindow,
	MCRevBrowserPropertySource,
	MCRevBrowserPropertyScale,
	MCRevBrowserPropertyBorder,
	MCRevBrowserPropertyScrollbars,
	MCRevBrowserPropertyRect,
	MCRevBrowserPropertyInst,
	MCRevBrowserPropertyVScroll,
	MCRevBrowserPropertyHScroll,
	MCRevBrowserPropertyWindowID,
	MCRevBrowserPropertyUserAgent,
	MCRevBrowserPropertyBusy,
	MCRevBrowserPropertyURL,
	MCRevBrowserPropertyTitle,
	MCRevBrowserPropertyImage,
	MCRevBrowserPropertyFormattedWidth,
	MCRevBrowserPropertyFormattedHeight,
	MCRevBrowserPropertyFormattedRect,
} MCRevBrowserProperty;

struct MCRevBrowserIPCMessageCreateBrowser
{
	int window_id;
};
extern bool MCRevBrowserIPCWriteCreateBrowser(MCIPCRef p_ipc, const MCRevBrowserIPCMessageCreateBrowser &p_message);
extern bool MCRevBrowserIPCReadCreateBrowser(MCIPCRef p_ipc, MCRevBrowserIPCMessageCreateBrowser &r_message);

struct MCRevBrowserIPCMessageDestroyBrowser
{
	int32_t browser;
};
extern bool MCRevBrowserIPCWriteDestroyBrowser(MCIPCRef p_ipc, const MCRevBrowserIPCMessageDestroyBrowser &p_message);
extern bool MCRevBrowserIPCReadDestroyBrowser(MCIPCRef p_ipc, MCRevBrowserIPCMessageDestroyBrowser &r_message);

struct MCRevBrowserIPCMessageGetProperty
{
	MCRevBrowserProperty property;
};
extern bool MCRevBrowserIPCWriteGetProperty(MCIPCRef p_ipc, const MCRevBrowserIPCMessageGetProperty &p_message);
extern bool MCRevBrowserIPCReadGetProperty(MCIPCRef p_ipc, MCRevBrowserIPCMessageGetProperty &r_message);

struct MCRevBrowserIPCMessageSetProperty
{
	MCRevBrowserProperty property;
	MCIPCValue *value;
};
extern bool MCRevBrowserIPCWriteSetProperty(MCIPCRef p_ipc, const MCRevBrowserIPCMessageSetProperty &p_message);
extern bool MCRevBrowserIPCReadSetProperty(MCIPCRef p_ipc, MCRevBrowserIPCMessageSetProperty &r_message);
extern void MCRevBrowserIPCFreeSetProperty(MCRevBrowserIPCMessageSetProperty &p_message);

struct MCRevBrowserIPCMessageExecuteScript
{
	char *script;
};
extern bool MCRevBrowserIPCWriteExecuteScript(MCIPCRef p_ipc, const MCRevBrowserIPCMessageExecuteScript &p_message);
extern bool MCRevBrowserIPCReadExecuteScript(MCIPCRef p_ipc, MCRevBrowserIPCMessageExecuteScript &r_message);
extern void MCRevBrowserIPCFreeExecuteScript(MCRevBrowserIPCMessageExecuteScript &p_message);

struct MCRevBrowserIPCMessageCallScript
{
	char *function;
	char **args;
	int32_t arg_count;
};
extern bool MCRevBrowserIPCWriteCallScript(MCIPCRef p_ipc, const MCRevBrowserIPCMessageCallScript &p_message);
extern bool MCRevBrowserIPCReadCallScript(MCIPCRef p_ipc, MCRevBrowserIPCMessageCallScript &r_message);
extern void MCRevBrowserIPCFreeCallScript(MCRevBrowserIPCMessageCallScript &p_message);

struct MCRevBrowserIPCMessageFindString
{
	char *string;
	bool search_up;
};
extern bool MCRevBrowserIPCWriteFindString(MCIPCRef p_ipc, const MCRevBrowserIPCMessageFindString &p_message);
extern bool MCRevBrowserIPCReadFindString(MCIPCRef p_ipc, MCRevBrowserIPCMessageFindString &r_message);
extern void MCRevBrowserIPCFreeFindString(MCRevBrowserIPCMessageFindString &p_message);

struct MCRevBrowserIPCMessageAddJavaScriptHandler
{
	char *handler;
};
extern bool MCRevBrowserIPCWriteAddJavaScriptHandler(MCIPCRef p_ipc, const MCRevBrowserIPCMessageAddJavaScriptHandler &p_message);
extern bool MCRevBrowserIPCReadAddJavaScriptHandler(MCIPCRef p_ipc, MCRevBrowserIPCMessageAddJavaScriptHandler &r_message);
extern void MCRevBrowserIPCFreeAddJavaScriptHandler(MCRevBrowserIPCMessageAddJavaScriptHandler &p_message);

struct MCRevBrowserIPCMessageRemoveJavaScriptHandler
{
	char *handler;
};
extern bool MCRevBrowserIPCWriteRemoveJavaScriptHandler(MCIPCRef p_ipc, const MCRevBrowserIPCMessageRemoveJavaScriptHandler &p_message);
extern bool MCRevBrowserIPCReadRemoveJavaScriptHandler(MCIPCRef p_ipc, MCRevBrowserIPCMessageRemoveJavaScriptHandler &r_message);
extern void MCRevBrowserIPCFreeRemoveJavaScriptHandler(MCRevBrowserIPCMessageRemoveJavaScriptHandler &p_message);

struct MCRevBrowserIPCMessageCallback
{
	int32_t instance_id;
	char *message;
	char **params;
	int32_t param_count;
};
extern bool MCRevBrowserIPCWriteCallback(MCIPCRef p_ipc, const MCRevBrowserIPCMessageCallback &p_message);
extern bool MCRevBrowserIPCReadCallback(MCIPCRef p_ipc, MCRevBrowserIPCMessageCallback &r_message);
extern void MCRevBrowserIPCFreeCallback(MCRevBrowserIPCMessageCallback &p_message);
	
struct MCRevBrowserIPCMessageResult
{
	MCIPCValue *value;
};
extern bool MCRevBrowserIPCWriteResult(MCIPCRef p_ipc, const MCRevBrowserIPCMessageResult &p_message);
extern bool MCRevBrowserIPCReadResult(MCIPCRef p_ipc, MCRevBrowserIPCMessageResult &r_message);
extern void MCRevBrowserIPCFreeResult(MCRevBrowserIPCMessageResult &p_message);

class MCRevBrowserIPC : public CWebBrowserBase;

extern bool MCRevBrowserIPCCreateBrowser(MCIPCRef p_ipc, int p_window_id, MCRevBrowserIPC *&r_browser);

#endif//__MC_REVBROWSERIPC_H__
