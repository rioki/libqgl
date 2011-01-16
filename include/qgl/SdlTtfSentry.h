// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_SDLTTFSENTRY_H_
#define _QGL_SDLTTFSENTRY_H_

#include "config.h"
#include "SdlSentry.h"

namespace qgl
{
    class QGL_EXPORT SdlTtfSentry : public SdlSentry
    {
    public:
        SdlTtfSentry();
        ~SdlTtfSentry();
    private:
        static unsigned int use_count;
    };
}

#endif
