// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_SDL_NET_SENTRY_H_
#define _QGL_SDL_NET_SENTRY_H_

#include "config.h"

#include "SdlSentry.h"

namespace qgl
{
    class QGL_EXPORT SdlNetSentry : public SdlSentry
    {
    public:
        SdlNetSentry();

        SdlNetSentry(const SdlNetSentry&);

        ~SdlNetSentry();

        const SdlNetSentry& operator = (const SdlNetSentry&);

    private:
        static unsigned int use_count;
    };

}

#endif
