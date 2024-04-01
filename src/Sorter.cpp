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
    }
    catch(const std::ios_base::failure &)
    {
        throw BadCfgEx();
    }
}

void Sorter::startSort(const fs::path &src, const fs::path &out)
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
        performOutputTape(tmpTapes, out);
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
        sleep(_moveDealy * _readWriteDelay);
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

void Sorter::performOutputTape(std::vector<Tape> &srcTapes, const fs::path &out)
{
    try
    {
        fs::path outC = out;
        if(outC.remove_filename() != "")
            fs::create_directory(outC);
        
        std::ofstream outputFile(out, std::ios::out);

        std::unordered_map<int, int> mapp;
        std::unordered_map<int,int> index_offset;
        std::vector<Tape>::iterator iter;
        std::vector<Tape>::iterator minTapeIter;
        bool firstIter = true;
        for(iter = srcTapes.begin(); iter != srcTapes.end();)
        {
            sleep(_readWriteDelay);
            mapp.insert(std::make_pair(std::distance(srcTapes.begin(), iter), (*iter).readHead()));
            iter++;
        }
        while(!mapp.empty())
        {
            std::pair<int, int> min = *std::min_element(mapp.begin(), mapp.end(),
                [](std::unordered_map<int, int>::value_type a,
                std::unordered_map<int, int>::value_type b)
                    { return a.second < b.second; });

            if(firstIter)
            {
                outputFile << min.second;
                firstIter = false;
            }
            else
                outputFile <<' '<< min.second;

            minTapeIter = srcTapes.begin();
            std::advance(minTapeIter, min.first);
            try
            {
                sleep(_readWriteDelay);
                (*minTapeIter).eraseHead();
                sleep(_readWriteDelay);
                mapp[min.first] = (*minTapeIter).readHead();
            }
            catch(const EmptyTapeEx &)
            {
                mapp.erase(min.first);
            }
            catch(const std::exception& e)
            {
                outputFile.close();
                throw;
            }
        }
        outputFile.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << "\tException while performing output tape: " <<e.what() << '\n';
    }
}