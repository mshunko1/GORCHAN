#ifndef EAR_H
#define EAR_H

#pragma once
#include "pch.h"

class ear
{
public:
    ear();
    ~ear();
    gvector<base_shape*> parse_shapes(gstring line);
private:

};

#endif