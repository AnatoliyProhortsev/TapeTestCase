#include "BadConfigException.h"

BadCfgEx::BadCfgEx():msg("Bad config") {}

BadCfgEx::BadCfgEx(const char *message): msg(message) {}

const char *BadCfgEx::what() const noexcept
{
    return msg;
}