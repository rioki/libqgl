// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Entry.h"

#include "GraphicContext.h"

namespace qgl
{
//------------------------------------------------------------------------------
    Entry::Entry() {}

//------------------------------------------------------------------------------
    Entry::~Entry() {}

//------------------------------------------------------------------------------
    void Entry::set_text(const std::string& value)
    {
        label.set_text(value);
    }

//------------------------------------------------------------------------------
    const std::string& Entry::get_text() const
    {
        return label.get_text();
    }

//------------------------------------------------------------------------------
    void Entry::set_font(FontPtr value)
    {
        label.set_font(value);
    }

//------------------------------------------------------------------------------
    FontPtr Entry::get_font() const
    {
        return label.get_font();
    }

//------------------------------------------------------------------------------
    void Entry::set_background(ImagePtr value)
    {
        background = value;
        if (background)
        {
            set_size(Vector2f(background->get_width(), background->get_height()));
        }
    }

//------------------------------------------------------------------------------
    ImagePtr Entry::get_background() const
    {
        return background;
    }

//------------------------------------------------------------------------------
    void Entry::draw(GraphicContext& gc) const
    {
        gc.push_model_view_matrix();
        gc.translate(get_position());

        /*if (background)
        {
            gc.draw_image(background);
        }*/
        label.draw(gc);

        gc.pop_model_view_matrix();
    }
}
