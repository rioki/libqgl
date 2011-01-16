// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Image.h"

#include <cstring>
#include <stdexcept>

#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>

namespace qgl
{
//------------------------------------------------------------------------------
    ImagePtr Image::load_from_file(const std::string& file)
    {
        ImagePtr image(new Image(file));
        return image;
    }

//------------------------------------------------------------------------------
    Image::Image()
    : surface(NULL), loaded_opengl(false), gl_id(0) {}

//------------------------------------------------------------------------------
    Image::Image(const std::string& f)
    : surface(NULL), loaded_opengl(false), gl_id(0)
    {
        load(f);
    }

//------------------------------------------------------------------------------
    Image::Image(SDL_Surface* s)
    : surface(s), loaded_opengl(false), gl_id(0) {}

//------------------------------------------------------------------------------
    Image::~Image()
    {
        SDL_FreeSurface(surface);
        if (loaded_opengl)
        {
            glDeleteTextures(1, &gl_id);
        }
    }

//------------------------------------------------------------------------------
    const std::string& Image::get_file() const
    {
        return file;
    }

//------------------------------------------------------------------------------
    unsigned int Image::get_width() const
    {
        if (surface != NULL)
            return surface->w;
        else
            return 0;
    }

//------------------------------------------------------------------------------
    unsigned int Image::get_height() const
    {
        if (surface != NULL)
            return surface->h;
        else
            return 0;
    }

//------------------------------------------------------------------------------
    Vector2ui Image::get_size() const
    {
        return create_vector2(get_width(), get_height());
    }

//------------------------------------------------------------------------------
    ColorFormat Image::get_format() const
    {
        if (surface != NULL)
        {
            if (surface->format->BytesPerPixel == 3)
            {
                return RGB_COLOR_FORMAT;
            }
            else if (surface->format->BytesPerPixel == 4)
            {
                return RGBA_COLOR_FORMAT;
            }
            else
            {
                throw std::runtime_error("Unhandled color format.");
            }
        }
        else
        {
            throw std::runtime_error("No surface.");
        }
    }

//------------------------------------------------------------------------------
    const void* Image::get_data() const
    {
        if (surface != NULL)
        {
            return surface->pixels;
        }
        else
        {
            return NULL;
        }
    }

//------------------------------------------------------------------------------
    void Image::bind(unsigned int i) const
    {
        if (surface != NULL)
        {
            if (! loaded_opengl)
            {
                upload_to_opengl();
            }

            glEnable(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, gl_id);
        }
    }

//------------------------------------------------------------------------------
    void Image::unbind(unsigned int i) const
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }

//------------------------------------------------------------------------------
    void Image::upload_to_opengl() const
    {
        if (surface != NULL)
        {
            if (! loaded_opengl)
            {
                int mode = 0;
                if (get_format() == RGB_COLOR_FORMAT)
                    mode = GL_RGB;
                else if (get_format() == RGBA_COLOR_FORMAT)
                    mode = GL_RGBA;
                else
                    throw std::logic_error("qgl::opengl::TextureManager::load_image(): Unknoen pixel format.");

                //glEnable(GL_TEXTURE_2D);
                glGenTextures(1, &gl_id);

                glBindTexture(GL_TEXTURE_2D, gl_id);

                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                glTexImage2D(GL_TEXTURE_2D, 0, mode, get_width(), get_height(), 0, mode, GL_UNSIGNED_BYTE, get_data());

                //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                //gluBuild2DMipmaps(GL_TEXTURE_2D, 4, get_width(), get_height(), mode, GL_UNSIGNED_BYTE, get_data());

                loaded_opengl = true;
            }
        }
    }

//------------------------------------------------------------------------------
    void Image::load(const std::string& f)
    {
        surface = IMG_Load(f.c_str());
        if (surface == NULL)
        {
            throw std::runtime_error(IMG_GetError());
        }
        file = f;
    }
}

