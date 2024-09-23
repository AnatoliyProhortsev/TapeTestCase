#pragma once

class ReadWriteInterface
{
    virtual void read() const = 0;
    virtual void write() = 0;
};