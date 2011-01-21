// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_WINSOCK_SENTRY_H_
#define _QGL_WINSOCK_SENTRY_H_

#ifdef _WIN32

#include "config.h"

namespace qgl
{
    class QGL_EXPORT WinSockSentry
    {
    public:
        WinSockSentry();

        ~WinSockSentry();

    private:
        static unsigned int use_count;

        WinSockSentry(const WinSockSentry&);
        const WinSockSentry& operator = (const WinSockSentry&);
    };

}

#endif
#endif
