// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Screen.h"

#include <algorithm>
#include <stdexcept>

#include "GraphicContext.h"
#include "FrameBuffer.h"
#include "ScreenItem.h"

namespace qgl
{
//------------------------------------------------------------------------------
    Screen::Screen()
    : size(create_vector2(640.0f, 480.0f)) {}

//------------------------------------------------------------------------------
    Screen::Screen(const Vector2d& s)
    : size(s) {}

//------------------------------------------------------------------------------
    Screen::~Screen() {}

//------------------------------------------------------------------------------
    const Vector2f& Screen::get_size() const
    {
        return size;
    }

//------------------------------------------------------------------------------
    float Screen::get_width() const
    {
        return size(0);
    }

//------------------------------------------------------------------------------
    float Screen::get_height() const
    {
        return size(1);
    }

//------------------------------------------------------------------------------
    void Screen::set_size(const Vector2f& value)
    {
        size = value;
    }

//------------------------------------------------------------------------------
    void Screen::update()
    {

    }

//------------------------------------------------------------------------------
    void Screen::add_item(ScreenItem& item)
    {
        items.push_back(&item);
    }

//------------------------------------------------------------------------------
    void Screen::remove_item(ScreenItem& item)
    {
        std::list<ScreenItem*>::iterator iter = std::find(items.begin(), items.end(), &item);
        if (iter != items.end())
        {
            items.erase(iter);
        }
        else
        {
            throw std::logic_error("Trying to remove ScreenItem but that item is not on this screen.");
        }
    }

//------------------------------------------------------------------------------
    const ShaderPtr Screen::get_fullscreen_effect() const
    {
        return fullscreen_effect;
    }

//------------------------------------------------------------------------------
    void Screen::set_fullscreen_effect(ShaderPtr effect)
    {
        fullscreen_effect = effect;
    }

//------------------------------------------------------------------------------
    void Screen::handle_mouse_move(Vector2ui pos, Vector2i rel)
    {
        std::list<ScreenItem*>::iterator iter = items.begin();
        while (iter != items.end())
        {
            (*iter)->handle_mouse_move(pos, rel);
            iter++;
        }
    }

//------------------------------------------------------------------------------
    void Screen::handle_mouse_down(MouseButton button, Vector2ui pos)
    {
        std::list<ScreenItem*>::iterator iter = items.begin();
        while (iter != items.end())
        {
            (*iter)->handle_mouse_down(button, pos);
            iter++;
        }
    }

//------------------------------------------------------------------------------
    void Screen::handle_mouse_up(MouseButton button, Vector2ui pos)
    {
        std::list<ScreenItem*>::iterator iter = items.begin();
        while (iter != items.end())
        {
            (*iter)->handle_mouse_up(button, pos);
            iter++;
        }
    }

//------------------------------------------------------------------------------
    void Screen::handle_key_down(Key key)
    {
        std::list<ScreenItem*>::iterator iter = items.begin();
        while (iter != items.end())
        {
            (*iter)->handle_key_down(key);
            iter++;
        }
    }

//------------------------------------------------------------------------------
    void Screen::handle_key_up(Key key)
    {
        std::list<ScreenItem*>::iterator iter = items.begin();
        while (iter != items.end())
        {
            (*iter)->handle_key_down(key);
            iter++;
        }
    }

//------------------------------------------------------------------------------
    void Screen::draw(GraphicContext& graphic) const
    {
        graphic.clear_screen();

        if (fullscreen_effect)
        {
            if (frame_buffer1 == NULL)
            {
                frame_buffer1 = FrameBuffer::create(get_width(), get_height());
                frame_buffer2 = FrameBuffer::create(get_width(), get_height());
            }

            frame_buffer1->bind();
            // H4X:
            //graphic.push_viewport(0, 0, frame_buffer->get_width(), frame_buffer->get_height());
            float old_viewport[4];
            glGetFloatv(GL_VIEWPORT, old_viewport);

            glViewport(0, 0, 640, 480);
            graphic.clear_screen();

            draw_contents(graphic);

            frame_buffer1->unbind();

            // apply fullscreen effect
            frame_buffer2->bind();
            graphic.clear_screen();

            graphic.set_2d_projection(0, size(0), 0, size(1));
            frame_buffer1->bind_textures();

            fullscreen_effect->bind();

            setup_fullscreen_effect(graphic);

            graphic.draw_rect(size(0) / 2, size(1) / 2, size(0), size(1));
            fullscreen_effect->unbind();

            frame_buffer1->unbind_textures();

            frame_buffer2->unbind();

            // final pass
            glViewport(old_viewport[0], old_viewport[1], old_viewport[2], old_viewport[3]);

            frame_buffer2->unbind();

            graphic.set_2d_projection(0, size(0), 0, size(1));
            frame_buffer2->bind_textures();

            graphic.draw_rect(size(0) / 2, size(1) / 2, size(0), size(1));

            frame_buffer2->unbind_textures();
        }
        else
        {
            draw_contents(graphic);
        }
    }

//------------------------------------------------------------------------------
    void Screen::setup_fullscreen_effect(GraphicContext& graphic) const {}

//------------------------------------------------------------------------------
    void Screen::draw_contents(GraphicContext& graphic) const
    {
        graphic.set_2d_projection(0, size(0), size(1), 0);

        std::list<ScreenItem*>::const_iterator iter = items.begin();
        while (iter != items.end())
        {
            (*iter)->draw(graphic);
            iter++;
        }
    }
}
