#ifndef AP_SECONDMS_MYEXCEPTION_H
#define AP_SECONDMS_MYEXCEPTION_H

#include <iostream>
#include <string>

#define DEF_ERROR -1

int Guard(int check, const std::string &message, int error = DEF_ERROR);

class MyException {
    std::string _message;
    std::system_error _error;

public:
    explicit MyException(const std::string &message);

    std::string GetMessage() { return _message; }

    std::system_error GetError() { return _error; }
};

#endif
