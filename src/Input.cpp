// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Input.h"

#include <SDL.h>

namespace qgl
{
//------------------------------------------------------------------------------
    Input::Input(Window& w)
    : window(w) {}

//------------------------------------------------------------------------------
    sigc::signal<void>& Input::get_quit_signal()
    {
        return quit_signal;
    }

//------------------------------------------------------------------------------
    sigc::signal<void, Vector2ui, Vector2i>& Input::get_mouse_move_signal()
    {
        return mouse_move_signal;
    }

//------------------------------------------------------------------------------
    sigc::signal<void, MouseButton, Vector2ui>& Input::get_mouse_press_signal()
    {
        return mouse_press_signal;
    }

//------------------------------------------------------------------------------
    sigc::signal<void, MouseButton, Vector2ui>& Input::get_mouse_release_signal()
    {
        return mouse_release_signal;
    }

//------------------------------------------------------------------------------
    sigc::signal<void, Key>& Input::get_key_press_signal()
    {
        return key_press_signal;
    }

//------------------------------------------------------------------------------
    sigc::signal<void, Key>& Input::get_key_release_signal()
    {
        return key_release_signal;
    }

//------------------------------------------------------------------------------
    void Input::poll_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit_signal();
                break;
            case SDL_MOUSEMOTION:
                mouse_move_signal(create_vector2<unsigned int>(event.motion.x, event.motion.y), create_vector2<int>(event.motion.xrel, event.motion.yrel));
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouse_press_signal(static_cast<MouseButton>(event.button.button), create_vector2<unsigned int>(event.motion.x, event.motion.y));
                break;
            case SDL_MOUSEBUTTONUP:
                mouse_release_signal(static_cast<MouseButton>(event.button.button), create_vector2<unsigned int>(event.motion.x, event.motion.y));
                break;
            case SDL_KEYDOWN:
                key_press_signal(static_cast<Key>(event.key.keysym.sym));
                break;
            case SDL_KEYUP:
                key_release_signal(static_cast<Key>(event.key.keysym.sym));
                break;
            default:
                /* do nothing */
                break;
            }
        }
    }
}
