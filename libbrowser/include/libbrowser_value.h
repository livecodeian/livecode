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

typedef struct __MCBrowserValue *MCBrowserValueRef;
typedef struct __MCBrowserString *MCBrowserStringRef;
typedef struct __MCBrowserList *MCBrowserListRef;
typedef struct __MCBrowserDictionary *MCBrowserDictionaryRef;

enum MCBrowserValueType
{
	kMCBrowserValueTypeNone,
	kMCBrowserValueTypeBoolean,
	kMCBrowserValueTypeInteger,
	kMCBrowserValueTypeDouble,
	kMCBrowserValueTypeString,
	kMCBrowserValueTypeList,
	kMCBrowserValueTypeDictionary,
};

extern "C"
{

MC_DLLEXPORT void MCBrowserValueClear(MCBrowserValueRef p_value);
MC_DLLEXPORT bool MCBrowserValueCopy(const MCBrowserValueRef p_src, MCBrowserValueRef r_dst);
	
MC_DLLEXPORT bool MCBrowserValueGetType(MCBrowserValueRef p_valueref, MCBrowserValueType &r_type);

MC_DLLEXPORT bool MCBrowserValueSetBoolean(MCBrowserValueRef p_valueref, bool p_value);
MC_DLLEXPORT bool MCBrowserValueSetInteger(MCBrowserValueRef p_valueref, int32_t p_value);
MC_DLLEXPORT bool MCBrowserValueSetDouble(MCBrowserValueRef p_valueref, double p_value);
MC_DLLEXPORT bool MCBrowserValueSetString(MCBrowserValueRef p_valueref, MCBrowserStringRef p_value);
MC_DLLEXPORT bool MCBrowserValueSetList(MCBrowserValueRef p_valueref, MCBrowserListRef p_value);
MC_DLLEXPORT bool MCBrowserValueSetDictionary(MCBrowserValueRef p_valueref, MCBrowserDictionaryRef p_value);

MC_DLLEXPORT bool MCBrowserValueGetBoolean(MCBrowserValueRef p_valueref, bool &r_value);
MC_DLLEXPORT bool MCBrowserValueGetInteger(MCBrowserValueRef p_valueref, int32_t &r_value);
MC_DLLEXPORT bool MCBrowserValueGetDouble(MCBrowserValueRef p_valueref, double &r_value);
MC_DLLEXPORT bool MCBrowserValueGetString(MCBrowserValueRef p_valueref, MCBrowserStringRef &r_value);
MC_DLLEXPORT bool MCBrowserValueGetList(MCBrowserValueRef p_valueref, MCBrowserListRef &r_value);
MC_DLLEXPORT bool MCBrowserValueGetDictionary(MCBrowserValueRef p_valueref, MCBrowserDictionaryRef &r_value);

//////////

MC_DLLEXPORT bool MCBrowserStringCreateWithUTF8String(const char *p_utf8_string, MCBrowserStringRef &r_string);
MC_DLLEXPORT bool MCBrowserStringCreateWithUTF8Substring(const char *p_utf8_string, uint32_t p_length, MCBrowserStringRef &r_string);
MC_DLLEXPORT bool MCBrowserStringGetUTF8String(MCBrowserStringRef p_string, char *&r_utf8_string);

MC_DLLEXPORT bool MCBrowserStringIsEqualTo(MCBrowserStringRef p_left, MCBrowserStringRef p_right);
MC_DLLEXPORT bool MCBrowserStringIsEqualToCaseless(MCBrowserStringRef p_left, MCBrowserStringRef p_right);

MC_DLLEXPORT MCBrowserStringRef MCBrowserStringRetain(MCBrowserStringRef p_value);
MC_DLLEXPORT void MCBrowserStringRelease(MCBrowserStringRef p_value);

//////////

MC_DLLEXPORT bool MCBrowserListCreate(MCBrowserListRef &r_browser, uint32_t p_size = 0);
MC_DLLEXPORT MCBrowserListRef MCBrowserListRetain(MCBrowserListRef p_list);
MC_DLLEXPORT void MCBrowserListRelease(MCBrowserListRef p_list);

MC_DLLEXPORT bool MCBrowserListGetSize(MCBrowserListRef p_list, uint32_t &r_size);
MC_DLLEXPORT bool MCBrowserListGetType(MCBrowserListRef p_list, uint32_t p_index, MCBrowserValueType &r_type);

MC_DLLEXPORT bool MCBrowserListSetValue(MCBrowserListRef p_list, uint32_t p_index, MCBrowserValueRef p_value);
MC_DLLEXPORT bool MCBrowserListSetBoolean(MCBrowserListRef p_list, uint32_t p_index, bool p_value);
MC_DLLEXPORT bool MCBrowserListSetInteger(MCBrowserListRef p_list, uint32_t p_index, int32_t p_value);
MC_DLLEXPORT bool MCBrowserListSetDouble(MCBrowserListRef p_list, uint32_t p_index, double p_value);
MC_DLLEXPORT bool MCBrowserListSetString(MCBrowserListRef p_list, uint32_t p_index, MCBrowserStringRef p_value);
MC_DLLEXPORT bool MCBrowserListSetList(MCBrowserListRef p_list, uint32_t p_index, MCBrowserListRef p_value);
MC_DLLEXPORT bool MCBrowserListSetDictionary(MCBrowserListRef p_list, uint32_t p_index, MCBrowserDictionaryRef p_value);

MC_DLLEXPORT bool MCBrowserListAppendValue(MCBrowserListRef p_list, MCBrowserValueRef p_value);
MC_DLLEXPORT bool MCBrowserListAppendBoolean(MCBrowserListRef p_list, bool p_value);
MC_DLLEXPORT bool MCBrowserListAppendInteger(MCBrowserListRef p_list, int32_t p_value);
MC_DLLEXPORT bool MCBrowserListAppendDouble(MCBrowserListRef p_list, double p_value);
MC_DLLEXPORT bool MCBrowserListAppendString(MCBrowserListRef p_list, MCBrowserStringRef p_value);
MC_DLLEXPORT bool MCBrowserListAppendList(MCBrowserListRef p_list, MCBrowserListRef p_value);
MC_DLLEXPORT bool MCBrowserListAppendDictionary(MCBrowserListRef p_list, MCBrowserDictionaryRef p_value);

MC_DLLEXPORT bool MCBrowserListGetValue(MCBrowserListRef p_list, uint32_t p_index, MCBrowserValueRef &r_value);
MC_DLLEXPORT bool MCBrowserListGetBoolean(MCBrowserListRef p_list, uint32_t p_index, bool &r_value);
MC_DLLEXPORT bool MCBrowserListGetInteger(MCBrowserListRef p_list, uint32_t p_index, int32_t &r_value);
MC_DLLEXPORT bool MCBrowserListGetDouble(MCBrowserListRef p_list, uint32_t p_index, double &r_value);
MC_DLLEXPORT bool MCBrowserListGetString(MCBrowserListRef p_list, uint32_t p_index, MCBrowserStringRef &r_value);
MC_DLLEXPORT bool MCBrowserListGetList(MCBrowserListRef p_list, uint32_t p_index, MCBrowserListRef &r_value);
MC_DLLEXPORT bool MCBrowserListGetDictionary(MCBrowserListRef p_list, uint32_t p_index, MCBrowserDictionaryRef &r_value);

//////////

MC_DLLEXPORT bool MCBrowserDictionaryCreate(MCBrowserDictionaryRef &r_dict, uint32_t p_size = 0);
MC_DLLEXPORT MCBrowserDictionaryRef MCBrowserDictionaryRetain(MCBrowserDictionaryRef p_dict);
MC_DLLEXPORT void MCBrowserDictionaryRelease(MCBrowserDictionaryRef p_dict);

MC_DLLEXPORT bool MCBrowserDictionaryGetType(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, MCBrowserValueType &r_type);
MC_DLLEXPORT bool MCBrowserDictionaryGetKeys(MCBrowserDictionaryRef p_dict, MCBrowserStringRef *&r_keys, uint32_t &r_count);

/* WORKAROUND - Can't currently dereference a Pointer-to-CString at the moment so need to provide key accessor functions */
MC_DLLEXPORT bool MCBrowserDictionaryGetKeyCount(MCBrowserDictionaryRef p_dict, uint32_t &r_count);
MC_DLLEXPORT bool MCBrowserDictionaryGetKey(MCBrowserDictionaryRef p_dict, uint32_t p_index, MCBrowserStringRef &r_key);

MC_DLLEXPORT bool MCBrowserDictionarySetValue(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, MCBrowserValueRef p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetBoolean(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, bool p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetInteger(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, int32_t p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetDouble(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, double p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetString(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, MCBrowserStringRef p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetList(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, MCBrowserListRef p_value);
MC_DLLEXPORT bool MCBrowserDictionarySetDictionary(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, MCBrowserDictionaryRef p_value);

MC_DLLEXPORT bool MCBrowserDictionaryGetValue(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, MCBrowserValueRef &r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetBoolean(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, bool &r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetInteger(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, int32_t &r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetDouble(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, double &r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetString(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, MCBrowserStringRef &r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetList(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, MCBrowserListRef &r_value);
MC_DLLEXPORT bool MCBrowserDictionaryGetDictionary(MCBrowserDictionaryRef p_dict, MCBrowserStringRef p_key, MCBrowserDictionaryRef &r_value);

}

//////////

#endif // __LIBBROWSER_VALUE_H__
