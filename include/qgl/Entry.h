// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_ENTRY_H_
#define _QGL_ENTRY_H_

#include <string>

#include "config.h"

#include "ScreenItem.h"
#include "Label.h"
#include "Image.h"
#include "Font.h"

namespace qgl
{
    /**
     * Single line text entry field.
     **/
    class QGL_EXPORT Entry : public ScreenItem
    {
    public:
        /**
         * Constructor
         **/
        Entry();

        /**
         * Destructor
         **/
        ~Entry();

        /**
         * Set the text.
         **/
        void set_text(const std::string& value);

        /**
         * Get the text.
         **/
        const std::string& get_text() const;

        /**
         * Set the font.
         **/
        void set_font(FontPtr value);

        /**
         * Get the font.
         **/
        FontPtr get_font() const;

        /**
         * Set the background.
         **/
        void set_background(ImagePtr value);

        /**
         * Get the background.
         **/
        ImagePtr get_background() const;

        /**
         * Draw the entry.
         **/
        void draw(GraphicContext& gc) const;

    private:
        Label label;
        ImagePtr background;
    };
}

#endif
