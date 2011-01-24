// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_IP_ADDRESS_H_
#define _QGL_IP_ADDRESS_H_

#include "config.h"

#include <string>
#include <iostream>
#include <SDL_net.h>

#include "SdlNetSentry.h"

namespace qgl
{
    /**
     * IP Address representation.
     *
     * @note All values are given and retrived in local byte order. The conversion
     * is done interally and automatically for you.
     **/
    class QGL_EXPORT IpAddress
    {
    public:

        static IpAddress resolve(const std::string& hostname);

        static IpAddress get_local_address();

        IpAddress();

        IpAddress(IPaddress c_adr);

        IpAddress(unsigned long host, unsigned short port);

        IpAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);

        unsigned long get_host() const;

        unsigned char get_a() const;

        unsigned char get_b() const;

        unsigned char get_c() const;

        unsigned char get_d() const;

        void set_host(unsigned long value);

        void set_host(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

        unsigned short get_port() const;

        void set_port(unsigned short value);

        IPaddress get_c_adr() const;

    private:
        SdlNetSentry sentry;
        IPaddress address;

        void resolve_impl(const std::string& hostname);
        void get_local_address_impl();
    };

    QGL_EXPORT bool operator == (const IpAddress& a, const IpAddress& b);

    QGL_EXPORT bool operator != (const IpAddress& a, const IpAddress& b);

    QGL_EXPORT std::ostream& operator << (std::ostream& os, const IpAddress& adr);
}

#endif
