/*
 *  sserialize_osx.h
 *  libcore
 *
 *  Created by Ian Macphail on 22/10/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
 
#ifndef __MC_SSERIALIZE_OSX_H__
#define __MC_SSERIALIZE_OSX_H__

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <Carbon/Carbon.h>

#include "core.h"

extern bool serialize_cfdata(char *&r_stream, uint32_t &r_stream_size, uint32_t &r_offset, CFDataRef p_data);
extern bool deserialize_cfdata(const char *p_stream, uint32_t p_stream_size, uint32_t &r_offset, CFDataRef &r_data);

extern bool serialize_cfstring(char *&r_stream, uint32_t &r_stream_size, uint32_t &r_offset, CFStringRef p_string);
extern bool deserialize_cfstring(const char *p_stream, uint32_t p_stream_size, uint32_t &r_offset, CFStringRef &r_string);

extern bool serialize_handle(char *&r_stream, uint32_t &r_stream_size, uint32_t &r_offset, Handle p_data);
extern bool deserialize_handle(const char *p_stream, uint32_t p_stream_size, uint32_t &r_offset, Handle &r_handle);


extern bool serialize_printer_settings(char *&r_stream, uint32_t &r_stream_size, PMPrintSession p_session, PMPrinter p_printer, PMPrintSettings p_settings, PMPageFormat p_format);
extern bool deserialize_printer_settings(const char *p_stream, uint32_t p_stream_size, PMPrintSession &r_session, PMPrinter &r_printer, PMPrintSettings &r_settings, PMPageFormat &r_format);

#endif
