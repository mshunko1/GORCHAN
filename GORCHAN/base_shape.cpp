#include "pch.h"
#include "base_shape.h"


base_shape::base_shape()
:m_links_out(new linker(this)),
m_links_in(new linker(this)),
m_ray_count_initial(0),
m_ray_count_additional(0),
m_ray_count_pass(0)
{

}
bool base_shape::can_be_raised(bool just_check)
{
	if(just_check == true)
	{
		return (m_ray_count_initial + m_ray_count_additional) > 0;
	}
	else
	{
		bool encount = false;
		if(m_ray_count_initial > 0)
		{
			m_ray_count_initial--;
			encount = true;
		}
		if(m_ray_count_additional > 0 && encount == false)
		{
			m_ray_count_additional--;
			encount = true;
		}
		return (m_ray_count_initial + m_ray_count_additional) > 0 || (encount == true && (m_ray_count_initial + m_ray_count_additional) == 0);
	}
}

gint base_shape::raycast_size()
{
	return (m_ray_count_initial + m_ray_count_additional);
}

void base_shape::reset_daycaster()
{
	m_ray_count_additional = 0;
	m_ray_count_initial = m_links_in->size() + m_links_out->size();
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
gint ssss = 0;
bool base_shape::link_shapes(base_shape* from, base_shape* to, rule* rule, link_type type, bool rewrite = false, bool replace = false)
{
	ssss++;
	if(rewrite == true || (rewrite == true && replace == true))
	{
		throw new gexception("not impemented");		
	}
	if(ssss == 71 || ssss == 29)
	{
		int a = 21;
		bool ss = true;
		//while(ss)
		{
			std::cout<<L"MAZAFAKA"<<std::endl;
		}
	}
	gint index = -1;
	gint ok = 0;
	const gint okcount = 2;
	if(from->get_index() == eos_shape_index && to->get_index() == soul_matter_shape_index)
	{
		int a = 21;
		bool ss = true;
		//while(ss)
		{
			std::cout<<L"MAZAFAKA"<<std::endl;
		}
	}
	if(from->m_links_out->exists(to, &index) == false)
	{
		from->m_links_out->add_link(to, rule, type);
		from->m_ray_count_additional++;
		ok++;
	}
	else
	{
		if(replace == true)
		{ 
			from->m_links_out->remove(index);
			from->m_links_out->add_link(to, rule, type);
			from->m_ray_count_additional++;
			ok++;
		}
	}

	if(to->m_links_in->exists(from, &index) == false)
	{
		to->m_links_in->add_link(from, rule, type);
		to->m_ray_count_additional++;
		ok++;
		return ok == okcount;
	}
	else
	{
		if(replace == true)
		{ 
			to->m_links_in->remove(index);
			to->m_links_in->add_link(from, rule, type);
			to->m_ray_count_additional++;
			ok++;
			return ok == okcount;
		}
	}
	return ok == okcount;
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
	return m_index;
}

shape_type base_shape::get_type()
{
	return m_type;
}

void base_shape::set_index(shape_index index)
{
	m_index = index;
}

gfs_path base_shape::get_filename()
{
	return L"";
}

gguid base_shape::get_guid()
{
	return m_guid;
}