#include "MyException.h"

int Guard(int check, const std::string &message, int error){
    if (check == error) {
        throw MyException(message);
    }
    return check;
}

MyException::MyException(const std::string &message) {
        this->_message = message;
        this->_error = std::system_error(
                std::error_code(errno, std::generic_category()),
                message);
}
