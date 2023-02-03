#ifndef GORCHAN_H
#define GORCHAN_H

#pragma once
#include "pch.h"
#include "mind.h"

class GORCHAN:public mind
{
public:
    GORCHAN();
    ~GORCHAN();
    void init();
    void deinit();
    virtual void percive(std::string signal);
    virtual void add_callback(mind_callback* callback);
private:
    gvector<mind_callback*> m_callbacks;
    shape_iterator* m_shape_iterator;
    ls_memory* m_memory;
};

#endif