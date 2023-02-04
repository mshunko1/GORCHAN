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

    base_shape::link_shapes(input[input.size() - 1], eos_shape->second, link_type_init);
    
    m_down = input;

    m_state = shape_iterator_state_init;
}

shape_iterator_state shape_iterator::build_up()
{
    m_state = shape_iterator_state_in_up; 
    gmap<linker*, gint> fercher;
    bool ferch = true;

    m_up.clear();

    while(ferch == true)
    {
        for(gint i = 0; i < m_down.size(); i++)
        {
            base_shape* shape = m_down[i];
            linker* outs = shape->get_outs();
            gint index = fercher[outs];
            base_shape* shape = outs->at(index);
            fercher[outs]++;
            auto exist_shape = std::find(m_up.begin(), m_up.end(), shape);
            if(exist_shape == m_up.end())
            {
                m_up.push_back(shape);
            }
        }
        gint ferch_reach_end = 0;
        for(auto item:fercher)
        {
            gint index = item.second;
            linker* linker = item.first;
            if(index == linker->size())
            {
                ferch_reach_end++;
            }
        }
        if(ferch_reach_end == m_down.size())
        {
            ferch = false;
        }
    }

    bool eq = false;
    for(auto up:m_ups)
    {
        eq = std::equal(up.begin(), up.end(), m_up.begin());
        if(eq == true)
        {
            break;
        }
    }
    if(eq == false)
    {
        m_ups.push_back(m_up);
    }
    else
    {
        return shape_iterator_state_synced;
    }
}

shape_iterator_state shape_iterator::build_down()
{
    m_state = shape_iterator_state_in_down;
    gmap<linker*, gint> fercher;
    bool ferch = true;

    m_down.clear();

    while(ferch == true)
    {
        for(gint i = 0; i < m_up.size(); i++)
        {
            base_shape* shape = m_up[i];
            linker* outs = shape->get_outs();
            gint index = fercher[outs];
            base_shape* shape = outs->at(index);
            fercher[outs]++;
            auto exist_shape = std::find(m_down.begin(), m_down.end(), shape);
            if(exist_shape == m_down.end())
            {
                m_down.push_back(shape);
            }
        }
        gint ferch_reach_end = 0;
        for(auto item:fercher)
        {
            gint index = item.second;
            linker* linker = item.first;
            if(index == linker->size())
            {
                ferch_reach_end++;
            }
        }
        if(ferch_reach_end == m_down.size())
        {
            ferch = false;
        }
    }
    
    bool eq = false;
    for(auto down:m_downs)
    {
        eq = std::equal(down.begin(), down.end(), m_down.begin());
        if(eq == true)
        {
            break;
        }
    }
    if(eq == false)
    {
        m_downs.push_back(m_down);
    }
    else
    {
        return shape_iterator_state_synced;
    }
}

shape_iterator_state shape_iterator::build_rules()
{

}

void shape_iterator::deinit()
{

}