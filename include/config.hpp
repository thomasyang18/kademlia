#pragma once
/* no allocate, preferably is serializable, explicitly forbids default constructor */
#include <boost/container/static_vector.hpp>

using serializable_max_buffer_t = boost::container::static_vector<Node, Config::K>;

/*
    Some parts are TODO, this code doesn't compile atm because middle of big refactor. Gonna work on this later
*/

struct Config {
    static constexpr size_t K = 20;  // word size  
    static constexpr size_t W = 256; // word size of the keys

    

    // Delete all constructors and assignment operators
    Config() = delete;
    ~Config() = delete;
    Config(const Config&) = delete;
    Config(Config&&) = delete;
    Config& operator=(const Config&) = delete;
    Config& operator=(Config&&) = delete;
};

