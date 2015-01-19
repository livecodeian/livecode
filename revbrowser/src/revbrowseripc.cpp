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

#include "revbrowseripc.h"

//////////

bool MCRevBrowserIPCWriteProperty(MCIPCRef p_ipc, MCRevBrowserProperty p_property)
{
	return MCIPCWriteInt32(p_ipc, (int32_t)p_property);
}

bool MCRevBrowserIPCReadProperty(MCIPCRef p_ipc, MCRevBrowserProperty &r_property)
{
	int32_t t_property;
	if (!MCIPCReadInt32(p_ipc, t_property))
		return false;
		
	r_property = (MCRevBrowserProperty)t_property;
	return true;
}

//////////

bool MCRevBrowserIPCWriteCreateBrowser(MCIPCRef p_ipc, const MCRevBrowserIPCMessageCreateBrowser &p_message)
{
	return MCIPCWriteInt32(p_ipc, p_message.window_id);
}

bool MCRevBrowserIPCReadCreateBrowser(MCIPCRef p_ipc, MCRevBrowserIPCMessageCreateBrowser &r_message)
{
	return MCIPCReadInt32(p_ipc, p_message.window_id);
}

//////////

bool MCRevBrowserIPCWriteDestroyBrowser(MCIPCRef p_ipc, const MCRevBrowserIPCMessageDestroyBrowser &p_message)
{
	return MCIPCWriteInt32(p_ipc, p_message.browser);
}

bool MCRevBrowserIPCReadDestroyBrowser(MCIPCRef p_ipc, MCRevBrowserIPCMessageDestroyBrowser &r_message)
{
	return MCIPCReadInt32(p_ipc, p_message.browser);
}

//////////

bool MCRevBrowserIPCWriteGetProperty(MCIPCRef p_ipc, const MCRevBrowserIPCMessageGetProperty &p_message)
{
	return MCRevBrowserIPCWriteProperty(p_ipc, p_message.property);
}
	
bool MCRevBrowserIPCReadGetProperty(MCIPCRef p_ipc, MCRevBrowserIPCMessageGetProperty &r_message)
{
	return MCRevBrowserIPCReadProperty(p_ipc, r_message.property);
}

//////////

bool MCRevBrowserIPCWriteSetProperty(MCIPCRef p_ipc, const MCRevBrowserIPCMessageSetProperty &p_message)
{
	return MCRevBrowserIPCWriteProperty(p_ipc, p_message.property) &&
		MCIPCWriteValue(p_ipc, p_message.value);
}

bool MCRevBrowserIPCReadSetProperty(MCIPCRef p_ipc, MCRevBrowserIPCMessageSetProperty &r_message)
{
	return MCRevBrowserIPCReadProperty(p_ipc, r_message.property) &&
		MCIPCReadValue(p_ipc, r_message.value);
}

void MCRevBrowserIPCFreeSetProperty(MCRevBrowserIPCMessageSetProperty &p_message)
{
	MCIPCFreeValue(p_message.value);
	p_message.value = nil;
}

//////////

bool MCRevBrowserIPCWriteExecuteScript(MCIPCRef p_ipc, const MCRevBrowserIPCMessageExecuteScript &p_message)
{
	return MCIPCWriteCString(p_ipc, p_message.script);
}

bool MCRevBrowserIPCReadExecuteScript(MCIPCRef p_ipc, MCRevBrowserIPCMessageExecuteScript &r_message)
{
	return MCIPCReadCString(p_ipc, r_message.script);
}

void MCRevBrowserIPCFreeExecuteScript(MCRevBrowserIPCMessageExecuteScript &p_message)
{
	MCIPCFreeCString(p_message.script);
	p_message.script = nil;
}

//////////

bool MCRevBrowserIPCWriteCallScript(MCIPCRef p_ipc, const MCRevBrowserIPCMessageCallScript &p_message)
{
	return MCIPCWriteCString(p_ipc, p_message.function) &&
		MCIPCWriteCStringArray(p_ipc, p_message.args, p_message.arg_count);
}

