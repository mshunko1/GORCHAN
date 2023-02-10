#include "pch.h"
#include "eos_shape.h"

eos_shape* eos_shape::m_instance = nullptr;

eos_shape::eos_shape()
{
    m_type = shape_type_eos;
    m_index = eos_shape_index;
    m_guid = oes_shape_guid;
}

eos_shape::~eos_shape()
{
    m_instance = nullptr;
}

eos_shape* eos_shape::get_instance()
{
    if(m_instance == nullptr)
    {
        m_instance = new eos_shape();
    }
    return m_instance;
}

void eos_shape::serialize(gofstream& stream)
{

}

void eos_shape::deserialize(gifstream& stream)
{
    
}

gfs_path eos_shape::get_filename()
{
    return gfs_path();
}

gguid eos_shape::get_guid()
{
    return oes_shape_guid;
}