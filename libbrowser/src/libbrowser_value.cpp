/* Copyright (C) 2015 LiveCode Ltd.
 
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

#include <core.h>

#include "libbrowser.h"
#include "libbrowser_internal.h"

////////////////////////////////////////////////////////////////////////////////

void MCBrowserValueClear(MCBrowserValue &p_value)
{
	switch (p_value.type)
	{
		case kMCBrowserValueTypeString:
			MCBrowserStringRelease(p_value.string);
			break;
		
		case kMCBrowserValueTypeList:
			MCBrowserListRelease(p_value.array);
			break;
		
		case kMCBrowserValueTypeDictionary:
			MCBrowserDictionaryRelease(p_value.dictionary);
			break;
		
		default:
			break;
	}
	
	p_value.type = kMCBrowserValueTypeNone;
}

bool MCBrowserValueCopy(const MCBrowserValue &p_src, MCBrowserValue &r_dst)
{
	switch (p_src.type)
	{
		case kMCBrowserValueTypeBoolean:
			return MCBrowserValueSetBoolean(r_dst, p_src.boolean);
		
		case kMCBrowserValueTypeInteger:
			return MCBrowserValueSetInteger(r_dst, p_src.integer);
		
		case kMCBrowserValueTypeDouble:
			return MCBrowserValueSetDouble(r_dst, p_src.double_val);
		
		case kMCBrowserValueTypeNone:
			MCBrowserValueClear(r_dst);
			return true;
		
		case kMCBrowserValueTypeString:
			return MCBrowserValueSetString(r_dst, p_src.string);
		
		case kMCBrowserValueTypeList:
			return MCBrowserValueSetList(r_dst, p_src.array);
		
		case kMCBrowserValueTypeDictionary:
			return MCBrowserValueSetDictionary(r_dst, p_src.dictionary);
		
		default:
			// unknown type
			break;
	}
	
	return false;
}

bool MCBrowserValueSetBoolean(MCBrowserValue &self, bool p_value)
{
	MCBrowserValueClear(self);
	self.type = kMCBrowserValueTypeBoolean;
	self.boolean = p_value;
	
	return true;
}

bool MCBrowserValueGetBoolean(MCBrowserValue &self, bool &r_value)
{
	if (self.type != kMCBrowserValueTypeBoolean)
		return false;
	
	r_value = self.boolean;
	return true;
}

bool MCBrowserValueSetInteger(MCBrowserValue &self, int32_t p_value)
{
	MCBrowserValueClear(self);
	self.type = kMCBrowserValueTypeInteger;
	self.integer = p_value;
	
	return true;
}

bool MCBrowserValueGetInteger(MCBrowserValue &self, int32_t &r_value)
{
	if (self.type != kMCBrowserValueTypeInteger)
		return false;
	
	r_value = self.integer;
	return true;
}

bool MCBrowserValueSetDouble(MCBrowserValue &self, double p_value)
{
	MCBrowserValueClear(self);
	self.type = kMCBrowserValueTypeDouble;
	self.double_val = p_value;
	
	return true;
}

bool MCBrowserValueGetDouble(MCBrowserValue &self, double &r_value)
{
	if (self.type != kMCBrowserValueTypeDouble)
		return false;
	
	r_value = self.double_val;
	return true;
}

bool MCBrowserValueSetString(MCBrowserValue &self, MCBrowserStringRef p_value)
{
	MCBrowserStringRef t_string;
	t_string = MCBrowserStringRetain(p_value);
	MCBrowserValueClear(self);
	self.type = kMCBrowserValueTypeString;
	self.string = t_string;
	
	return true;
}

bool MCBrowserValueGetString(MCBrowserValue &self, MCBrowserStringRef &r_value)
{
	if (self.type != kMCBrowserValueTypeString)
		return false;
	
	r_value = self.string;
	return true;
}

bool MCBrowserValueSetList(MCBrowserValue &self, MCBrowserListRef p_value)
{
	MCBrowserListRef t_array;
	t_array = MCBrowserListRetain(p_value);
	MCBrowserValueClear(self);
	self.type = kMCBrowserValueTypeList;
	self.array = t_array;

	return true;
}

bool MCBrowserValueGetList(MCBrowserValue &self, MCBrowserListRef &r_value)
{
	if (self.type != kMCBrowserValueTypeList)
		return false;
	
	r_value = self.array;
	return true;
}

bool MCBrowserValueSetDictionary(MCBrowserValue &self, MCBrowserDictionaryRef p_value)
{
	MCBrowserDictionaryRef t_dict;
	t_dict = MCBrowserDictionaryRetain(p_value);
	MCBrowserValueClear(self);
	self.type = kMCBrowserValueTypeDictionary;
	self.dictionary = t_dict;
	
	return true;
}

bool MCBrowserValueGetDictionary(MCBrowserValue &self, MCBrowserDictionaryRef &r_value)
{
	if (self.type != kMCBrowserValueTypeDictionary)
		return false;
	
	r_value = self.dictionary;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

class MCBrowserString : public MCBrowserRefCounted
{
public:
	MCBrowserString()
	{
		m_string = nil;
	}
	
	virtual ~MCBrowserString()
	{
		Clear();
	}
	
	void Clear()
	{
		if (m_string != nil)
			MCCStringFree(m_string);
		m_string = nil;
	}
	
	bool SetUTF8String(const char *p_utf8_string)
	{
		MCAssert(m_string == nil);
		
		char *t_string;
		if (!MCCStringClone(p_utf8_string, t_string))
			return false;
		Clear();
		m_string = t_string;
		return true;
	}
	
	bool SetUTF8Substring(const char *p_utf8_string, uint32_t p_length)
	{
		MCAssert(m_string == nil);
		
		char *t_string;
		if (!MCCStringCloneSubstring(p_utf8_string, p_length, t_string))
			return false;
		Clear();
		m_string = t_string;
		return true;
	}
	
	bool GetUTF8String(char *&r_utf8_string)
	{
		if (m_string == nil)
		{
			r_utf8_string = nil;
			return true;
		}
		return MCCStringClone(m_string, r_utf8_string);
	}
	
	bool IsEqualTo(MCBrowserString *p_other)
	{
		if (this == p_other)
			return true;

		if (p_other == nil)
			return false;
		
		if (m_string == nil)
			return p_other->m_string == nil;
		else if (p_other->m_string == nil)
			return false;
		
		return MCCStringEqual(m_string, p_other->m_string);
	}
	
	bool IsEqualToCaseless(MCBrowserString *p_other)
	{
		if (this == p_other)
			return true;
		
		if (p_other == nil)
			return false;
		
		if (m_string == nil)
			return p_other->m_string == nil;
		else if (p_other->m_string == nil)
			return false;
		
		return MCCStringEqualCaseless(m_string, p_other->m_string);
	}
	
private:
	char *m_string;
};

bool MCBrowserStringCreateWithUTF8String(const char *p_utf8_string, MCBrowserStringRef &r_string)
{
	MCBrowserString *t_string;
	t_string = new MCBrowserString();
	if (t_string == nil)
		return false;
	if (!t_string->SetUTF8String(p_utf8_string))
	{
		delete t_string;
		return false;
	}
	
	r_string = (MCBrowserStringRef)t_string;
	return true;
}

bool MCBrowserStringCreateWithUTF8Substring(const char *p_utf8_string, uint32_t p_length, MCBrowserStringRef &r_string)
{
	MCBrowserString *t_string;
	t_string = new MCBrowserString();
	if (t_string == nil)
		return false;
	if (!t_string->SetUTF8Substring(p_utf8_string, p_length))
	{
		delete t_string;
		return false;
	}
	
	r_string = (MCBrowserStringRef)t_string;
	return true;
}

bool MCBrowserStringGetUTF8String(MCBrowserStringRef p_string, char *&r_utf8_string)
{
	if (p_string == nil)
		return false;
	
	return ((MCBrowserString*)p_string)->GetUTF8String(r_utf8_string);
}

bool MCBrowserStringIsEqualTo(MCBrowserStringRef p_left, MCBrowserStringRef p_right)
{
	MCAssert(p_left != nil && p_right != nil);

	return ((MCBrowserString*)p_left)->IsEqualTo((MCBrowserString*)p_right);
}

bool MCBrowserStringIsEqualToCaseless(MCBrowserStringRef p_left, MCBrowserStringRef p_right)
{
	MCAssert(p_left != nil && p_right != nil);
	
	return ((MCBrowserString*)p_left)->IsEqualToCaseless((MCBrowserString*)p_right);
}

MCBrowserStringRef MCBrowserStringRetain(MCBrowserStringRef p_string)
{
	if (p_string != nil)
		((MCBrowserString*)p_string)->Retain();
	return p_string;
}

void MCBrowserStringRelease(MCBrowserStringRef p_string)
{
	if (p_string != nil)
		((MCBrowserString*)p_string)->Release();
}

////////////////////////////////////////////////////////////////////////////////

class MCBrowserList : public MCBrowserRefCounted
{
public:
	MCBrowserList()
	{
		m_elements = nil;
		m_size = 0;
	}
	
	virtual ~MCBrowserList()
	{
		for (uint32_t i = 0; i < m_size; i++)
			MCBrowserValueClear(m_elements[i]);
		MCBrowserMemoryDeleteArray(m_elements);
	}
	
	uint32_t GetSize()
	{
		return m_size;
	}
	
	bool Expand(uint32_t p_size)
	{
		if (p_size <= m_size)
			return true;
		
		return MCBrowserMemoryResizeArray(p_size, m_elements, m_size);
	}
	
	bool GetType(uint32_t p_index, MCBrowserValueType &r_type)
	{
		if (p_index >= m_size)
			return false;
		
		r_type = m_elements[p_index].type;
		return true;
	}
	
	bool SetValue(uint32_t p_index, const MCBrowserValue &p_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueCopy(p_value, m_elements[p_index]);
	}
	
	bool GetValue(uint32_t p_index, MCBrowserValue &r_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueCopy(m_elements[p_index], r_value);
	}
	
	bool SetBoolean(uint32_t p_index, bool p_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueSetBoolean(m_elements[p_index], p_value);
	}
	
	bool GetBoolean(uint32_t p_index, bool &r_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueGetBoolean(m_elements[p_index], r_value);
	}
	
	bool SetInteger(uint32_t p_index, int32_t p_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueSetInteger(m_elements[p_index], p_value);
	}
	
	bool GetInteger(uint32_t p_index, int32_t &r_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueGetInteger(m_elements[p_index], r_value);
	}
	
	bool SetDouble(uint32_t p_index, double p_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueSetDouble(m_elements[p_index], p_value);
	}

	bool GetDouble(uint32_t p_index, double &r_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueGetDouble(m_elements[p_index], r_value);
	}
	
	bool SetString(uint32_t p_index, MCBrowserStringRef p_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueSetString(m_elements[p_index], p_value);
	}
	
	bool GetString(uint32_t p_index, MCBrowserStringRef &r_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueGetString(m_elements[p_index], r_value);
	}
	
	bool SetList(uint32_t p_index, MCBrowserListRef p_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueSetList(m_elements[p_index], p_value);
	}
	
	bool GetList(uint32_t p_index, MCBrowserListRef &r_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueGetList(m_elements[p_index], r_value);
	}
	
	bool SetDictionary(uint32_t p_index, MCBrowserDictionaryRef p_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueSetDictionary(m_elements[p_index], p_value);
	}
	
	bool GetDictionary(uint32_t p_index, MCBrowserDictionaryRef &r_value)
	{
		if (p_index >= m_size)
			return false;
		
		return MCBrowserValueGetDictionary(m_elements[p_index], r_value);
	}
	
	bool AppendValue(const MCBrowserValue &p_value)
	{
		uint32_t t_index;
		t_index = m_size;
		
		return Expand(m_size + 1) && SetValue(t_index, p_value);
	}
	
	bool AppendBoolean(bool p_value)
	{
		uint32_t t_index;
		t_index = m_size;
		
		return Expand(m_size + 1) && SetBoolean(t_index, p_value);
	}
	
	bool AppendInteger(int32_t p_value)
	{
		uint32_t t_index;
		t_index = m_size;
		
		return Expand(m_size + 1) && SetInteger(t_index, p_value);
	}
	
	bool AppendDouble(double p_value)
	{
		uint32_t t_index;
		t_index = m_size;
		
		return Expand(m_size + 1) && SetDouble(t_index, p_value);
	}
	
	bool AppendString(MCBrowserStringRef p_value)
	{
		uint32_t t_index;
		t_index = m_size;
		
		return Expand(m_size + 1) && SetString(t_index, p_value);
	}
	
	bool AppendList(MCBrowserListRef p_value)
	{
		uint32_t t_index;
		t_index = m_size;
		
		return Expand(m_size + 1) && SetList(t_index, p_value);
	}
	
	bool AppendDictionary(MCBrowserDictionaryRef p_value)
	{
		uint32_t t_index;
		t_index = m_size;
		
		return Expand(m_size + 1) && SetDictionary(t_index, p_value);
	}

private:
	MCBrowserValue *m_elements;
	uint32_t m_size;
};

////////////////////////////////////////////////////////////////////////////////

bool MCBrowserListCreate(MCBrowserListRef &r_browser, uint32_t p_size)
{
	MCBrowserList *t_browser;
	t_browser = new MCBrowserList();
	if (t_browser == nil)
		return false;
	
	if (!t_browser->Expand(p_size))
	{
		delete t_browser;
		return false;
	}
	
	r_browser = (MCBrowserListRef)t_browser;
	return true;
}

MCBrowserListRef MCBrowserListRetain(MCBrowserListRef p_list)
{
	if (p_list != nil)
		((MCBrowserList*)p_list)->Retain();
	
	return p_list;
}

void MCBrowserListRelease(MCBrowserListRef p_list)
{
	if (p_list != nil)
		((MCBrowserList*)p_list)->Release();
}

bool MCBrowserListGetSize(MCBrowserListRef p_list, uint32_t &r_size)
{
	if (p_list == nil)
		return false;
	
	r_size = ((MCBrowserList*)p_list)->GetSize();
	return true;
}

bool MCBrowserListGetType(MCBrowserListRef p_list, uint32_t p_index, MCBrowserValueType &r_type)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->GetType(p_index, r_type);
}

bool MCBrowserListSetValue(MCBrowserListRef p_list, uint32_t p_index, const MCBrowserValue &p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->SetValue(p_index, p_value);
}

bool MCBrowserListSetBoolean(MCBrowserListRef p_list, uint32_t p_index, bool p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->SetBoolean(p_index, p_value);
}

bool MCBrowserListSetInteger(MCBrowserListRef p_list, uint32_t p_index, int32_t p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->SetInteger(p_index, p_value);
}

bool MCBrowserListSetDouble(MCBrowserListRef p_list, uint32_t p_index, double p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->SetDouble(p_index, p_value);
}

bool MCBrowserListSetString(MCBrowserListRef p_list, uint32_t p_index, MCBrowserStringRef p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->SetString(p_index, p_value);
}

bool MCBrowserListSetList(MCBrowserListRef p_list, uint32_t p_index, MCBrowserListRef p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->SetList(p_index, p_value);
}

bool MCBrowserListSetDictionary(MCBrowserListRef p_list, uint32_t p_index, MCBrowserDictionaryRef p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->SetDictionary(p_index, p_value);
}

bool MCBrowserListAppendValue(MCBrowserListRef p_list, const MCBrowserValue &p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->AppendValue(p_value);
}

bool MCBrowserListAppendBoolean(MCBrowserListRef p_list, bool p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->AppendBoolean(p_value);
}

bool MCBrowserListAppendInteger(MCBrowserListRef p_list, int32_t p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->AppendInteger(p_value);
}

bool MCBrowserListAppendDouble(MCBrowserListRef p_list, double p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->AppendDouble(p_value);
}

bool MCBrowserListAppendString(MCBrowserListRef p_list, MCBrowserStringRef p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->AppendString(p_value);
}

bool MCBrowserListAppendList(MCBrowserListRef p_list, MCBrowserListRef p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->AppendList(p_value);
}

bool MCBrowserListAppendDictionary(MCBrowserListRef p_list, MCBrowserDictionaryRef p_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->AppendDictionary(p_value);
}

bool MCBrowserListGetValue(MCBrowserListRef p_list, uint32_t p_index, MCBrowserValue &r_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->GetValue(p_index, r_value);
}

bool MCBrowserListGetBoolean(MCBrowserListRef p_list, uint32_t p_index, bool &r_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->GetBoolean(p_index, r_value);
}

bool MCBrowserListGetInteger(MCBrowserListRef p_list, uint32_t p_index, int32_t &r_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->GetInteger(p_index, r_value);
}

bool MCBrowserListGetDouble(MCBrowserListRef p_list, uint32_t p_index, double &r_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->GetDouble(p_index, r_value);
}

bool MCBrowserListGetString(MCBrowserListRef p_list, uint32_t p_index, MCBrowserStringRef &r_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->GetString(p_index, r_value);
}

bool MCBrowserListGetList(MCBrowserListRef p_list, uint32_t p_index, MCBrowserListRef &r_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->GetList(p_index, r_value);
}

bool MCBrowserListGetDictionary(MCBrowserListRef p_list, uint32_t p_index, MCBrowserDictionaryRef &r_value)
{
	if (p_list == nil)
		return false;
	
	return ((MCBrowserList*)p_list)->GetDictionary(p_index, r_value);
}

////////////////////////////////////////////////////////////////////////////////

class MCBrowserDictionary : public MCBrowserRefCounted
{
public:
	MCBrowserDictionary()
	{
		m_elements = nil;
		m_keys = nil;
		m_capacity = 0;
		m_size = 0;
	}
	
	virtual ~MCBrowserDictionary()
	{
		for (uint32_t i = 0; i < m_size; i++)
			MCBrowserValueClear(m_elements[i]);
		for (uint32_t i = 0; i < m_size; i++)
			MCBrowserStringRelease(m_keys[i]);
		
		MCBrowserMemoryDeleteArray(m_elements);
		MCBrowserMemoryDeleteArray(m_keys);
	}
	
	bool GetKeys(MCBrowserStringRef *&r_keys, uint32_t &r_count)
	{
		r_keys = m_keys;
		r_count = m_size;
		
		return true;
	}
	
	bool Expand(uint32_t p_size)
	{
		if (p_size <= m_capacity)
			return true;
		
		uindex_t t_element_capacity, t_key_capacity;
		// Need to pass original capacity to BOTH calls to MCBrowserMemoryResizeArray, to ensure memory is appropriately cleared.
		t_element_capacity = t_key_capacity = m_capacity;
		if (MCBrowserMemoryResizeArray(p_size, m_elements, t_element_capacity) && MCBrowserMemoryResizeArray(p_size, m_keys, t_key_capacity))
		{
			m_capacity = t_element_capacity;
			return true;
		}
		
		return false;
	}
	
	bool FindElement(MCBrowserStringRef p_key, uint32_t &r_index)
	{
		for (uint32_t i = 0; i < m_size; i++)
		{
			if (MCBrowserStringIsEqualToCaseless(m_keys[i], p_key))
			{
				r_index = i;
				return true;
			}
		}
		
		return false;
	}
	
	bool EnsureElement(MCBrowserStringRef p_key, uint32_t &r_index)
	{
		if (FindElement(p_key, r_index))
			return true;
		
		if (!Expand(m_size + 1))
			return false;
		
		r_index = m_size;
		m_keys[m_size++] = MCBrowserStringRetain(p_key);
		
		return true;
	}
	
	bool GetType(MCBrowserStringRef p_key, MCBrowserValueType &r_type)
	{
		uint32_t t_index;
		if (!FindElement(p_key, t_index))
			return false;
		
		r_type = m_elements[t_index].type;
		return true;
	}
	
	bool SetValue(MCBrowserStringRef p_key, const MCBrowserValue &p_value)
	{
		uint32_t t_index;
		if (!EnsureElement(p_key, t_index))
			return false;
		
		return MCBrowserValueCopy(p_value, m_elements[t_index]);
	}
	
	bool GetValue(MCBrowserStringRef p_key, MCBrowserValue &r_value)
	{
		uint32_t t_index;
		if (!FindElement(p_key, t_index))
			return false;
		
		return MCBrowserValueCopy(m_elements[t_index], r_value);
	}
	
	bool SetBoolean(MCBrowserStringRef p_key, bool p_value)
	{
		uint32_t t_index;
		if (!EnsureElement(p_key, t_index))
			return false;
		
		return MCBrowserValueSetBoolean(m_elements[t_index], p_value);
	}
	
	bool GetBoolean(MCBrowserStringRef p_key, bool &r_value)
	{
		uint32_t t_index;
		if (!FindElement(p_key, t_index))
			return false;
		
		return MCBrowserValueGetBoolean(m_elements[t_index], r_value);
	}
	
	bool SetInteger(MCBrowserStringRef p_key, int32_t p_value)
	{
		uint32_t t_index;
		if (!EnsureElement(p_key, t_index))
			return false;
		
		return MCBrowserValueSetInteger(m_elements[t_index], p_value);
	}
	
	bool GetInteger(MCBrowserStringRef p_key, int32_t &r_value)
	{
		uint32_t t_index;
		if (!FindElement(p_key, t_index))
			return false;
		
		return MCBrowserValueGetInteger(m_elements[t_index], r_value);
	}
	
	bool SetDouble(MCBrowserStringRef p_key, double p_value)
	{
		uint32_t t_index;
		if (!EnsureElement(p_key, t_index))
			return false;
		
		return MCBrowserValueSetDouble(m_elements[t_index], p_value);
	}

	bool GetDouble(MCBrowserStringRef p_key, double &r_value)
	{
		uint32_t t_index;
		if (!FindElement(p_key, t_index))
			return false;
		
		return MCBrowserValueGetDouble(m_elements[t_index], r_value);
	}
	
	bool SetString(MCBrowserStringRef p_key, MCBrowserStringRef p_value)
	{
		uint32_t t_index;
		if (!EnsureElement(p_key, t_index))
			return false;
		
		return MCBrowserValueSetString(m_elements[t_index], p_value);
	}
	
	bool GetString(MCBrowserStringRef p_key, MCBrowserStringRef &r_value)
	{
		uint32_t t_index;
		if (!FindElement(p_key, t_index))
			return false;
		
		return MCBrowserValueGetString(m_elements[t_index], r_value);
	}
	
	bool SetList(MCBrowserStringRef p_key, MCBrowserListRef p_value)
	{
		uint32_t t_index;
		if (!EnsureElement(p_key, t_index))
			return false;
		
		return MCBrowserValueSetList(m_elements[t_index], p_value);
	}
	
	bool GetList(MCBrowserStringRef p_key, MCBrowserListRef &r_value)
	{
		uint32_t t_index;
		if (!FindElement(p_key, t_index))
			return false;
		
		return MCBrowserValueGetList(m_elements[t_index], r_value);
	}
	
	bool SetDictionary(MCBrowserStringRef p_key, MCBrowserDictionaryRef p_value)
	{
		uint32_t t_index;
		if (!EnsureElement(p_key, t_index))
			return false;
		
		return MCBrowserValueSetDictionary(m_elements[t_index], p_value);
	}
	
	bool GetDictionary(MCBrowserStringRef p_key, MCBrowserDictionaryRef &r_value)
	{
		uint32_t t_index;
		if (!FindElement(p_key, t_index))
			return false;
		
		return MCBrowserValueGetDictionary(m_elements[t_index], r_value);
	}
	
private:
	MCBrowserValue *m_elements;
	MCBrowserStringRef *m_keys;
	uint32_t m_capacity;
	uint32_t m_size;
};

////////////////////////////////////////////////////////////////////////////////

bool MCBrowserDictionaryCreate(MCBrowserDictionaryRef &r_dict, uint32_t p_size)
{
	MCBrowserDictionary *t_dict;
	t_dict = new MCBrowserDictionary();
	if (t_dict == nil)
		return false;
	
	if (!t_dict->Expand(p_size))
	{
		delete t_dict;
		return false;
	}
	
	r_dict = (MCBrowserDictionaryRef)t_dict;
	return true;
}

MCBrowserDictionaryRef MCBrowserDictionaryRetain(MCBrowserDictionaryRef p_dictionary)
{
	if (p_dictionary != nil)
		((MCBrowserDictionary*)p_dictionary)->Retain();
	
	return p_dictionary;
}

void MCBrowserDictionaryRelease(MCBrowserDictionaryRef p_dictionary)
{
	if (p_dictionary != nil)
		((MCBrowserDictionary*)p_dictionary)->Release();
}

bool MCBrowserDictionaryGetKeys(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef *&r_keys, uint32_t &r_count)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->GetKeys(r_keys, r_count);
}

/* WORKAROUND - Lack of Pointer dereferencing or C Array abstraction in LCB */
bool MCBrowserDictionaryGetKeyCount(MCBrowserDictionaryRef p_dictionary, uint32_t &r_count)
{
	MCBrowserStringRef *t_keys;
	return MCBrowserDictionaryGetKeys(p_dictionary, t_keys, r_count);
}

