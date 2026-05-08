#include <iostream>
#include <string>
#include <zmq.hpp>

int main() {
    const std::string bind_endpoint = "tcp://*:5557";

    zmq::context_t ctx(1);
    zmq::socket_t rep(ctx, zmq::socket_type::rep);
    rep.bind(bind_endpoint);

    std::cout << "[ACTOR-PRE] REP en " << bind_endpoint << "\n";

    while (true) {
        zmq::message_t msg;
        if (!rep.recv(msg, zmq::recv_flags::none)) {
            continue;
        }

        const std::string body(static_cast<char*>(msg.data()), msg.size());
        std::string response;

        if (body.rfind("PRESTAR|", 0) == 0) {
            // Hardcoded OK response
            response = "OK|prestamo_aprobado|L0001|fecha_entrega=2026-05-19";
            rep.send(zmq::buffer(response), zmq::send_flags::none);
            std::cout << "[ACTOR-PRE] Aprobado prestamo para " << body << "\n";
        } else {
            response = "ERROR|operacion_no_soportada";
            rep.send(zmq::buffer(response), zmq::send_flags::none);
            std::cout << "[ACTOR-PRE] Operacion no soportada: " << body << "\n";
        }
    }

    return 0;
}