#include <spi.h>

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

extern int errno;

[[nodiscard]] std::shared_ptr<SPI> SPI::getInstance(const std::string& device)
{
    if (device.empty()) {
        throw std::runtime_error("device name cannot be empty");
    }

    const auto itInterface = _interfaces.find(device);
    if (itInterface == _interfaces.end()) {
        _interfaces[device] = std::shared_ptr<SPI>(new SPI(device));
    }
    return _interfaces[device];
}

SPI::SPI(const std::string& device)
    : _device(device)
    , _spi(CLOSE)
    , _config({})
{
}

SPI::~SPI()
{
    if (isOpened()) {
        ::close(_spi);
    }
}

std::string SPI::getDevice() const noexcept
{
    return _device;
}

bool SPI::isOpened() const noexcept
{
    return _spi > CLOSE;
}

void SPI::open()
{
    if (!isOpened()) {
        _spi = ::open(_device.data(), O_RDWR);
        if (_spi < 0) {
            //throw std::runtime_error(std::string("can't open spi device. error is ") + strerror(errno));
        }
        _spi = 1;
    }
}

void SPI::open(const SPI::Config& config)
{
    open();
    setConfig(config);
}

void SPI::close()
{
    if (isOpened()) {
        if (::close(_spi) < 0) {
            //throw std::runtime_error(std::string("can't close spi device. error is ") + strerror(errno));
        }
        _spi = CLOSE;
    }
}

SPI::Config SPI::getConfig() const noexcept
{
    return _config;
}

void SPI::setConfig(const Config& config)
{
    setMode(config.mode);
    setBitPerWord(config.bitPerWord);
    setSpeed(config.speed);
}

void SPI::setSpeed(uint32_t speed)
{
    if (ioctl(_spi, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0 || ioctl(_spi, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) {
        throw std::runtime_error("can't set max speed hz");
    }
    _config.speed = speed;
}

void SPI::setBitPerWord(uint8_t bitPerWord)
{
    if (ioctl(_spi, SPI_IOC_WR_BITS_PER_WORD, &bitPerWord) < 0 || ioctl(_spi, SPI_IOC_RD_BITS_PER_WORD, &bitPerWord) < 0) {
        throw std::runtime_error("can't set bits per word");
    }
    _config.bitPerWord = bitPerWord;
}

void SPI::setMode(uint32_t mode)
{
    if (ioctl(_spi, SPI_IOC_WR_MODE, &mode) < 0 || ioctl(_spi, SPI_IOC_RD_MODE, &mode) < 0) {
        throw std::runtime_error("can't set spi mode");
    }
    _config.mode = mode;
}