/* WORKAROUND - Lack of Pointer dereferencing or C Array abstraction in LCB */
bool MCBrowserDictionaryGetKey(MCBrowserDictionaryRef p_dictionary, uint32_t p_index, MCBrowserStringRef &r_key)
{
	MCBrowserStringRef *t_keys;
	uint32_t t_count;
	
	if (!MCBrowserDictionaryGetKeys(p_dictionary, t_keys, t_count))
		return false;
	
	if (p_index >= t_count)
		return false;
	
	r_key = t_keys[p_index];
	return true;
}

bool MCBrowserDictionaryGetType(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, MCBrowserValueType &r_type)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->GetType(p_key, r_type);
}

bool MCBrowserDictionarySetValue(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, const MCBrowserValue &p_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->SetValue(p_key, p_value);
}

bool MCBrowserDictionaryGetValue(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, MCBrowserValue &r_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->GetValue(p_key, r_value);
}

bool MCBrowserDictionarySetBoolean(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, bool p_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->SetBoolean(p_key, p_value);
}

bool MCBrowserDictionarySetInteger(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, int32_t p_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->SetInteger(p_key, p_value);
}

bool MCBrowserDictionarySetDouble(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, double p_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->SetDouble(p_key, p_value);
}

bool MCBrowserDictionarySetString(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, MCBrowserStringRef p_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->SetString(p_key, p_value);
}

bool MCBrowserDictionarySetList(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, MCBrowserListRef p_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->SetList(p_key, p_value);
}

bool MCBrowserDictionarySetDictionary(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, MCBrowserDictionaryRef p_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->SetDictionary(p_key, p_value);
}

bool MCBrowserDictionaryGetBoolean(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, bool &r_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->GetBoolean(p_key, r_value);
}

bool MCBrowserDictionaryGetInteger(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, int32_t &r_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->GetInteger(p_key, r_value);
}

bool MCBrowserDictionaryGetDouble(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, double &r_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->GetDouble(p_key, r_value);
}

bool MCBrowserDictionaryGetString(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, MCBrowserStringRef &r_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->GetString(p_key, r_value);
}

bool MCBrowserDictionaryGetList(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, MCBrowserListRef &r_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->GetList(p_key, r_value);
}

bool MCBrowserDictionaryGetDictionary(MCBrowserDictionaryRef p_dictionary, MCBrowserStringRef p_key, MCBrowserDictionaryRef &r_value)
{
	if (p_dictionary == nil)
		return false;
	
	return ((MCBrowserDictionary*)p_dictionary)->GetDictionary(p_key, r_value);
}

////////////////////////////////////////////////////////////////////////////////
