// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Window.h"

#include <SDL.h>
#include <GL/glew.h>

#include <stdexcept>

#include "GraphicContext.h"

namespace qgl
{
//------------------------------------------------------------------------------
    std::vector<Vector2ui> Window::get_valid_resolutions()
    {
        std::vector<Vector2ui> result;

        SDL_Rect **modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_OPENGL);
        for(unsigned int i = 0; modes[i] != NULL; ++i)
        {
            result.push_back(create_vector2(modes[i]->w, modes[i]->h));
        }
        return result;
    }

//------------------------------------------------------------------------------
    Window::Window(unsigned int width, unsigned int height, bool fullscreen)
    : graphic_context(NULL)
    {
        set_video_mode(width, height, fullscreen);
    }

//------------------------------------------------------------------------------
    Window::Window(const Vector2ui& size, bool fullscreen)
    : graphic_context(NULL)
    {
        set_video_mode(size, fullscreen);
    }

//------------------------------------------------------------------------------
    Window::~Window()
    {
        if (graphic_context != NULL)
        {
            delete graphic_context;
        }
    }

//------------------------------------------------------------------------------
    void Window::set_video_mode(unsigned int width, unsigned int height, bool fullscreen)
    {
        if (graphic_context != NULL)
        {
            delete graphic_context;
            graphic_context = NULL;
        }

        SDL_Surface* screen = SDL_SetVideoMode(width, height, 0, fullscreen ? SDL_OPENGL | SDL_FULLSCREEN : SDL_OPENGL);
        if (!screen)
        {
            throw std::runtime_error(SDL_GetError());
        }

        graphic_context = new GraphicContext;
        graphic_context->set_viewport(0, 0, width, height);
    }

//------------------------------------------------------------------------------
    void Window::set_video_mode(const Vector2ui& size, bool fullscreen)
    {
        set_video_mode(size(0), size(1), fullscreen);
    }

//------------------------------------------------------------------------------
    unsigned int Window::get_width() const
    {
        SDL_Surface* screen = SDL_GetVideoSurface();
        if (!screen)
        {
            throw std::runtime_error(SDL_GetError());
        }
        return screen->w;
    }

//------------------------------------------------------------------------------
    unsigned int Window::get_height() const
    {
        SDL_Surface* screen = SDL_GetVideoSurface();
        if (!screen)
        {
            throw std::runtime_error(SDL_GetError());
        }
        return screen->h;
    }

//------------------------------------------------------------------------------
    Vector2ui Window::get_size() const
    {
        return create_vector2(get_width(), get_height());
    }

//------------------------------------------------------------------------------
    bool Window::is_fullscreen() const
    {
        SDL_Surface* screen = SDL_GetVideoSurface();
        if (!screen)
        {
            throw std::runtime_error(SDL_GetError());
        }
        return (screen->flags & SDL_FULLSCREEN) != 0;
    }

//------------------------------------------------------------------------------
    void Window::set_caption(const std::string& value)
    {
        SDL_WM_SetCaption(value.c_str(), value.c_str());
    }

//------------------------------------------------------------------------------
    std::string Window::get_caption() const
    {
        char* buff = NULL;
        SDL_WM_GetCaption(&buff, NULL);
        if (buff != NULL)
            return std::string(buff);
        else
            return std::string();
    }

//------------------------------------------------------------------------------
    void Window::hide_cursor()
    {
        SDL_ShowCursor(SDL_DISABLE);
    }

//------------------------------------------------------------------------------
    void Window::show_cursor()
    {
        SDL_ShowCursor(SDL_ENABLE);
    }

//------------------------------------------------------------------------------
    bool Window::is_cursor_visible() const
    {
        return SDL_ShowCursor(SDL_QUERY) != SDL_ENABLE;
    }

//------------------------------------------------------------------------------
    GraphicContext& Window::get_graphic_context()
    {
        return *graphic_context;
    }

//------------------------------------------------------------------------------
    const GraphicContext& Window::get_graphic_context() const
    {
        return *graphic_context;
    }

//------------------------------------------------------------------------------
    void Window::draw()
    {
        draw_signal(*graphic_context);
        SDL_GL_SwapBuffers();
    }

//------------------------------------------------------------------------------
    sigc::signal<void, GraphicContext&>& Window::get_draw_signal()
    {
        return draw_signal;
    }
}
