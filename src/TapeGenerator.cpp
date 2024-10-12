#include <random>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

inline int gen_random_int();

// Handle 2 arguments:
// [elements count] [multiply]
int main(int argc, char **argv)
{
    bool multiplyMode;
    if (argc == 3)
    {
        std::cout << "Generating common tape.\n";
        multiplyMode = false;
    }
    else if (argc == 4)
    {
        std::cout << "Generating count*multiply tape\n";
        multiplyMode = true;
    }
    else
    {
        std::cout << "Invalid parameters.\n";
        std::cout << "Usage: ./tapeGenerator [name] [elements count] [opt: multiply]\n";
        return -1;
    }

    std::size_t elementsCount;
    std::size_t multiply;

    std::istringstream stream(argv[1]);

    if (!(stream >> elementsCount))
    {
        std::cout << "Invalid [elementsCount] argument.\n";
        return -1;
    }

    if (multiplyMode)
    {
        stream = std::istringstream(argv[2]);
        if (!(stream >> multiply))
        {
            std::cout << "Invalid [multiply] argument.\n";
            return -1;
        }
    }

    int max = std::numeric_limits<int>::max();
    int min = std::numeric_limits<int>::min();

    std::ofstream outputFile(multiplyMode ? argv[3] : argv[2], std::ios::out);
    if(!outputFile.is_open())
    {
        std::cout<<"Unable to create output file.\n";
        return -1;
    }

    srand(time(0));

    if(multiply)
    {
        for(std::size_t i = 0; i < multiply; i++)
            for(std::size_t j = 0; j < elementsCount; j++)
                outputFile << gen_random_int() << '\n';
    }
    else
        for(std::size_t i = 0; i < elementsCount; i++)
                outputFile << gen_random_int() << '\n';
    
    outputFile.close();
    std::cout<<"Tape created.\n";
    return 0;
}

int gen_random_int() 
{
    const int BITS_PER_RAND = (int)(log2(RAND_MAX/2 + 1) + 1.0);
    int ret = 0;
    for (int i = 0; i < sizeof(int) * CHAR_BIT; i += BITS_PER_RAND) {
        ret <<= BITS_PER_RAND;
        ret |= rand();
    }
    return ret;
}