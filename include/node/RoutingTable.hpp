#pragma once

#include <vector>
#include <map>
#include "node/NodeId.hpp"

class RoutingTable {
public:
    RoutingTable();
    RoutingTable(NodeID self);

    void update(const Node& node);

    std::vector<Node> findClosestNodes(NodeID target, int k = K_BUCKET_SIZE);

private:
    NodeID selfID;
    std::vector<std::vector<Node>> buckets;  // 256 buckets

    int xorDistance(const NodeID& a, const NodeID& b);
};
