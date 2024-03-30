#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class TapeInterface
{
    public:
        TapeInterface(const fs::path &fileName): _fileName(fileName) {}

        TapeInterface(fs::path &&fileName): _fileName(std::move(fileName)) {}

        [[nodiscard]] virtual std::vector<int> readTape(const size_t &elemCount = 0) const = 0;

        virtual void writeTape(const std::vector<int> &elements) = 0;

        virtual ~TapeInterface() = default;

    private:
        fs::path _fileName;
};