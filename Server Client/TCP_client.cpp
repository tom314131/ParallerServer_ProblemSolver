#include "TCP_client.h"

std::string server_side::TCP_client::GetLine() {
    int numOfReceivedBytes;
    int bufferLen = (int) sizeof(buffer);
    bzero(buffer, static_cast<size_t>(bufferLen));

    for (;;) {

        if (ManageStrings(buffer, current_string, leftovers)) {
            std::string line = current_string;
            current_string.clear();
            return line;
        }

        bzero(buffer, static_cast<size_t>(bufferLen));

        numOfReceivedBytes = (int) read(sock.sock_fd, buffer,
                                        static_cast<size_t>(bufferLen -
                                                            1));

        if (numOfReceivedBytes < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                throw MyException(ERR_READ_TIMEOUT);
            }
            throw MyException(ERR_READ);
        }
    }
}

void server_side::TCP_client::settimeout(int sec, int usec) {
    sock.settimeout(sec, usec);
}

void server_side::TCP_client::Send(std::string message) {
    Guard(write(sock.sock_fd, message.c_str(), message.size()), ERR_SEND);
}
