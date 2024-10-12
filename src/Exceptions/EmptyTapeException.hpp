#ifndef EMPTYEXCEPTION
#define EMPTYEXCEPTION

#include <exception>
#include <string>

class EmptyTapeEx: public std::exception
{
    public:
        EmptyTapeEx();
        EmptyTapeEx(const char *msg);
        const char *what() const noexcept override;
    private:
        const char* msg;
};

#endif // EMPTYEXCEPTION