#ifndef TAPE
#define TAPE

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "TapeInterface.hpp"

class Tape : public TapeInterface
{
public:
    Tape();

    Tape(const std::string &srcPath);

    ~Tape();

    int read() const override;

    void write(const int src) override;

    bool isEnd() const override;

    void moveForward() override;

    void moveBackward() override;

    void rewind() override;

    bool loadTape();

    bool unloadTape();

private:
    std::string         m_path;
    std::ifstream       m_file;
    std::vector<int>    m_data;
    size_t              m_headPos;
};

#endif // TAPE