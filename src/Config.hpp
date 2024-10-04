#ifndef CONFIG
#define CONFIG

struct Config
{
    // delays in [msec]
    unsigned m_readDelay;
    unsigned m_writeDelay;
    unsigned m_moveDelay;
    unsigned m_rewindDelay;
};

#endif // CONFIG