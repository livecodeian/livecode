/* Copyright (C) 2003-2014 Runtime Revolution Ltd.
 
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

#include "prefix.h"

#include "core.h"

#include "graphics.h"
#include "graphics_util.h"

#include "layer.h"

////////////////////////////////////////////////////////////////////////////////

void MCLayerReset(MCLayer &x_layer)
{
	x_layer.id = 0;
	x_layer.mode = kMCLayerModeHintStatic;
	x_layer.is_opaque = false;
	x_layer.is_sprite = false;
	
	x_layer.region = x_layer.clip = MCRectangle32Make(0, 0, 0, 0);
}

bool MCLayerIsActive(const MCLayer &p_layer)
{
	return p_layer.id != 0;
}

////////////////////////////////////////////////////////////////////////////////
