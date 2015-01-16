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

#ifndef __MC_IPC_H__
#define __MC_IPC_H__

#include "core.h"

typedef struct __MCIPC *MCIPCRef;

extern bool MCIPCCreateWithPipe(int p_input, int p_output, MCIPCRef &r_ipc);
extern void MCIPCDestroy(MCIPCRef p_ipc);

extern bool MCIPCWrite(MCIPCRef p_ipc, const uint8_t *p_data, uint32_t p_length);
extern bool MCIPCRead(MCIPCRef p_ipc, uint8_t *p_data, uint32_t p_length);

extern bool MCIPCWriteBoolean(MCIPCRef p_ipc, bool p_value);
extern bool MCIPCReadBoolean(MCIPCRef p_ipc, bool &r_value);

extern bool MCIPCWriteInt32(MCIPCRef p_ipc, int32_t p_value);
extern bool MCIPCReadInt32(MCIPCRef p_ipc, int32_t &r_value);

extern bool MCIPCWriteCString(MCIPCRef p_ipc, const char *p_value);
extern bool MCIPCReadCString(MCIPCRef p_ipc, char *&r_value);

//extern bool MCIPCSendMessage(MCIPCRef p_ipc, const uint8_t *p_data, uint32_t p_length);
//extern bool MCIPCWaitForMessage(MCIPCRef p_ipc, uint8_t *&r_data, uint32_t &r_length);

#endif//__MC_IPC_H__
