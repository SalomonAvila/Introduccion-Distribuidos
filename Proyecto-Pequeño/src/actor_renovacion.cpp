#include <iostream>
#include <string>
#include <zmq.hpp>

int main() {
    const std::string pub_endpoint = "tcp://load-manager:5556";
    const std::string topic = "RENOVACION";

    zmq::context_t ctx(1);
    zmq::socket_t sub(ctx, zmq::socket_type::sub);
    sub.connect(pub_endpoint);
    sub.set(zmq::sockopt::subscribe, topic);

    std::cout << "[ACTOR-REN] Escuchando " << topic << " en " << pub_endpoint << "\n";
    while (true) {
        zmq::message_t msg;
        if (!sub.recv(msg, zmq::recv_flags::none)) {
            continue;
        }
        const std::string body(static_cast<char*>(msg.data()), msg.size());
        std::cout << "[ACTOR-REN] " << body << "\n";
    }
    return 0;
}