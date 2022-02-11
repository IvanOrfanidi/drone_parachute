#include <boost/program_options.hpp>
#include <command_parser.h>
#include <limits>

CommandParser::CommandParser(int argc, char* argv[])
{
    bool cpha;
    bool cpol;
    uint32_t bitPerWord;
    uint32_t speed;
    boost::program_options::options_description desc("options");
    desc.add_options()
        //
        ("device,d", boost::program_options::value<std::string>(&_device)->default_value("/dev/spidev1.0"), "device to use(default for manifold 'spidev1.0')")
        //
        ("bpw,b", boost::program_options::value<uint32_t>(&bitPerWord)->default_value(8), "bits per word")
        //
        ("speed,s", boost::program_options::value<uint32_t>(&speed)->default_value(1'000'000), "max speed (Hz)")
        //
        ("cpha,H", boost::program_options::value<bool>(&cpha), "clock phase")
        //
        ("cpol,O", boost::program_options::value<bool>(&cpol), "clock polarity")
        //
        ("version,v", "print version number and exit")
        //
        ("help,h", "produce help message");
    // "  -L --lsb      least significant bit first\n"
    // "  -C --cs-high  chip select active high\n"
    // "  -3 --3wire    SI/SO signals shared\n"
    // "  -v --verbose  Verbose (show tx buffer)\n"
    // "  -p            Send data (e.g. \"1234\\xde\\xad\")\n"
    // "  -N --no-cs    no chip select\n"
    // "  -R --ready    slave pulls low to pause\n"
    // "  -2 --dual     dual transfer\n"
    // "  -4 --quad     quad transfer\n"
    // "  -8 --octal    octal transfer\n"
    boost::program_options::variables_map options;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), options);
    boost::program_options::notify(options);

    if (options.count("help")) {
        std::stringstream ss;
        ss << desc;
        _message = ss.str();
        return;
    }
    if (options.count("version")) {
        _message = "version: " + std::string(PROJECT_VERSION);
        return;
    }

    if (bitPerWord > std::numeric_limits<uint8_t>::max()) {
        bitPerWord = 8;
    }

    _config.bitPerWord = bitPerWord;
    _config.speed = speed;
}

std::string CommandParser::getDevice() const noexcept
{
    return _device;
}

SPI::Config CommandParser::getConfig() const noexcept
{
    return _config;
}

std::string CommandParser::getMessage() const noexcept
{
    return _message;
}