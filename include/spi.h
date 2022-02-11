#pragma once

#include <linux/const.h>
#include <linux/spi/spidev.h>
#include <map>
#include <string>

class SPI {
public:
    enum Mode {
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
        uint32_t mode;
        uint8_t bitPerWord;
        uint32_t speed;
    };

    [[nodiscard]] static SPI& instance(const std::string& device);

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

    static void clearAll();

    ~SPI();

private:
    static constexpr int CLOSE = -1;

    SPI(const std::string& device);

    std::string _device;
    Config _config;
    int _spi;

    inline static std::map<std::string, SPI*> _interfaces;
};