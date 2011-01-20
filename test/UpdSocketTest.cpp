// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include <UnitTest++/UnitTest++.h>

#include <qgl/UdpSocket.h>

SUITE(UdpSocket)
{
    TEST(get_local_address)
    {
        qgl::IpAddress adr = qgl::UdpSocket::get_local_address();
        unsigned int ip = adr.get_host_address();
        CHECK(ip != 0);
    }
}
