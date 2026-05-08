#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <zmq.hpp>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: requester_ps <archivo_solicitudes>\n";
        return 1;
    }

    const std::string input_file = argv[1];
    const std::string gc_endpoint = "tcp://load-manager:5555";

    std::ifstream in(input_file);
    if (!in.is_open()) {
        std::cerr << "No se pudo abrir archivo: " << input_file << "\n";
        return 1;
    }

    zmq::context_t ctx(1);
    zmq::socket_t req(ctx, zmq::socket_type::req);
    req.connect(gc_endpoint);

    std::cout << "[PS] Conectado a " << gc_endpoint << "\n";

    std::string line;
    int sent = 0;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        zmq::message_t req_msg(line.begin(), line.end());
        req.send(req_msg, zmq::send_flags::none);

        zmq::message_t rep_msg;
        if (!req.recv(rep_msg, zmq::recv_flags::none)) {
            std::cerr << "[PS] No se recibio respuesta para: " << line << "\n";
            continue;
        }

        std::cout << "[PS] Solicitud=" << line << " | Respuesta=" 
                  << std::string(static_cast<char*>(rep_msg.data()), rep_msg.size()) << "\n";

        ++sent;
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
    }

    std::cout << "[PS] Total solicitudes enviadas: " << sent << "\n";
    return 0;
}