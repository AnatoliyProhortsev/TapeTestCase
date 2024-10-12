#ifndef TAPEINTERFACE
#define TAPEINTERFACE

class TapeInterface
{
public:
    virtual      ~TapeInterface()     = default;

    virtual bool isEnd()        const = 0;
    virtual int  read()               = 0;
    virtual bool write()              = 0;
    virtual void moveForward()        = 0; 
    virtual void moveBackward()       = 0;
    virtual void rewind()             = 0;

    virtual bool loadTape()   = 0;
    virtual bool unloadTape() = 0;
};

#endif // TAPEINTERFACE