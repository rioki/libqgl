// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_FRAMEBUFFER_H_
#define _QGL_FRAMEBUFFER_H_

#include "config.h"

#include <tr1/memory>
#include <GL/glew.h>

#include "Vector.h"

namespace qgl
{
    class FrameBuffer;
    typedef std::tr1::shared_ptr<FrameBuffer> FrameBufferPtr;

    /**
     * Frame Buffer
     *
     * The current version of the framebuffer only supports color mapping, sich
     * take up the first texture slot.
     *
     * @todo Add a depth texture.
     **/
    class QGL_EXPORT FrameBuffer
    {
    public:

        static FrameBufferPtr create(unsigned int width, unsigned int height);

        /**
         * Constructor
         *
         * @param width
         * @param height
         *
         * @throw std::runtime_error
         * If the version of openGL on the given system does not support frame
         * buffers, std::runtime_error is thrown.
         *
         * @todo Add exception for unseported openGL features.
         **/
        FrameBuffer(unsigned int width, unsigned int height);

        /**
         * Destructor
         **/
        ~FrameBuffer();

        /**
         * Get the framebuffer's size.
         **/
        const Vector2ui& get_size() const;

        /**
         * Get the framebuffer's width.
         **/
        unsigned int get_width() const;

        /**
         * Get the framebuffer's height.
         **/
        unsigned int get_height() const;

        /**
         * Bind the framebuffer.
         **/
        void bind();

        /**
         * Unbind the framebuffer.
         **/
        void unbind();

        /**
         * Bind the textures of the frambuffer.
         **/
        void bind_textures();

        /**
         * Unbind the textures.
         **/
        void unbind_textures();

    private:
        Vector2ui size;
        GLuint fbo;
        GLuint color_tex;
    };
}

#endif // FRAMEBUFFER_H
