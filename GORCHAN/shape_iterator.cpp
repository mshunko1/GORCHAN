#include "pch.h"
#include "shape_iterator.h"


shape_iterator::shape_iterator(ls_memory* memory, bg_context* context)
:m_state(shape_iterator_state_undefined),
m_context(context),
m_ls_memory(memory)
{
   
}

void shape_iterator::dump_gvector(gvector<base_shape*> &vector)
{
    for(base_shape* shape:vector)
    {
        std::wcout << shape->get_guid() << L" ; ";
    }

}

void shape_iterator::dump_gvector(bg_context* vector)
{
     std::wcout<<L"CONTEXT:"<<std::endl;
    for(gint i = 0; i < vector->size(); i++)
    {
        std::wcout<<vector->at(i)->get_guid()<<L"   index:"<<vector->at(i)->get_index()<<std::endl;
    }
}

void shape_iterator::init()
{
    
}

shape_iterator::~shape_iterator()
{
    m_down.clear();
    m_up.clear();
}

void shape_iterator::set_initial_shapes(gvector<base_shape*> input)
{
    m_input = input;
    m_down.clear();
    m_up.clear();
 
    base_shape::link_shapes(input[0], input[1], new rule() , link_type_temproray, false, false);
    for(gint i = 1; i < input.size() - 1; i++)
    {
        base_shape::link_shapes(input[i], input[i + 1], new rule() ,link_type_temproray, false, false);
    }
    m_ls_memory->reset_raycast();
    m_up = input;

    m_state = shape_iterator_state_init;
    context_was_merged = false;
    std::wcout << L"init_was:---------------------------------------------------------------------------------------------------------";
    dump_gvector(m_input);
    std::wcout << std::endl;
}

shape_iterator_state shape_iterator::build_up()
{
    m_state = shape_iterator_state_in_up; 
    gmap<linker*, gint> fercher;
    bool ferch = true;
    std::wcout<<L"build_up look at m_down:----------------------";
    dump_gvector(m_down);
    std::wcout<<std::endl;
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
            link* shape_ray_link = outs->at(index);
            shape_index shape_ray_index = outs->at(index)->m_shape_to;
            base_shape* shape_ray = m_ls_memory->get_shape(shape_ray_index);
            fercher[outs]++;
            auto exist_shape = std::find(m_up.begin(), m_up.end(), shape_ray);
            if(exist_shape == m_up.end())
            {
                if(shape->can_be_raised(false) == false)
                {
                    std::wcout<<L"CAN NOT ADD IN up FROM CONDITION 2: "<<shape->get_guid()<<L" SHAPE:"<<shape_ray->get_guid()<<L" BECAUSE OF RAYCAST?:"<<shape->can_be_raised(true)<<std::endl;
                    continue;
                }
                std::wcout<<L"up FROM: "<<shape->get_guid()<<L" WE ADD:    "<<shape_ray->get_guid()<<std::endl;
                m_up.push_back(shape_ray); 
            }
            else
            { 
                std::wcout<<L"CAN NOT ADD IN up FROM: "<<shape->get_guid()<<L" SHAPE:"<<shape_ray->get_guid()<<L" BECAUSE OF RAYCAST?:"<<shape->can_be_raised(true)<<std::endl;
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
        if(ferch_reach_end == fercher.size())
        {
            ferch = false;
        }
    }

    std::wcout<<L"ups:";
    dump_gvector(m_up);
    std::wcout<<std::endl;


    if(fercher.size() == 0)
    {
        return shape_iterator_state_synced;
    }
    return shape_iterator_state_in_up;
}

