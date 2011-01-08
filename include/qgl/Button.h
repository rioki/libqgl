// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_BUTTON_H_
#define _QGL_BUTTON_H_

#include "config.h"

#include <sigc++/signal.h>

#include "ScreenItem.h"
#include "Label.h"

namespace qgl
{

    class QGL_EXPORT Button : public ScreenItem
    {
    public:
        /** Default constructor */
        Button();

        /** Default destructor */
        ~Button();

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

        virtual void handle_mouse_up(MouseButton button, Vector2ui pos);

        /**
         * Draw the button.
         **/
        virtual void draw(GraphicContext& graphic) const;

        sigc::signal<void>& get_click_signal();

    private:
        Label label;
        sigc::signal<void> click_signal;
    };
}

#endif
