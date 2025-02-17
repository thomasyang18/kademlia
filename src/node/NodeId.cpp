#include "node/NodeId.hpp"

NodeID NodeID::operator^(const NodeID& other) const {
    NodeID result;
    for (size_t i = 0; i < bytes.size(); i++) {
        result.bytes[i] = bytes[i] ^ other.bytes[i];
    }
    return result;
}
