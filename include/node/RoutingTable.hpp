#pragma once

#include <vector>
#include <map>
#include "node/NodeId.hpp"
#include "config.hpp"

class RoutingTable {

public:
    RoutingTable(NodeID self);

    serializable_max_buffer_t findClosestNodes(NodeID target);

private:
    NodeID selfID;
    std::array<serializable_max_buffer_t, 256> buckets;
};
