// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_UTILS_H_
#define _QGL_UTILS_H_

#include "config.h"

#include <vector>
#include <string>
#include <sstream>

#include "Vector.h"

namespace qgl
{
    /**
     * Draw a rectangle.
     **/
    QGL_EXPORT void draw_rect(float x, float y, float w, float h);

    /**
     * Draw a rectangle.
     **/
    QGL_EXPORT void draw_rect(const Vector2f& pos, const Vector2f& size);

    /**
     * Get a random foat.
     **/
    QGL_EXPORT float rand_float(float min, float max);

    QGL_EXPORT std::vector<std::string> explode(const std::string& str, const std::string& delimiter);

    template <typename T>
    std::string to_string(T value)
    {
        std::stringstream buff;
        buff << value;
        return buff.str();
    }

    QGL_EXPORT bool file_exists(const std::string& file);

    QGL_EXPORT std::string load_file(const std::string& file);

    // REVIEW: could we move this code to libConfig with params?
    QGL_EXPORT std::string get_config_filename();
}

#endif
