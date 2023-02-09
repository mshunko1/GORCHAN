#include "mind_preservation_service.h"

mind_preservation_service::mind_preservation_service(ls_memory* memory, bg_context* context)
:m_memory(memory),
m_context(context)
{

}

mind_preservation_service::~mind_preservation_service()
{

}


/// @brief Перебрать все образы в ls memory и если они не достигают bg_context 
/// содержимого отвязать их от всех но оставить в памяти
void mind_preservation_service::mind_preserve_operation()
{
    auto shapes = m_memory->get_index_to_shape_map();

    for(auto item:*shapes)
    {
        linker* outs_mem_shape = item.second->get_outs();
        linker* ins_mem_shape = item.second->get_ins();
        if(outs_mem_shape->size() == 0 && ins_mem_shape->size() == 0)
        {
            continue;
        }
        if(soul_matter_shape::get_instance() == item.second || eos_shape::get_instance() == item.second)
        {
            continue;
        }



        bool passed = false;
        for(gint i = 0; i < m_context->size(); i++)
        {
            if(item.second == m_context->at(i))
            {
                continue;
            }
 
            base_shape* context_shape = m_context->at(i);
            gmap<base_shape*, bool> passed_shapes;
            gint ray_cast_limit = item.second->raycast_size();
            passed = is_this_shape_passed_to(item.second, context_shape, ray_cast_limit, passed_shapes);
            if(passed == true)
            {
                break;
            }
        }
        if(passed == false)
        {
            gint removed_links_count = m_memory->remove_shape(item.second);
            std::cout<<"Removed links:"<<removed_links_count<<std::endl;
        }
    }
}

bool mind_preservation_service::is_this_shape_passed_to(base_shape* shape, base_shape* to, gint& raycast, gmap<base_shape*, bool>& passed_shapes)
{
    if(shape == to)
    {
       return true;
    }
    if(raycast == 0)
    {
        return false;
    }
    --raycast;
    linker* linker = shape->get_outs();
    for(gint i = 0; i < linker->size(); i++)
    {
        base_shape* shape = m_memory->get_shape(linker->at(i)->m_shape_to);
        
        if(passed_shapes[shape] == false)
        {
            passed_shapes[shape] = true;
            return is_this_shape_passed_to(shape, to, raycast, passed_shapes);
        }
    }
    return false;
}