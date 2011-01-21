// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_UDP_SOCKET_H_
#define _QGL_UDP_SOCKET_H_

#include "config.h"

#include <vector>

#include "IpAddress.h"

namespace qgl
{
    /**
     * UDP Socket
     *
     *
     **/
    class QGL_EXPORT UdpSocket
    {
    public:

        UdpSocket();

        UdpSocket(unsigned short port);

        ~UdpSocket();

        IpAddress get_local_address() const;

        void send(const IpAddress& address, const std::vector<unsigned char>& payload);

        bool recive(IpAddress& address, std::vector<unsigned char>& payload);

    private:
        int handle;

        void init(unsigned short port = 0);

        UdpSocket(const UdpSocket&);
        const UdpSocket& operator = (const UdpSocket&);
    };
}

#endif
