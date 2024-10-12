#ifndef SLOWTAPE
#define SLOWTAPE

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <chrono> // for exclusive tmp data stamp
#include <vector>

#include "Exceptions/BadConfigException.hpp"
#include "Exceptions/TapeIOException.hpp"
#include "Exceptions/TapeLoadException.hpp"
#include "Exceptions/EmptyTapeException.hpp"

#include "TapeInterface.hpp"

namespace fs = std::filesystem;

class SlowTape : public TapeInterface
{
public:
    ~SlowTape();
    SlowTape()                               = delete;
    SlowTape(const SlowTape&other)           = delete;
    SlowTape operator=(const SlowTape&other) = delete;
    SlowTape(const fs::path &tmpPath, const fs::path &inputFilepath, const std::size_t &maxElementsCount);

    inline bool isEnd() const noexcept override;
    inline void moveForward() noexcept override;
    inline void moveBackward() noexcept override;
    inline bool write() override;
    inline int read() override;
    void rewind() noexcept override;

    bool loadTape() noexcept;
    bool unloadTape() noexcept;

private:
    bool createTmpDir();

private:
    fs::path m_tmpPrefix;     // 'tmp' path
    fs::path m_inputPath;     // input file path
    fs::path m_currentTmpDir; // current prefix in tmp
    std::ifstream m_inputFile;
    std::ofstream m_outputFile;
    std::vector<int> m_currentData; // Storage for N elements
    std::size_t m_maxElementsCount; // Max tmp file elements count
    std::size_t m_elementsCount;    // Elements to write count
    std::size_t m_currentTape = 0;  // Current tmp tape
    std::size_t m_currentElement;           // Raw file record
    char m_delim;
};

#endif