// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_SCREEN_H_
#define _QGL_SCREEN_H_

#include "config.h"

#include <list>

#include "Vector.h"
#include "Key.h"
#include "MouseButton.h"
#include "Shader.h"
#include "FrameBuffer.h"

namespace qgl
{
    class ScreenItem;
    class GraphicContext;

    class QGL_EXPORT Screen
    {
    public:
        /** Default constructor */
        Screen();

        /** Default destructor */
        virtual ~Screen();

        const Vector2f& get_size() const;

        float get_width() const;

        float get_height() const;

        void set_size(const Vector2f& value);

        virtual void update();

        void add_item(ScreenItem& item);

        void remove_item(ScreenItem& item);

        const ShaderPtr get_fullscreen_effect() const;

        void set_fullscreen_effect(ShaderPtr effect);

        virtual void handle_mouse_move(Vector2ui pos, Vector2i rel);

        virtual void handle_mouse_down(MouseButton button, Vector2ui pos);

        virtual void handle_mouse_up(MouseButton button, Vector2ui pos);

        virtual void handle_key_down(Key key);

        virtual void handle_key_up(Key key);

        virtual void draw(GraphicContext& graphic) const;

    protected:
        virtual void setup_fullscreen_effect(GraphicContext& graphic) const;
        virtual void draw_contents(GraphicContext& graphic) const;

    private:
        Vector2f size;
        std::list<ScreenItem*> items;

        mutable FrameBufferPtr frame_buffer1;
        mutable FrameBufferPtr frame_buffer2;
        mutable ShaderPtr fullscreen_effect;
    };
}

#endif