shape_iterator_state shape_iterator::build_down()
{
    m_state = shape_iterator_state_in_down;
    gmap<linker*, gint> fercher;
    bool ferch = true;
    std::wcout<<L"build_down look at m_up:------------------";
    dump_gvector(m_up);
    std::wcout<<std::endl;
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
            link* shape_ray_link = outs->at(index);
            shape_index shape_ray_index = outs->at(index)->m_shape_to;
            base_shape* shape_ray = m_ls_memory->get_shape(shape_ray_index);

            fercher[outs]++;
            auto exist_shape = std::find(m_down.begin(), m_down.end(), shape_ray);
            if(exist_shape == m_down.end())
            {
                if(shape->can_be_raised(false) == false)
                {
                    std::wcout<<L"CAN NOT ADD IN downd FROM CONDITION 2: "<<shape->get_guid()<<L" SHAPE:"<<shape_ray->get_guid()<<L" BECAUSE OF RAYCAST?:"<<shape->can_be_raised(true)<<std::endl;
                    continue;
                }

                std::wcout<<L"down FROM: "<<shape->get_guid()<<L" WE ADD:"<<shape_ray->get_guid()<<std::endl;
                m_down.push_back(shape_ray);
            }
            else
            {
                std::wcout<<L"CAN NOT ADD IN up FROM: "<<shape->get_guid()<<L" SHAPE:"<<shape_ray->get_guid()<<L" BECAUSE OF RAYCAST?:"<<shape->can_be_raised(true)<<std::endl;
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
        if(ferch_reach_end == fercher.size())
        {
            ferch = false;
        }
    }
    
 
    std::wcout<<L"downs:";
    dump_gvector(m_down);
    std::wcout<<std::endl;

    if(fercher.size() == 0)
    {
        return shape_iterator_state_synced;
    }
    return shape_iterator_state_in_down;
}

