#ifndef TAPEIOEXCEPTION
#define TAPEIOEXCEPTION

#include <exception>
#include <string>

class TapeIOEX: public std::exception
{
    public:
        TapeIOEX();
        TapeIOEX(const char *msg);
        const char *what() const noexcept override;
    private:
        const char* msg;
};

#endif // TAPEIOEXCEPTION