#pragma once

class linker;

class base_shape
{
public:
	base_shape();
	void serialize(gofstream& stream);
	void deserialize(gifstream& stream);
	gguid get_guid();
private:
	shape_index m_index;
	linker* m_links_out;
	linker* m_links_in;
};

