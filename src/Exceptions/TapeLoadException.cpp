#include "TapeLoadException.hpp"

TapeLoadEx::TapeLoadEx():msg("Unable to load tape") {}

TapeLoadEx::TapeLoadEx(const char *message): msg(message) {}

const char *TapeLoadEx::what() const noexcept
{
    return msg;
}