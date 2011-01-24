// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "UdpSocket.h"

#include <cassert>
#include <stdexcept>
#include <cstring>

namespace qgl
{
//------------------------------------------------------------------------------
    UdpSocket::UdpSocket()
    {
        init();
    }

//------------------------------------------------------------------------------
    UdpSocket::UdpSocket(unsigned short p)
    {
        init(p);
    }

//------------------------------------------------------------------------------
    UdpSocket::~UdpSocket()
    {
        SDLNet_UDP_Close(socket);
    }

//------------------------------------------------------------------------------
    unsigned int UdpSocket::get_max_packet_size() const
    {
        return max_packet_size;
    }

//------------------------------------------------------------------------------
    void UdpSocket::set_max_packet_size(unsigned int value)
    {
        max_packet_size = value;
    }

//------------------------------------------------------------------------------
    void UdpSocket::send(const IpAddress& address, const std::vector<unsigned char>& payload)
    {
        if (payload.empty())
        {
            throw std::invalid_argument("UdpSocket::send: payload is empty.");
        }
        if (payload.size() > max_packet_size)
        {
            // NOTE: Sending packets may even work with this check disabled.
            // But we assume that the client code will set this value on the
            // other end to the same value. If the payload exedes the packet
            // will be dropped at that end (even though it made it through
            // the network).
            throw std::invalid_argument("UdpSocket::send: payload larger than maximum packet size");
        }

        UDPpacket* packet = NULL;
        try
        {
            packet = SDLNet_AllocPacket(payload.size());
            if (packet == NULL)
            {
                throw std::runtime_error(SDLNet_GetError());
            }

            packet->address = address.get_c_adr();
            std::memcpy(packet->data, &payload[0], payload.size());
            packet->len = payload.size();

            int result = SDLNet_UDP_Send(socket, -1, packet);
            if (! result)
            {
                throw std::runtime_error(SDLNet_GetError());
            }

            SDLNet_FreePacket(packet);
        }
        catch (...)
        {
            if (packet != NULL)
            {
                SDLNet_FreePacket(packet);
            }
            throw;
        }
    }

//------------------------------------------------------------------------------
    bool UdpSocket::recive(IpAddress& address, std::vector<unsigned char>& payload)
    {
        UDPpacket* packet = NULL;
        try
        {
            packet = SDLNet_AllocPacket(max_packet_size);
            if (packet == NULL)
            {
                throw std::runtime_error(SDLNet_GetError());
            }

            int result = SDLNet_UDP_Recv(socket, packet);

            if (result)
            {
                address = IpAddress(packet->address);
                payload = std::vector<unsigned char>(packet->len);
                std::memcpy(&payload[0], packet->data, packet->len);
            }
            SDLNet_FreePacket(packet);

            return result > 0;
        }
        catch (...)
        {
            if (packet != NULL)
            {
                SDLNet_FreePacket(packet);
            }
            throw;
        }
    }

//------------------------------------------------------------------------------
    void UdpSocket::init(unsigned short port)
    {
        max_packet_size = 512;

        socket = SDLNet_UDP_Open(port);
        if (socket == NULL)
        {
            throw std::runtime_error(SDLNet_GetError());
        }
    }
}
