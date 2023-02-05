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

    base_shape::link_shapes(input[0], input[1], link_type_temproray);
    for(gint i = 1; i < input.size() - 1; i++)
    {
        base_shape::link_shapes(input[i], input[i + 1], link_type_temproray);
    }

    base_shape::link_shapes(input[input.size() - 1], eos_shape->second, link_type_temproray);
    
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
            if(index >= outs->size())
            {
                continue;
            }
            base_shape* shape_ray = outs->at(index)->m_shape_to;
            fercher[outs]++;
            auto exist_shape = std::find(m_up.begin(), m_up.end(), shape_ray);
            if(exist_shape == m_up.end())
            {
                m_up.push_back(shape_ray);
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
            if(index >= outs->size())
            {
                continue;
            }
            base_shape* shape_ray = outs->at(index)->m_shape_to;
            fercher[outs]++;
            auto exist_shape = std::find(m_down.begin(), m_down.end(), shape_ray);
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
    gint init_count = 0;
    gint fr_count = 0;
    for(base_shape* in_shape:m_input)
    {
        for(base_shape* up_shape:m_up)
        {
            linker* up_ins = up_shape->get_ins();
            gint index = 0;
            bool exists = up_ins->exists(in_shape, &index);
            if(exists == true)
            {
                link* link = up_ins->at(index);
                if(link->m_type == link_type_init)
                {
                    init_count++;
                }
                if(link->m_type >= link_type_friendly && link->m_type < link_type_soul_matter)
                {
                    fr_count++;
                }
            }
        }
    }
    // build find_rule, at first check fr_rules

    //1 если нет FR создать все IR
    if(fr_count == 0 && init_count == 0)
    {
        for(base_shape* in_shape:m_input)
        {
            for(base_shape* up_shape:m_up)
            {
                linker* up_ins = up_shape->get_ins();
                bool exists = up_ins->exists(in_shape, nullptr);
                if(exists == false)
                { 
                    base_shape::link_shapes(in_shape, up_shape, link_type_init);
                }
            }
        }
    }
    //2 если все IR то пройтись по IR и попробывать создать FR
    else if(fr_count == 0 && init_count > 0)
    {
        for(base_shape* in_shape:m_input)
        {
            for(base_shape* up_shape:m_up)
            {
                linker* up_ins = up_shape->get_ins();
                gint index = 0;
                bool exists = up_ins->exists(in_shape, &index);
                bool do_link = false;
                if(exists == true)
                {
                    link* link = up_ins->at(index);
                    if(link->m_type < link_type_init)
                    {
                        do_link = true;
                    }
                }
                else
                {
                    do_link = true;
                }

                if(do_link == true)
                {
                    gvector<shape_index> path;
                    gmap<base_shape*, bool> passed_shapes;
                    bool way_exist = find_this_way(up_shape, in_shape, path, passed_shapes);
                    if(way_exist == true)
                    {
                        base_shape::link_shapes(in_shape, up_shape, link_type_friendly);
                    }
                }
            }
        }
    }
    //2.1 если есть FR то собрать все FR и делать FR там где IR анализируя правила всех FR
    else if(fr_count > 0)
    {
        
    }
}

bool shape_iterator::find_this_way(base_shape* from, base_shape* to, gvector<shape_index>& path, gmap<base_shape*, bool>& passed_shapes)
{
    if(from == to)
    {
       return true;
    }
    linker* linker = from->get_outs();
    for(gint i = 0; i < linker->size(); i++)
    {
        base_shape* shape = linker->at(i)->m_shape_to;
        if(passed_shapes[shape] == false)
        {
            path.push_back(shape->get_index());
            passed_shapes[shape] = true;
            return find_this_way(shape, to, path, passed_shapes);
        }
    }
    return false;
}

void shape_iterator::deinit()
{

}