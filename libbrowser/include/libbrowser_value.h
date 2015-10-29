/* Copyright (C) 2003-2015 Runtime Revolution Ltd.
 
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

////////////////////////////////////////////////////////////////////////////////

#ifndef __LIBBROWSER_VALUE_H__
#define __LIBBROWSER_VALUE_H__

////////////////////////////////////////////////////////////////////////////////
//
//  SYMBOL EXPORTS
//
#ifdef _WIN32
#  ifdef _MSC_VER
#    define MC_DLLEXPORT __declspec(dllexport)
#  else
#    define MC_DLLEXPORT __attribute__((dllexport))
#  endif
#else
#  define MC_DLLEXPORT __attribute__((__visibility__("default")))
#endif

////////////////////////////////////////////////////////////////////////////////

typedef struct __MCBrowserList *MCBrowserListRef;
typedef struct __MCBrowserDictionary *MCBrowserDictionaryRef;

enum MCBrowserValueType
{
	kMCBrowserValueTypeNone,
	kMCBrowserValueTypeBoolean,
	kMCBrowserValueTypeInteger,
	kMCBrowserValueTypeDouble,
	kMCBrowserValueTypeUTF8String,
	kMCBrowserValueTypeList,
	kMCBrowserValueTypeDictionary,
};

extern "C"
{

MC_DLLEXPORT bool MCBrowserListCreate(MCBrowserListRef &r_browser, uint32_t p_size = 0);
MC_DLLEXPORT MCBrowserListRef MCBrowserListRetain(MCBrowserListRef p_list);
MC_DLLEXPORT void MCBrowserListRelease(MCBrowserListRef p_list);

MC_DLLEXPORT bool MCBrowserListGetSize(MCBrowserListRef p_list, uint32_t &r_size);
MC_DLLEXPORT bool MCBrowserListGetType(MCBrowserListRef p_list, uint32_t p_index, MCBrowserValueType &r_type);

MC_DLLEXPORT bool MCBrowserListSetBoolean(MCBrowserListRef p_list, uint32_t p_index, bool p_value);
MC_DLLEXPORT bool MCBrowserListSetInteger(MCBrowserListRef p_list, uint32_t p_index, int32_t p_value);
MC_DLLEXPORT bool MCBrowserListSetDouble(MCBrowserListRef p_list, uint32_t p_index, double p_value);
MC_DLLEXPORT bool MCBrowserListSetUTF8String(MCBrowserListRef p_list, uint32_t p_index, const char *p_value);
MC_DLLEXPORT bool MCBrowserListSetList(MCBrowserListRef p_list, uint32_t p_index, MCBrowserListRef p_value);
MC_DLLEXPORT bool MCBrowserListSetDictionary(MCBrowserListRef p_list, uint32_t p_index, MCBrowserDictionaryRef p_value);

MC_DLLEXPORT bool MCBrowserListAppendBoolean(MCBrowserListRef p_list, bool p_value);
MC_DLLEXPORT bool MCBrowserListAppendInteger(MCBrowserListRef p_list, int32_t p_value);
MC_DLLEXPORT bool MCBrowserListAppendDouble(MCBrowserListRef p_list, double p_value);
MC_DLLEXPORT bool MCBrowserListAppendUTF8String(MCBrowserListRef p_list, const char *p_value);
MC_DLLEXPORT bool MCBrowserListAppendList(MCBrowserListRef p_list, MCBrowserListRef p_value);
MC_DLLEXPORT bool MCBrowserListAppendDictionary(MCBrowserListRef p_list, MCBrowserDictionaryRef p_value);

MC_DLLEXPORT bool MCBrowserListGetBoolean(MCBrowserListRef p_list, uint32_t p_index, bool &r_value);
MC_DLLEXPORT bool MCBrowserListGetInteger(MCBrowserListRef p_list, uint32_t p_index, int32_t &r_value);
MC_DLLEXPORT bool MCBrowserListGetDouble(MCBrowserListRef p_list, uint32_t p_index, double &r_value);
MC_DLLEXPORT bool MCBrowserListGetUTF8String(MCBrowserListRef p_list, uint32_t p_index, char *&r_value);
MC_DLLEXPORT bool MCBrowserListGetList(MCBrowserListRef p_list, uint32_t p_index, MCBrowserListRef &r_value);
MC_DLLEXPORT bool MCBrowserListGetDictionary(MCBrowserListRef p_list, uint32_t p_index, MCBrowserDictionaryRef &r_value);

//////////

MC_DLLEXPORT bool MCBrowserDictionaryCreate(MCBrowserDictionaryRef &r_dict, uint32_t p_size = 0);
MC_DLLEXPORT MCBrowserDictionaryRef MCBrowserDictionaryRetain(MCBrowserDictionaryRef p_dict);
MC_DLLEXPORT void MCBrowserDictionaryRelease(MCBrowserDictionaryRef p_dict);

MC_DLLEXPORT bool MCBrowserDictionaryGetType(MCBrowserDictionaryRef p_dict, const char *p_key, MCBrowserValueType &r_type);
MC_DLLEXPORT bool MCBrowserDictionaryGetKeys(MCBrowserDictionaryRef p_dict, char **&r_keys, uint32_t &r_count);

/* WORKAROUND - Can't currently dereference a Pointer-to-CString at the moment so need to provide key accessor functions */
MC_DLLEXPORT bool MCBrowserDictionaryGetKeyCount(MCBrowserDictionaryRef p_dict, uint32_t &r_count);
MC_DLLEXPORT bool MCBrowserDictionaryGetKey(MCBrowserDictionaryRef p_dict, uint32_t p_index, char *&r_key);

MC_DLLEXPORT bool MCBrowserDictionarySetBoolean(MCBrowserDictionaryRef p_dict, const char *p_key, bool p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetInteger(MCBrowserDictionaryRef p_dict, const char *p_key, int32_t p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetDouble(MCBrowserDictionaryRef p_dict, const char *p_key, double p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetUTF8String(MCBrowserDictionaryRef p_dict, const char *p_key, const char *p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetList(MCBrowserDictionaryRef p_dict, const char *p_key, MCBrowserListRef p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetDictionary(MCBrowserDictionaryRef p_dict, const char *p_key, MCBrowserDictionaryRef p_value);

MC_DLLEXPORT bool MCBrowserDictionaryGetBoolean(MCBrowserDictionaryRef p_dict, const char *p_key, bool &r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetInteger(MCBrowserDictionaryRef p_dict, const char *p_key, int32_t &r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetDouble(MCBrowserDictionaryRef p_dict, const char *p_key, double &r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetUTF8String(MCBrowserDictionaryRef p_dict, const char *p_key, char *&r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetList(MCBrowserDictionaryRef p_dict, const char *p_key, MCBrowserListRef &r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetDictionary(MCBrowserDictionaryRef p_dict, const char *p_key, MCBrowserDictionaryRef &r_value);

}

//////////

#endif // __LIBBROWSER_VALUE_H__
