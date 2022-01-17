// Author: Guerrini Alberto

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>

class Logger {
    private:
        std::ofstream log_file;

    public:
        explicit Logger(const std::string& filename);
        ~Logger();
        bool log_move(const std::string& move) const;
};

#endif