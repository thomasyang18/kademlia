#pragma once

#include <vector>
#include <algorithm>

#include "node/NodeId.hpp"
#include "config.hpp"

// Come back to this - the idea is that we want to do a lot of parallel queries really quickly so. 

/*
    No logging system for now... 
*/

enum class MessageType {
    PING,           // Check if node is alive
    PONG,           // Response to PING
    FIND_NODE,      // Request nodes closest to a given ID
    FIND_NODE_REPLY // Response containing a list of nodes
};

struct Message {
    /*
        PING: NodeID 
        PONG: NodeID 
        FIND_NODE: 2 * NodeID
        FIND_NODE_REPLY: buffer_t = K * NODEID. This fails when K=1
    */

    static constexpr size_t max_network_length = 
        (
            sizeof(MessageType) + 
            std::max(
                2U * sizeof(NodeID), // FIND_NODE
                sizeof(serializable_max_buffer_t) // PONG
            )
        );

    MessageType type;
    Node sender;
    NodeID target;  // Target node (for FIND_NODE)
    std::vector<Node> nodes;  // Nodes returned in response

    // Serialize/deserialize methods should be implemented
};
