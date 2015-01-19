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

#include "ipc.h"

typedef struct __MCIPC
{
	int input;
	int output;
	
} *MCIPCRef;

bool MCIPCCreateWithPipe(int p_input, int p_output, MCIPCRef &r_ipc)
{
	MCIPCRef t_ipc;
	t_ipc = nil;
	
	if (!MCMemoryNew(t_ipc))
		return false;
	
	t_ipc->input = p_input;
	t_ipc->output = p_output;
	
	r_ipc = t_ipc;
	
	return true;
}

void MCIPCDestroy(MCIPCRef p_ipc)
{
	close(p_ipc->input);
	close(p_ipc->output);
	MCMemoryDelete(p_ipc);
}

bool MCIPCWrite(MCIPCRef p_ipc, const uint8_t *p_data, uint32_t p_length)
{
	ssize_t t_written;
	while (p_length > 0)
	{
		t_written = write(p_ipc->output, p_data, p_length)
		if (t_written == -1)
			return false;
		
		p_data += t_written;
		p_length -= p_length;
	}
	
	return true;
}

bool MCIPCWriteRectangle(MCIPCRef p_ipc, const MCIPCRectangle &p_rect)
{
	return MCIPCWriteInt32(p_ipc, p_rect.left) &&
		MCIPCWriteInt32(p_ipc, p_rect.top) &&
		MCIPCWriteInt32(p_ipc, p_rect.right) &&
		MCIPCWriteInt32(p_ipc, p_rect.bottom);
}

bool MCIPCReadRectangle(MCIPCRef p_ipc, MCIPCRectangle &r_rect)
{
	MCIPCRectangle t_rect;
	if (!(MCIPCReadInt32(p_ipc, t_rect.left) &&
		MCIPCReadInt32(p_ipc, t_rect.top) &&
		MCIPCReadInt32(p_ipc, t_rect.right) &&
		MCIPCReadInt32(p_ipc, t_rect.bottom)))
		return false;
	
	r_rect = t_rect;
	return true;
}

bool MCIPCWriteValue(MCIPCRef p_ipc, const MCIPCValue *p_value)
{
	if (!MCIPCWrite(p_ipc, &p_value->type, sizeof(MCIPCValueType)))
		return false;
	
	switch (p_value->type)
	{
		case kMCIPCValueTypeBoolean:
			return MCIPCWriteBoolean(p_ipc, p_value->boolean);
			
		case kMCIPCValueTypeString:
			return MCIPCWriteString(p_ipc, p_value->string);
		
		case kMCIPCValueTypeInt32:
			return MCIPCWriteInt32(p_ipc, p_value->int32);
		
		case kMCIPCValueTypeRectangle:
			return MCIPCWriteRectangle(p_ipc, p_value->rectangle);
	}

	return false;
}

bool MCIPCReadValue(MCIPCRef p_ipc, MCIPCValue *&r_value)
{
	bool t_success;
	t_success = true;
	
	MCIPCValue *t_value;
	t_value = nil;
	
	if (t_success)
		t_success = MCMemoryNew(t_value);
	
	if (t_success)
		t_success = MCIPCRead(p_ipc, &t_value->type, sizeof(MCIPCValueType));
	
	if (t_success)
	{
		switch (t_value->type)
		{
			case kMCIPCValueTypeBoolean:
				t_success = MCIPCReadBoolean(p_ipc, t_value->boolean);
				break;
				
			case kMCIPCValueTypeString:
				t_success = MCIPCReadString(p_ipc, t_value->string);
				break;
			
			case kMCIPCValueTypeInt32:
				t_success = MCIPCReadInt32(p_ipc, t_value->int32);
				break;
			
			case kMCIPCValueTypeRectangle:
				t_success = MCIPCReadRectangle(p_ipc, t_value->rectangle);
				break;
		}
	}
	
	if (t_success)
		r_value = t_value;
	else
		MCIPCFreeValue(t_value);
	
	return t_success;
}

void MCIPCFreeValue(MCIPCValue *p_value)
{
	switch (p_value->type)
	{
		case kMCIPCValueTypeString:
			MCCStringFree(p_value->string);
			break;
	}
	
	MCMemoryDelete(p_value);
}



bool MCIPCSendMessage(MCIPCRef p_ipc, const uint8_t *p_data, uint32_t p_length)
{
	if (p_length == 0)
		return true;
		
	return MCIPCWrite(p_ipc, &p_length, sizeof(p_length)) &&
		MCIPCWrite(p_ipc, p_data, p_length);
}

bool MCIPCRead(MCIPCRef p_ipc, uint8_t *p_data, uint32_t p_length)
{
	ssize_t t_read;
	while (p_length > 0)
	{
		t_read = read(p_ipc->input, p_data, p_length);
		if (t_read == -1)
			return false;
		p_data += t_read;
		p_length -= t_read;
	}
	
	return true;
}

bool MCIPCWaitForMessage(MCIPCRef p_ipc, void *&r_data, uint32_t &r_length)
{
	uint32_t t_length;
	if (!MCIPCRead(p_ipc, &t_length, sizeof(t_length)))
		return false;
	
	uint8_t *t_data;
	t_data = nil;
	
	if (!MCMemoryAllocate(t_length, t_data))
		return false;
	
	if (!MCIPCRead(p_ipc, t_data, t_length))
	{
		MCMemoryDeallocate(t_data);
		return false;
	}
	
	r_data = t_data;
	r_length = t_length;
	
	return true;
}

#endif//__MC_IPC_H__
