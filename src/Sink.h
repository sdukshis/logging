#ifndef SINK_H
#define SINK_H

#include <string>

class Sink {
 public:
    virtual ~Sink() { }

    virtual void append(const std::string &log) = 0;
};

#endif  // SINK_H
