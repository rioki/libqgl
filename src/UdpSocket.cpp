// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "UdpSocket.h"

#include <cassert>
#include <stdexcept>

#include "Lock.h"

namespace qgl
{
//------------------------------------------------------------------------------
    IpAddress UdpSocket::get_local_address()
    {
        /*IPaddress adr;
        adr.host = NULL;
        adr.port = 12;

        const char* host = SDLNet_ResolveIP(&adr);
        SDLNet_ResolveHost(&adr, host, 0);
        return IpAddress(adr);*/
    }

//------------------------------------------------------------------------------
    UdpSocket::UdpSocket()
    : port(0),
      destructing(false),
      comunication_thread(sigc::mem_fun(this, &UdpSocket::comunication_handler)) {}

//------------------------------------------------------------------------------
    UdpSocket::UdpSocket(unsigned short p)
    : port(p),
      destructing(false),
      comunication_thread(sigc::mem_fun(this, &UdpSocket::comunication_handler)) {}

//------------------------------------------------------------------------------
    UdpSocket::~UdpSocket()
    {
        destructing = true;
        comunication_thread.wait();
    }

//------------------------------------------------------------------------------
    void UdpSocket::send(const IpAddress& address, const std::vector<unsigned char>& data)
    {
        if (data.size() > MAX_PACKET_SIZE)
        {
            throw std::logic_error("UdpSocket::send: Trying to send more data then MAX_PACKET_SIZE.");
        }
        if (data.size() == 0)
        {
            throw std::logic_error("UdpSocket::send: Trying to send empty packet.");
        }

        SendHandover handover;
        handover.address = address;
        handover.data = data;

        {
            Lock<Mutex> lock(mutex);
            send_queue.push(handover);
        }
    }

//------------------------------------------------------------------------------
    sigc::signal<void, const IpAddress&, const std::vector<unsigned char>&>& UdpSocket::get_data_recived_signal()
    {
        return data_recived_signal;
    }

//------------------------------------------------------------------------------
    void UdpSocket::comunication_handler()
    {
        UDPsocket socket = NULL;
        UDPpacket* packet = NULL;

        SendHandover send_handover;
        bool send_queue_empty = true;

        try
        {
            socket = SDLNet_UDP_Open(port);
            if (socket == NULL)
            {
                throw std::runtime_error(SDLNet_GetError());
            }

            packet = SDLNet_AllocPacket(512);
            if (packet == NULL)
            {
                throw std::runtime_error(SDLNet_GetError());
            }

            while (! destructing)
            {
                // send
                {
                    Lock<Mutex> lock(mutex);
                    if (! send_queue.empty())
                    {
                        send_handover = send_queue.front();
                        send_queue.pop();
                        send_queue_empty = false;
                    }
                    else
                    {
                        send_queue_empty = true;
                    }
                }

                if (! send_queue_empty)
                {
                    // these conditions are checked in UdpSocket::send;
                    assert(send_handover.data.size() != 0);
                    assert(send_handover.data.size() <= packet->maxlen);

                    packet->channel = -1;
                    memcpy(packet->data, &send_handover.data[0], send_handover.data.size());
                    packet->len = send_handover.data.size();
                    packet->address = send_handover.address.get_c_object();
                    packet->status = 0;

                    SDLNet_UDP_Send(socket, packet->channel, packet);
                }

                // revice
                int recv_result = SDLNet_UDP_Recv(socket, packet);
                if (recv_result == -1)
                {
                    throw std::logic_error(SDLNet_GetError());
                }
                if (recv_result == 1)
                {
                    assert(packet->len != 0); // this "never" happens
                    assert(packet->len <= packet->maxlen); // ok this would be a SDL_net bug

                    std::vector<unsigned char> data(packet->len);
                    memcpy(&data[0], packet->data, packet->len);

                    IpAddress address(packet->address);

                    data_recived_signal(address, data);
                }
            }

            SDLNet_FreePacket(packet);
            SDLNet_UDP_Close(socket);
        }
        catch (...)
        {
            SDLNet_FreePacket(packet);
            SDLNet_UDP_Close(socket);
            throw;
        }
    }

}
