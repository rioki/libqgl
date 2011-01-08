// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_MUTEX_H_
#define _QGL_MUTEX_H_

#include "config.h"

#include <SDL.h>

namespace qgl
{
    /**
     * Mutual exculsion lock.
     **/
    class QGL_EXPORT Mutex
    {
    public:

        /**
         * Constructor
         **/
        Mutex();

        /**
         * Destructor
         **/
        ~Mutex();

        /**
         * Lock the mutex.
         **/
        void lock();

        /**
         * Unlock the mutex.
         **/
        void unlock();

    private:
        SDL_mutex* mutex;

        Mutex(const Mutex&);
        const Mutex& operator = (const Mutex&);
    };
}

#endif
