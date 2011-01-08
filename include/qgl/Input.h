// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_INPUT_H_
#define _QGL_INPUT_H_

#include "config.h"

#include <sigc++/sigc++.h>

#include "Vector.h"
#include "Key.h"
#include "MouseButton.h"

namespace qgl
{
    class Window;

    /**
     * Input
     **/
    class QGL_EXPORT Input
    {
    public:
        Input(Window& window);

        sigc::signal<void>& get_quit_signal();

        sigc::signal<void, Vector2ui, Vector2i>& get_mouse_move_signal();

        sigc::signal<void, MouseButton, Vector2ui>& get_mouse_press_signal();

        sigc::signal<void, MouseButton, Vector2ui>& get_mouse_release_signal();

        sigc::signal<void, Key>& get_key_press_signal();

        sigc::signal<void, Key>& get_key_release_signal();

        /**
         * Poll all pending events.
         **/
        void poll_events();

    private:
        Window& window;

        sigc::signal<void> quit_signal;
        sigc::signal<void, Vector2ui, Vector2i> mouse_move_signal;
        sigc::signal<void, MouseButton, Vector2ui> mouse_press_signal;
        sigc::signal<void, MouseButton, Vector2ui> mouse_release_signal;
        sigc::signal<void, Key> key_press_signal;
        sigc::signal<void, Key> key_release_signal;

        Input(const Input&);
        const Input& operator = (const Input&);
    };
}

#endif // INPUT_H
