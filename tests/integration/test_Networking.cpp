#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include <thread>
#include "protocol/Networking.hpp"
#include "node/RoutingTable.hpp"
#include "node/NodeId.hpp"
#include "protocol/Protocol.hpp"

void runNode(uint16_t port) {
    boost::asio::io_context io_context;
    UDPNode node(io_context, port);
    io_context.run();
}

TEST(NetworkingTest, NodeCommunication) {
    std::thread node1Thread(runNode, 12345);
    std::thread node2Thread(runNode, 12346);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    boost::asio::io_context io_context;
    UDPNode node(io_context, 12347);

    Message pingMsg = {MessageType::PING, {{0}}, {{0}}, {}};
    node.sendMessage(pingMsg, "127.0.0.1", 12345);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    node1Thread.detach();
    node2Thread.detach();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
