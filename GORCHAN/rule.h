#pragma once


class rule
{
public:
	rule(); 
	void serialize(gofstream& stream);
	void deserialize(gifstream& stream);
	rule* clone();
	void up_weight();
	gint m_weight;
	gvector<shape_index> m_path;
};

