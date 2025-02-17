#pragma once

#include <array>
#include <string>

struct NodeID {
    std::array<uint8_t, 32> bytes;  // 256-bit ID

    bool operator==(const NodeID& other) const {
        return bytes == other.bytes;
    }

    // XOR distance for routing logic
    NodeID operator^(const NodeID& other) const;
};

struct Node {
    NodeID id;
    std::string ip;
    uint16_t port;
};
