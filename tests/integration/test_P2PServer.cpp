#include <gtest/gtest.h>
#include <boost/asio.hpp>
#include "protocol/P2PServer.hpp"

TEST(P2PServerTest, Ping) {
    boost::asio::io_context io_context;
    P2PServer server1(io_context, 12345);
    P2PServer server2(io_context, 12346);

    server1.start();
    server2.start();

    server1.ping("127.0.0.1", 12346);

    // Wait for the ping to be processed
    io_context.run_for(std::chrono::seconds(1));

    // Check if server2 has server1 in its routing table
    auto& routingTable = server2.getRoutingTable();
    auto nodes = routingTable.findClosestNodes(server1.getMyNode().id);
    ASSERT_EQ(nodes.size(), 1);
    ASSERT_EQ(nodes[0].id, server1.getMyNode().id);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
