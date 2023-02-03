#pragma once
#include "link.h"

class linker
{
public:
	linker();
	void serialize(gofstream& stream);
	void deserialize(gifstream& stream);
	void add_link(link*);
protected:
	void init();
	void increase_size();
private:
	link** m_links;
	gint m_increase_num;
};

