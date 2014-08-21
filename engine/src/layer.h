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

#ifndef __MC_LAYER__
#define __MC_LAYER__

// This enum describes the 'hint' that is applied to the object via
// the 'layerMode' property. The engine uses this to derive the actual
// type of layer that will be used.
enum MCLayerModeHint
{
	// The object's layer should be considered to be rarely changing
	// and composited with the background wherever possible.
	kMCLayerModeHintStatic,
	// The object's layer should be considered to be rapidly changing
	// and cached independently.
	kMCLayerModeHintDynamic,
	// The object's layer should be considered to be scrolling, its
	// content cached independently and clipped to the bounds.
	kMCLayerModeHintScrolling,
	// The object's layer should be considered a union of its
	// children's layers, rather than a layer in its own right.
	kMCLayerModeHintContainer
};

struct MCLayerAttributes
{
	// MW-2011-08-24: [[ Layers ]] The layer id of the control.
	uint32_t id;
	
	// MW-2011-09-21: [[ Layers ]] The effective layerMode as used in the
	//   last frame.
	MCLayerModeHint mode : 3;
	// MW-2011-09-21: [[ Layers ]] Whether the layer should be considered
	//   completely opaque.
	bool is_opaque : 1;
	// MW-2011-09-21: [[ Layers ]] Whether the layer is a sprite or scenery
	//   layer.
	bool is_sprite : 1;
};

void MCLayerAttributesReset(MCLayerAttributes &x_attributes);
//MCLayerModeHint MCLayerAttributesCompute(MCLayerAttributes &x_attributes, bool p_is_unadorned);
bool MCLayerAttributesIsActive(const MCLayerAttributes &p_layer);

#endif /* __MC_LAYER__ */