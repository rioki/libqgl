// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_MATHEX_H_
#define _QGL_MATHEX_H_

#include <cmath>

namespace qgl
{
    /**
     * Check two values if they are close.
     **/
    template <typename T>
    bool close(T a, T b, T eps)
    {
        return std::abs(a - b) < eps;
    }
}

#endif
