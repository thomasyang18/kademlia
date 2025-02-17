#include "protocol/P2PServer.hpp"
#include <iostream>

P2PServer::P2PServer(uint16_t port)
    : io_context_(std::make_unique<boost::asio::io_context>()),
      udpNode_(*io_context_, port) {}

void P2PServer::start() {
    udpNode_.startReceive();
    io_context_->run();
}

void P2PServer::ping(const std::string& ip, uint16_t port) {
    Message msg = {MessageType::PING, udpNode_.getMyNode(), {}, {}};
    udpNode_.sendMessage(msg, ip, port);
}

void P2PServer::findNode(const NodeID& target, const std::string& ip, uint16_t port) {
    Message msg = {MessageType::FIND_NODE, udpNode_.getMyNode(), target, {}};
    udpNode_.sendMessage(msg, ip, port);
}

void P2PServer::handleMessage(const Message& msg) {
    switch (msg.type) {
        case MessageType::PING:
            udpNode_.sendMessage({MessageType::PONG, udpNode_.getMyNode(), {}, {}}, msg.sender.ip, msg.sender.port);
            break;
        case MessageType::FIND_NODE:
            udpNode_.sendMessage({MessageType::FIND_NODE_REPLY, udpNode_.getMyNode(), msg.target, udpNode_.getRoutingTable().findClosestNodes(msg.target)}, msg.sender.ip, msg.sender.port);
            break;
        case MessageType::FIND_NODE_REPLY:
            for (const auto& node : msg.nodes) {
                udpNode_.getRoutingTable().update(node);
            }
            break;
        default:
            break;
    }
}
