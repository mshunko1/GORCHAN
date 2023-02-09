#ifndef BG_CONTEXT_H
#define BG_CONTEXT_H

#pragma once

#include "pch.h"

class bg_context
{
public:
    ~bg_context();
	bg_context();

	void add_shape(base_shape* shape);
	gint size();
	void remove(gint index);
	base_shape* at(gint index);
	bool exists(base_shape* shape, gint* index);
	gstring try_merge(volatile bool& merged);

	void serialize(gofstream& stream);
	void deserialize(gifstream& stream);
private: 
	gvector<base_shape*> m_context;
};

#endif