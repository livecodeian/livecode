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

typedef enum _MCIPCValueType
{
	MCIPCValueTypeBoolean,
	MCIPCValueTypeString,
	MCIPCValueTypeRectangle,
	MCIPCValueTypeInteger,
} MCIPCValueType;

typedef struct _MCIPCValue
{
	MCIPCValueType type;
	
	union
	{
		bool boolean;
		char *string;
		int integer;
		struct
		{
			int left, top, right, bottom;
		} rectangle;
	} value;
} MCIPCValue;

extern bool MCIPCWriteValue(MCIPCRef p_ipc, const MCIPCValue *p_value);
extern bool MCIPCReadValue(MCIPCRef p_ipc, MCIPCValue *&r_value);
extern void MCIPCFreeValue(MCIPCValue *p_value);

typedef enum _MCRevBrowserIPCMessage
{
	// LiveCode -> Browser
	kMCRevBrowserIPCMessageInit,
	kMCRevBrowserIPCMessageShutdown,
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
	
	// Browser -> LiveCode
	kMCRevBrowserIPCMessageNavigateRequest,
	kMCRevBrowserIPCMessageNavigateComplete,
	kMCRevBrowserIPCMessageNavigateFrameRequest,
	kMCRevBrowserIPCMessageNavigateFrameComplete,
	kMCRevBrowserIPCMessageDocumentComplete,
	kMCRevBrowserIPCMessageDocumentFrameComplete,
	kMCRevBrowserIPCMessageDownloadRequest,
	
	kMCRevBrowserIPCMessageCallLiveCodeHandler,
	
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

extern bool MCRevBrowserIPCInit(MCIPCRef p_ipc);
extern bool MCRevBrowserIPCShutdown(MCIPCRef p_ipc);

class MCRevBrowserIPC : public CWebBrowserBase;

extern bool MCRevBrowserIPCCreateBrowser(MCIPCRef p_ipc, int p_window_id, MCRevBrowserIPC *&r_browser);


#endif//__MC_REVBROWSERIPC_H__
