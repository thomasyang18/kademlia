#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include "protocol/Protocol.hpp"

class UDPNode {
public:
    UDPNode(boost::asio::io_context& io_context, uint16_t port);

    void sendMessage(const Message& msg, const std::string& ip, uint16_t port);

    void startReceive();

private:
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remoteEndpoint_;
    std::array<char, 1024> recvBuffer_;

    Message deserializeMessage(std::array<char, 1024>& buffer, std::size_t len);

    std::vector<uint8_t> serializeMessage(const Message& msg);

    void handleMessage(const Message& msg);

    Node myNode;
    RoutingTable routingTable_;
};
