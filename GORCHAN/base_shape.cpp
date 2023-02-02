#include "pch.h"
#include "base_shape.h"


base_shape::base_shape()
{

}

void base_shape::serialize(gofstream& stream)
{
	stream << m_guid;
}

void base_shape::deserialize(gifstream& stream)
{
	stream >> m_guid;
}