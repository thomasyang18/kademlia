#include "node/RoutingTable.hpp"
#include "config.hpp"
#include <algorithm>

RoutingTable::RoutingTable() : selfID(NodeID()) {
    buckets.resize(MAX_BUCKETS);  // One bucket per bit
}

RoutingTable::RoutingTable(NodeID self) : selfID(self) {
    buckets.resize(MAX_BUCKETS);  // One bucket per bit
}

void RoutingTable::update(const Node& node) {
    int bucketIdx = xorDistance(node.id, selfID);
    auto& bucket = buckets[bucketIdx];

    // If node is already present, move it to the end (most recently seen)
    auto it = std::find_if(bucket.begin(), bucket.end(), [&](const Node& n) {
        return n.id == node.id;
    });
    if (it != bucket.end()) {
        bucket.erase(it);
    }
    bucket.push_back(node);

    // Enforce a size limit (e.g., k=20 for Kademlia)
    if (bucket.size() > K_BUCKET_SIZE) {
        bucket.erase(bucket.begin());  // Remove oldest
    }
}

std::vector<Node> RoutingTable::findClosestNodes(NodeID target, int k) {
    std::vector<Node> closest;
    // Iterate over buckets, starting with the closest
    for (int i = xorDistance(selfID, target); i < MAX_BUCKETS && closest.size() < k; i++) {
        closest.insert(closest.end(), buckets[i].begin(), buckets[i].end());
    }
    return closest;
}

int RoutingTable::xorDistance(const NodeID& a, const NodeID& b) {
    NodeID dist = a ^ b;
    for (int i = 0; i < MAX_BUCKETS; i++) {
        if ((dist.bytes[i / 8] >> (7 - (i % 8))) & 1) return i;
    }
    return MAX_BUCKETS - 1;
}
