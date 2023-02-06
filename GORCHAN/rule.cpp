#include "pch.h"
#include "rule.h"

rule::rule()
:m_weight(0)
{

}

rule* rule::clone()
{
	rule* ret = new rule();
	ret->m_path = m_path;
	ret->m_weight = m_weight;
	return ret;
}

void rule::up_weight()
{
	m_weight++;
}

void rule::serialize(gofstream& stream)
{
	stream << m_weight << std::endl;
	stream << m_path.size() << std::endl;
	for(gint i = 0; i < m_path.size(); i++)
	{
		stream << m_path[i] << std::endl;
	}
}

void rule::deserialize(gifstream& stream)
{
	stream >> m_weight ;
	gint size = 0;
	stream >> size;
	for(gint i = 0; i < size; i++)
	{
		gint tmp = 0;
		stream >> tmp;
		m_path.push_back(tmp);
	}
}