#include "slowTape.hpp"

SlowTape::~SlowTape()
{
    m_inputFile.close();
    m_outputFile.close();
    m_currentData.clear();
}

SlowTape::SlowTape(const fs::path &tmpPath, const fs::path &inputFilePath, const std::size_t &maxElementsCount)
{
    if (!fs::is_directory(tmpPath))
        throw BadCfgEx("Incorrect file path");

    if (!fs::is_regular_file(inputFilePath))
        throw BadCfgEx("Incorrect input file");

    m_maxElementsCount = maxElementsCount;
    m_currentData.resize(m_maxElementsCount);

    m_inputPath = inputFilePath;
    m_tmpPrefix = tmpPath;
}

void SlowTape::rewind() noexcept
{
    m_currentData.clear();
}

inline bool SlowTape::isEnd() const noexcept
{
    return m_inputFile.eof();
}

inline void SlowTape::moveForward() noexcept
{
    m_currentData.push_back(read());
}

inline void SlowTape::moveBackward() noexcept {}

inline bool SlowTape::write()
{
    m_outputFile.write(reinterpret_cast<char *>(m_currentData.data()), m_currentData.size() * sizeof(int));
    return !m_outputFile.bad();
}

inline int SlowTape::read()
{
    m_inputFile >> m_currentElement >> m_delim;

    if (m_inputFile.bad())
        throw TapeIOEX("Bad input file");

    return m_currentElement;
}

bool SlowTape::loadTape() noexcept
{
    m_inputFile.open(m_inputPath);

    if (!m_inputFile.is_open())
        throw TapeLoadEx("Unable to open input file\n");

    if (!createTmpDir())
        throw TapeLoadEx("Unable to create temporary directory\n");

    while (!isEnd())
    {
        m_elementsCount = 0;

        while (!isEnd() && m_elementsCount != m_maxElementsCount)
        {
            moveForward();
            m_elementsCount++;
        }

        if(!isEnd())
        {
            m_currentTape++;
            unloadTape();
            rewind();
        }
    }

    return true;
}

bool SlowTape::unloadTape() noexcept
{
    if(m_currentData.empty())
        throw EmptyTapeEx("Nothing to write to tmp tape");

    fs::path currentTmpFileName = m_currentTmpDir / std::string(std::to_string(m_currentTape) + ".bin");
    m_outputFile.open(currentTmpFileName, std::ios::out | std::ios::binary);

    if(!m_outputFile.is_open())
        throw TapeLoadEx("Unable to create tmp tape");

    bool result = write();
    m_outputFile.close();
    return result;
}

bool SlowTape::createTmpDir()
{
    auto currentDT = std::chrono::system_clock::now();
    auto toTime_t = std::chrono::system_clock::to_time_t(currentDT);
    std::stringstream stringDT;
    stringDT << std::put_time(std::localtime(&toTime_t), "%m_%d_%H_%M_%S");
    fs::create_directory(m_tmpPrefix);
    m_currentTmpDir = m_tmpPrefix / stringDT.str();
    std::cout<<"Current tmp dir: "<<m_currentTmpDir<<'\n';
    return fs::create_directory(m_currentTmpDir);
}
