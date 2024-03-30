#include "Tape.h"

Tape::Tape(const fs::path &fileName): TapeInterface(fileName)
{}

Tape::Tape(fs::path &&fileName): TapeInterface(fileName)
{}

std::vector<int> Tape::readTape(const size_t &elemCount = 0) const
{
    if(!elemCount)
    {
        //Полное чтение
    }
    else
    {
        //Чтение n элементов
    }
}

void Tape::writeTape(const std::vector<int> &elements)
{
    if(elements.empty())
    {
        //Выбрасываем исключение пустой ленты
    }
    else
    {
        //Записываем вектор на ленту
    }
}