#include "pch.h"
#include "base_shape.h"


base_shape::base_shape()
{

}

void base_shape::serialize(gofstream& stream)
{
	serialize_type(this, stream);
}

void base_shape::deserialize(gifstream& stream)
{
	m_type = deserialize_type(stream, false);
}

void base_shape::serialize_type(base_shape* shape, gofstream& stream)
{
	stream << shape->m_type;
}

shape_type base_shape::deserialize_type(gifstream& stream, bool reset_file_pos = true)
{
	gint type = (gint)shape_type_undefined;
	stream>>type;
	if(reset_file_pos == true)
	{
		stream.seekg(0);
	}
	return (shape_type)type;
}

shape_index base_shape::get_index()
{

}

shape_type base_shape::get_type()
{

}