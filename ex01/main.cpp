# include "RPN.hpp"

int main ( int argc, char **argv )
{
    if (argc != 2)
    {
        std::cerr << "Error: invalid params" << std::endl;
        return (0);
    }

    try {
        std::string args = std::string(argv[1]);
        std::reverse(args.begin(), args.end());
        RPN test(args);
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}