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

TEST(RoutingTableTest, UpdateWithManyNodes) {
    NodeID selfID = {{0}};
    RoutingTable routingTable(selfID);

    for (int i = 1; i <= 30; ++i) {
        Node node = {{static_cast<uint8_t>(i)}, "127.0.0.1", 12345 + i};
        routingTable.update(node);
    }

    std::vector<Node> closestNodes = routingTable.findClosestNodes({{1}});
    ASSERT_EQ(closestNodes.size(), 20);
    for (int i = 1; i <= 20; ++i) {
        ASSERT_EQ(closestNodes[i - 1].id.bytes[0], static_cast<uint8_t>(i + 9));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
