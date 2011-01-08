// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Font.h"

#include <stdexcept>

#include "utils.h"

namespace qgl
{
//------------------------------------------------------------------------------
    Font::Font()
    : size(0), font(NULL) {}

//------------------------------------------------------------------------------
    Font::Font(const std::string& file, unsigned int size)
    : size(0), font(NULL)
    {
        load(file, size);
    }

//------------------------------------------------------------------------------
    Font::~Font()
    {
        TTF_CloseFont(font);
        font = NULL;
    }

//------------------------------------------------------------------------------
    std::string Font::get_file() const
    {
        return file;
    }

//------------------------------------------------------------------------------
    unsigned int Font::get_size() const
    {
        return size;
    }

//------------------------------------------------------------------------------
    void Font::load(const std::string& file, unsigned int size)
    {
        TTF_Font* font = TTF_OpenFont(file.c_str(), size);
        if (font == NULL)
            throw std::runtime_error(TTF_GetError());

        this->file = file;
        this->size = size;
        this->font = font;
    }

//------------------------------------------------------------------------------
    Vector2ui Font::estimate(const std::string& text) const
    {
        if (font == NULL)
            return create_vector2<unsigned int>(0, 0);

        int result = 0;
        int w = 0;
        int h = 0;

        if (text.empty())
            result = TTF_SizeUTF8(font, " ", &w, &h);
        else
            result = TTF_SizeUTF8(font, text.c_str(), &w, &h);

        if (result == 0)
            return create_vector2<unsigned int>(w, h);
        else
           throw std::logic_error(TTF_GetError());
    }

//------------------------------------------------------------------------------
    Vector2ui Font::estimate_multiline(const std::string& text) const
    {
        std::vector<std::string> lines = explode(text, "\n");
        Vector2ui result = create_vector2<unsigned int>(0,0);

        for (unsigned int i = 0; i < lines.size(); i++)
        {
            Vector2ui line_size = estimate(lines[i]);
            result(0) = std::max(result(0), line_size(0));
            result(1) += line_size(1);
        }

        return result;
    }

//------------------------------------------------------------------------------
    ImagePtr Font::render(const std::string& text) const
    {
        return render(text, create_vector3<float>(1.0, 1.0, 1.0));
    }

//------------------------------------------------------------------------------
    ImagePtr Font::render(const std::string& text, const Vector3f& color) const
    {
        if (font == NULL)
            throw std::logic_error("No font to render.");

        SDL_Surface* surface = NULL;

        SDL_Color sdl_color = {0};
        sdl_color.r = static_cast<unsigned int>(color(0) * 255);
        sdl_color.g = static_cast<unsigned int>(color(1) * 255);
        sdl_color.b = static_cast<unsigned int>(color(2) * 255);

        if (text.empty())
        {
            // SDL_ttf won't let us render an empty string, thus
            // we render a space.
            surface = TTF_RenderUTF8_Blended(font, " ", sdl_color);
        }
        else
        {
            surface = TTF_RenderUTF8_Blended(font, text.c_str(), sdl_color);
        }


        if (surface != NULL)
        {
            return ImagePtr(new Image(surface));
        }
        else
        {
            throw std::logic_error(TTF_GetError());
        }
    }

//------------------------------------------------------------------------------
    std::vector<ImagePtr> Font::render_multiline(const std::string& text) const
    {
        return render_multiline(text, create_vector3<float>(1.0, 1.0, 1.0));
    }

//------------------------------------------------------------------------------
    std::vector<ImagePtr> Font::render_multiline(const std::string& text, const Vector3f& color) const
    {
        std::vector<std::string> lines = explode(text, "\n");
        std::vector<ImagePtr> images;

        for (unsigned int i = 0; i < lines.size(); i++)
        {
            images.push_back(render(lines[i], color));
        }

        return images;
    }
}

