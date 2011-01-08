// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_GRAPHIC_SYSTEM_H_
#define _QGL_GRAPHIC_SYSTEM_H_

#include "config.h"

#include <string>

#include "SdlSentry.h"
#include "Shader.h"
#include "Vector.h"

namespace qgl
{
    class FrameBuffer;
    class Image;

    /**
     * GraphicContext
     **/
    class QGL_EXPORT GraphicContext
    {
    public:
        /**
         * Create GraphicContext.
         **/
        GraphicContext();

        ~GraphicContext();

        void set_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

        void clear_screen();

        FrameBuffer& get_frame_buffer();

        void set_2d_projection(float left, float right, float bottom, float top);

        void enable_blending();

        void disable_blending();

        void draw_rect(float x, float y, float width, float height);

        void draw_rect(const Vector2f& pos, const Vector2f& size);


        void draw_image(float x, float y, const Image& image);

        void draw_image(Vector2f pos, const Image& image);

        void swap_buffers();

    private:
        SdlSentry sdl_sentry;

        FrameBuffer* frame_buffer;
    };
}

#endif // GraphicContext_H
