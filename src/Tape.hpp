#ifndef TAPE
#define TAPE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

#include <algorithm>
#include <iterator>

#include "TapeInterface.hpp"

// Exceptions
#include "Exceptions/EmptyTapeException.hpp"
#include "Exceptions/TapeLoadException.hpp"
#include "Exceptions/TapeIOException.hpp"

class Tape : public TapeInterface
{
public:
    ~Tape();

    // Create tape and specify file path
    Tape(const std::string &srcPath);

    // Read from magnet head position
    int read() const noexcept override;

    // Write to tape on magnet head position
    void write(const int src) noexcept override;

    // End of tape bool indicator getter
    bool isEnd() const noexcept override;

    // Move magnet head forward
    void moveForward() noexcept override;

    // Move magnet head backward
    void moveBackward() noexcept override;

    // Rewind magnet head to start position
    void rewind() noexcept override;

    // Load (N) bytes from file to tape
    bool loadTape() override;

    // Unload tape to current file
    bool unloadTape();

    // Unload tape to back of existing file
    bool appendTape(const std::string &path);

private:
    std::string                 m_path;
    std::fstream                m_file;
    std::vector<int>            m_data;
    std::vector<int>::iterator  m_head;
};

#endif // TAPE