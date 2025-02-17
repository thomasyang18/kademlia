#include "node/NodeId.hpp"
#include <random>

NodeID NodeID::operator^(const NodeID& other) const {
    NodeID result;
    for (size_t i = 0; i < bytes.size(); i++) {
        result.bytes[i] = bytes[i] ^ other.bytes[i];
    }
    return result;
}

NodeID generateRandomNodeID() {
    NodeID id;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    for (size_t i = 0; i < id.bytes.size(); i++) {
        id.bytes[i] = dis(gen);
    }
    return id;
}
