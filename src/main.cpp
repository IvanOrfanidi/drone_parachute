#include <boost/program_options.hpp>
#include <iostream>
#include <memory>
#include <spi.h>

int main(/*int argc, char* argv[]*/)
{
    {
        auto& spi = SPI::instance("1");
        std::cout << spi.getNameDevice() << std::endl;
        spi.open();

        auto& spi_1 = SPI::instance("1");
        std::cout << spi_1.getNameDevice() << std::endl;
        spi_1.open();
    }

    auto& spi = SPI::instance("1");
    std::cout << spi.getNameDevice() << std::endl;
    spi.open();
    spi.close();
    // SPI::Config config{ 500'000 };
    // spi->open(config);

    auto& spi1 = SPI::instance("1");
    std::cout << spi1.getNameDevice() << std::endl;
    spi1.open();

    return EXIT_SUCCESS;
}