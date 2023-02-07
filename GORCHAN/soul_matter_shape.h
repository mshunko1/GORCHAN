#pragma once
#include "base_shape.h"

static shape_index soul_matter_shape_index = (shape_index)-2;


class soul_matter_shape :
    public base_shape
{
public:
    soul_matter_shape();
    ~soul_matter_shape();
	virtual void serialize(gofstream& stream);
	virtual void deserialize(gifstream& stream);
    virtual gfs_path get_filename();
    static soul_matter_shape* get_instance();
protected:
	virtual gguid get_guid();
private:
    const gguid sm_shape_guid = L"[*SOUL_MATTER*]";
    static soul_matter_shape* m_instance;
};

