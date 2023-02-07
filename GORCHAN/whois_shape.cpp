#include "pch.h"
#include "whois_shape.h"

whois_shape::whois_shape(gguid guid)
{
    m_guid = guid;
    m_type = shape_type_whois;
}

whois_shape::~whois_shape()
{

}


void whois_shape::serialize(gofstream& stream)
{

}

void whois_shape::deserialize(gifstream& stream)
{
    
}

gfs_path whois_shape::get_filename()
{
    return gfs_path();
}

gguid whois_shape::get_guid()
{
    return m_guid;
}