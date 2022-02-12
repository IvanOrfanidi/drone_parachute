#include <command_parser.h>
#include <iostream>

int main(int argc, char* argv[])
{
    CommandParser parse(argc, argv);
    const auto message = parse.getMessage();
    if (!message.empty()) {
        std::cout << message << std::endl;
        return EXIT_SUCCESS;
    }

    auto spi = SPI::getInstance(parse.getDevice());
    spi->open(parse.getConfig());
    spi->close();

    return EXIT_SUCCESS;
}