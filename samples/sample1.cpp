#line 2 "sample1.cpp"

#include <memory>
#include <iostream>

#include "Logging.h"
#include "StreamSink.h"

ENABLE_LOGGING("sample")

class Foo {
 public:
    Foo() {
        LOG_INFO("Foo created");
    }

    void bar(const char*, int, double, Foo) {
        LOG_INFO("bar called")
    }

    friend std::ostream & operator<<(std::ostream &stream, const Foo &) {
        return stream;
    }

    ~Foo() {
        LOG_INFO("Foo destroyed");
    }
};

int buzz(int a) {
    return a + 1;
}


int main(int argc, char const *argv[])
{
    int b = TRACE(buzz, 1);
    return 0;
}