// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "ScreenItem.h"

namespace qgl
{
//------------------------------------------------------------------------------
    ScreenItem::ScreenItem()
    : position(create_vector2(0.0f, 0.0f)), size(create_vector2(15.0f, 15.0f)),
      visible(true) {}

//------------------------------------------------------------------------------
    ScreenItem::~ScreenItem() {}

//------------------------------------------------------------------------------
    const Vector2f& ScreenItem::get_position() const
    {
        return position;
    }

//------------------------------------------------------------------------------
    void ScreenItem::set_position(const Vector2f& value)
    {
        position = value;
    }

//------------------------------------------------------------------------------
    const Vector2f& ScreenItem::get_size() const
    {
        return size;
    }

//------------------------------------------------------------------------------
    void ScreenItem::set_size(const Vector2f& value)
    {
        size = value;
    }

//------------------------------------------------------------------------------
    void ScreenItem::set_visible(bool value)
    {
        visible = value;
    }

//------------------------------------------------------------------------------
    bool ScreenItem::get_visible() const
    {
        return visible;
    }

//------------------------------------------------------------------------------
    void ScreenItem::handle_mouse_move(Vector2ui pos, Vector2i rel) {}

//------------------------------------------------------------------------------
    void ScreenItem::handle_mouse_down(MouseButton button, Vector2ui pos) {}

//------------------------------------------------------------------------------
    void ScreenItem::handle_mouse_up(MouseButton button, Vector2ui pos) {}

//------------------------------------------------------------------------------
    void ScreenItem::handle_key_down(Key key) {}

//------------------------------------------------------------------------------
    void ScreenItem::handle_key_up(Key key) {}

//------------------------------------------------------------------------------
    void ScreenItem::draw(GraphicContext& graphic) const {}
}

