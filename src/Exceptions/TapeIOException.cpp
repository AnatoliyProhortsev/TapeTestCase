#include "TapeIOException.hpp"

TapeIOEX::TapeIOEX():msg("Unable to perform R/W operation with tape") {}

TapeIOEX::TapeIOEX(const char *message): msg(message) {}

const char *TapeIOEX::what() const noexcept
{
    return msg;
}