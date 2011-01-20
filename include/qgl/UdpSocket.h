// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_UDPSOCKET_H_
#define _QGL_UDPSOCKET_H_

#include "config.h"

#include <vector>
#include <string>
#include <queue>

#include <sigc++/signal.h>

#include "IpAddress.h"
#include "Mutex.h"
#include "Thread.h"

namespace qgl
{
    /**
     * The maximum packet size to use.
     **/
    const unsigned int MAX_PACKET_SIZE = 512;

    /**
     * UDP Socket
     *
     *
     **/
    class QGL_EXPORT UdpSocket
    {
    public:

        /**
         * Get the local address.
         **/
        static IpAddress get_local_address();

        /**
         * Create an UDP socket with unspecific port.
         **/
        UdpSocket();

        /**
         * Create an UDP socket with specific port.
         **/
        UdpSocket(unsigned short port);

        /**
         * Destroy the socket.
         **/
        ~UdpSocket();

        /**
         * Send data over the socket.
         **/
        void send(const IpAddress& address, const std::vector<unsigned char>& data);

        /**
         * Signal that is triggered when data was recived on the socket.
         **/
        sigc::signal<void, const IpAddress&, const std::vector<unsigned char>&>& get_data_recived_signal();

    private:
        struct SendHandover
        {
            IpAddress address;
            std::vector<unsigned char> data;
        };

        Mutex mutex;
        unsigned int port;
        std::queue<SendHandover> send_queue;
        bool destructing;

        sigc::signal<void, const IpAddress&, const std::vector<unsigned char>&> data_recived_signal;

        Thread comunication_thread;

        void comunication_handler();
    };
}

#endif
