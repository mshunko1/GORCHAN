#include "bg_context.h"

bg_context::~bg_context()
{

}

bg_context::bg_context()
:m_links(nullptr),
m_increase_num(1),
m_start_pos(0),
m_back_pos(0)
{
    m_size = m_increase_num++ * 200;
    m_links = new link*[m_size];
    memset(m_links, 0, sizeof(link*) * m_size);
}
 

void bg_context::add_link(link* add_link)
{
    gint index = 0;
    if(this->exists(add_link->m_shape_to, &index) == true)
    {
        if(add_link->m_type > this->at(index)->m_type)
        {
            this->at(index)->m_type = add_link->m_type;
        }
        return;
    }
    // IR       ADD IR  CIRCLE
    // IR       ADD FR  EXPAND
    // FR       ADD IR  EXPAND
    // FR       ADD FR  CIRCLE

    bool action_circle = false;
    bool action_expand = false;

    link* start = m_links[m_start_pos];

    if(size() == 0) 
    {
        m_start_pos = 0;
        m_back_pos = 0;
        m_links[m_back_pos++] = add_link;
        return;
    }

    if(add_link->m_type <= link_type_temproray)
    {
        action_expand = true;
    }
    else if(start->m_type <= link_type_init && add_link->m_type <= link_type_init)
    {
        action_circle = true;
    }
    else if(start->m_type <= link_type_init && add_link->m_type >= link_type_friendly)
    {
        action_expand = true;
    }
    else if(start->m_type >= link_type_friendly && add_link->m_type <= link_type_init)
    {
        action_expand = true;
    }
    else if(start->m_type >= link_type_friendly && add_link->m_type >= link_type_friendly)
    {
        action_circle = true;
    }
    else
    {
        throw new gexception("undefined behaviour when try add link");
    }

    if(m_back_pos >= m_size)
    {
        m_size = m_increase_num++ * 20;
        link** new_links = new link*[m_size];
        std::memset(new_links, 0, sizeof(link*) * m_size);

        std::memcpy(new_links, m_links + sizeof(link*) * m_start_pos, size() * sizeof(link*));
        delete m_links;
        m_links = new_links;
        m_start_pos = 0;
        m_back_pos = 0;
    }

    if(action_circle == true)
    {
        link* start = m_links[m_start_pos];
        m_links[m_start_pos] = nullptr;
        m_start_pos++;
        delete start;
        m_links[m_back_pos++] = add_link;
    }
    if(action_expand == true)
    {
        m_links[m_back_pos++] = add_link;
    }
    if(action_circle == true && action_expand == true)
    {
        throw new gexception("pizdec");
    }
}

link* bg_context::at(gint index)
{
    return m_links[m_start_pos + index];
}

gint bg_context::size()
{
    return m_back_pos - m_start_pos;
}

void bg_context::add_link(base_shape* to_shape, link_type type)
{
    link* l = new link();
    l->m_shape_to = to_shape->get_index();
    l->m_type = type;
    add_link(l);
}

bool bg_context::exists(base_shape* shape, gint* index = nullptr)
{
    for(gint i = m_start_pos; i < m_back_pos; i++)
    {
        if(m_links[i]->m_shape_to == shape->get_index())
        {
            if(index != nullptr)
            {
                *index = (m_back_pos - m_start_pos) - (m_back_pos - i) ;
            }
            return true;
        }
    }
    return false;
}

void bg_context::remove(gint index)
{
    throw new gexception("not implemented");
}

bool bg_context::exists(shape_index shape_index, gint* index = nullptr)
{
    for(gint i = m_start_pos; i < m_back_pos; i++)
    {
        if(m_links[i]->m_shape_to == shape_index)
        {
            if(index != nullptr)
            {
                *index = (m_back_pos - m_start_pos) - (m_back_pos - i) ;
            }
            return true;
        }
    }
    return false;
}

void bg_context::serialize(gofstream& stream)
{

}

void bg_context::deserialize(gifstream& stream)
{

}