#pragma once

#include <linux/const.h>
#include <linux/spi/spidev.h>
#include <map>
#include <memory>
#include <string>

class SPI {
public:
    enum Mode : uint32_t {
        TX_OCTAL = _BITUL(13),
        TX_QUAD = SPI_TX_QUAD,
        TX_DUAL = SPI_TX_DUAL,

        RX_OCTAL = _BITUL(14),
        RX_QUAD = SPI_RX_QUAD,
        RX_DUAL = SPI_RX_DUAL,
        READY = SPI_READY,
        CPHA = SPI_CPHA,
        CPOL = SPI_CPOL,

        LSB_FIRST = SPI_LSB_FIRST,
        CS_HIGH = SPI_CS_HIGH,
        THREE_WIRE = SPI_3WIRE,
        NO_CS = SPI_NO_CS,
    };

    struct Config {
        uint32_t mode = 0;
        uint8_t bitPerWord = 8;
        uint32_t speed = 1'000'000;
    };

    [[nodiscard]] static std::shared_ptr<SPI> getInstance(const std::string& device);
    ~SPI();

    SPI(const SPI& other) = default;
    SPI& operator=(const SPI& other) = default;
    SPI(SPI&& other) = default;
    SPI& operator=(SPI&& other) = default;

    std::string getDevice() const noexcept;
    bool isOpened() const noexcept;

    void open();
    void open(const Config& config);
    void close();

    void setConfig(const Config& config);
    Config getConfig() const noexcept;
    void setSpeed(uint32_t speed);
    void setBitPerWord(uint8_t bits);
    void setMode(uint32_t mode);

private:
    static constexpr int CLOSE = -1;

    explicit SPI(const std::string& device);

    std::string _device;
    int _spi;
    Config _config;
    inline static std::map<std::string, std::shared_ptr<SPI>> _interfaces;
};