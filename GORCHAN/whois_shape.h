#ifndef WHOIS_SHAPE_H
#define WHOIS_SHAPE_H

#pragma once

class whois_shape: public base_shape
{
public:
    whois_shape(gguid guid);
    ~whois_shape();
	virtual void serialize(gofstream& stream);
	virtual void deserialize(gifstream& stream);
    virtual gfs_path get_filename();
protected:
	virtual gguid get_guid();
private: 
};

#endif