#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unistd.h>

#include <gtest/gtest.h>
#include "Tape.h"

namespace fs = std::filesystem;

class Sorter
{
    public:
        Sorter() = default;

        ~Sorter() = default;

        void readConfig(const fs::path &configFileName);

        void startSort(const fs::path &src, const fs::path &out);

        //Для unit-тестирования

        FRIEND_TEST(cfg_reading, invalid_cfg);
        FRIEND_TEST(cfg_reading, valid_cfg);

    private:
        //Функции для сортировки
        [[nodiscard]] size_t            splitIntoTmpTapes(const fs::path &src, const size_t elemCount) const;
        [[nodiscard]] std::vector<int>  sortTape(const Tape &src);
        void                            performOutputTape(std::vector<Tape> &srcTapes, const fs::path &out);

        //Переменные конфига
        size_t      _readWriteDelay;
        size_t      _rewindDelay;
        size_t      _moveDealy;
        size_t      _memoryMax;
};