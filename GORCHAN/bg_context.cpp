#include "bg_context.h"

bg_context::~bg_context()
{

}

bg_context::bg_context()
{
   
}

void bg_context::add_shape(base_shape* shape)
{
    if (shape->get_type() == shape_type_eos || shape->get_type() == shape_type_soul_matter)
    {
        return;
    }
    auto exists = std::find(m_context.begin(), m_context.end(), shape);
    if(exists == m_context.end())
    {
        m_context.push_back(shape);
    }
}

gstring bg_context::try_merge()
{
    gmap<shape_type, gint> merge_map;
    for(gint i = 0; i < size(); i++)
    {
        auto exists = merge_map.find(at(i)->get_type());
        shape_type st;
        if (exists == merge_map.end())
        {
            shape_type st = at(i)->get_type();
            merge_map[st]=1;
        }
        else
        {
            shape_type st = at(i)->get_type();
            merge_map[st]++;
        }
    }
    for(auto i:merge_map)
    {
        if(i.second > 1)
        {
            gvector<base_shape*> merged_shapes;
            for(gint j = 0; j < size(); j++)
            {
                if(i.first == at(j)->get_type())
                {
                    if(merged_shapes.size() < 2)
                    {
                        merged_shapes.push_back(at(j));
                    }
                }
            }
            gstring merged_shapes_log;

            if(merged_shapes.size() == 2)
            {

                auto retu = L"MERGED SHAPES ["+merged_shapes[0]->get_guid()+L"] : [" +merged_shapes[1]->get_guid()+L"]\r\n";
                auto erase1 = std::find(m_context.begin(), m_context.end(), merged_shapes[0]);
                m_context.erase(erase1);

                auto erase2 = std::find(m_context.begin(), m_context.end(), merged_shapes[1]);
                m_context.erase(erase2);
                return retu;
            }
        }
    }
    return L"CAT MERGE SHAPES\r\n";
}

base_shape* bg_context::at(gint index)
{
    return m_context.at(index);
}

gint bg_context::size()
{
    return m_context.size();
}
 
bool bg_context::exists(base_shape* shape, gint* index = nullptr)
{
    for(gint i = 0; i < m_context.size(); i++)
    {
        if(m_context[i] == shape)
        {
            *index = i;
            return true;
        }
    }
    return false;
}

void bg_context::remove(gint index)
{
    m_context.erase(m_context.begin() + index);
}
 
void bg_context::serialize(gofstream& stream)
{

}

void bg_context::deserialize(gifstream& stream)
{

}