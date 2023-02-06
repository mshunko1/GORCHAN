#ifndef LINK_H
#define LINK_H
//MAMA OCHEN RASTORELAS'
#pragma once


enum link_type {link_type_undefined, link_type_temproray, link_type_init, link_type_friendly, link_type_aquare_by_rule, link_type_soul_matter};

class rule;

class rule_priority_queue_comparer
{
public:
    rule_priority_queue_comparer();
    ~rule_priority_queue_comparer();
    bool operator() (rule* l, rule* r);
private:

};


class link
{
public:
    link();
    ~link();
    void serialize(gofstream& stream);
    void deserialize(gifstream& stream);
    link_type m_type;
    //shape_index m_from; same for all
    shape_index m_shape_to;
    grule_queue<rule*, gvector<rule*>, rule_priority_queue_comparer> m_rules;
private:

};

#endif