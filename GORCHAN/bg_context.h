#ifndef BG_CONTEXT_H
#define BG_CONTEXT_H

#pragma once

#include "pch.h"

class bg_context
{
public:
    ~bg_context();
	bg_context();
	void serialize(gofstream& stream);
	void deserialize(gifstream& stream);
	void add_link(link* link);
	void add_link(base_shape* to_shape, link_type type);
	bool exists(base_shape* shape, gint* index);
	bool exists(shape_index shape_index, gint* index);
	gint size();
	void remove(gint index);
	link* at(gint index);
	base_shape* get_owner();
protected:
	gint calc_warrings();
	gint get_warring_weight(link_type link);
private:
	link** m_links;
	gint m_increase_num;
	gint m_start_pos;
	gint m_back_pos;
	gint m_size;
};

#endif