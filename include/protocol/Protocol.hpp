#pragma once

#include <vector>
#include "node/NodeId.hpp"

enum class MessageType {
    PING,           // Check if node is alive
    PONG,           // Response to PING
    FIND_NODE,      // Request nodes closest to a given ID
    FIND_NODE_REPLY // Response containing a list of nodes
};

struct Message {
    MessageType type;
    Node sender;
    NodeID target;  // Target node (for FIND_NODE)
    std::vector<Node> nodes;  // Nodes returned in response

    // Serialize/deserialize methods should be implemented
};
