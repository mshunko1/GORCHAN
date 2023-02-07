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
    shape_iterator(ls_memory* memory);
    ~shape_iterator();
    void set_initial_shapes(gvector<base_shape*> input);
    shape_iterator_state build_up();
    shape_iterator_state build_down();
    shape_iterator_state build_rules();
    shape_iterator_state get_state();
    void init();
    void deinit();
protected:
    bool find_this_way(base_shape* from, base_shape* to, gvector<shape_index>& path, gmap<base_shape*, bool>& passed_shapes);

private:
    gvector<base_shape*> m_input;
    gvector<base_shape*> m_down;
    gvector<gvector<base_shape*>> m_downs;
    gvector<base_shape*> m_up;
    gvector<gvector<base_shape*>> m_ups;
    volatile shape_iterator_state m_state;
    ls_memory* m_ls_memory;



    void dump_gvector(gvector<base_shape*> vector);
    gofstream* folog;
};

