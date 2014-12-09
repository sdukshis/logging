#ifndef STREAMSINK_H
#define STREAMSINK_H

#include "Sink.h"

#include <ostream>

class StreamSink: public Sink {
 public:
    StreamSink(std::ostream *stream) :
        stream_{stream}
    {
        if (!stream_) {
            throw std::invalid_argument("Invalid std::ostream pointer");
        }
    }

    ~StreamSink() override {
        stream_->flush();
    }

    void append(const std::string &log) override {
        *stream_ << log << std::endl;
    }

 private:
    std::ostream *stream_;
};  // class StreamSink
#endif  // STREAMSINK_H
