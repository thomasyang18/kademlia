#include <iostream>
#include <boost/asio.hpp>
#include "protocol/Networking.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    uint16_t port = std::stoi(argv[1]);

    boost::asio::io_context io_context;
    UDPNode node(io_context, port);

    std::cout << "UDP server started on port " << port << std::endl;
    io_context.run();

    return 0;
}
