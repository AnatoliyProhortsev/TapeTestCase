#include "exceptions.h"
#include "Tape.h"

namespace fs = std::filesystem;

class Sorter
{
    public:
        Sorter(fs::path &ConfigfileName);

        void startSort(const fs::path);

    private:
        //Функции для сортировки
        std::vector<Tape>   splitIntoTmpTapes(const std::vector<int> Tape, const int elemCount) const;
        std::vector<int>    sortTape(const Tape &src);

        //Переменные конфига
        size_t      _readWriteDelay;
        size_t      _rewindDelay;
        size_t      _moveDealy;
        size_t      _memoryMax;
        fs::path    _configFileName;
};