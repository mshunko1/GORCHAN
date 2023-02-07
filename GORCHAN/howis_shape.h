#ifndef HOWIS_SHAPE_H
#define HOWIS_SHAPE_H

#pragma once

class howis_shape: public base_shape
{
public:
    howis_shape(gguid guid);
    ~howis_shape();
	virtual void serialize(gofstream& stream);
	virtual void deserialize(gifstream& stream);
    virtual gfs_path get_filename();
protected:
	virtual gguid get_guid();
private: 
};

#endif