bool MCRevBrowserIPCReadCallScript(MCIPCRef p_ipc, MCRevBrowserIPCMessageCallScript &r_message)
{
	bool t_success;
	t_success = true;
	
	char *t_function;
	t_function = nil;
	
	char **t_args;
	t_args = nil;
	
	int32_t t_arg_count;
	t_arg_count = 0;
	
	if (t_success)
		t_success = MCIPCReadCString(p_ipc, t_function);
	
	if (t_success)
		t_success = MCIPCReadCStringArray(p_ipc, t_args, t_arg_count);
	
	if (t_success)
	{
		r_message.function = t_function;
		r_message.args = t_args;
		r_message.arg_count = t_arg_count;
	}
	else if (t_args != nil)
	{
		MCIPCFreeCString(t_function);
		MCIPCFreeCStringArray(t_args, t_arg_count);
	}
	
	return t_success;
}

void MCRevBrowserIPCFreeCallScript(MCRevBrowserIPCMessageCallScript &p_message)
{
	MCIPCFreeCString(p_message.function);
	p_message.function = nil;
	MCIPCFreeCStringArray(p_message.args, p_message.arg_count);
	p_message.args = nil;
	p_message.arg_count = 0;
}

//////////

bool MCRevBrowserIPCWriteFindString(MCIPCRef p_ipc, const MCRevBrowserIPCMessageFindString &p_message)
{
	return MCIPCWriteCString(p_ipc, p_message.string) &&
		MCIPCWriteBoolean(p_ipc, p_message.search_up);
}

bool MCRevBrowserIPCReadFindString(MCIPCRef p_ipc, MCRevBrowserIPCMessageFindString &r_message)
{
	return MCIPCReadCString(p_ipc, p_message.string) &&
		MCIPCReadBoolean(p_ipc, p_message.search_up);
}

void MCRevBrowserIPCFreeFindString(MCRevBrowserIPCMessageFindString &p_message)
{
	MCIPCFreeCString(p_message.string);
	p_message.string = nil;
}

//////////

bool MCRevBrowserIPCWriteAddJavaScriptHandler(MCIPCRef p_ipc, const MCRevBrowserIPCMessageAddJavaScriptHandler &p_message)
{
	return MCIPCWriteCString(p_ipc, p_message.handler);
}

bool MCRevBrowserIPCReadAddJavaScriptHandler(MCIPCRef p_ipc, MCRevBrowserIPCMessageAddJavaScriptHandler &r_message)
{
	return MCIPCReadCString(p_ipc, p_message.handler);
}

void MCRevBrowserIPCFreeAddJavaScriptHandler(MCRevBrowserIPCMessageAddJavaScriptHandler &p_message)
{
	MCIPCFreeCString(p_message.handler);
	p_message.handler = nil;
}

//////////

bool MCRevBrowserIPCWriteRemoveJavaScriptHandler(MCIPCRef p_ipc, const MCRevBrowserIPCMessageRemoveJavaScriptHandler &p_message)
{
	return MCIPCWriteCString(p_ipc, p_message.handler);
}

bool MCRevBrowserIPCReadRemoveJavaScriptHandler(MCIPCRef p_ipc, MCRevBrowserIPCMessageRemoveJavaScriptHandler &r_message)
{
	return MCIPCReadCString(p_ipc, p_message.handler);
}

void MCRevBrowserIPCFreeRemoveJavaScriptHandler(MCRevBrowserIPCMessageRemoveJavaScriptHandler &p_message)
{
	MCIPCFreeCString(p_message.handler);
	p_message.handler = nil;
}

//////////

bool MCRevBrowserIPCWriteCallback(MCIPCRef p_ipc, const MCRevBrowserIPCMessageCallback &p_message)
{
	return MCIPCWriteInt32(p_ipc, p_message.instance_id) &&
		MCIPCWriteCString(p_ipc, p_message.message) &&
		MCIPCWriteCStringArray(p_ipc, p_message.params, p_message.param_count);
}

