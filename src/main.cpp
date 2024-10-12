// #include "TapeSorter.hpp"
// #include "Tape.hpp"
#include <iostream>
#include <sstream>

#include "slowTape.hpp"


int main(int argc, char** argv)
{
    std::cout<<"inputFile: "<<argv[2]<<'\n';
    std::istringstream stream(argv[3]);
    std::size_t maxElementsCount;
    stream >> maxElementsCount;
    SlowTape inputTape(argv[1], argv[2], maxElementsCount);
    inputTape.loadTape();
    std::cout<<"Input file splitted. Result:\n";
    return 0;
}