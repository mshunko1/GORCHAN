#include "pch.h"
#include "link.h"

link::link()
{

}

link::~link()
{

}

void link::serialize(gofstream& stream)
{
    stream << m_type << std::endl;
    stream << m_shape_to << std::endl;
    stream << m_rules.size();
    while(m_rules.empty() == false)
    {
        rule* rule = m_rules.top();
        m_rules.pop();
        rule->serialize(stream);
    }
}

void link::deserialize(gifstream& stream)
{
    gint tmp = -1;
    stream >> tmp;
    m_type = (link_type)tmp;
    stream >> tmp;
    m_shape_to = (shape_index)tmp;
    stream >> tmp;
    for(gint i = 0; i < tmp; i++)
    {
        rule* r = new rule();
        r->deserialize(stream);
        m_rules.push(r);
    }
}

bool rule_priority_queue_comparer::operator() (rule* l, rule* r)
{
    return l->m_weight > r->m_weight;
}


rule_priority_queue_comparer::rule_priority_queue_comparer()
{

}
rule_priority_queue_comparer::~rule_priority_queue_comparer()
{
    
}