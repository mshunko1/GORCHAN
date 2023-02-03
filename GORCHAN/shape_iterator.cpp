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