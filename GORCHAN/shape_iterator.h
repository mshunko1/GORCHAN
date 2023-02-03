#pragma once
#include "pch.h"

enum shape_iterator_state 
    { 
        shape_iterator_state_undefined,
        shape_iterator_state_init,
        shape_iterator_state_in_up,
        shape_iterator_state_in_down,
        shape_iterator_state_in_build_rules,
        shape_iterator_state_synced
    };

class shape_iterator
{
public:
    shape_iterator();
    ~shape_iterator();
    void set_initial_shapes(gvector<base_shape*> input);
    shape_iterator_state build_up();
    shape_iterator_state build_down();
    shape_iterator_state build_rules();

private:
    gvector<base_shape*> m_input;
    gvector<base_shape*> m_down;
    gvector<gvector<base_shape*>> m_downs;
    gvector<base_shape*> m_up;
    gvector<gvector<base_shape*>> m_ups;
    shape_iterator_state m_state;
};

