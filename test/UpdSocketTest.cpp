// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include <UnitTest++/UnitTest++.h>

#include <qgl/UdpSocket.h>

SUITE(UdpSocket)
{
//-----------------------------------------------------------------------------
    TEST(default_constructible)
    {
        qgl::UdpSocket sock;
    }

//-----------------------------------------------------------------------------
    TEST(simple_send_recive)
    {
        qgl::UdpSocket sock_a(1234);
        qgl::UdpSocket sock_b;

        qgl::IpAddress sock_a_adr(127, 0, 0, 1, 1234);
        sock_b.send(sock_a_adr, std::vector<unsigned char>(1, 123));

        qgl::IpAddress recv_adr;
        std::vector<unsigned char> recv_payload;
        while (sock_a.recive(recv_adr, recv_payload) == false) {}

        CHECK(std::vector<unsigned char>(1, 123) == recv_payload);
    }
}
