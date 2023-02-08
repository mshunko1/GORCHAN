#include "pch.h"
#include "soul_matter_shape.h"

soul_matter_shape* soul_matter_shape::m_instance = nullptr;

soul_matter_shape::soul_matter_shape()
{
    m_index = soul_matter_shape_index;
    m_type = shape_type_soul_matter;
    m_guid = sm_shape_guid;
}


soul_matter_shape* soul_matter_shape::get_instance()
{
    if(m_instance == nullptr)
    {
        m_instance = new soul_matter_shape();
    }
    return m_instance;
}

soul_matter_shape::~soul_matter_shape()
{

}

void soul_matter_shape::serialize(gofstream& stream)
{

}

void soul_matter_shape::deserialize(gifstream& stream)
{
    
}

gfs_path soul_matter_shape::get_filename()
{
    return gfs_path();
}

gguid soul_matter_shape::get_guid()
{
    return sm_shape_guid;
}