bool MCRevBrowserIPCReadCallback(MCIPCRef p_ipc, MCRevBrowserIPCMessageCallback &r_message)
{
	return MCIPCReadInt32(p_ipc, p_message.instance_id) &&
		MCIPCReadCString(p_ipc, p_message.message) &&
		MCIPCReadCStringArray(p_ipc, p_message.params, p_message.param_count);
}

void MCRevBrowserIPCFreeCallback(MCRevBrowserIPCMessageCallback &p_message)
{
	MCIPCFreeCString(p_message.message);
	p_message.message = nil;
	MCIPCFreeCStringArray(p_message.params, p_message.param_count);
	p_message.params = nil;
	p_message.param_count = 0;
}

//////////

bool MCRevBrowserIPCWriteResult(MCIPCRef p_ipc, const MCRevBrowserIPCMessageResult &p_message)
{
	return MCIPCWriteValue(p_ipc, p_message.value);
}

bool MCRevBrowserIPCReadResult(MCIPCRef p_ipc, MCRevBrowserIPCMessageResult &r_message)
{
	return MCIPCReadValue(p_ipc, p_message.value);
}

void MCRevBrowserIPCFreeResult(MCRevBrowserIPCMessageResult &p_message)
{
	MCIPCFreeValue(p_message.value);
	p_message.value = nil;
}

//////////

bool MCRevBrowserIPCWriteMessage(MCIPCRef p_ipc, const MCRevBrowserIPCMessage *p_message)
{
	if (!MCRevBrowserIPCWriteMessageType(p_ipc, p_message->type))
		return false;
	
	switch (p_message->type)
	{
		case kMCRevBrowserIPCMessageCreateBrowser:
			return MCRevBrowserIPCWriteCreateBrowser(p_ipc, p_message->create_browser);
		
		case kMCRevBrowserIPCMessageDestroyBrowser:
			return MCRevBrowserIPCWriteDestroyBrowser(p_ipc, p_message->destroy_browser);
		
		case kMCRevBrowserIPCMessageGetProperty:
			return MCRevBrowserIPCWriteGetProperty(p_ipc, p_message->get_property);
		
		case kMCRevBrowserIPCMessageSetProperty:
			return MCRevBrowserIPCWriteSetProperty(p_ipc, p_message->set_property);
		
		case kMCRevBrowserIPCMessageExecuteScript:
			return MCRevBrowserIPCWriteExecuteScript(p_ipc, p_message->execute_script);
		
		case kMCRevBrowserIPCMessageCallScript:
			return MCRevBrowserIPCWriteCallScript(p_ipc, p_message->call_script);
		
		case kMCRevBrowserIPCMessageFindString:
			return MCRevBrowserIPCWriteFindString(p_ipc, p_message->find_string);
		
		case kMCRevBrowserIPCMessageAddJavaScriptHandler:
			return MCRevBrowserIPCWriteAddJavaScriptHandler(p_ipc, p_message->add_javascript_handler);
		
		case kMCRevBrowserIPCMessageRemoveJavaScriptHandler:
			return MCRevBrowserIPCWriteRemoveJavaScriptHandler(p_ipc, p_message->remove_javascript_handler);
		
		case kMCRevBrowserIPCMessageCallback:
			return MCRevBrowserIPCWriteCallback(p_ipc, p_message->callback);
		
		case kMCRevBrowserIPCMessageResult:
			return MCRevBrowserIPCWriteResult(p_ipc, p_message->result);
	}
	
	return true;
}

