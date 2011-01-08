// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#ifndef _QGL_IPADDRESS_H_
#define _QGL_IPADDRESS_H_

#include "config.h"

#include <SDL_net.h>
#include <string>

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

        /**
         * Create a blank address object.
         *
         * @warning This object is not usable for anyting except storage.
         **/
        IpAddress();

        /**
         * Create server address.
         *
         * @param port the port
         *
         * This address can be used to bind a TCP port to a specific port, but not address.
         **/
        IpAddress(unsigned short port);

        /**
         * Create a regular address with name resolution.
         *
         * @param host the host name
         * @param port the port
         **/
        IpAddress(const std::string& host, unsigned short port);

        /**
         * Create a address from host name.
         *
         * @param host the host name
         *
         * @warning This object is not usable for normal use.
         * It only serves as a way to resolve addresses.
         **/
        IpAddress(const std::string& host);

        /**
         * Wrap a SDL_net's IPaddress object.
         *
         * @param c_object the C object.
         **/
        IpAddress(IPaddress c_object);

        /**
         * Copy Constructor.
         **/
        IpAddress(const IpAddress& orig);

        /**
         * Destructor
         **/
        ~IpAddress();

        /**
         * Copy constructor.
         **/
        const IpAddress& operator = (const IpAddress& orig);

        /**
         * Get the host address.
         **/
        unsigned int get_host_address();

        /**
         * Set the host address.
         *
         * @param value the value to set the address to.
         *
         * @return the host address
         **/
        void set_host_address(unsigned int value);

        /**
         * Get the host address.
         *
         * @note This function will trigger reverse name resolution.
         * It is assumed that you will not use it ofren.
         *
         * @return the host name
         **/
        std::string get_host_name();

        /**
         * Set the host address.
         *
         * @param value the value to set the address to.
         *
         * @note Since this method will trigger host name resolution and
         * the coresponding getter will trigger reverse resolution, setting
         * and getting this value on one object may not be the same value.
         **/
        void set_host_name(const std::string& value);

        /**
         * Get the remote port.
         *
         * @return the remote port
         **/
        unsigned int get_port();

        /**
         * Set the remote port.
         *
         * @param value the value to set the port.
         **/
        void set_port(const unsigned int value);

        /**
         * Get the underlying C object.
         **/
        IPaddress get_c_object();

        /**
         * Get the underlying C object.
         **/
        const IPaddress get_c_object() const;

    private:
        IPaddress c_object;
    };
}

#endif
