// Author: Guerrini Alberto

#ifndef CHECKEXCEPTION_HPP
#define CHECKEXCEPTION_HPP

#include <exception>
#include <string>

class CheckException : public std::exception{
    private:
        std::string what_;
    public:
        CheckException(std::string description = "Check made") : 
            what_ {description} {}

        //override what function
        const std::string what() {
            return what_;
        }
};

#endif