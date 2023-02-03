#include "pch.h"
#include "linker.h"

linker::linker()
:m_links(nullptr),
m_increase_num(0)
{

}

void linker::init()
{

}

void linker::increase_size()
{
    m_increase_num++;
}

void linker::serialize(gofstream& stream)
{

}

void linker::deserialize(gifstream& stream)
{

}