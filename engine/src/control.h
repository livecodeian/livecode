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

//
// Base class for all control objects
//
#ifndef	CONTROL_H
#define	CONTROL_H
#define __CONTROL_H

#include "object.h"
#include "layer.h"

class MCControl : public MCObject
{
protected:
	int2 mx;
	int2 my;
	int2 leftmargin;
	int2 rightmargin;
	int2 topmargin;
	int2 bottommargin;
	
	MCBitmapEffectsRef m_bitmap_effects;

	// MW-2011-09-21: [[ Layers ]] Whether something about the control has
	//   changed requiring a recompute the layer attributes.
	bool m_layer_attr_changed : 1;
	// MW-2011-09-21: [[ Layers ]] The layerMode as specified by the user
	MCLayerModeHint m_layer_mode_hint : 3;
	// IM-2014-08-20: [[ Layers ]] The layer attributes of this object
	MCLayer m_layer;
//	MCLayer *m_layers;
//	uint32_t m_layer_count;

	static int2 defaultmargin;
	static int2 xoffset;
	static int2 yoffset;
	static MCControl *focused;
	static double aspect;

public:
	MCControl();
	MCControl(const MCControl &cref);
	~MCControl();

	// virtual functions from MCObject
	virtual void open();
	virtual void close();
	virtual void kfocus();
	virtual void kunfocus();
	virtual Boolean kdown(const char *string, KeySym key);
	virtual Boolean mfocus(int2 x, int2 y);
	virtual void munfocus();
	virtual Boolean doubledown(uint2 which);
	virtual Boolean doubleup(uint2 which);
	virtual void timer(MCNameRef mptr, MCParameter *params);
	virtual uint2 gettransient() const;

	// MW-2011-11-23: [[ Array Chunk Props ]] Add 'effective' param to arrayprop access.
	virtual Exec_stat getprop(uint4 parid, Properties which, MCExecPoint &, Boolean effective);
	virtual Exec_stat getarrayprop(uint4 parid, Properties which, MCExecPoint &, MCNameRef key, Boolean effective);
	virtual Exec_stat setprop(uint4 parid, Properties which, MCExecPoint &, Boolean effective);
	virtual Exec_stat setarrayprop(uint4 parid, Properties which, MCExecPoint&, MCNameRef key, Boolean effective);

	virtual void select();
	virtual void deselect();
	virtual Boolean del();
	virtual void paste(void);

	virtual void undo(Ustruct *us);

	// MW-2011-09-06: [[ Redraw ]] Added 'sprite' option - if true, ink and opacity are not set.
	virtual void draw(MCDC *dc, const MCRectangle &dirty, bool p_isolated, bool p_sprite) = 0;

	virtual IO_stat save(IO_handle stream, uint4 p_part, bool p_force_ext);
	virtual Boolean kfocusset(MCControl *target);
	virtual MCControl *clone(Boolean attach, Object_pos p, bool invisible);
	virtual MCControl *findnum(Chunk_term type, uint2 &num);
	virtual MCControl *findname(Chunk_term type, const MCString &);
	virtual MCControl *findid(Chunk_term type, uint4 inid, Boolean alt);
	virtual Boolean count(Chunk_term otype, MCObject *stop, uint2 &num);
	virtual Boolean maskrect(const MCRectangle &srect);
	virtual void installaccels(MCStack *stack);
	virtual void removeaccels(MCStack *stack);
	virtual MCCdata *getdata(uint4 cardid, Boolean clone);
	virtual void replacedata(MCCdata *&data, uint4 newid);
	virtual void compactdata();
	virtual void resetfontindex(MCStack *oldstack);
	virtual Exec_stat hscroll(int4 offset, Boolean doredraw);
	virtual Exec_stat vscroll(int4 offset, Boolean doredraw);
	virtual void readscrollbars();
	virtual void setsbrects();
	virtual void resetscrollbars(Boolean move);
	virtual void fliph();
	virtual void flipv();
	virtual void getwidgetthemeinfo(MCWidgetInfo &widgetinfo);
	virtual void unlink(MCControl *p_control);
	
