// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "Thread.h"

#include <stdexcept>
#include <iostream>

namespace qgl
{
//------------------------------------------------------------------------------
    int threadfunc(void* data)
    {
        try
        {
            Thread* thread = reinterpret_cast<Thread*>(data);
            thread->slot();
            return 0;
        }
        catch (const std::exception& ex)
        {
            std::cerr << "ERROR: " << ex.what() << std::endl;
            return -1;
        }
        catch (...)
        {
            std::cerr << "ERROR: Thread Crashed" << std::endl;
            return -1;
        }
    }

//------------------------------------------------------------------------------
    Thread::Thread(sigc::slot<void> s)
    : slot(s)
    {
        thread = SDL_CreateThread(&threadfunc, this);
        if (thread == NULL)
        {
            throw std::logic_error(SDL_GetError());
        }
    }

//------------------------------------------------------------------------------
    Thread::~Thread()
    {
        if (thread != NULL)
        {
            kill();
        }
    }

//------------------------------------------------------------------------------
    void Thread::wait()
    {
        SDL_WaitThread(thread, NULL);
        thread = NULL;
    }

//------------------------------------------------------------------------------
    void Thread::kill()
    {
        SDL_KillThread(thread);
        thread = NULL;
    }
}
