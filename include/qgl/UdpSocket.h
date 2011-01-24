// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_UDP_SOCKET_H_
#define _QGL_UDP_SOCKET_H_

#include "config.h"

#include <vector>
#include <SDL_net.h>

#include "SdlNetSentry.h"
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

        /**
         * Get the maximum packet size.
         **/
        unsigned int get_max_packet_size() const;

        /**
         * Set the maximum packet size.
         **/
        void set_max_packet_size(unsigned int value);

        void send(const IpAddress& address, const std::vector<unsigned char>& payload);

        /**
         * Recive a packet.
         *
         *
         **/
        bool recive(IpAddress& address, std::vector<unsigned char>& payload);

    private:
        SdlNetSentry sentry;
        UDPsocket socket;

        unsigned int max_packet_size;

        void init(unsigned short port = 0);

        UdpSocket(const UdpSocket&);
        const UdpSocket& operator = (const UdpSocket&);
    };
}

#endif
