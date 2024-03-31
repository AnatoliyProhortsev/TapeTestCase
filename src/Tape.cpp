#include "Tape.h"

Tape::Tape(const fs::path &fileName): TapeInterface(fileName) {}

Tape::Tape(fs::path &&fileName): TapeInterface(std::move(fileName)) {}

Tape::~Tape() = default;

std::vector<int> Tape::readTape(const size_t &elemCount) const
{
    std::vector<int> res;
    try
    {
        std::ifstream inputFile(_fileName, std::ios::in);
        std::istream_iterator<int> start(inputFile), end;
        
        if(elemCount == 0)
            std::copy(start, end, std::back_inserter(res));
        else
        {
            int value;
            size_t readedElems = 0;
            while(inputFile >> value && ++readedElems != elemCount)
                res.push_back(value);
        }
    }
    catch(const std::ios_base::failure & e)
    {
        std::cerr << "Exception during opening/reading/closing tape file" << std::flush;
    }
    return res;
}

void Tape::writeTape(const std::vector<int> &elements)
{
    if(elements.empty())
        throw EmptyTapeEx();
    else
    {
        try
        {
            std::ofstream outputFile(_fileName, std::ios::out);
            std::ostream_iterator<int> output_iterator(outputFile, " ");
            std::copy(elements.begin(), elements.end(), output_iterator);
            outputFile.close();
        }
        catch(const std::exception & e)
        {
            std::cerr << "Exception during opening/writing/closing tape file: "<< e.what() << std::flush;
        }
    }
}

int Tape::readHead() const
{
    try
    {
        std::ifstream inputFile(_fileName, std::ios::in);
        int value;
        inputFile >> value;
        return value;
    }
    catch(const std::ios_base::failure & e)
    {
        std::cerr << "Exception during opening/writing/closing tape file" << std::flush;
    }
}

void Tape::eraseHead()
{
    try
    {
        std::vector<int> tape = readTape(0);
        if(tape.empty())
            throw EmptyTapeEx();
            
        tape.erase(tape.begin());
        writeTape(tape);
    }
    catch(const std::exception &e)
    {
        std::cerr << "Exception during erasing head from tape: "<< e.what() << std::flush;
    }
    
}