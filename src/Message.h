#ifndef MESSAGE_H
#define MESSAGE_H

#include <chrono>
#include <string>
#include <cstdint>

struct Message {
    using time_point = std::chrono::system_clock::time_point;

    Message(const std::string &logger_,
            const std::string &text_, time_point time_ = std::chrono::system_clock::now(),
            const std::string &file_ = std::string(),
            const std::string &func_ = std::string(),
            std::size_t line_ = 0,
            std::size_t pid_ = 0, std::size_t tid_ = 0) :
        logger{logger_},
        text{text_},
        time{time_},
        file{file_},
        func{func_},
        line{line_},
        pid{pid_},
        tid{tid_} { }

    std::string logger;
    std::string text;
    time_point time;
    std::string file;
    std::string func;
    std::size_t line;
    std::size_t pid;
    std::size_t tid;
};

bool operator==(const Message &lhs, const Message &rhs) {
    return lhs.logger == rhs.logger &&
           lhs.text == rhs.text &&
           lhs.file == rhs.file &&
           lhs.func == rhs.func &&
           lhs.line == rhs.line &&
           lhs.pid  == rhs.pid  &&
           lhs.tid  == rhs.tid;
}

bool operator!=(const Message &lhs, const Message &rhs) {
    return !(lhs == rhs);
}

#endif  // MESSAGE_H