#ifndef RULE_PRIORITY_QUEUE_COMPARER_H
#define RULE_PRIORITY_QUEUE_COMPARER_H

#pragma once
#include "../pch.h"

class rule_priority_queue_comparer
{
public:
    rule_priority_queue_comparer();
    ~rule_priority_queue_comparer();
    bool operator() (rule* l, rule* r)
    {
        return l->m_weight > r->m_weight;
    }
private:

};

#endif