#ifndef MIND_H
#define MIND_H

#pragma once
#include <string>
#include "mind_callback.h"

class mind
{
public:
    mind();
    ~mind();
    virtual void percive(std::string signal, bool debug) = 0;
    virtual void add_callback(mind_callback* callback) = 0;
    virtual void init() = 0;
private:

};

#ifdef __cplusplus
   extern "C" {
#endif

void get_mind(mind** lvalue);

#ifdef __cplusplus
}
#endif

#endif