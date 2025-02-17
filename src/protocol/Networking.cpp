#include "protocol/Networking.hpp"
#include "config.hpp"

UDPNode::UDPNode(boost::asio::io_context& io_context, uint16_t port)
    : socket_(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)),
      myNode({generateRandomNodeID(), "127.0.0.1", port}),
      routingTable_(myNode.id) {
    startReceive();
}

void UDPNode::sendMessage(const Message& msg, const std::string& ip, uint16_t port) {
    boost::asio::ip::udp::endpoint target(boost::asio::ip::make_address(ip), port);
    std::vector<uint8_t> data = serializeMessage(msg);
    socket_.send_to(boost::asio::buffer(data), target);
}

void UDPNode::startReceive() {
    socket_.async_receive_from(
        boost::asio::buffer(recvBuffer_), remoteEndpoint_,
        [this](boost::system::error_code ec, std::size_t bytesReceived) {
            if (!ec) {
                Message msg = deserializeMessage(recvBuffer_, bytesReceived);
                handleMessage(msg);
            }
            startReceive(); // Keep listening
        });
}

Message UDPNode::deserializeMessage(std::array<char, 1024>& buffer, std::size_t len) {
    // Implement deserialization (use JSON, Protobuf, etc.)
}

std::vector<uint8_t> UDPNode::serializeMessage(const Message& msg) {
    // Implement serialization
}

void UDPNode::handleMessage(const Message& msg) {
    switch (msg.type) {
        case MessageType::PING:
            sendMessage({MessageType::PONG, myNode, {}, {}}, msg.sender.ip, msg.sender.port);
            break;
        case MessageType::FIND_NODE:
            sendMessage({MessageType::FIND_NODE_REPLY, myNode, msg.target, routingTable_.findClosestNodes(msg.target, Config::().kBucketSize)}, msg.sender.ip, msg.sender.port);
            break;
        case MessageType::FIND_NODE_REPLY:
            for (const auto& node : msg.nodes) {
                routingTable_.update(node);
            }
            break;
        default:
            break;
    }
}
