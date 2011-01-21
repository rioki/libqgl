// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "IpAddress.h"

#include <stdexcept>

namespace qgl
{
//------------------------------------------------------------------------------
    IpAddress IpAddress::resolve(const std::string& hostname)
    {
        hostent* hdata = gethostbyname(hostname.c_str());
        if (hdata == NULL)
        {
            throw std::runtime_error("Failed to resolve hostname.");
        }
        return IpAddress(ntohl(*hdata->h_addr), 0);
    }

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
        unsigned long host = ((unsigned long)a << 24) | ((unsigned long)b << 16) | ((unsigned long)c << 8) | (unsigned long)d;

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
    unsigned char IpAddress::get_a() const
    {
        unsigned long host = get_host();
        return (host & 0xFF000000) >> 24;
    }

//------------------------------------------------------------------------------
    unsigned char IpAddress::get_b() const
    {
        unsigned long host = get_host();
        return (host & 0x00FF0000) >> 16;
    }

//------------------------------------------------------------------------------
    unsigned char IpAddress::get_c() const
    {
        unsigned long host = get_host();
        return (host & 0x0000FF00) >> 8;
    }

//------------------------------------------------------------------------------
    unsigned char IpAddress::get_d() const
    {
        unsigned long host = get_host();
        return host & 0x000000FF;
    }

//------------------------------------------------------------------------------
    void IpAddress::set_host(unsigned long value)
    {
        address.sin_addr.s_addr = htonl(value);
    }

//------------------------------------------------------------------------------
    void IpAddress::set_host(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
    {
        unsigned long host = (a << 24) | (b << 16) | (c << 8) | d;
        set_host(host);
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

//------------------------------------------------------------------------------
    QGL_EXPORT bool operator == (const IpAddress& a, const IpAddress& b)
    {
        return a.get_host() == b.get_host() && a.get_port() == b.get_port();
    }

//------------------------------------------------------------------------------
    QGL_EXPORT bool operator != (const IpAddress& a, const IpAddress& b)
    {
        return !(a == b);
    }

//------------------------------------------------------------------------------
    QGL_EXPORT std::ostream& operator << (std::ostream& os, const IpAddress& adr)
    {
        os << (unsigned int)adr.get_a() << "." << (unsigned int)adr.get_b() << "."
           << (unsigned int)adr.get_c() << "." << (unsigned int)adr.get_d();
        if (adr.get_port() != 0)
        {
            os << ":" << adr.get_port();
        }
        return os;
    }
}
