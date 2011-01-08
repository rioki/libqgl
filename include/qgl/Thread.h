// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_THREAD_H_
#define _QGL_THREAD_H_

#include "config.h"

#include <SDL.h>
#include <sigc++/slot.h>

namespace qgl
{
    /**
     * Thread of execution.
     **/
    class QGL_EXPORT Thread
    {
    public:
        /**
         * Constructor
         *
         * @param slot the slot to execute in the thread function.
         **/
        Thread(sigc::slot<void> slot);

        /**
         * Destructor.
         **/
        ~Thread();

        /**
         * Join thread.
         **/
        void wait();

        /**
         * Kill the thread.
         **/
        void kill();

    private:
        sigc::slot<void> slot;
        SDL_Thread* thread;

    friend int threadfunc(void* data);
    };
}

#endif
