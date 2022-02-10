#include <boost/program_options.hpp>
#include <iostream>
#include <memory>
#include <spi.h>

int main(/*int argc, char* argv[]*/)
{
    {
        auto spi = SPI::instance("1");
        std::cout << spi->getNameDevice() << std::endl;
        spi->open();

        auto spi_1 = SPI::instance("1");
        std::cout << spi_1->getNameDevice() << std::endl;
        spi_1->open();

        // spi.close();
        // spi_1.close();
    }

    // auto spi = SPI::instance("1");
    // std::cout << spi->getNameDevice() << std::endl;
    // // SPI::Config config{ 500'000 };
    // // spi->open(config);

    // auto spi1 = SPI::instance("1");
    // std::cout << spi1->getNameDevice() << std::endl;

    return EXIT_SUCCESS;
}