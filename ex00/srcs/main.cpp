#include "../includes/Converter.hpp"
#include <iostream>
#include <limits>

int main (int argc, char *argv[])
{
    Converter   converter;

    if (argc != 2)
    {
        std::cerr << "you must provide one litteral to the program" << std::endl;
        return (1);
    }
    converter.initializer(argv[1]);
    if (converter.identifyRealType())
    {
        std::cerr << "you entered an invalid litteral" << std::endl;
        return (1);
    }
    converter.convertToRealType();
    converter.convertToOtherType();
    converter.displayTypes();
    return (0);
}