// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_SDLSENTRY_H_
#define _QGL_SDLSENTRY_H_

#include "config.h"

namespace qgl
{
    class QGL_EXPORT SdlSentry
    {
    public:
        /** Default constructor */
        SdlSentry();

        /** Default destructor */
        ~SdlSentry();
    private:
        static unsigned int ref_count;
    };
}

#endif
