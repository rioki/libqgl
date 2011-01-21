// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "IpAddress.h"

#include <stdexcept>

namespace qgl
{
//------------------------------------------------------------------------------
    IpAddress::IpAddress()
    {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = 0;
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(sockaddr_in c_adr)
    {
        address = c_adr;
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(unsigned long host, unsigned short port)
    {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl(host);
        address.sin_port = htons(port);
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
    {
        unsigned int host = (a << 24) | (b << 16) | (c << 8) | d;

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl(host);
        address.sin_port = htons(port);
    }

//------------------------------------------------------------------------------
    unsigned long IpAddress::get_host() const
    {
        return ntohl(address.sin_addr.s_addr);
    }

//------------------------------------------------------------------------------
    void IpAddress::set_host(unsigned long value)
    {
        address.sin_addr.s_addr = htonl(value);
    }

//------------------------------------------------------------------------------
    void IpAddress::set_host(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
    {
        set_host((a << 24) | (b << 16) | (c << 8) | d);
    }

//------------------------------------------------------------------------------
    unsigned short IpAddress::get_port() const
    {
        return ntohs(address.sin_port);
    }

//------------------------------------------------------------------------------
    void IpAddress::set_port(unsigned short value)
    {
        address.sin_port = htons(value);
    }

//------------------------------------------------------------------------------
    sockaddr_in IpAddress::get_c_adr() const
    {
        return address;
    }
}
