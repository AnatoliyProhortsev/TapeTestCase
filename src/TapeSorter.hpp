#ifndef TAPESORTER
#define TAPESORTER

#include <string>
#include <vector>

#include "Tape.hpp"
#include "Config.hpp"

class TapeSorter
{
public:
    TapeSorter();

    ~TapeSorter();

    TapeSorter(const std::string &configPath);

    void setInputTapeFileName(const std::string &path);

    void setOutputTapeFileName(const std::string &path);

    void setConfigFileName(const std::string &path);

    void setConfig(const Config &srcConfig);

    bool sort();

private:
    void sortTape();    // метод будет асинхронным

private:
    std::vector<Tape*> m_tapes;
    Config m_config;
    std::string m_inputTapeFileName;
    std::string m_outputTapeFileName;
};

#endif