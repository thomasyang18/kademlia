#pragma once

#include "protocol/Networking.hpp"
#include <boost/asio.hpp>
#include <memory>

class P2PServer {
public:
    P2PServer(uint16_t port);

    void start();

    void ping(const std::string& ip, uint16_t port);

    void findNode(const NodeID& target, const std::string& ip, uint16_t port);

    void handleMessage(const Message& msg);

    Node getMyNode() const { return udpNode_.getMyNode(); }

    RoutingTable& getRoutingTable() { return udpNode_.getRoutingTable(); }

private:
    std::unique_ptr<boost::asio::io_context> io_context_;
    UDPNode udpNode_;
};
