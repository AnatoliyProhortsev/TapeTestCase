#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include "Sorter.h"
#include "exceptions.h"

const int upper_bound = 5000;
const int lower_bound = -5000;

void generate_big_tape();
void generate_tape(const size_t &elemCount);

TEST(random_tape, valid)
{
    Sorter sorter;
    sorter.readConfig("../cfg/defaultCfg.txt");
    ASSERT_NO_THROW(sorter.startSort("../tapes/testTape.txt", "result1.txt"));

    std::ifstream tape("result1.txt", std::ios::in);
    while(!tape.eof())
    {
        int prev_value, next_value;
        tape >> prev_value;
        if(!tape.eof())
        {
            tape>>next_value;
            ASSERT_TRUE(next_value >= prev_value);
        }
    }
}

TEST(cfg_reading, invalid_cfg)
{
    Sorter sorter;
    ASSERT_THROW(sorter.readConfig("../cfg/invalidCfg.txt"), BadCfgEx);
}

TEST(cfg_reading, valid_cfg)
{
    Sorter sorter;
    sorter.readConfig("../cfg/defaultCfg.txt");
    ASSERT_TRUE(sorter._memoryMax == 1000 &&
                sorter._moveDealy == 0 &&
                sorter._readWriteDelay == 0 && 
                sorter._rewindDelay == 0);
}

int main(int argc, char*argv[])
{
    ::testing::InitGoogleTest(&argc,argv);
    // generate_big_tape();
    generate_tape(10);
    return RUN_ALL_TESTS();
}

void generate_big_tape()
{
    std::ofstream outputTape("../tapes/bigTape.txt", std::ios::out);
    std::cout<<"Generating biiiiig tape....\n";
    // for(int i = 0; i < 20; i++)
        for(int64_t i = INT64_MIN; i < INT64_MAX; i++)
            outputTape << (rand() % (int64_t(upper_bound - lower_bound + 1))) + lower_bound << ' ';
    
    outputTape.close();
}

void generate_tape(const size_t &elemCount)
{
    std::ofstream outputTape("../tapes/testTape.txt", std::ios::out);
    std::cout<<"Generating normal random tape...\n";
    for(size_t i = 0; i < elemCount; i++)
        outputTape << (rand() % (upper_bound - lower_bound + 1)) + lower_bound << ' ';
    
    outputTape.close();
}