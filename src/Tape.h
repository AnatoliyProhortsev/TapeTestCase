#pragma once
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "TapeInterface.h"
#include "exceptions.h"

class Tape: public TapeInterface
{
    public:
        Tape(const fs::path &fileName);

        Tape(fs::path &&fileName);

        ~Tape() override;

        // [[nodiscard]] bool checkEOF() const override;

        [[nodiscard]] std::vector<int> readTape(const size_t &elemCount = 0) const override;

        [[nodiscard]] int readHead() const override;

        void eraseHead() override;

        void writeTape(const std::vector<int> &elements) override;
};