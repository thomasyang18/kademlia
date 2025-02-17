#include <gtest/gtest.h>
#include "protocol/P2PServer.hpp"
#include <thread>

class P2PTestEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        // Option 1: Use fixed ports
        server1 = std::make_unique<P2PServer>(10001);
        server2 = std::make_unique<P2PServer>(10002);

        // Option 2: Bind to port 0 and query the OS-assigned port if available
        // server1 = std::make_unique<P2PServer>(0);
        // server2 = std::make_unique<P2PServer>(0);

        std::thread server1Thread([this]() { server1->start(); });
        std::thread server2Thread([this]() { server2->start(); });

        // Detach threads to let them run independently
        server1Thread.detach();
        server2Thread.detach();
    }

    void TearDown() override {
        // No need to stop servers explicitly since they will be destroyed
    }

    // Provide accessors if your tests need direct access:
    P2PServer* GetServer1() { return server1.get(); }
    P2PServer* GetServer2() { return server2.get(); }

private:
    std::unique_ptr<P2PServer> server1;
    std::unique_ptr<P2PServer> server2;
};

::testing::Environment* const p2p_env =
    ::testing::AddGlobalTestEnvironment(new P2PTestEnvironment);

TEST(P2PServerTest, Ping) {
    auto* env = static_cast<P2PTestEnvironment*>(::testing::GetGlobalTestEnvironment());
    P2PServer* server1 = env->GetServer1();
    P2PServer* server2 = env->GetServer2();

    server1->ping("127.0.0.1", 10002);

    // Wait for the ping to be processed
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Check if server2 has server1 in its routing table
    auto& routingTable = server2->getRoutingTable();
    auto nodes = routingTable.findClosestNodes(server1->getMyNode().id);
    ASSERT_EQ(nodes.size(), 1);
    ASSERT_EQ(nodes[0].id, server1->getMyNode().id);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
