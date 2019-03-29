#ifndef AP_SECONDMS_CLIENT_H
#define AP_SECONDMS_CLIENT_H

#include <netdb.h>
#include <strings.h>
#include "../Server Client/TCP_socket.h"

using namespace server_side;

class clientSender {

    bool stop;
    TCP_socket sock;


public:
    static void *OpenClient(void *args);
    static pthread_t Start();

    void init(int port);

    void send(std::string);

    std::string listen();
};


void *clientSender::OpenClient(void *args) {
    clientSender sender;
    std::string msg;

    std::cout << "input:\n>> ";
    std::cin >> msg;

    if (msg != "end") {
        sender.init(stoi(msg));
        std::cout << "input:\n>> ";
        std::cin >> msg;
    }

    while (msg != "end") {
        msg += "\n";
        sender.send(msg);
        msg = sender.listen();

        std::cout << "input:\n>> ";
        std::cin >> msg;
    }
    msg += "\n";
    sender.send(msg);

    std::cout << "client::finished\n";
}

void clientSender::init(int port) {
    struct sockaddr_in serv_addr{};
    struct hostent *server;

    std::string ip = "127.0.0.1";
    server = gethostbyname(ip.c_str());

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;


    if (server == nullptr) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(port);

    /* Now connect to the server */
    if (connect(sock.sock_fd, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
}

void clientSender::send(std::string msg) {
    int n = write(sock.sock_fd, msg.c_str(), msg.size());
    if (n < 0) {
        perror("Error writing to socket");
        exit(1);
    }
}

std::string clientSender::listen() {
    char buffer[256];
    read(sock.sock_fd, buffer, 255);
    return std::string(buffer);
}

pthread_t clientSender::Start() {
    pthread_t trid;
    pthread_create(&trid, nullptr, clientSender::OpenClient, nullptr);
    return trid;
}


#endif