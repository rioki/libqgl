// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include "IpAddress.h"

#include <stdexcept>

namespace qgl
{
//------------------------------------------------------------------------------
    IpAddress::IpAddress()
    {
        // make the address really invalid
        c_object.host = INADDR_ANY;
        c_object.port = 0;
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(unsigned short port)
    {
        if (SDLNet_ResolveHost(&c_object, NULL, port) < 0)
        {
            throw std::runtime_error(SDLNet_GetError());
        }
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(const std::string& host, unsigned short port)
    {
        if (SDLNet_ResolveHost(&c_object, host.c_str(), port) < 0)
        {
            throw std::runtime_error(SDLNet_GetError());
        }
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(const std::string& host)
    {
        if (SDLNet_ResolveHost(&c_object, host.c_str(), 0) < 0)
        {
            throw std::runtime_error(SDLNet_GetError());
        }
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(IPaddress co)
    {
        c_object = co;
    }

//------------------------------------------------------------------------------
    IpAddress::IpAddress(const IpAddress& orig)
    {
        c_object = orig.c_object;
    }

//------------------------------------------------------------------------------
    IpAddress::~IpAddress() {}

//------------------------------------------------------------------------------
    const IpAddress& IpAddress::operator = (const IpAddress& orig)
    {
        c_object = orig.c_object;
        return *this;
    }

//------------------------------------------------------------------------------
    unsigned int IpAddress::get_host_address()
    {
        return SDLNet_Read32(&c_object.host);
    }

//------------------------------------------------------------------------------
    void IpAddress::set_host_address(unsigned int value)
    {
        SDLNet_Write32(value, &c_object.host);
    }

//------------------------------------------------------------------------------
    std::string IpAddress::get_host_name()
    {
        const char* host = SDLNet_ResolveIP(&c_object);
        if (host != NULL)
        {
            return std::string(host);
        }
        else
        {
            throw std::runtime_error(SDLNet_GetError());
        }
    }

//------------------------------------------------------------------------------
    void IpAddress::set_host_name(const std::string& value)
    {
        if (SDLNet_ResolveHost(&c_object, value.c_str(), get_port()) < 0)
        {
            throw std::runtime_error(SDLNet_GetError());
        }
    }

//------------------------------------------------------------------------------
    unsigned int IpAddress::get_port()
    {
        return SDLNet_Read16(&c_object.port);
    }

//------------------------------------------------------------------------------
    void IpAddress::set_port(const unsigned int value)
    {
        SDLNet_Write16(value, &c_object.port);
    }

//------------------------------------------------------------------------------
    IPaddress IpAddress::get_c_object()
    {
        return c_object;
    }

//------------------------------------------------------------------------------
    const IPaddress IpAddress::get_c_object() const
    {
        return c_object;
    }
}
