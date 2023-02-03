#pragma once
#include "base_shape.h"

static shape_index eos_shape_index = (shape_index)-1;

class eos_shape :
    public base_shape
{
public:
    eos_shape();
    ~eos_shape();

private:

};

