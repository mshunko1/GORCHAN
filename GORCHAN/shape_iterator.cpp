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
    m_downs.clear();
    m_ups.clear();
    m_down.clear();
    m_up.clear();
}

void shape_iterator::set_initial_shapes(gvector<base_shape*> input)
{
    m_input = input;
    m_downs.clear();
    m_ups.clear();
    m_down.clear();
    m_up.clear();

    m_state = shape_iterator_state_init;

    auto shapes_map = m_ls_memory->get_index_to_shape_map();
    auto eos_shape = shapes_map->find(eos_shape_index);
    if(eos_shape == shapes_map->end())
    {
        throw new gexception("not found");
    }

    base_shape::link_shapes(input[0], input[1], new rule() , link_type_temproray, false, false);
    for(gint i = 1; i < input.size() - 1; i++)
    {
        base_shape::link_shapes(input[i], input[i + 1], new rule() ,link_type_temproray, false, false);
    }

    base_shape::link_shapes(input[input.size() - 1], eos_shape->second, new rule() ,link_type_temproray, false, false);
    
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
            shape_index shape_ray_index = outs->at(index)->m_shape_to;
            base_shape* shape_ray = m_ls_memory->get_index_to_shape_map()->find(shape_ray_index)->second;
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
            shape_index shape_ray_index = outs->at(index)->m_shape_to;
            base_shape* shape_ray = m_ls_memory->get_index_to_shape_map()->find(shape_ray_index)->second;

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
    return shape_iterator_state_in_up;
}

shape_iterator_state shape_iterator::build_rules()
{
    m_state = shape_iterator_state_in_build_rules;
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
                    base_shape::link_shapes(in_shape, up_shape, new rule() ,link_type_init, false, false);
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
                        rule* r = new rule();
                        r->m_path = path;
                        base_shape* soul_matter_shape = m_ls_memory->get_index_to_shape_map()->find(soul_matter_shape_index)->second;
                        base_shape::link_shapes(in_shape, up_shape, r, link_type_friendly, false, false);
                        rule* smr = new rule();
                        base_shape::link_shapes(up_shape, soul_matter_shape, smr, link_type_soul_matter, false, false);
                        base_shape::link_shapes(soul_matter_shape, in_shape, smr, link_type_soul_matter, false, false);
                    }
                }
            }
        }
    }
    //2.1 если есть FR то собрать все FR и делать FR там где IR анализируя правила всех FR
    else if(fr_count > 0)
    {
        gvector<base_shape*> fr_shapes;
        gvector<link*> fr_links;
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
                    if(link->m_type == link_type_friendly)
                    {
                        fr_shapes.push_back(up_shape);
                        fr_links.push_back(link);
                    }
                }
            }
        }

        for(base_shape* in_shape:m_input)
        {
            for(base_shape* up_shape:m_up)
            {
                linker* up_ins = up_shape->get_ins();
                gint index = 0;
                bool exists = up_ins->exists(in_shape, &index);
                if(exists == true)
                {
                    rule* find_passed_rule = nullptr;
                    base_shape* find_passed_shape = nullptr;
                    link* exst_link = up_ins->at(index);
                    if(exst_link->m_type == link_type_init)
                    {
                        gint o = 0;
                        //foreach all FR rules to find way else build by find_this_way
                        for(link* current_link:fr_links)
                        {
                            o++;
                            //try pass way from rules, pass = up_shape to in_shape
                            auto rules = current_link->m_rules;
                            grule_queue<rule*, gvector<rule*>, rule_priority_queue_comparer> rules_for_processed = rules;
                            bool not_passed_at_all = true;
                           
                            while(rules_for_processed.empty() == false)
                            {
                                rule* rule_for_pass = rules_for_processed.top();
                                rules_for_processed.pop();
                                //try to pass rule
                                base_shape* passirov_shape = up_shape;
                                auto shape_index_to_shape = m_ls_memory->get_index_to_shape_map();
                                gint passed_way_step_count = 0;
                                for(shape_index sh_index:rule_for_pass->m_path)
                                {
                                    auto find_shape_value = shape_index_to_shape->find(sh_index);
                                    if(find_shape_value == shape_index_to_shape->end())
                                    {
                                        //break pass rule
                                        break;
                                    }
                                    base_shape* find_shape_shape = find_shape_value->second;
                                    //пробуем выяснить, имеют ли образы хотя бы одну связь, т.е исходящую или входящую
                                    //проверяем исходящую
                                    linker* out_links = passirov_shape->get_outs();
                                    bool out_link_exist = out_links->exists(find_shape_shape, nullptr);
                                    //проверяем входящую
                                    linker* in_links = find_shape_shape->get_ins();
                                    bool in_link_exist = in_links->exists(passirov_shape, nullptr);

                                    if(out_link_exist == false && in_link_exist == false)
                                    {
                                        break;
                                    }
                                    passirov_shape = find_shape_shape;
                                    passed_way_step_count++;
                                }
                                if(passed_way_step_count == rule_for_pass->m_path.size())
                                {
                                    find_passed_rule = rule_for_pass;
                                    break;
                                }
                            }
                            if(find_passed_rule != nullptr)
                            {
                                find_passed_shape = fr_shapes[o - 1];
                                break;
                            }
                        }
                        if(find_passed_rule != nullptr)
                        {
                            // мы нашли правило по которому достижим образ
                            // оно нужно для того что бы создать новое правило, и добавить его в существующие ???
                            // клонируем правило и увеличиваем его вес и добавляем во все fr связи текущего образа
                            find_passed_rule->up_weight();
                            rule* clone_find_passed_rule = find_passed_rule->clone();
                            base_shape* soul_matter_shape = m_ls_memory->get_index_to_shape_map()->find(soul_matter_shape_index)->second;
                            base_shape::link_shapes(in_shape, up_shape, clone_find_passed_rule, link_type_aquare_by_rule, false, false);
                            rule* smr = new rule();
                            base_shape::link_shapes(up_shape, soul_matter_shape, smr, link_type_soul_matter, false, false);
                            base_shape::link_shapes(soul_matter_shape, in_shape, smr, link_type_soul_matter, false, false);
                        }
                        else
                        {
                            gvector<shape_index> path;
                            gmap<base_shape*, bool> passed_shapes;
                            bool way_exist = find_this_way(up_shape, in_shape, path, passed_shapes);
                            if(way_exist == true)
                            {
                                rule* r = new rule();
                                r->m_path = path;
                                base_shape* soul_matter_shape = m_ls_memory->get_index_to_shape_map()->find(soul_matter_shape_index)->second;
                                base_shape::link_shapes(in_shape, up_shape, r, link_type_friendly, false, false);
                                rule* smr = new rule();
                                base_shape::link_shapes(up_shape, soul_matter_shape, smr, link_type_soul_matter, false, false);
                                base_shape::link_shapes(soul_matter_shape, in_shape, smr, link_type_soul_matter, false, false);
                            }
                        }
                    }
                }
            }
        }
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
        base_shape* shape = m_ls_memory->get_shape(linker->at(i)->m_shape_to);
        
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

shape_iterator_state shape_iterator::get_state()
{
    return m_state;
}