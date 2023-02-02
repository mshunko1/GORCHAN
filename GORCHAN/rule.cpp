#include "pch.h"
#include "rule.h"

rule::rule()
{

}

void rule::serialize(gofstream& stream)
{
	stream << (gint)m_type;
	stream << m_from->get_guid();
}

void rule::deserialize(gifstream& stream)
{

}