
#include "TCP_socket.h"

void server_side::TCP_socket::settimeout(int sec, int usec) {
    timeval timeout{};
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;

    // setting socket option for recieve timeout
    Guard(setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO,
                     (char *) &timeout, sizeof(timeout)), ERR_OPT);
}

void server_side::TCP_socket::close() {
    Guard(::close(sock_fd), ERR_CLOSE);
}
