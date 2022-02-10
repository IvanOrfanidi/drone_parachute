#pragma once

#include <map>
#include <memory>
#include <string>

class SPI {
public:
    struct Config {
        uint32_t speed;
    };

    [[nodiscard]] static std::shared_ptr<SPI> instance(const std::string& device);

    std::string getNameDevice() const;
    bool isOpened() const noexcept;

    void open();
    void open(const Config& config);
    void close();

    void setSpeed(uint32_t speed);
    bool setBitPerWord(uint8_t p_bit);

    ~SPI();

private:
    static constexpr int CLOSE = -1;

    SPI(const std::string& device);

    std::string _device;
    Config _config;
    int _spi;

    inline static std::map<std::string, SPI*> _interfaces;
};