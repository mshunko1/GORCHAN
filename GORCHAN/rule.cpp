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
}

void rule::up_weight()
{
	m_weight++;
}

void rule::serialize(gofstream& stream)
{
 
}

void rule::deserialize(gifstream& stream)
{

}