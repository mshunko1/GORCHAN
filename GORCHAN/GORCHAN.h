#ifndef GORCHAN_H
#define GORCHAN_H

#pragma once
#include "pch.h"
#include "mind.h"

enum mind_status {mind_status_undefined, mind_status_ready_to_new_signal, mind_status_in_proc, mind_status_eat_context};

extern "C" class GORCHAN:public mind
{
public:
    GORCHAN();
    ~GORCHAN();
    void init();
    void deinit();
    virtual void percive(std::string signal);
    virtual void add_callback(mind_callback* callback);

protected:
    void mind_proc();
    void react_proc();

private:
    gvector<mind_callback*> m_callbacks;
    gqueue<gvector<base_shape*>> m_input_q;
    shape_iterator* m_shape_iterator;
    ls_memory* m_memory;
    ear* m_ear;
    bg_context* m_context;
    gthread m_mind_proc;
    gthread m_react_proc;
    mind_status m_mind_status;
};

#endif