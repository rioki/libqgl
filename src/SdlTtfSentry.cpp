// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "SdlTtfSentry.h"

#include <SDL_ttf.h>
#include <stdexcept>

namespace qgl
{
    unsigned int SdlTtfSentry::use_count = 0;

//------------------------------------------------------------------------------
    SdlTtfSentry::SdlTtfSentry()
    {
        if (++use_count == 1)
        {
            if (TTF_Init() < 0)
            {
                throw std::runtime_error(TTF_GetError());
            }
        }
    }

//------------------------------------------------------------------------------
    SdlTtfSentry::~SdlTtfSentry()
    {
        if (--use_count == 0)
        {
            TTF_Quit();
        }
    }

}

