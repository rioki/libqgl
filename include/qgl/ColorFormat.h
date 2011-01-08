// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_COLOR_FORMAT_H_
#define _QGL_COLOR_FORMAT_H_

#include "config.h"

#include <iosfwd>

namespace qgl
{
    /**
     * Color Format
     **/
    enum ColorFormat
    {
        NO_COLOR_FORMAT,
        RGB_COLOR_FORMAT,
        RGBA_COLOR_FORMAT
    };

    QGL_EXPORT std::ostream& operator << (std::ostream& os, ColorFormat cf);
}

#endif
