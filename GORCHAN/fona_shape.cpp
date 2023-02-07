#include "pch.h"
#include "fona_shape.h"

fona_shape::fona_shape()
{

}

fona_shape::fona_shape(gstring fona)
{
    m_fona = fona;
    m_type = shape_type_fona;
}

fona_shape::~fona_shape()
{

}

void fona_shape::serialize(gofstream& stream)
{

}

void fona_shape::deserialize(gifstream& stream)
{
    
}

gfs_path fona_shape::get_filename()
{
    return gfs_path();
}

gguid fona_shape::get_guid()
{
    return m_fona;
}