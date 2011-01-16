// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "GraphicContext.h"

#include <stdexcept>
#include <GL/glew.h>

#include "FrameBuffer.h"
#include "Image.h"

#include "utils.h"

namespace qgl
{
//------------------------------------------------------------------------------
    GraphicContext::GraphicContext()
    : frame_buffer(NULL)
    {
        glewInit();
    }

//------------------------------------------------------------------------------
    GraphicContext::~GraphicContext()
    {
        delete frame_buffer;
    }

//------------------------------------------------------------------------------
    void GraphicContext::set_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
        glViewport(x, y, width, height);
    }

//------------------------------------------------------------------------------
    void GraphicContext::clear_screen()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

//------------------------------------------------------------------------------
    FrameBuffer& GraphicContext::get_frame_buffer()
    {
        if (frame_buffer == NULL)
        {
            // FIXME
            frame_buffer = new FrameBuffer(640, 480);
        }
        return *frame_buffer;
    }

//------------------------------------------------------------------------------
    void GraphicContext::set_2d_projection(float left, float right, float bottom, float top)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluOrtho2D(left, right, bottom, top);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

//------------------------------------------------------------------------------
    void GraphicContext::enable_blending()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

//------------------------------------------------------------------------------
    void GraphicContext::disable_blending()
    {
        glDisable(GL_BLEND);
    }

//------------------------------------------------------------------------------
    void GraphicContext::draw_rect(float x, float y, float w, float h)
    {
        glPushMatrix();
        glTranslatef(x, y, 0.0f);

        float w2 = w * 0.5f;
        float h2 = h * 0.5f;

        glBegin(GL_QUADS);

            glTexCoord2f(0.0, 0.0);
            glVertex2f(-w2, -h2);

            glTexCoord2f(1.0, 0.0);
            glVertex2f( w2, -h2);

            glTexCoord2f(1.0, 1.0);
            glVertex2f( w2,  h2);

            glTexCoord2f(0.0, 1.0);
            glVertex2f(-w2,  h2);

        glEnd();

        glPopMatrix();
    }

//------------------------------------------------------------------------------
    void GraphicContext::draw_rect(const Vector2f& pos, const Vector2f& size)
    {
        draw_rect(pos(0), pos(1), size(0), size(1));
    }

//------------------------------------------------------------------------------
    void GraphicContext::draw_image(float x, float y, const Image& image)
    {
        image.bind();
        draw_rect(x, y, image.get_width(), image.get_height());
        image.unbind();
    }

//------------------------------------------------------------------------------
    void GraphicContext::draw_image(Vector2f pos, const Image& image)
    {
        draw_image(pos(0), pos(1), image);
    }

//------------------------------------------------------------------------------
    void GraphicContext::draw_image(const Image& image)
    {
        draw_image(0, 0, image);
    }

//------------------------------------------------------------------------------
    void GraphicContext::push_model_view_matrix()
    {
        glPushMatrix();
    }

//------------------------------------------------------------------------------
    void GraphicContext::pop_model_view_matrix()
    {
        glPopMatrix();
    }

//------------------------------------------------------------------------------
    void GraphicContext::translate(const Vector2f& value)
    {
        glTranslatef(value(0), value(1), 0.0f);
    }

//------------------------------------------------------------------------------
    void GraphicContext::swap_buffers()
    {
        SDL_GL_SwapBuffers();
    }
}
