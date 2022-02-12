#include <boost/program_options.hpp>
#include <command_parser.h>

CommandParser::CommandParser(int argc, char* argv[])
{
    bool cpha = false;
    bool cpol = false;
    bool lsb = false;
    bool csHigh = false;
    bool threeWire = false;
    bool cs = false;
    bool ready = false;
    bool dual = false;
    bool quad = false;
    uint32_t bitPerWord;
    uint32_t speed;

    boost::program_options::options_description desc("options");
    desc.add_options()
        // default for manifold 'spidev1.0'
        ("device,D", boost::program_options::value<std::string>(&_device)->default_value("/dev/spidev1.0"), "device to use(default for manifold 'spidev1.0')")
        //
        ("bpw,b", boost::program_options::value<uint32_t>(&bitPerWord)->default_value(8), "bits per word (8 to 32)")
        //
        ("speed,s", boost::program_options::value<uint32_t>(&speed)->default_value(1'000'000), "max speed (Hz)")
        //
        ("cpha,H", boost::program_options::value<bool>(&cpha), "clock phase")
        //
        ("cpol,O", boost::program_options::value<bool>(&cpol), "clock polarity")
        //
        ("lsb,L", boost::program_options::value<bool>(&lsb), "least significant bit first")
        //
        ("cs-high,C", boost::program_options::value<bool>(&csHigh), "chip select active high")
        //
        ("3wire,3", boost::program_options::value<bool>(&threeWire), "SI/SO signals shared")
        //
        ("no-cs,N", boost::program_options::value<bool>(&cs), "SI/SO signals shared")
        //
        ("ready,R", boost::program_options::value<bool>(&ready), "slave pulls low to pause")
        //
        ("dual,2", boost::program_options::value<bool>(&dual), "dual transfer")
        //
        ("quad,4", boost::program_options::value<bool>(&quad), "quad transfer")
        //
        ("octal,8", boost::program_options::value<bool>(&quad), "octal transfer")
        //
        ("version,v", "print version number and exit")
        //
        ("help,h", "produce help message");

    boost::program_options::variables_map options;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).run(), options);
    boost::program_options::notify(options);

    if (options.count("help")) {
        std::stringstream ss;
        ss << desc;
        _message = ss.str();
    }
    if (options.count("version")) {
        _message = PROJECT_VERSION;
    }

    _config.bitPerWord = (bitPerWord > 32U) ? 32U : bitPerWord;
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