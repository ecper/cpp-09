#include "BitcoinExchange.hpp"

int main ( int argc, char **argv )
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return (1);
    }

    try {
        BitcoinExchange test(argv[1]);
    } catch (std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return (1);
    }
    return (0);
}