bool _MCRevBrowserIPCReadMessage(MCIPCRef p_ipc, MCRevBrowserIPCMessage &r_message)
{
	if (!MCRevBrowserIPCReadMessageType(p_ipc, r_message->type))
		return false;
	
	switch (r_message->type)
	{
		case kMCRevBrowserIPCMessageCreateBrowser:
			return MCRevBrowserIPCReadCreateBrowser(p_ipc, r_message->create_browser);
		
		case kMCRevBrowserIPCMessageDestroyBrowser:
			return MCRevBrowserIPCReadDestroyBrowser(p_ipc, r_message->destroy_browser);
		
		case kMCRevBrowserIPCMessageGetProperty:
			return MCRevBrowserIPCReadGetProperty(p_ipc, r_message->get_property);
		
		case kMCRevBrowserIPCMessageSetProperty:
			return MCRevBrowserIPCReadSetProperty(p_ipc, r_message->set_property);
		
		case kMCRevBrowserIPCMessageExecuteScript:
			return MCRevBrowserIPCReadExecuteScript(p_ipc, r_message->execute_script);
		
		case kMCRevBrowserIPCMessageCallScript:
			return MCRevBrowserIPCReadCallScript(p_ipc, r_message->call_script);
		
		case kMCRevBrowserIPCMessageFindString:
			return MCRevBrowserIPCReadFindString(p_ipc, r_message->find_string);
		
		case kMCRevBrowserIPCMessageAddJavaScriptHandler:
			return MCRevBrowserIPCReadAddJavaScriptHandler(p_ipc, r_message->add_javascript_handler);
		
		case kMCRevBrowserIPCMessageRemoveJavaScriptHandler:
			return MCRevBrowserIPCReadRemoveJavaScriptHandler(p_ipc, r_message->remove_javascript_handler);
		
		case kMCRevBrowserIPCMessageCallback:
			return MCRevBrowserIPCReadCallback(p_ipc, r_message->callback);
		
		case kMCRevBrowserIPCMessageResult:
			return MCRevBrowserIPCReadResult(p_ipc, r_message->result);
	}
	
	return true;
}

bool MCRevBrowserIPCReadMessage(MCIPCRef p_ipc, MCRevBrowserIPCMessage *&r_message)
{
	bool t_success;
	t_success = true;
	
	MCRevBrowserIPCMessage *t_message;
	t_message = nil;
	
	if (t_success)
		t_success = MCMemoryNew(t_message);
		
	if (t_success)
		t_success = _MCRevBrowserIPCReadMessage(p_ipc, *t_message);
		
	if (t_success)
		r_message = t_message;
	else
		MCRevBrowserIPCFreeMessage(t_message);
	
	return t_success;
}

void MCRevBrowserIPCFreeMessage(MCRevBrowserIPCMessage *p_message)
{
	if (p_message == nil)
		return;
		
	switch (p_message->type)
	{
		case kMCRevBrowserIPCMessageSetProperty:
			return MCRevBrowserIPCFreeSetProperty(p_message->set_property);
		
		case kMCRevBrowserIPCMessageExecuteScript:
			return MCRevBrowserIPCFreeExecuteScript(p_message->execute_script);
		
		case kMCRevBrowserIPCMessageCallScript:
			return MCRevBrowserIPCFreeCallScript(p_message->call_script);
		
		case kMCRevBrowserIPCMessageFindString:
			return MCRevBrowserIPCFreeFindString(p_message->find_string);
		
		case kMCRevBrowserIPCMessageAddJavaScriptHandler:
			return MCRevBrowserIPCFreeAddJavaScriptHandler(p_message->add_javascript_handler);
		
		case kMCRevBrowserIPCMessageRemoveJavaScriptHandler:
			return MCRevBrowserIPCFreeRemoveJavaScriptHandler(p_message->remove_javascript_handler);
		
		case kMCRevBrowserIPCMessageCallback:
			return MCRevBrowserIPCFreeCallback(p_message->callback);
		
		case kMCRevBrowserIPCMessageResult:
			return MCRevBrowserIPCFreeResult(p_message->result);
	}
	
	MCMemoryDelete(p_message);
}
