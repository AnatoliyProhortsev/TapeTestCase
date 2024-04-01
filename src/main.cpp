#include "Sorter.h"

int main(void)
{
    Sorter sorter;
    sorter.readConfig("../cfg/defaultCfg.txt");
    sorter.startSort("../tapes/validInput.txt", "out.txt");
    return 0;
}