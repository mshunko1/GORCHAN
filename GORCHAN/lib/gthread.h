#ifndef GTHREAD_H
#define GTHREAD_H

#pragma once

#include "../pch.h"

template<class T>
class gthread
{
public:
    gthread(std::function<T> f);
    gthread();
    ~gthread();

private:

};

#endif