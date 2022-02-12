#pragma once

#include <project_version.h>
#include <spi.h>

class CommandParser {
public:
    explicit CommandParser(int argc, char* argv[]);

    std::string getDevice() const noexcept;

    SPI::Config getConfig() const noexcept;

    std::string getMessage() const noexcept;

private:
    std::string _device;
    SPI::Config _config;
    std::string _message;
};