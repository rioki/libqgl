// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Entry.h"

#include <cmath>

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
        update_size();
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
        update_size();
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
        update_size();
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

//------------------------------------------------------------------------------
    void Entry::update_size()
    {
        if (background)
        {
            Vector2f size;
            size(0) = std::max<float>(background->get_width(), label.get_size()(0));
            size(1) = std::max<float>(background->get_height(), label.get_size()(1));
            set_size(size);
        }
        else
        {
            set_size(label.get_size());
        }
    }
}
