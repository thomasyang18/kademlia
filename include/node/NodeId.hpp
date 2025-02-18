#pragma once

#include <array>
#include <string>
#include <bitset>
#include "config.hpp"

class NodeID {
    std::bitset<Config::W> _id;
public:
    // useful for testing, serialization; generally should just move with moveID though 
    explicit NodeID(const std::bitset<Config::W>& id) : _id(id) {}

    // Equality operator
    bool operator==(const NodeID& other) const {
        return _id == other._id;
    }

    // XOR distance for routing logic
    NodeID operator^(const NodeID& other) const {
        return NodeID(_id ^ other._id);
    }

    // Static function to generate a random NodeID
    static NodeID generateRandomNodeID();
};

struct Node {
    NodeID id;
    std::string ip;
    uint16_t port;
};
