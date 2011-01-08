// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_SCREEN_ITEM_H_
#define _QGL_SCREEN_ITEM_H_

#include "config.h"

#include "Vector.h"
#include "Key.h"
#include "MouseButton.h"

namespace qgl
{
    class GraphicContext;

    /**
     * Screen Item
     **/
    class QGL_EXPORT ScreenItem
    {
    public:
        /** Default constructor */
        ScreenItem();

        /** Default destructor */
        virtual ~ScreenItem();

        const Vector2f& get_position() const;

        void set_position(const Vector2f& value);

        const Vector2f& get_size() const;

        void set_size(const Vector2f& value);

        void set_visible(bool value);

        bool get_visible() const;

        virtual void handle_mouse_move(Vector2ui pos, Vector2i rel);

        virtual void handle_mouse_down(MouseButton button, Vector2ui pos);

        virtual void handle_mouse_up(MouseButton button, Vector2ui pos);

        virtual void handle_key_down(Key key);

        virtual void handle_key_up(Key key);

        /**
         * Draw
         **/
        virtual void draw(GraphicContext& graphic) const;

    protected:
        Vector2f position;
        Vector2f size;
        bool visible;
    };
}

#endif
