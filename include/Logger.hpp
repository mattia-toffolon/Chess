// Author: Guerrini Alberto

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>

class Logger {
    private:
        std::ofstream log_file;

    public:
        explicit Logger(const std::string& filename = "match_log.txt");
        ~Logger();
        bool log_move(const std::string& from, const std::string& to);
};

#endif