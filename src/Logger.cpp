// Author: Guerrini Alberto

#ifndef LOGGER_CPP
#define LOGGER_CPP

#include "../include/Logger.hpp"

Logger::Logger(const std::string& filename = "match_log.txt") {
    // open an output stream to the file passed as parameter
    log_file.open(filename, std::ofstream::out);
    
    if(log_file.is_open())
        return true;
    else
        throw std::invalid_argument("Parameter filename is not a valid path for a file.");
    return false;
}

Logger::~Logger() {
    log_file.close();
}
bool Logger::log_move(const std::string& move) const;

#endif