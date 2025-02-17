#pragma once 

#include <array>
#include <string>

#include <array>
#include <string>

struct NodeID {
    std::array<uint8_t, 32> bytes;  // 256-bit ID

    bool operator==(const NodeID& other) const {
        return bytes == other.bytes;
    }

    // XOR distance for routing logic
    NodeID operator^(const NodeID& other) const {
        NodeID result;
        for (size_t i = 0; i < bytes.size(); i++) {
            result.bytes[i] = bytes[i] ^ other.bytes[i];
        }
        return result;
    }
};

struct Node {
    NodeID id;
    std::string ip;
    uint16_t port;
};
