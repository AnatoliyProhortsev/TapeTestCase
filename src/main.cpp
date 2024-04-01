#include "Sorter.h"

int main(int argc, char **argv)
{
    if(argc <= 1 || argc > 4)
    {
        std::cerr<<"Invalid command-line parameters!\n";
        return -1;
    }
    fs::path cfgPath = argv[1];
    fs::path inputFile = argv[2];
    fs::path outputFile = argv[3];

    if(!cfgPath.has_filename()      || 
        !inputFile.has_filename()   || 
        !outputFile.has_filename()  ||
        !fs::exists(cfgPath)        ||
        !fs::exists(inputFile))
    {
        std::cerr<<"Invalid command-line parameters!\n";
        return -1;
    }

    Sorter sorter;
    sorter.readConfig(cfgPath);
    sorter.startSort(inputFile, outputFile);
    return 0;
}