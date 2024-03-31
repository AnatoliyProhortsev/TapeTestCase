#include "exceptions.h"

BadCfgEx::BadCfgEx():msg("Bad config") {}

BadCfgEx::BadCfgEx(const char *message): msg(message) {}

const char *BadCfgEx::what() const noexcept
{
    return msg;
}

EmptyTapeEx::EmptyTapeEx():msg("Tape is empty") {}

EmptyTapeEx::EmptyTapeEx(const char *message): msg(message) {}

const char *EmptyTapeEx::what() const noexcept
{
    return msg;
}