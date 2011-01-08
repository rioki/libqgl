// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "SdlSentry.h"

#include <stdexcept>
#include <SDL.h>
#include <SDL_ttf.h>

namespace qgl
{
    unsigned int SdlSentry::ref_count = 0;

//------------------------------------------------------------------------------
    SdlSentry::SdlSentry()
    {
        if (ref_count == 0)
        {
            if (SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                throw std::runtime_error(SDL_GetError());
            }
            if (TTF_Init() < 0)
            {
                throw std::runtime_error(TTF_GetError());
            }
        }
        ref_count++;
    }

//------------------------------------------------------------------------------
    SdlSentry::~SdlSentry()
    {
        ref_count--;
        if (ref_count == 0)
        {
            SDL_Quit();
        }
    }
}
