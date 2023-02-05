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

bool base_shape::link_shapes(base_shape* from, base_shape* to, link_type type, bool rewrite = false, bool replace = false)
{
	if(rewrite == true || (rewrite == true && replace == true))
	{
		throw new gexception("not impemented");		
	}
	gint index = -1;
	if(from->m_links_out->exists(to, &index) == false)
	{
		from->m_links_out->add_link(to, type);
	}
	else
	{
		if(replace == true)
		{ 
			from->m_links_out->remove(index);
			from->m_links_out->add_link(to, type);
		}
	}

	if(to->m_links_in->exists(from, &index) == false)
	{
		to->m_links_in->add_link(from, type);
	}
	else
	{
		if(replace == true)
		{ 
			to->m_links_out->remove(index);
			to->m_links_in->add_link(from, type);
		}
	}
}

linker* base_shape::get_outs()
{
	return m_links_out;
}

linker* base_shape::get_ins()
{
	return m_links_in;
}

shape_index base_shape::get_index()
{

}

shape_type base_shape::get_type()
{

}