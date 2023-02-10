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
    base_shape* sm_shape = soul_matter_shape::get_instance();
    linker* outs_mem_shape = sm_shape->get_outs();
    linker* ins_mem_shape = sm_shape->get_ins();
    if (outs_mem_shape->size() == 0 && ins_mem_shape->size() == 0)
    {
        std::cout << "Mind preserve operation skiped, BECAUSE SM EMPTY"<<std::endl;
        return;
    }
 
    gvector<base_shape*> shapes_to_remove;
    for(auto item:m_memory->m_index_to_shape)
    {

        if(soul_matter_shape::get_instance() == item.second    || eos_shape::get_instance() == item.second )
        {
            std::cout << "Mind preserve operation skiped,  BECAUSE IT SM;" << std::endl;
            continue;
        }


       
        if (item.second->get_just_added() == true)
        {
            std::cout << "Mind preserve operation skiped, context size = 0;" << std::endl;
            continue;
        }
        
        bool passed = false;
        gint ray_cast_limit = item.second->raycast_size();
        gmap<base_shape*, bool> passed_shapes;
        passed = is_this_shape_passed_to(item.second, sm_shape, ray_cast_limit, passed_shapes);
   
        if(passed == false)
        {
            shapes_to_remove.push_back(item.second);
        }
    }

    for (base_shape* shape : shapes_to_remove)
    {
        std::cout << "Remove shape:  [";
        std::wcout << shape->get_guid();
        std::cout << "]   Removed links:" << "   INDEX:" << shape->get_index() << std::endl;
        gint removed_links_count = m_memory->remove_shape(shape);
        gint index = -1;
        if (m_context->exists(shape, &index) == true)
        {
            m_context->remove(index);
            std::cout << "ALSO REMOVED FROM CONTEXT"<<std::endl;
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

    passed_shapes[shape] = true;

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