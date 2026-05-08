#include <iostream>
#include <string>
#include <zmq.hpp>

int main() {
    const std::string client_bind = "tcp://*:5555";
    const std::string pub_bind = "tcp://*:5556";
    const std::string prestamo_endpoint = "tcp://actor-prestamo:5557";

    zmq::context_t ctx(1);

    zmq::socket_t rep_client(ctx, zmq::socket_type::rep);
    rep_client.bind(client_bind);

    zmq::socket_t pub_updates(ctx, zmq::socket_type::pub);
    pub_updates.bind(pub_bind);

    zmq::socket_t req_prestamo(ctx, zmq::socket_type::req);
    req_prestamo.connect(prestamo_endpoint);

    std::cout << "[GC] REP clientes en " << client_bind << "\n";
    std::cout << "[GC] PUB eventos en " << pub_bind << "\n";
    std::cout << "[GC] REQ prestamo hacia " << prestamo_endpoint << "\n";

    while (true) {
        zmq::message_t in_msg;
        if (!rep_client.recv(in_msg, zmq::recv_flags::none)) {
            continue;
        }

        const std::string request(static_cast<char*>(in_msg.data()), in_msg.size());
        std::string response;

        // Check operation by looking for first pipe
        size_t pos1 = request.find('|');
        if (pos1 == std::string::npos) {
            response = "ERROR|formato_invalido";
            rep_client.send(zmq::buffer(response), zmq::send_flags::none);
            continue;
        }
        std::string op = request.substr(0, pos1);

        if (op == "DEVOLVER") {
            // Immediately respond OK and publish event
            response = "OK|devolucion_aceptada|L0001";
            rep_client.send(zmq::buffer(response), zmq::send_flags::none);
            const std::string evt = "DEVOLUCION|u001|L0001|2026-05-05T19:33:00Z";
            pub_updates.send(zmq::buffer(evt), zmq::send_flags::none);
            std::cout << "[GC] Evento DEVOLUCION publicado\n";
            continue;
        }

        if (op == "RENOVAR") {
            // Immediately respond OK and publish event
            response = "OK|renovacion_aceptada|nueva_fecha=2026-05-12T19:33:00Z";
            rep_client.send(zmq::buffer(response), zmq::send_flags::none);
            const std::string evt = "RENOVACION|u001|L0001|2026-05-05T19:33:00Z|2026-05-12T19:33:00Z";
            pub_updates.send(zmq::buffer(evt), zmq::send_flags::none);
            std::cout << "[GC] Evento RENOVACION publicado\n";
            continue;
        }

        if (op == "PRESTAR") {
            // Forward to actor_prestamo and relay response
            zmq::message_t fwd(request);
            req_prestamo.send(fwd, zmq::send_flags::none);

            zmq::message_t actor_reply;
            if (!req_prestamo.recv(actor_reply, zmq::recv_flags::none)) {
                response = "ERROR|sin_respuesta_actor_prestamo";
                rep_client.send(zmq::buffer(response), zmq::send_flags::none);
                continue;
            }

            response = std::string(static_cast<char*>(actor_reply.data()), actor_reply.size());
            rep_client.send(zmq::buffer(response), zmq::send_flags::none);
            continue;
        }

        response = "ERROR|operacion_desconocida";
        rep_client.send(zmq::buffer(response), zmq::send_flags::none);
    }

    return 0;
}