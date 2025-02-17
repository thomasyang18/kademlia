#pragma once

struct Config {
    static Config& getInstance() {
        static Config instance;
        return instance;
    }

    const int kBucketSize = 20;
    const int maxBuckets = 256;

    Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
};
