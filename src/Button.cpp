// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Button.h"
#include "GraphicContext.h"

#include <GL/glew.h>

namespace qgl
{
//------------------------------------------------------------------------------
    Button::Button() {}

//------------------------------------------------------------------------------
    Button::~Button()
    {}

//------------------------------------------------------------------------------
    void Button::set_font(const FontPtr& f)
    {
        label.set_font(f);
        set_size(label.get_size());
    }

//------------------------------------------------------------------------------
    const FontPtr& Button::get_font() const
    {
        return label.get_font();
    }

//------------------------------------------------------------------------------
    void Button::set_text(const std::string& t)
    {
        label.set_text(t);
        set_size(label.get_size());
    }

//------------------------------------------------------------------------------
    const std::string& Button::get_text() const
    {
        return label.get_text();
    }

//------------------------------------------------------------------------------
    void Button::handle_mouse_up(MouseButton button, Vector2ui pos)
    {
        if (visible)
        {
            Vector2f min = position - (size * 0.5f);
            Vector2f max = position + (size * 0.5f);

            if (pos(0) > min(0) && pos(0) < max(0) &&
                pos(1) > min(1) && pos(1) < max(1))
            {
                click_signal.emit();
            }
        }
    }

//------------------------------------------------------------------------------
    void Button::draw(GraphicContext& graphic) const
    {
        if (visible)
        {
            glPushMatrix();
            glTranslatef(position(0), position(1), 0.0f);

            label.draw(graphic);

            glPopMatrix();
        }
    }

//------------------------------------------------------------------------------
    sigc::signal<void>& Button::get_click_signal()
    {
        return click_signal;
    }
}
