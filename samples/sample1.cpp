#include <memory>
#include <iostream>

#include "Logger.h"
#include "StreamSink.h"

int main(int argc, char const *argv[])
{
    Logger logger("test");

    logger.append(std::make_shared<StreamSink>(&std::clog));

    LOG(logger, Logger::LogLevel::info, "Hello," << " world ");

    return 0;
}