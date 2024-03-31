#pragma once
#include <exception>
#include <string>

class BadCfgEx: public std::exception
{
    public:
        BadCfgEx();
        BadCfgEx(const char *msg);
        const char *what() const noexcept override;
    private:
        const char *msg;
};

class EmptyTapeEx: public std::exception
{
    public:
        EmptyTapeEx();
        EmptyTapeEx(const char *msg);
        const char *what() const noexcept override;
    private:
        const char* msg;
};