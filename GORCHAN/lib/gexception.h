#ifndef GEXCEPTION_H
#define GEXCEPTION_H

#pragma once
#include <exception>
#include <string>

class gexception:public std::exception
{
public:
    gexception(char* message);
    ~gexception();
    virtual const char* what();
private:
    std::string m_message;
};

#endif