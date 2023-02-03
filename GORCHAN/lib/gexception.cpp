#include "gexception.h"

gexception::gexception(char* message)
{
    m_message = message;
}

gexception::~gexception()
{
    m_message.clear();
}

const char* gexception::what()
{
    return m_message.c_str();
}