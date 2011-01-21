// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "WinSockSentry.h"

#ifdef _WIN32

#include <winsock2.h>
#include <stdexcept>

namespace qgl
{
    unsigned int WinSockSentry::use_count = 0;

//------------------------------------------------------------------------------
    WinSockSentry::WinSockSentry()
    {
        if (use_count++ == 0)
        {
            WSADATA WsaData;
            if (WSAStartup(MAKEWORD(2,2), &WsaData) != NO_ERROR)
            {
                throw std::runtime_error("Failed to initialize WinSock32.");
            }
        }
    }

//------------------------------------------------------------------------------
    WinSockSentry::~WinSockSentry()
    {
        if (--use_count == 0)
        {
            WSACleanup();
        }
    }
}

#endif
