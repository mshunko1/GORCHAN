#ifndef mind_callback_H
#define mind_callback_H

#pragma once
#include <string>

class mind_callback
{
public:
    mind_callback();
    ~mind_callback();
    virtual void fona_callback(std::wstring signal) = 0;
    virtual void stat() = 0;
private:

};

#endif