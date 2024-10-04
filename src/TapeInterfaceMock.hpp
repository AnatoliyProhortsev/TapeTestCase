#ifndef TAPEMOCK
#define TAPEMOCK

#include <gmock/gmock.h>

#include "TapeInterface.hpp"

class TapeInterfaceMock: public TapeInterface
{
public:
    ~TapeInterfaceMock() override = default;
    MOCK_CONST_METHOD0(read, int(void));
    MOCK_CONST_METHOD0(isEnd, bool(void));
    MOCK_METHOD1(write, void(int));
    MOCK_METHOD0(moveForward, void(void));
    MOCK_METHOD0(moveBackward, void(void));
};

#endif // TAPEMOCK