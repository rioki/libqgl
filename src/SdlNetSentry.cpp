// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "SdlNetSentry.h"

#include <SDL_net.h>

namespace qgl
{
    unsigned int SdlNetSentry::use_count = 0;

//------------------------------------------------------------------------------
    SdlNetSentry::SdlNetSentry()
    {
        if (use_count++ == 0)
        {
            SDLNet_Init();
        }
    }

//------------------------------------------------------------------------------
    SdlNetSentry::SdlNetSentry(const SdlNetSentry&)
    {
        use_count++;
    }

//------------------------------------------------------------------------------
    SdlNetSentry::~SdlNetSentry()
    {
        if (--use_count == 0)
        {
            SDLNet_Quit();
        }
    }

//------------------------------------------------------------------------------
    const SdlNetSentry& SdlNetSentry::operator = (const SdlNetSentry&)
    {
        return *this;
    }
}
