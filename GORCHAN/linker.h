#pragma once
#include "link.h"

class linker
{
public:
	linker();
	void serialize(gofstream& stream);
	void deserialize(gifstream& stream);
	void add_link(link* link);
	void add_link(base_shape* to_shape, link_type type);
	bool exists(base_shape* shape);
	bool exists(shape_index shape_index);
	gint size();
	base_shape* at(gint index);
protected:
private:
	link** m_links;
	gint m_increase_num;
	gint m_start_pos;
	gint m_back_pos;
	gint m_size;
};

