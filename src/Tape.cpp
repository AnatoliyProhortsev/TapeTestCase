#include "Tape.hpp"

// Load a tape with (tape_count).txt file 

// Create tape and specify file path
Tape::Tape(const std::string &srcPath)
    : m_path(srcPath) {}

Tape::~Tape()
{

}

// Returns true if magnet head reached end of tape
bool Tape::isEnd() const noexcept
{
    return true;
}

// Read from magnet head position
int Tape::read() const noexcept
{
    return 1;
}

// Write to tape on magnet head position
void Tape::write(const int src) noexcept
{
    
}

// Move magnet head forward
void Tape::moveForward() noexcept
{

}

// Move magnet head backward
void Tape::moveBackward() noexcept
{
    // Ensure that iter != begin()
}

// Rewind magnet head to start position
void Tape::rewind() noexcept
{
    // Магнитная головка откатывается на позицию первого элемента
}

// Load (N) bytes from file to tape
bool Tape::loadTape(const std::size_t &N) 
{
    try
    {
        auto fileSize = std::filesystem::file_size(std::filesystem::path(m_path));
        // Ensure that we reading correct count of elements
        std::cout<<"file size in ints: "<<fileSize<<'\n';

        m_file.open(m_path, std::ios::in | std::ios::binary);
        if(!m_file.is_open())
            throw TapeLoadEx("Unable to open file to load tape\n");

        m_data.resize(N);
        m_file.read(reinterpret_cast<char*>(m_data.data()), N * sizeof(int));

        if(m_data.empty())
            throw EmptyTapeEx();

        m_file.close();
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        m_file.close();
        return false;
    }


    return true;
}

bool Tape::unloadTape()
{
    try
    {
        m_file.open(m_path, std::ios::out | std::ios::binary);

        if(!m_file.is_open())
            throw TapeLoadEx("Unable to open file to load tape\n");

        m_file.write(reinterpret_cast<char*>(m_data.data()), m_data.size() * sizeof(int));
        m_file.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        m_file.close();
        return false;
    }
    
    return true;
}

bool Tape::appendTape(const std::string &filePath)
{
    try
    {
        m_file.open(filePath, std::ios::out | std::ios::app);
        if(!m_file.is_open())
            throw TapeLoadEx("Unable to open file to load tape\n");

        m_file.write(reinterpret_cast<char*>(m_data.data()), m_data.size() * sizeof(int));
        m_file.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        m_file.close();
        return false;
    }

    return true;
}