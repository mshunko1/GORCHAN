#pragma once
#include "base_shape.h"
class fona_shape :
    public base_shape
{
public:
    fona_shape();
    fona_shape(gstring fona);
    ~fona_shape();
	virtual void serialize(gofstream& stream);
	virtual void deserialize(gifstream& stream);
    virtual gfs_path get_filename();
protected:
	virtual gguid get_guid();
private:
    gstring m_fona;
};

