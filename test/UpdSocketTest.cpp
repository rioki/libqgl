// Quick Game Library
// Copyright 2010-2011 Sean Farrell

#include <UnitTest++/UnitTest++.h>

#include <iostream>
#include <qgl/UdpSocket.h>

SUITE(UdpSocket)
{
//-----------------------------------------------------------------------------
    TEST(default_constructible)
    {
        qgl::UdpSocket sock;
    }

//-----------------------------------------------------------------------------
    TEST(default_max_packet_size_is_512)
    {
        qgl::UdpSocket socket;
        CHECK_EQUAL(512, socket.get_max_packet_size());
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
        while (!sock_a.recive(recv_adr, recv_payload)) {}

        CHECK(std::vector<unsigned char>(1, 123) == recv_payload);
    }

//-----------------------------------------------------------------------------
    TEST(get_local_address)
    {
        qgl::IpAddress address = qgl::IpAddress::get_local_address();

        CHECK(qgl::IpAddress() != address);
    }

//-----------------------------------------------------------------------------
    TEST(resolve_address)
    {
        qgl::IpAddress adr = qgl::IpAddress::resolve("localhost");
        qgl::IpAddress ref(127, 0, 0, 1, 0);
        CHECK_EQUAL(ref, adr);
    }
}
