#include "pch.h"
#include "linker.h"

linker::linker(base_shape* owner)
:m_links(nullptr),
m_increase_num(1),
m_start_pos(0),
m_back_pos(0),
m_owner(owner)
{
    m_size = m_increase_num++ * 200;
    m_links = new link*[m_size];
    memset(m_links, 0, sizeof(link*) * m_size);
}

base_shape* linker::get_owner()
{
    return m_owner;
}

gint linker::get_warring_weight(link_type link)
{
    switch (link)
    {
    case link_type_temproray:
            return 0; 
    case link_type_init:
            return -1; 
    case link_type_soul_matter:
            return -2; 
    case link_type_friendly:
            return 1; 
    case link_type_aquare_by_rule:
            return 2; 
    default:
        throw new gexception("GADY!!!");
    }
}

gint linker::calc_warrings()
{
    gint waring_value = 0;
    for(gint i = 0; i < size(); i++)
    {
        waring_value += get_warring_weight(at(i)->m_type);
    }
    return waring_value;
}

void linker::add_link(link* add_link)
{
    if(this->exists(add_link->m_shape_to, nullptr) == true)
    {
        return;
    }
    // IR       ADD IR  CIRCLE
    // IR       ADD FR  EXPAND
    // FR       ADD IR  EXPAND
    // FR       ADD FR  CIRCLE

    bool action_circle = false;
    bool action_expand = false;
    bool action_narrow = false;

    link* start = m_links[m_start_pos];

    if(size() == 0) 
    {
        m_start_pos = 0;
        m_back_pos = 0;
        m_links[m_back_pos++] = add_link;
        return;
    }
    // Задача переработать как можно больше информации
    // так как контекст merge в момент build fr то это значит что важны IR і не важны все остальные
    if (add_link->m_type <= link_type_temproray)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_temproray && add_link->m_type == link_type_init)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_temproray && add_link->m_type == link_type_friendly)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_temproray && add_link->m_type == link_type_aquare_by_rule)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_temproray && add_link->m_type == link_type_soul_matter)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_init && add_link->m_type == link_type_init)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_init && add_link->m_type == link_type_friendly)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_init && add_link->m_type == link_type_aquare_by_rule)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_init && add_link->m_type == link_type_soul_matter)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_friendly && add_link->m_type == link_type_init)
    {
        action_circle = true;
    }
    else if (start->m_type == link_type_friendly && add_link->m_type == link_type_friendly)
    {
        action_circle = true;
    }
    else if (start->m_type == link_type_friendly && add_link->m_type == link_type_aquare_by_rule)
    {
        action_circle = true;
    }
    else if (start->m_type == link_type_friendly && add_link->m_type == link_type_soul_matter)
    {
        action_circle = true;
    }
    else if (start->m_type == link_type_aquare_by_rule && add_link->m_type == link_type_init)
    {
        action_circle = true;
    }
    else if (start->m_type == link_type_aquare_by_rule && add_link->m_type == link_type_friendly)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_aquare_by_rule && add_link->m_type == link_type_aquare_by_rule)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_aquare_by_rule && add_link->m_type == link_type_soul_matter)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_soul_matter && add_link->m_type == link_type_init)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_soul_matter && add_link->m_type == link_type_friendly)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_soul_matter && add_link->m_type == link_type_aquare_by_rule)
    {
        action_expand = true;
    }
    else if (start->m_type == link_type_soul_matter && add_link->m_type == link_type_soul_matter)
    {
        action_expand = true;
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
        m_links[m_start_pos++] = nullptr;
        delete start;
        m_links[m_back_pos++] = add_link;
    }
    if(action_expand == true)
    {
        m_links[m_back_pos++] = add_link;
    }
    if (action_narrow == true)
    {
        link* link = m_links[m_start_pos];
        m_start_pos++;
        delete link;
        m_links[m_back_pos++] = add_link;
    }
 
}

link* linker::at(gint index)
{
    return m_links[m_start_pos + index];
}

gint linker::size()
{
    return m_back_pos - m_start_pos;
}

void linker::add_link(base_shape* to_shape, rule* rule,link_type type)
{
    link* l = new link();
    l->m_shape_to = to_shape->get_index();
    l->m_type = type;
    l->m_rules.push(rule);
    add_link(l);
}

bool linker::exists(base_shape* shape, gint* index = nullptr)
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


bool linker::has_link_type(link_type link)
{
    for (gint i = m_start_pos; i < m_back_pos; i++)
    {
        if (m_links[i]->m_type == link)
        {
            return true;
        }
    }
    return false;
}

void linker::remove(gint index)
{
    gint start_pos = m_start_pos + index;


    if(m_start_pos > 0 && m_links[m_start_pos - 1] != nullptr)
    {
        int a = 21;
    }

    if(start_pos == 0)
    {
        if(m_back_pos == 1)
        {
            link* l = m_links[0];
            delete l;
            m_links[0] = nullptr;
            m_back_pos--;
            return;
        }
        memcpy(m_links + ((start_pos)), m_links + ((start_pos + 1)) , (size() - index) * sizeof(link*));
        m_links[m_back_pos - 1] = nullptr;
        m_back_pos--;
        return;
    }
    else
    {
        link* l = m_links[start_pos];
        delete l;
        memcpy(m_links + (start_pos), m_links + (start_pos + 1) , (size() - index) * sizeof(link*));
        m_links[m_back_pos - 1] = nullptr;
        m_back_pos--;
    }
}

bool linker::exists(shape_index shape_index, gint* index = nullptr)
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

void linker::serialize(gofstream& stream)
{

}

void linker::deserialize(gifstream& stream)
{

}