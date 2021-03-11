/* Copyright (C) 2021 LiveCode Ltd.

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

#import <Cocoa/Cocoa.h>

#include "foundation.h"
#include "foundation-objc.h"

bool MCMacPlatformDoAsAppleScript(MCStringRef p_script, MCStringRef &r_return_value, MCStringRef &r_error)
{
	bool t_success = true;
	NSAppleScript *t_script;
	
	if (t_success)
	{
		t_script = [[[NSAppleScript alloc] initWithSource:MCStringConvertToAutoreleasedNSString(p_script)] autorelease];
		t_success = t_script != nil;
	}
	
	if (t_success)
	{
		NSDictionary *t_error = nil;
		if (![t_script compileAndReturnError:&t_error])
		{
			t_success = MCStringCreateWithCFStringRef((CFStringRef)[t_error valueForKey:NSAppleScriptErrorMessage], r_error);
			return t_success;
		}
	}
	
	NSAppleEventDescriptor *t_return_value = nil;
	if (t_success)
	{
		NSDictionary *t_error = nil;
		t_return_value = [t_script executeAndReturnError:&t_error];
		if (nil == t_return_value)
		{
			t_success = MCStringCreateWithCFStringRef((CFStringRef)[t_error valueForKey:NSAppleScriptErrorMessage], r_error);
			return t_success;
		}
	}
	
	if (t_success)
	{
		NSString *t_return_string = [t_return_value stringValue];
		if (t_return_string != nil)
			t_success = MCStringCreateWithCFStringRef((CFStringRef)[t_return_value stringValue], r_return_value);
	}
	
	return t_success;
}

bool MCPlatformExecuteScript(MCStringRef p_script, MCStringRef p_language, MCStringRef &r_return_value, MCStringRef &r_error_message)
{
	if (MCStringIsEqualTo(p_language, MCSTR("applescript"), kMCStringOptionCompareCaseless))
		return MCMacPlatformDoAsAppleScript(p_script, r_return_value, r_error_message);
	
	return false;
}
