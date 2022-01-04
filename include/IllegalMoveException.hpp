#ifndef INVALIDMOVEEXCEPTION_HPP
#define INVALIDMOVEEXCEPTION_HPP

#include <exception>
#include <string>

class IllegalMoveException : public std::exception{
    private:
        std::string what_;
    public:
        IllegalMoveException(std::string description = "Illegal move made") : 
            what_ {description} {}

        //override what function
        const std::string what() {
            return what_;
        }
};

#endif