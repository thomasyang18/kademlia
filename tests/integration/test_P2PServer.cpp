#include <gtest/gtest.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <atomic>

// Dummy P2PServer implementation for illustration.
class P2PServer {
public:
    explicit P2PServer(uint16_t port)
      : port_(port), running(false) {}

    // Simulate a server loop.
    void start() {
        running = true;
        std::cout << "Server started on port " << port_ << std::endl;
        while (running.load()) {
            // In a real server, you’d wait for connections, etc.
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "Server stopped on port " << port_ << std::endl;
    }

    void stop() {
        running = false;
    }

    void ping(const std::string& ip, uint16_t port) {
        std::cout << "Ping from server on port " << port_
                  << " to " << ip << ":" << port << std::endl;
    }

    void findNode(const std::string& target, const std::string& ip, uint16_t port) {
        std::cout << "findNode (" << target << ") from server on port " << port_
                  << " to " << ip << ":" << port << std::endl;
    }

private:
    uint16_t port_;
    std::atomic<bool> running;
};

// Dummy definitions for NodeID and generateRandomNodeID.
using NodeID = std::string;
NodeID generateRandomNodeID() {
    return "random-node-id";
}

// Global test environment that starts our P2P servers.
class P2PTestEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        // Option 1: Use fixed ports.
        server1 = std::make_unique<P2PServer>(10001);
        server2 = std::make_unique<P2PServer>(10002);

        // Option 2: Bind to port 0 for ephemeral ports (if supported):
        // server1 = std::make_unique<P2PServer>(0);
        // server2 = std::make_unique<P2PServer>(0);

        // Start the servers in their own threads.
        server1Thread = std::thread([this]() { server1->start(); });
        server2Thread = std::thread([this]() { server2->start(); });

        // (Optional) Wait a bit for the servers to initialize.
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void TearDown() override {
        // Stop the servers and join their threads.
        if (server1) server1->stop();
        if (server2) server2->stop();

        if (server1Thread.joinable())
            server1Thread.join();
        if (server2Thread.joinable())
            server2Thread.join();
    }

    // Accessors for tests.
    P2PServer* GetServer1() { return server1.get(); }
    P2PServer* GetServer2() { return server2.get(); }

private:
    std::unique_ptr<P2PServer> server1;
    std::unique_ptr<P2PServer> server2;
    std::thread server1Thread;
    std::thread server2Thread;
};

// Since Google Test does not provide a way to retrieve our custom environment,
// we store the pointer in a global variable.
P2PTestEnvironment* p2pEnv = nullptr;

// Test that uses the ping functionality.
TEST(P2PServerTest, Ping) {
    ASSERT_NE(p2pEnv, nullptr) << "P2PTestEnvironment not initialized";
    P2PServer* server1 = p2pEnv->GetServer1();
    // Call ping on server1 targeting server2 (on port 10002)
    server1->ping("127.0.0.1", 10002);

    // Here you would add assertions to verify that ping was successful.
    SUCCEED();
}

// Test that uses the findNode functionality.
TEST(P2PServerTest, FindNode) {
    ASSERT_NE(p2pEnv, nullptr) << "P2PTestEnvironment not initialized";
    P2PServer* server1 = p2pEnv->GetServer1();
    NodeID target = generateRandomNodeID();
    server1->findNode(target, "127.0.0.1", 10002);

    // Here you would add assertions to verify that findNode was successful.
    SUCCEED();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // Create and add our global test environment.
    p2pEnv = new P2PTestEnvironment();
    ::testing::AddGlobalTestEnvironment(p2pEnv);

    return RUN_ALL_TESTS();
}
