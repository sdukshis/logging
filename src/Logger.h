#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <memory>
#include <vector>
#include <utility>

#include "Message.h"
#include "Sink.h"
#include "Formatter.h"

class Logger {
 public:
    Logger(const std::string &name) :
        name_{name},
        logLevel_{LogLevel::info} { }

    Logger(const Logger &) = delete;

    Logger(Logger &&other) noexcept :
        name_{std::move(other.name_)},
        logLevel_{other.logLevel_},
        sink_list_{std::move(other.sink_list_)},
        formatter_{std::move(other.formatter_)} { }


    Logger & operator=(const Logger &) = delete;

    Logger & operator=(Logger &&other) noexcept {
        name_ = std::move(other.name_);
        logLevel_ = other.logLevel_;
        sink_list_ = std::move(other.sink_list_);
        formatter_ = std::move(other.formatter_);

        return *this;
    }

    ~Logger() { }

    friend bool operator==(const Logger &, const Logger &);

    Formatter formatter(const Formatter &fmt) {
        Formatter prev_fmt = formatter_;
        formatter_ = fmt;
        return prev_fmt;
    }

    Formatter formatter() const { return formatter_; }

    void append(std::shared_ptr<Sink> sink) {
        sink_list_.emplace_back(std::move(sink));
    }

    void clear_sink() {
        sink_list_.clear();
    }

    void log(const Message &msg) {
        auto log_str = formatter_.format(msg);
        for (auto &sink: sink_list_) {
            sink->append(log_str);
        }
    }

    enum class LogLevel {
        trace,
        debug,
        warn,
        info,
        error,
        fatal,
        off
    };

    bool active(LogLevel ll) const {
        return logLevel_ != LogLevel::off &&
               static_cast<int>(logLevel_) <= static_cast<int>(ll);
    }

    LogLevel logLevel(LogLevel ll) {
        LogLevel prev_level = logLevel_;
        logLevel_ = ll;
        return prev_level;
    }

    LogLevel logLevel() const { return logLevel_; }

 private:
    std::string name_;
    LogLevel logLevel_;
    std::vector<std::shared_ptr<Sink>> sink_list_;
    Formatter formatter_;
};  // class Logger

#define LOG(logger, logLevel, expr)             \
    if (logger.active(logLevel)) {              \
        std::ostringstream stream;              \
        stream << expr;                         \
        logger.log(Message(stream.str()));      \
    }                                           \


#endif  // LOGGER_H