	virtual MCObject *hittest(int32_t x, int32_t y);

	IO_stat save_extended(IO_handle p_stream, const MCString& p_data, uint4 p_part);

	// MCControl functions
	void attach(Object_pos p, bool invisible);

	void redraw(MCDC *dc, const MCRectangle &dirty);

	void sizerects(MCRectangle *rects);
	void drawselected(MCDC *dc);
	void drawarrow(MCDC *dc, int2 x, int2 y, uint2 size,
	               Arrow_direction dir, Boolean border, Boolean hilite);
	void continuesize(int2 x, int2 y);
	uint2 sizehandles();
	void start(Boolean canclone);
	void end(bool p_send_mouse_up, bool p_release);
	void create(int2 x, int2 y);
	Boolean moveable();
	void newmessage();
	void enter();
	void leave();
	void hblt(MCRectangle &drect, int4 offset);
	void vblt(MCRectangle &drect, int4 offset);
	Boolean sbfocus(int2 x, int2 y, MCScrollbar *hsb, MCScrollbar *vsb);
	Boolean sbdown(uint2 which, MCScrollbar *hsb, MCScrollbar *vsb);
	Boolean sbup(uint2 which, MCScrollbar *hsb, MCScrollbar *vsb);
	Boolean sbdoubledown(uint2 which, MCScrollbar *hsb, MCScrollbar *vsb);
	Boolean sbdoubleup(uint2 which, MCScrollbar *hsb, MCScrollbar *vsb);
	Exec_stat setsbprop(Properties which, const MCString &data, int4 tx, int4 ty,
	                    uint2 &sbw, MCScrollbar *&hsb, MCScrollbar *&vsb,
	                    Boolean &dirty);

	void drawfocus(MCDC* p_dc, const MCRectangle& p_dirty);

	void grab();
	void ungrab(uint2 which);

	// MW-2009-06-11: [[ Bitmap Effects ]] This call computes the pixel bounds of the
	//   control, rather than just its active bounds. (Some effects extend outside of
	//   a control's boundary).
	virtual MCRectangle geteffectiverect(void) const;

	// MW-2009-08-24: Accessor for bitmap effects to allow saving in MCObject.
	MCBitmapEffectsRef getbitmapeffects(void);
	void setbitmapeffects(MCBitmapEffectsRef bitmap_effects);

	// This method computes the area of effect of a stack for the current bitmap
	// effects applied to this control (and its parents) when using the given rect.
	MCRectangle computeeffectsrect(const MCRectangle& area) const;

	// MW-2011-08-18: [[ Layers ]] Mark the whole object's layer as needing redrawn.
	void layer_redrawall(void);
	// MW-2011-08-18: [[ Layers ]] Mark a portion of the object's layer as needing redrawn.
	void layer_redrawrect(const MCRectangle& rect);
	// MW-2011-08-18: [[ Layers ]] Take note of any changes to 'transient' and mark the whole object's layer as needing redrawn.
	void layer_transientchangedandredrawall(int32_t old_transient);
	// MW-2011-08-18: [[ Layers ]] Set the rect of the control, invalidating as necessary.
	void layer_setrect(const MCRectangle& new_rect, bool redrawall);
	// MW-2011-08-18: [[ Layers ]] Take note of the fact that the rect has changed and invalidate the layer.
	void layer_rectchanged(const MCRectangle& old_rect, bool redrawall);
	// MW-2011-08-18: [[ Layers [[ Take note of the fact that the effective rect has changed and invalidate the layer.
	void layer_effectiverectchangedandredrawall(const MCRectangle& old_effective_rect);
	// MW-2011-08-18: [[ Layers ]] Take note of any changes in effects, only invalidating as necessary.
	void layer_effectschanged(const MCRectangle& old_effective_rect);
	// MW-2011-09-30: [[ Layers ]] The content origin has changed by the given amount.
	void layer_contentoriginchanged(int32_t dx, int32_t dy);
	// MW-2011-08-18: [[ Layers ]] Take note of a change in visibility.
	void layer_visibilitychanged(const MCRectangle& old_effective_rect);
	// MW-2011-09-26: [[ Layers ]] Mark the layer as having scrolled.
	void layer_scrolled(void);
	
