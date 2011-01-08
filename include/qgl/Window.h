// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_WINDOW_H_
#define _QGL_WINDOW_H_

#include "config.h"

#include <string>
#include <vector>
#include <sigc++/sigc++.h>

#include "SdlSentry.h"
#include "Vector.h"

namespace qgl
{
    class GraphicContext;

    /**
     * Window
     **/
    class QGL_EXPORT Window
    {
    public:
        /**
         * Get all valid resolutions this system can use.
         **/
        static std::vector<Vector2ui> get_valid_resolutions();

        Window(unsigned int width, unsigned int height, bool fullscreen);

        Window(const Vector2ui& size, bool fullscreen);

        ~Window();

        void set_video_mode(unsigned int width, unsigned int height, bool fullscreen);

        void set_video_mode(const Vector2ui& size, bool fullscreen);

        unsigned int get_width() const;

        unsigned int get_height() const;

        Vector2ui get_size() const;

        bool is_fullscreen() const;

        void set_caption(const std::string& value);

        std::string get_caption() const;

        void hide_cursor();

        void show_cursor();

        bool is_cursor_visible() const;

        GraphicContext& get_graphic_context();
        const GraphicContext& get_graphic_context() const;

        void draw();

        sigc::signal<void, GraphicContext&>& get_draw_signal();

    private:
        SdlSentry sdl_sentry;
        GraphicContext* graphic_context;

        sigc::signal<void, GraphicContext&> draw_signal;

        Window(const Window&);
        const Window& operator = (const Window&);
    };
}

#endif
