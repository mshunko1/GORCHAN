#include "pch.h"
#include "shape_iterator.h"


shape_iterator::shape_iterator(ls_memory* memory)
:m_state(shape_iterator_state_undefined),
m_ls_memory(memory)
{
    
}

void shape_iterator::init()
{
    
}


shape_iterator::~shape_iterator()
{

}

void shape_iterator::set_initial_shapes(gvector<base_shape*> input)
{
    m_input = input;
    m_downs.clear();
    m_ups.clear();
    m_down.clear();
    m_up.clear();

    auto shapes_map = m_ls_memory->get_index_to_shape_map();
    auto eos_shape = shapes_map->find(eos_shape_index);
    if(eos_shape == shapes_map->end())
    {
        throw new gexception("not found");
    }

    base_shape::link_shapes(input[0], input[1], link_type_init);
    for(gint i = 1; i < input.size() - 1; i++)
    {
        base_shape::link_shapes(input[i], input[i + 1], link_type_init);
    }

    m_state = shape_iterator_state_init;
}

shape_iterator_state shape_iterator::build_up()
{
       
}

shape_iterator_state shape_iterator::build_down()
{

}

shape_iterator_state shape_iterator::build_rules()
{

}

void shape_iterator::deinit()
{

}