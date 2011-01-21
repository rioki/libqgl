// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "UdpSocket.h"

#include <cassert>
#include <stdexcept>

#if _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#endif

#include "WinSockSentry.h"

namespace qgl
{
    #ifdef _WIN32
    WinSockSentry sentry;
    #endif

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
        #ifdef _WIN32
        closesocket(handle);
        #else
        close(handle);
        #endif
    }

//------------------------------------------------------------------------------
    IpAddress UdpSocket::get_local_address() const
    {
        sockaddr_in adr;
        int adr_len = sizeof(sockaddr_in);
        if (getsockname(handle, (sockaddr*)&adr, &adr_len) < 0)
        {
            throw std::runtime_error("Failed to get the local address.");
        }
        else
        {
            return IpAddress(adr);
        }
    }

//------------------------------------------------------------------------------
    void UdpSocket::send(const IpAddress& address, const std::vector<unsigned char>& payload)
    {
        sockaddr_in c_addr = address.get_c_adr();
        int sent_bytes = sendto(handle, (const char*)&payload[0], payload.size(), 0, (sockaddr*)&c_addr, sizeof(sockaddr_in));

        if (sent_bytes != payload.size())
        {
            throw std::runtime_error("Failed to send packet.");
        }
    }

//------------------------------------------------------------------------------
    bool UdpSocket::recive(IpAddress& address, std::vector<unsigned char>& payload)
    {
        std::vector<unsigned char> buff(256);

        sockaddr_in adr;
        int adr_len = sizeof(sockaddr_in);

        int received_bytes = recvfrom(handle, (char*)&buff[0], buff.size(), 0, (sockaddr*)&adr, &adr_len);
        if (received_bytes > 0)
        {
            payload.resize(received_bytes);
            std::copy(buff.begin(), buff.begin() + received_bytes, payload.begin());
            address = IpAddress(adr);
            return true;
        }
        else
        {
            return false;
        }
    }

//------------------------------------------------------------------------------
    void UdpSocket::init(unsigned short port)
    {
        handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (handle <= 0)
        {
            throw std::runtime_error("Failed to create socket.");
        }
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
        {
            throw std::runtime_error("Failed to bind socket.");
        }

        #ifdef _WIN32
        DWORD nonBlocking = 1;
        if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
        {
            throw std::runtime_error("Failed to set non-blocking socket.");
        }
        #else
        int nonBlocking = 1;
        if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
        {
            throw std::runtime_error("Failed to set non-blocking socket.");
        }
        #endif
    }
}
