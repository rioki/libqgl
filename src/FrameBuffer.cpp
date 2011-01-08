// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "FrameBuffer.h"

#include <GL/glew.h>
#include <stdexcept>

namespace qgl
{
//------------------------------------------------------------------------------
    GLuint create_texture(unsigned int width, unsigned int height, unsigned int iformat, unsigned int format, unsigned int type)
    {
        GLuint ret;
        glGenTextures(1, &ret);
        glBindTexture(GL_TEXTURE_2D, ret);
        glTexImage2D(GL_TEXTURE_2D, 0, iformat, width, height, 0, format, type, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        return ret;
    }

//------------------------------------------------------------------------------
    FrameBufferPtr FrameBuffer::create(unsigned int width, unsigned int height)
    {
        return FrameBufferPtr(new FrameBuffer(width, height));
    }

//------------------------------------------------------------------------------
    FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
    : size(create_vector2(width, height))
    {
        if (GLEW_VERSION_3_0)
        {
            glGenFramebuffers(1, &fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);

            color_tex = create_texture(width, height, GL_RGBA8, GL_RGB, GL_UNSIGNED_BYTE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex, 0);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        else if (GLEW_EXT_framebuffer_object)
        {
            glGenFramebuffersEXT(1, &fbo);
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);

            color_tex = create_texture(width, height, GL_RGBA8, GL_RGB, GL_UNSIGNED_BYTE);
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex, 0);

            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        }
        else
        {
            throw std::runtime_error("This version of openGL does not support Framebuffers.");
        }
    }

//------------------------------------------------------------------------------
    FrameBuffer::~FrameBuffer()
    {
        if (GLEW_VERSION_3_0)
        {
            glDeleteFramebuffers(1, &fbo);
            glDeleteTextures(1, &color_tex);
        }
        else if (GLEW_EXT_framebuffer_object)
        {
            glDeleteFramebuffersEXT(1, &fbo);
            glDeleteTextures(1, &color_tex);
        }
    }

//------------------------------------------------------------------------------
    const Vector2ui& FrameBuffer::get_size() const
    {
        return size;
    }

//------------------------------------------------------------------------------
    unsigned int FrameBuffer::get_width() const
    {
        return size(0);
    }

//------------------------------------------------------------------------------
    unsigned int FrameBuffer::get_height() const
    {
        return size(1);
    }

//------------------------------------------------------------------------------
    void FrameBuffer::bind()
    {
        if (GLEW_VERSION_3_0)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        }
        else if (GLEW_EXT_framebuffer_object)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
        }
        else
        {
            // this condition is checked in the constructor
            assert(false && "This version of openGL does not support Framebuffers.");
        }
    }

//------------------------------------------------------------------------------
    void FrameBuffer::unbind()
    {
        if (GLEW_VERSION_3_0)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        else if (GLEW_EXT_framebuffer_object)
        {
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        }
        else
        {
            // this condition is checked in the constructor
            assert(false && "This version of openGL does not support Framebuffers.");
        }
    }

//------------------------------------------------------------------------------
    void FrameBuffer::bind_textures()
    {
        glEnable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, color_tex);
    }

//------------------------------------------------------------------------------
    void FrameBuffer::unbind_textures()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
}

