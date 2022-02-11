#include <command_parser.h>
#include <iostream>

int main(/*int argc, char* argv[]*/)
{
    {
        auto& spi = SPI::instance("1");
        std::cout << spi.getDevice() << std::endl;
        spi.open();

        auto& spi_1 = SPI::instance("1");
        std::cout << spi_1.getDevice() << std::endl;
        spi_1.open();
    }

    auto& spi = SPI::instance("1");
    std::cout << spi.getDevice() << std::endl;
    spi.open();
    spi.close();
    // SPI::Config config{ 500'000 };
    // spi->open(config);

    auto& spi1 = SPI::instance("1");
    std::cout << spi1.getDevice() << std::endl;
    spi1.open();

    // CommandParser parse(argc, argv);
    // const auto message = parse.getMessage();
    // if (!message.empty()) {
    //     std::cout << message << std::endl;
    //     return EXIT_SUCCESS;
    // }

    // auto& spi = SPI::instance(parse.getDevice());
    // spi.open(parse.getConfig());
    // spi.close();

    // return EXIT_SUCCESS;
}