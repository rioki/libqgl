// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include <UnitTest++/UnitTest++.h>

#include <qgl/UdpSocket.h>

SUITE(UdpSocket)
{
    TEST(default_constructible)
    {
        qgl::UdpSocket socket;
    }
}
