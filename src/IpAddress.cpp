// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "IpAddress.h"

#include <stdexcept>

// PORT: we want htons and friends and gethostname
#ifdef _WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif


namespace qgl
{
//------------------------------------------------------------------------------
    IpAddress IpAddress::resolve(const std::string& hostname)
    {
        // NOTE: We use this scheme, since we need a valid instance of
        // SdlNetSentry active.
        IpAddress address;
        address.resolve_impl(hostname);
        return address;
    }

//------------------------------------------------------------------------------
    IpAddress IpAddress::get_local_address()
    {
        IpAddress address;
        address.get_local_address_impl();
        return address;
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress()
    {
        address.host = INADDR_NONE;
        address.port = 0;
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(IPaddress c_adr)
    {
        address = c_adr;
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(unsigned long host, unsigned short port)
    {
        address.host = htonl(host);
        address.port = htons(port);
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
    {
        unsigned long host = ((unsigned long)a << 24) | ((unsigned long)b << 16) | ((unsigned long)c << 8) | (unsigned long)d;

        address.host = htonl(host);
        address.port = htons(port);
    }

//------------------------------------------------------------------------------
    unsigned long IpAddress::get_host() const
    {
        return ntohl(address.host);
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
        address.host = htonl(value);
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
        return ntohs(address.port);
    }

//------------------------------------------------------------------------------
    void IpAddress::set_port(unsigned short value)
    {
        address.port = htons(value);
    }

//------------------------------------------------------------------------------
    IPaddress IpAddress::get_c_adr() const
    {
        return address;
    }

//------------------------------------------------------------------------------
    void IpAddress::resolve_impl(const std::string& hostname)
    {
        if (SDLNet_ResolveHost(&address, &hostname[0], 0) == -1)
        {
            throw std::runtime_error(SDLNet_GetError());
        }
    }

//------------------------------------------------------------------------------
    void IpAddress::get_local_address_impl()
    {
        char buff[512];
        if (gethostname(buff, 512) != 0)
        {
            throw std::runtime_error("Failed to get host name.");
        }
        resolve_impl(std::string(buff));
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