shape_iterator_state shape_iterator::build_rules()
{
    std::wcout<<std::endl;
    std::wcout<<L" ------- BUILD RULES -------------"<<std::endl;
     
    context_was_merged = false;

    m_state = shape_iterator_state_in_build_rules;
    gint init_count = 0;
    gint fr_count = 0;
    gint tr_count = 0;
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
                if (link->m_type == link_type_temproray)
                {
                    tr_count++;
                }
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
   /* if (tr_count > 0)
    {
        for (base_shape* in_shape : m_input)
        {
            for (base_shape* up_shape : m_up)
            {
                linker* up_ins = up_shape->get_ins();
                gint index = -1;
                if (up_ins->exists(in_shape, &index) == true)
                {
                    link* link = up_ins->at(index);
                    if (link->m_type == link_type_temproray)
                    {
                        base_shape::link_shapes(in_shape, up_shape, new rule(), link_type_init, false, true);
                    }
                }
            }
        }
    }*/

    bool tr_to_init_operation = false;
    bool init_to_fr_operation = false;
    bool fr_to_aqr_operation = false;

    if (tr_count >= init_count && tr_count >= fr_count)
    {
        tr_to_init_operation = true;
    }
    else if (init_count >= tr_count  && init_count >= fr_count)
    {
        init_to_fr_operation = true;
    }
    else if (fr_count >= tr_count && fr_count >= init_count)
    {
        fr_to_aqr_operation = true;
    }
    if ((tr_to_init_operation + init_to_fr_operation + fr_to_aqr_operation) > 1)
    {
        throw new gexception("");
    }
    bool breaker = false;
    //1 если нет FR создать все IR
    if(tr_to_init_operation == true)
    {
        for(base_shape* in_shape:m_input)
        {
            for(base_shape* up_shape:m_up)
            {
                if (soul_matter_shape::get_instance() == up_shape)
                {
                    continue;
                }
                linker* up_ins = up_shape->get_ins();
                bool exists = up_ins->exists(in_shape, nullptr);
                if(exists == false && in_shape != up_shape)
                {
                    base_shape::link_shapes(in_shape, up_shape, new rule() ,link_type_init, false, true);
                }
            }
        }
    }
    //2 если все IR то пройтись по IR и попробывать создать FR
    else if(init_to_fr_operation == true)
    {
        for(base_shape* in_shape:m_input)
        {
            for(base_shape* up_shape:m_up)
            {
                if (soul_matter_shape::get_instance() == up_shape)
                {
                    continue;
                }
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
                    if(up_shape == in_shape)
                    {
                        continue;
                    }
                    gvector<shape_index> path;
                    gmap<base_shape*, bool> passed_shapes;
                    gint ray_cast_size = up_shape->raycast_size();
                    bool way_exist = find_this_way(up_shape, in_shape, path, ray_cast_size, passed_shapes);
                    if(way_exist == true && in_shape != up_shape)
                    {
                        rule* r = new rule();
                        r->m_path = path;
                        base_shape* soul_matter_shape = m_ls_memory->get_shape(soul_matter_shape_index);
                        base_shape::link_shapes(in_shape, up_shape, r, link_type_friendly, false, true);
                        rule* smr = new rule();
                        base_shape::link_shapes(up_shape, soul_matter_shape, smr, link_type_soul_matter, false, true);
                        base_shape::link_shapes(soul_matter_shape, in_shape, smr, link_type_soul_matter, false, true);
 
                        std::wcout << L"&&&&&&&&&&&&&&&&&&& SM FROM:" << up_shape->get_guid() << L"  TO   " << in_shape->get_guid() << std::endl;
                        breaker = true;



                        if ( context_was_merged == false)
                        { 
                            std::wcout << L"CONTEXT ADD TO CONTEXT:" << up_shape->get_guid() << std::endl;
                            m_context->add_shape(up_shape);
                            std::wcout << L"CONTEXT OPERATION 3:" << m_context->try_merge(context_was_merged) << std::endl;
                        }
                        else
                        {
                            std::wcout << L"CONTEXT OPERATION 3:              ALREADY MERGED BUT WE TRY ADD:" << up_shape->get_guid()<< std::endl;
                        }
                        std::wcout << L"CONTEXT:";
                        dump_gvector(m_context);
                        std::wcout << std::endl;
                        breaker = true;
                    }
                }
                if (breaker == true)
                {
                  //  break;
                }
            }
            //context_was_merged = false;
            if (breaker == true)
            {
               //  break;
            }
        }
    }
    //2.1 если есть FR то собрать все FR и делать FR там где IR анализируя правила всех FR
    else if(fr_to_aqr_operation == true)
    {
        gvector<base_shape*> fr_shapes;
        gvector<link*> fr_links;
        for(base_shape* in_shape:m_input)
        {
            for(base_shape* up_shape:m_up)
            {
                if (soul_matter_shape::get_instance() == up_shape)
                {
                    continue;
                }
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
                if (soul_matter_shape::get_instance() == up_shape)
                {
                    continue;
                }
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
                                gint passed_way_step_count = 0;
                                for(shape_index sh_index:rule_for_pass->m_path)
                                {
                                    auto find_shape_value = m_ls_memory->get_shape(sh_index);
                                    if(find_shape_value == nullptr)
                                    {
                                        //break pass rule
                                        break;
                                    }
                                    base_shape* find_shape_shape = find_shape_value;
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
                        if(find_passed_rule != nullptr && in_shape != up_shape)
                        {
                            // мы нашли правило по которому достижим образ
                            // оно нужно для того что бы создать новое правило, и добавить его в существующие ???
                            // клонируем правило и увеличиваем его вес и добавляем во все fr связи текущего образа
                            find_passed_rule->up_weight();
                            rule* clone_find_passed_rule = find_passed_rule->clone();
                            base_shape* soul_matter_shape = m_ls_memory->get_shape(soul_matter_shape_index);
                            base_shape::link_shapes(in_shape, up_shape, clone_find_passed_rule, link_type_aquare_by_rule, false, true);
                            rule* smr = new rule();
                            base_shape::link_shapes(up_shape, soul_matter_shape, smr, link_type_soul_matter, false, true);
                            base_shape::link_shapes(soul_matter_shape, in_shape, smr, link_type_soul_matter, false, true); 
                            std::wcout << L"&&&&&&&&&&&&&&&&&&& SM FROM:" << up_shape->get_guid() << L"  TO   " << in_shape->get_guid() << std::endl;






                            if (context_was_merged == false)
                            {
                                std::wcout << L"CONTEXT ADD TO CONTEXT:" << up_shape->get_guid() << std::endl;
                                m_context->add_shape(up_shape);
                                std::wcout << L"CONTEXT OPERATION 1 :" << m_context->try_merge(context_was_merged) << std::endl;
                            }
                            else
                            {
                                std::wcout << L"CONTEXT OPERATION 1:                         ALREADY MERGED   BUT WE TRY ADD:"<< up_shape->get_guid() << std::endl;
                            }
                            breaker = true;
                            std::wcout << L"CONTEXT:";
                            dump_gvector(m_context);
                            std::wcout << std::endl;
                        }
                        else
                        {
                            gvector<shape_index> path;
                            gmap<base_shape*, bool> passed_shapes;
                            gint ray_cast_size = up_shape->raycast_size();
                            bool way_exist = find_this_way(up_shape, in_shape, path, ray_cast_size, passed_shapes);
                            if(way_exist == true && in_shape != up_shape)
                            {
                                rule* r = new rule();
                                r->m_path = path;
                                base_shape* soul_matter_shape = m_ls_memory->get_shape(soul_matter_shape_index);
                                base_shape::link_shapes(in_shape, up_shape, r, link_type_friendly, false, true);
                                rule* smr = new rule();
                                base_shape::link_shapes(up_shape, soul_matter_shape, smr, link_type_soul_matter, false, true);
                                base_shape::link_shapes(soul_matter_shape, in_shape, smr, link_type_soul_matter, false, true);
                                std::wcout << L"&&&&&&&&&&&&&&&&&&& SM FROM:" << up_shape->get_guid() <<L"  TO   "<< in_shape ->get_guid()<< std::endl;
                               


                                if ( context_was_merged == false)
                                {
                                    std::wcout << L"CONTEXT ADD TO CONTEXT:" << up_shape->get_guid() << std::endl;
                                    m_context->add_shape(up_shape);
                                    std::wcout << L"CONTEXT OPERATION 2:" << m_context->try_merge(context_was_merged) << std::endl;
                                }
                                else
                                {
                                    std::wcout << L"CONTEXT OPERATION 2:                         ALREADY MERGED BUT WE TRY ADD:" << up_shape->get_guid()<< std::endl;
                                }
                                breaker = true;
                                std::wcout << L"CONTEXT:";
                                dump_gvector(m_context);
                                std::wcout << std::endl;
                            }
                        }
                    }
                }
                if (breaker == true)
                {
                  //  break;
                }
            }

            //context_was_merged = false;
            if (breaker == true)
            {
              //  break;
            }
        }
    }

    std::wcout<<L"CONTEXT:";
    dump_gvector(m_context);
    std::wcout<<std::endl;

    return shape_iterator_state_in_build_rules;
}

bool shape_iterator::find_this_way(base_shape* from, base_shape* to,  gvector<shape_index>& path, gint& ray_caster, gmap<base_shape*, bool>& passed_shapes)
{
    if(from == to)
    {
       return true;
    }
    if (ray_caster == 0)
    {
        return false;
    }
    ray_caster--;
    linker* linker = from->get_outs();
    for(gint i = 0; i < linker->size(); i++)
    {
        base_shape* shape = m_ls_memory->get_shape(linker->at(i)->m_shape_to);
        
        if(passed_shapes[shape] == false)
        {
            path.push_back(shape->get_index());
            passed_shapes[shape] = true;
            return find_this_way(shape, to, path, ray_caster, passed_shapes);
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