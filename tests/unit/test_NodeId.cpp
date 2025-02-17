#include <gtest/gtest.h>
#include "node/NodeId.hpp"

TEST(NodeIdTest, XOROperator) {
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
