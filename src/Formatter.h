#ifndef FORMATTER_H
#define FORMATTER_H

#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

#include "Message.h"

class Formatter {
 public:
    Formatter(const std::string &format = std::string{"%t %m"}) :
        format_{format} { } 

    Formatter(const Formatter &) = default;

    Formatter & operator=(const Formatter &) = default;

    ~Formatter() = default;

    friend bool operator==(const Formatter &lhs, const Formatter &rhs) {
        return lhs.format_ == rhs.format_;
    }

    std::string format(const std::string &fmt) {
        std::string prev_format = format_;
        format_ = fmt;
        return prev_format;
    }

    std::string format() const { return format_; }

    std::string format(const Message &msg) const {
        std::ostringstream stream;
        std::time_t time = std::chrono::system_clock::to_time_t(msg.time);
        stream << std::put_time(std::localtime(&time), "%F %T") << " ";
        stream << msg.logger << ":";
        stream << msg.file << ":" << msg.func << ":" << msg.line << " ";
        stream << msg.text;
        return stream.str();
    }

 private:
    std::string format_;
};  // class Formatter

#endif  // FORMATTER_H
