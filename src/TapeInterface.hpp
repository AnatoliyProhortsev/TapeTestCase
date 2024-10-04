#ifndef TAPEINTERFACE
#define TAPEINTERFACE

class TapeInterface
{
public:
    virtual int read() const = 0;
    virtual void write(const int src) = 0;
    virtual bool isEnd() const = 0;
    virtual void moveForward() = 0;
    virtual void moveBackward() = 0;
    virtual void rewind() = 0;
    virtual ~TapeInterface() = default;
};

#endif // TAPEINTERFACE