	// MW-2011-10-04: [[ Layers ]] Used internally to apply an update. If 'update_card' is
	//   true then the dirty rect of the stack will be updated too.
	void layer_dirtyeffectiverect(const MCRectangle& effective_rect, bool update_card);
	// MW-2011-08-24: [[ Layers ]] Used internally to apply a size change. If 'update_card' is
	//   true then the dirty rect of the stack will be updated too.
	void layer_changeeffectiverect(const MCRectangle& old_effective_rect, bool force_update, bool update_card);
	// MW-2011-09-07: [[ Layers ]] Used internally to apply an update to a scrolling layer. If
	//   'update_card' is true then the dirty rect of the stack will be updated too.
	void layer_dirtycontentrect(const MCRectangle& content_rect, bool update_card);

	// MW-2011-09-22: [[ Layers ]] Returns the layer mode hint.
	MCLayerModeHint layer_getmodehint(void) { return m_layer_mode_hint; }
	// MW-2011-11-24: [[ LayerMode Save ]] Sets the layer mode hint (used by object unpickling).
	void layer_setmodehint(MCLayerModeHint p_mode) { m_layer_mode_hint = p_mode; m_layer_attr_changed = true; }
	// MW-2011-09-21: [[ Layers ]] Calculates the effective layer mode.
	MCLayerModeHint layer_geteffectivemode(void) { return layer_computeattrs(false); }
	// MW-2011-09-07: [[ Layers ]] Returns the content rect of the layer (if scrolling).
	MCRectangle layer_getcontentrect(void);

	bool layer_is_active(void) { return MCLayerIsActive(m_layer); }
	
	// MW-2011-09-21: [[ Layers ]] Returns whether the layer is a sprite or not.
	bool layer_issprite(void) { return m_layer.is_sprite; }
	// MW-2011-09-21: [[ Layers ]] Returns whether the layer is scrolling or not.
	bool layer_isscrolling(void) { return m_layer.mode == kMCLayerModeHintScrolling; }

	// MW-2011-09-21: [[ Layers ]] Make sure the layerMode attr's are accurate.
	MCLayerModeHint layer_computeattrs(bool commit);

	virtual bool layer_compute_unadorned(void);
	virtual bool layer_compute_opaque(void);
	virtual MCLayerModeHint layer_compute_mode(bool p_unadorned, bool p_opaque);
	
	// MW-2011-09-21: [[ Layers ]] Reset the attributes to defaults.
	void layer_resetattrs(void);
	
	virtual bool layer_getlayers(MCLayer *&r_layers, uint32_t &r_count);
	
	virtual void render(MCTileCacheRef p_tilecache, const MCRectangle &p_clip, const MCGAffineTransform &p_device_transform, bool p_reset_layers);

	static MCControl *getfocused()
	{
		return focused;
	}

	uint2 getstyle()
	{
		return getstyleint(flags);
	}

	uint2 getleftmargin() const
	{
		return leftmargin;
	}

	uint2 getrightmargin() const
	{
		return rightmargin;
	}

	MCControl *next()
	{
		return (MCControl *)MCDLlist::next();
	}

	MCControl *prev()
	{
		return (MCControl *)MCDLlist::prev();
	}

	void totop(MCControl *&list)
	{
		MCDLlist::totop((MCDLlist *&)list);
	}

	void insertto(MCControl *&list)
	{
		MCDLlist::insertto((MCDLlist *&)list);
	}

	void appendto(MCControl *&list)
	{
		MCDLlist::appendto((MCDLlist *&)list);
	}

	void append(MCControl *node)
	{
		MCDLlist::append((MCDLlist *)node);
	}

	void splitat(MCControl *node)
	{
		MCDLlist::splitat((MCDLlist *)node);
	}

	MCControl *remove(MCControl *&list)
	{
		return (MCControl *)MCDLlist::remove((MCDLlist *&)list);
	}
};
#endif
