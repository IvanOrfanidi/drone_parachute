#include <spi.h>

#include <errno.h>
#include <fcntl.h>
#include <linux/const.h>
#include <linux/ioctl.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

extern int errno;

[[nodiscard]] std::shared_ptr<SPI> SPI::instance(const std::string& device) {
    if (device.empty()) {
        throw std::runtime_error("device name cannot be empty");
    }

    const auto itDevice = _interfaces.find(device);
    if (itDevice == _interfaces.end()) {
        _interfaces[device] = new SPI(device);
    }

    return std::shared_ptr<SPI>{ _interfaces[device] };
}

SPI::SPI(const std::string& device)
    : _device(device)
    , _spi(CLOSE)
{
}

SPI::~SPI()
{
    // const auto itDevice = _interfaces.find(_device);
    // if (itDevice != _interfaces.end()) {
    //     bool error = false;
    //     if (isOpened()) {
    //         error = (::close(_spi) < 0);
    //     }
    //     if (!error) {
    //         _interfaces.erase(_device);
    //     }
    // }
}

std::string SPI::getNameDevice() const
{
    return _device;
}

bool SPI::isOpened() const noexcept
{
    return !(_spi <= CLOSE);
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

    setSpeed(config.speed);
    _config = config;
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

void SPI::setSpeed(uint32_t speed)
{
    if (ioctl(_spi, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0 || ioctl(_spi, SPI_IOC_RD_MAX_SPEED_HZ, &speed) < 0) {
        throw std::runtime_error("can't set max speed hz");
    }
    _config.speed = speed;
}