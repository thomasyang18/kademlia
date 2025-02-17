#include <gtest/gtest.h>
#include "node/RoutingTable.hpp"
#include "node/NodeId.hpp"

TEST(RoutingTableTest, Update) {
    NodeID selfID = {{0}};
    RoutingTable routingTable(selfID);

    Node node1 = {{1}, "127.0.0.1", 12345};
    Node node2 = {{2}, "127.0.0.1", 12346};

    routingTable.update(node1);
    routingTable.update(node2);

    std::vector<Node> closestNodes = routingTable.findClosestNodes(node1.id);
    ASSERT_EQ(closestNodes.size(), 2);
    ASSERT_EQ(closestNodes[0].id, node1.id);
    ASSERT_EQ(closestNodes[1].id, node2.id);
}

TEST(RoutingTableTest, FindClosestNodes) {
    NodeID selfID = {{0}};
    RoutingTable routingTable(selfID);

    Node node1 = {{1}, "127.0.0.1", 12345};
    Node node2 = {{2}, "127.0.0.1", 12346};

    routingTable.update(node1);
    routingTable.update(node2);

    std::vector<Node> closestNodes = routingTable.findClosestNodes(node1.id);
    ASSERT_EQ(closestNodes.size(), 2);
    ASSERT_EQ(closestNodes[0].id, node1.id);
    ASSERT_EQ(closestNodes[1].id, node2.id);
}

TEST(RoutingTableTest, XorDistance) {
    NodeID id1 = {{1, 2, 3}};
    NodeID id2 = {{4, 5, 6}};
    NodeID result = id1 ^ id2;
    ASSERT_EQ(result.bytes[0], 5);
    ASSERT_EQ(result.bytes[1], 7);
    ASSERT_EQ(result.bytes[2], 5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
