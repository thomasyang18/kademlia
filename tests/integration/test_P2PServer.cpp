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
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
