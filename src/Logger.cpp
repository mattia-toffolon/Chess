// Author: Guerrini Alberto

#ifndef LOGGER_CPP
#define LOGGER_CPP

#include "../include/Logger.hpp"

Logger::Logger(const bool open_file, const std::string& filename) {
    if(!open_file)
        return;
    // open an output stream to the file passed as parameter
    log_file.open(filename, std::ofstream::out);
    if(!log_file.is_open())
        throw std::invalid_argument("May parameter filename be not a valid path for a file.");
}

Logger::~Logger() {
    log_file.close();
}

bool Logger::log_move(const std::string& from, const std::string& to) {
    if(!log_file.is_open())
        throw std::runtime_error("Log file is not open, can't write");
    log_file << (char)std::toupper(from.at(0)) << from.at(1) << " " << (char)std::toupper(to.at(0)) << to.at(1) << "\n";
    return true;
}

bool Logger::log_player_ID(const bool& player_ID) {
    if(!log_file.is_open())
        throw std::runtime_error("Log file is not open, can't write");
    log_file << "BOTTOM_PLAYER=" << std::noboolalpha << player_ID << "\n";
    return true;
}

bool Logger::log_promotion(const std::string& cell, const char piece_type) {
    if(!log_file.is_open())
        throw std::runtime_error("Log file is not open, can't write");
    log_file << (char)std::toupper(cell.at(0)) << cell.at(1) << "=" << (char)std::toupper(piece_type) << "\n";
    return true;
}

#endif