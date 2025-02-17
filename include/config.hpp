#pragma once

struct Config {
    static Config& getInstance() {
        static Config instance;
        return instance;
    }

    const int K_BUCKET_SIZE = 20;
    const int MAX_BUCKETS = 256;

private:
    Config() = default;
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
};
