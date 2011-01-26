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

    /**
     * 2D Screen
     **/
    class QGL_EXPORT Screen
    {
    public:
        /**
         * Default Constructor
         *
         * This will create a screen with 640x480 size.
         **/
        Screen();

        /**
         * Constructor
         *
         * This will create a screen with initial size.
         *
         * @param size initial size
         **/
        Screen(const Vector2d& size);

        /**
         * Default destructor
         **/
        virtual ~Screen();

        /**
         * Get the size of the screen.
         **/
        const Vector2f& get_size() const;

        /**
         * Get the width of the screen.
         **/
        float get_width() const;

        /**
         * Get the height of the screen.
         **/
        float get_height() const;

        /**
         * Set the size of the screen.
         **/
        void set_size(const Vector2f& value);

        /**
         * Update the screen.
         **/
        // REVIEW: Does this even make sence?
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

        /**
         * Draw screen.
         **/
        virtual void draw(GraphicContext& graphic) const;

    protected:
        /**
         * Setup the fullscreen effect.
         *
         * This method is called prior to rendering the first pass. This
         * method should be overridden if the effect needs to change each
         * frame.
         **/
        virtual void setup_fullscreen_effect(GraphicContext& graphic) const;

        /**
         * Draw the actual contents of the screen.
         *
         * This method can be used to change rendering behavior. This method
         * calls each ScreenItem to render itsself.
         **/
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
