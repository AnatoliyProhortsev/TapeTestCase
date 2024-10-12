#include "EmptyTapeException.hpp"

EmptyTapeEx::EmptyTapeEx():msg("Tape is empty") {}

EmptyTapeEx::EmptyTapeEx(const char *message): msg(message) {}

const char *EmptyTapeEx::what() const noexcept
{
    return msg;
}