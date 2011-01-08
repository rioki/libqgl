// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "ColorFormat.h"

#include <iostream>

namespace qgl
{
//------------------------------------------------------------------------------
    std::ostream& operator << (std::ostream& os, ColorFormat cf)
    {
        switch (cf)
        {
            case NO_COLOR_FORMAT:
                os << "NO_COLOR_FORMAT";
                break;
            case RGB_COLOR_FORMAT:
                os << "RGB_COLOR_FORMAT";
                break;
            case RGBA_COLOR_FORMAT:
                os << "RGBA_COLOR_FORMAT";
                break;
            default:
                os << "ColorFormat(" << static_cast<unsigned int>(cf) << ")";
        }
        return os;
    }
}

