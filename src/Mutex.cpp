// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Mutex.h"

#include <stdexcept>

namespace qgl
{
//------------------------------------------------------------------------------
    Mutex::Mutex()
    {
        mutex = SDL_CreateMutex();
        if (mutex == NULL)
        {
            throw std::runtime_error(SDL_GetError());
        }
    }

//------------------------------------------------------------------------------
    Mutex::~Mutex()
    {
        SDL_DestroyMutex(mutex);
    }

//------------------------------------------------------------------------------
    void Mutex::lock()
    {
        SDL_LockMutex(mutex);
    }

//------------------------------------------------------------------------------
    void Mutex::unlock()
    {
        SDL_UnlockMutex(mutex);
    }
}
