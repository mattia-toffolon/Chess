#ifndef CHECKMATEEXCEPTION_HPP
#define CHECKMATEEXCEPTION_HPP

#include <exception>
#include <string>

class CheckMateException : public std::exception{
    private:
        std::string what_;
    public:
        CheckMateException(std::string description = "Check Mate made") : 
            what_ {description} {}

        //override what function
        const std::string what() {
            return what_;
        }
};

#endif