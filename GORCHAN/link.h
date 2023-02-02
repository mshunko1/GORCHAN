#ifndef LINK_H
#define LINK_H

#pragma once
enum link_type {link_type_undefined, link_type_temproray, link_type_init, link_type_friendly, link_type_aquare_by_rule, link_type_soul_matter};


class link
{
public:
    link();
    ~link();

    void serialize(gofstream& stream);
    void deserialize(gifstream& stream);

private:
    link_type m_type;
    shape_index m_from;
    shape_index m_to;
};

#endif