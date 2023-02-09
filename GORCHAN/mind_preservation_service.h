#ifndef MIND_PRESERVATION_SERVICE_H
#define MIND_PRESERVATION_SERVICE_H

#pragma once
#include "pch.h"



class mind_preservation_service
{
public:
    mind_preservation_service(ls_memory* memory, bg_context* context);
    ~mind_preservation_service();
    void mind_preserve_operation();

protected:
    bool is_this_shape_passed_to(base_shape* shape, base_shape* to, gint& raycast, gmap<base_shape*, bool>& passed_shapes);
private:
    ls_memory* m_memory;
    bg_context* m_context;
};

#endif