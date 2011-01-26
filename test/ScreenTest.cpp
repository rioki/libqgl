// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include <UnitTest++/UnitTest++.h>

#include <qgl/Screen.h>

SUITE(ScreenTest)
{
//------------------------------------------------------------------------------
    TEST(default_constructor)
    {
        qgl::Screen screen;
    }

//------------------------------------------------------------------------------
    TEST(default_size_is_640_480)
    {
        qgl::Screen screen;
        CHECK_EQUAL(qgl::Vector2f(640, 480), screen.get_size());
    }

//------------------------------------------------------------------------------
    TEST(initial_size)
    {
        qgl::Screen screen(qgl::Vector2f(100, 100));
        CHECK_EQUAL(qgl::Vector2f(100, 100), screen.get_size());
    }

//------------------------------------------------------------------------------
    TEST(resize)
    {
        qgl::Screen screen;
        screen.set_size(qgl::Vector2f(100, 100));
        CHECK_EQUAL(qgl::Vector2f(100, 100), screen.get_size());
    }


}
