#include "Sorter.h"

void Sorter::readConfig(const fs::path &ConfigFileName)
{
    std::ifstream configFile;

    try
    {
        configFile.open(ConfigFileName, std::ios::in);
        configFile >> _readWriteDelay;
        configFile >> _rewindDelay;
        configFile >> _moveDealy;
        configFile >> _memoryMax;
        if(_memoryMax <= 0)
            throw BadCfgEx();

        std::cout<<"Config values:\n"
        <<"rw delay: "<<_readWriteDelay<<'\n'
        <<"rew delay: "<<_rewindDelay<<'\n'
        <<"mov delay: "<<_moveDealy<<'\n'
        <<"memory lim: "<<_memoryMax<<'\n';
        configFile.close();
    
    }catch (const std::exception & e) {
        std::cerr << "Exception during opening/reading/closing config file: "<<e.what() << std::flush;
    }
}

void Sorter::startSort(const fs::path &src)
{
    try
    {
        std::cout<<"Splitting input tape..\n";
        size_t tapesCount = splitIntoTmpTapes(src, _memoryMax);
        std::cout<<"Input tape splitted!\n";
        std::vector<Tape> tmpTapes;

        for(size_t i = 1; i <= tapesCount; ++i)
        {
            Tape tmpTape("tmp/tmpTape" + std::to_string(i) + ".txt");
            std::vector<int> sortedData = sortTape(tmpTape);
            tmpTape.writeTape(sortedData);
            tmpTapes.push_back(tmpTape);
        }
        std::cout<<"Temporary tapes sorted\nStarted performing result tape\n";
        performOutputTape(tmpTapes);
        std::cout<<"Done!\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception in main sort function: " << e.what() << '\n';
    }
}

size_t Sorter::splitIntoTmpTapes(const fs::path &src, const size_t elemCount) const
{
    try
    {
        std::ifstream inputFile(src, std::ios::in);
        if(inputFile.eof())
            throw EmptyTapeEx("Input tape is empty");
        if(!fs::create_directory("tmp") && !fs::exists("tmp"))
            throw BadCfgEx("Can't create tmp folder");

        std::ofstream curOutputTape;
        size_t curTape = 1;
        size_t curElem = 0;
        int value;

        while(!inputFile.eof())
        {
            curOutputTape.open(
                "tmp/tmpTape" + std::to_string(curTape++) + ".txt",
                std::ios::out);

            curElem = 0;
            while(++curElem <= elemCount && !inputFile.eof())
            {
                inputFile >> value;
                curOutputTape << value << ' ';
            }
            curOutputTape.close();
        }
        curTape--;
        return curTape;
    }
    catch(const std::exception& e)
    {
        std::cerr << "\tException while splitting input tape: "<< e.what() << '\n';
    }
}

std::vector<int> Sorter::sortTape(const Tape &src)
{
    try
    {
        std::vector<int> data = src.readTape(0);
        if(data.empty())
            throw EmptyTapeEx();

        std::sort(data.begin(), data.end());
        return data;
    }
    catch(const std::exception& e)
    {
        std::cerr << "\tException while sorting a tape: " << e.what() << '\n';
    }
}

void Sorter::performOutputTape(const std::vector<Tape> &srcTapes)
{
    //Берём минимальный элемент - записываем в выходную ленту
}