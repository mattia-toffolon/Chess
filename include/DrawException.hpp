#ifndef DRAWEXCEPTION_HPP
#define DRAWEXCEPTION_HPP

#include <exception>
#include <string>

class DrawException : public std::exception{
    private:
        std::string what_;
    public:
        DrawException(std::string description = "Draw done") : 
            what_ {description} {}

        //override what function
        const std::string what() {
            return what_;
        }
};

#endif