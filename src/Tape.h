#include "TapeInterface.h"

class Tape: public TapeInterface
{
    public:
        Tape(const fs::path &fileName);

        Tape(fs::path &&fileName);

        ~Tape() override;

        [[nodiscard]] std::vector<int> readTape(const size_t &elemCount = 0) const override;

        void writeTape(const std::vector<int> &elements) override;
};