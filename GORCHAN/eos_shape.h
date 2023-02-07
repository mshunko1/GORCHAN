#pragma once
#include "base_shape.h"

static shape_index eos_shape_index = (shape_index)-1;

class eos_shape :
    public base_shape
{
public:
    eos_shape();
    ~eos_shape();
	virtual void serialize(gofstream& stream);
	virtual void deserialize(gifstream& stream);
    virtual gfs_path get_filename();
protected:
	virtual gguid get_guid();
private:
    const gguid oes_shape_guid = L"[*EOS*]";
};

