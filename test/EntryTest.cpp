// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include <UnitTest++/UnitTest++.h>

#include <qgl/Entry.h>
#include <qgl/Image.h>

SUITE(LabelTest)
{
//------------------------------------------------------------------------------
    TEST(default_constructor)
    {
        qgl::Entry entry;
    }

//------------------------------------------------------------------------------
    TEST(text)
    {
        qgl::Entry entry;

        entry.set_text("Hello world!");
        CHECK_EQUAL("Hello world!", entry.get_text());
    }

//------------------------------------------------------------------------------
    TEST(font)
    {
        qgl::Entry entry;

        qgl::FontPtr font = qgl::Font::load_from_file("test/DejaVuSans.ttf", 12);
        entry.set_font(font);
        CHECK(font == entry.get_font());
    }

//------------------------------------------------------------------------------
    TEST(background)
    {
        qgl::Entry entry;

        qgl::ImagePtr background = qgl::Image::load_from_file("test/label_bg.png");
        entry.set_background(background);
        CHECK(background == entry.get_background());

        qgl::Vector2f bg_size(background->get_width(), background->get_height());
        CHECK(qgl::close(bg_size, entry.get_size(), 1e-4f));
    }
}
