// Author: Guerrini Alberto

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>

class Logger {
    private:
        std::ofstream log_file;

    public:
        // constructor for logger class, create a logger for logging moves
        // can set a custom log file or use the default file math_log.txt
        explicit Logger(const bool open_file = true, const std::string& filename = "match_log.txt");
        ~Logger();
        // log a move made through cells from and to
        bool log_move(const std::string& from, const std::string& to);
        // log the color of the player playing in the bottom of the dashboard
        // format BOTTOM_PLAYER=[true|false]
        bool log_player_ID(const bool& player_ID);
        // log using standard [cell]=[piece_type_char] the promotion of the piece 
        bool log_promotion(const std::string& cell, const char piece_type);
};

#endif