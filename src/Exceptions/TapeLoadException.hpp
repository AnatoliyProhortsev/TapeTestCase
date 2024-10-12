#ifndef LOADEXCEPTION
#define LOADEXCEPTION

#include <exception>
#include <string>

class TapeLoadEx: public std::exception
{
    public:
        TapeLoadEx();
        TapeLoadEx(const char *msg);
        const char *what() const noexcept override;
    private:
        const char* msg;
};

#endif // LOADEXCEPTION