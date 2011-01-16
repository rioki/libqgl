// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Label.h"

#include "GraphicContext.h"

namespace qgl
{
//------------------------------------------------------------------------------
    void Label::set_font(const FontPtr& f)
    {
        font = f;
        if (font)
        {
            text_image = font->render(text);
            set_size(text_image->get_size());
        }
        else
        {
            text_image.reset();
        }
    }

//------------------------------------------------------------------------------
    const FontPtr& Label::get_font() const
    {
        return font;
    }

//------------------------------------------------------------------------------
    void Label::set_text(const std::string& t)
    {
        text = t;
        if (font)
        {
            text_image = font->render(text);
            set_size(text_image->get_size());
        }
        else
        {
            text_image.reset();
        }
    }

//------------------------------------------------------------------------------
    const std::string& Label::get_text() const
    {
        return text;
    }

//------------------------------------------------------------------------------
    void Label::draw(GraphicContext& graphic) const
    {
        if (visible && text_image)
        {
            graphic.enable_blending();
            graphic.draw_image(position, *text_image);
            graphic.disable_blending();
        }
    }

}
