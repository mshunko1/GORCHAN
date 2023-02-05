#include "pch.h"
#include "linker.h"

linker::linker(base_shape* owner)
:m_links(nullptr),
m_increase_num(1),
m_start_pos(0),
m_back_pos(0),
m_owner(owner)
{
    m_size = m_increase_num++ * 20;
    m_links = new link*[m_size];
    memset(m_links, 0, sizeof(link*) * m_size);
}

base_shape* linker::get_owner()
{
    return m_owner;
}

void linker::add_link(link* add_link)
{
    // IR       ADD IR  CIRCLE
    // IR       ADD FR  EXPAND
    // FR       ADD IR  EXPAND
    // FR       ADD FR  CIRCLE

    bool action_circle = false;
    bool action_expand = false;

    link* start = m_links[m_start_pos];

    if(start->m_type <= link_type_init && add_link->m_type <= link_type_init)
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
        memset(new_links, 0, sizeof(link*) * m_size);

        memcpy(new_links, m_links + sizeof(link*) * m_start_pos, size() * sizeof(link*));
        delete m_links;
        m_links = new_links;
        m_start_pos = 0;
        m_back_pos = 0;
    }

    if(action_circle == true)
    {
        link* start = m_links[m_start_pos];
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

link* linker::at(gint index)
{
    return m_links[m_start_pos + index];
}

gint linker::size()
{
    return m_back_pos - m_start_pos + 1;
}

void linker::add_link(base_shape* to_shape, rule* rule,link_type type)
{
    link* l = new link();
    l->m_shape_to = to_shape;
    l->m_type = type;
    l->m_rules.push(rule);
    add_link(l);
}

bool linker::exists(base_shape* shape, gint* index = nullptr)
{
    for(gint i = m_start_pos; i < m_back_pos; i++)
    {
        if(m_links[i]->m_shape_to == shape)
        {
            if(index != nullptr)
            {
                *index = i;
            }
            return true;
        }
    }
}

void linker::remove(gint index)
{
    throw new gexception("not implemented");
}

bool linker::exists(shape_index shape_index, gint* index = nullptr)
{
    for(gint i = m_start_pos; i < m_back_pos; i++)
    {
        if(m_links[i]->m_shape_to->get_index() == shape_index)
        {
            if(index != nullptr)
            {
                *index = i;
            }
            return true;
        }
    }
}

void linker::serialize(gofstream& stream)
{

}

void linker::deserialize(gifstream& stream)
{

}