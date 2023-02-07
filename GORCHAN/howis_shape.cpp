#include "pch.h"
#include "howis_shape.h"

howis_shape::howis_shape(gguid guid)
{
    m_guid = guid;
    m_type = shape_type_howis;
}

howis_shape::~howis_shape()
{

}
 
void howis_shape::serialize(gofstream& stream)
{

}

void howis_shape::deserialize(gifstream& stream)
{
    
}

gfs_path howis_shape::get_filename()
{
    return gfs_path();
}

gguid howis_shape::get_guid()
{
    return m_guid;
}