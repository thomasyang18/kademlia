#include <gtest/gtest.h>
#include "node/RoutingTable.hpp"
#include "node/NodeId.hpp"

TEST(RoutingTableTest, UpdateAndFindClosestNodes) {
    NodeID selfID = {{0}};
    RoutingTable routingTable(selfID);

    Node node1 = {{1}, "127.0.0.1", 12345};
    Node node2 = {{2}, "127.0.0.1", 12346};

    routingTable.update(node1);
    routingTable.update(node2);

    std::vector<Node> closestNodes = routingTable.findClosestNodes({{3}});
    ASSERT_EQ(closestNodes.size(), 2);
    ASSERT_EQ(closestNodes[0].id, node1.id);
    ASSERT_EQ(closestNodes[1].id, node2.id);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
