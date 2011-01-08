// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_LOCK_H_
#define _QGL_LOCK_H_

#include "config.h"

namespace qgl
{
    /**
     * Scope Lock
     *
     * A scope lock is a means to lock an object in a exception safe maner.
     * Just put an insante of Lock onto the stack and the wraped object gets
     * unlocked when the lock exits scope.
     **/
    template <typename Type>
    class Lock
    {
    public:
        /**
         * Lock the object.
         *
         * @param obj the object to lock
         **/
        Lock(Type& obj)
        : object(obj)
        {
            object.lock();
        }

        /**
         * Unlock the object.
         **/
        ~Lock()
        {
            object.unlock();
        }

    private:
        Type& object;

        Lock(const Lock<Type>&);
        const Lock<Type>& operator = (const Lock<Type>&);
    };

}

#endif
