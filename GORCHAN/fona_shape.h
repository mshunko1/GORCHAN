#pragma once
#include "base_shape.h"
class fona_shape :
    public base_shape
{
public:
    fona_shape();
    fona_shape(gstring fona);
    ~fona_shape();

private:
    gstring m_fona;
};

