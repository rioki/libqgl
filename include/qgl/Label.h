// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_LABEL_H_
#define _QGL_LABEL_H_

#include "config.h"

#include "ScreenItem.h"

#include "Image.h"
#include "Font.h"

namespace qgl
{
    /**
     * Label
     **/
    class QGL_EXPORT Label : public ScreenItem
    {
    public:
        /**
         * Set the text.
         **/
        void set_font(const FontPtr& font);

        /**
         * Get the font.
         **/
        const FontPtr& get_font() const;

        /**
         * Set the text.
         **/
        void set_text(const std::string& text);

        /**
         * Get the text.
         **/
        const std::string& get_text() const;

        /**
         * Draw the button.
         **/
        virtual void draw(GraphicContext& graphic) const;

    private:
        FontPtr font;
        std::string text;

        ImagePtr text_image;
    };
}

#endif
