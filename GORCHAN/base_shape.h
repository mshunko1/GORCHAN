#pragma once

enum shape_type {shape_type_undefined, shape_type_fona, shape_type_eos, shape_type_soul_matter};

class linker;

class base_shape
{
public:
	friend class ls_memory;
	base_shape();
	virtual void serialize(gofstream& stream);
	virtual void deserialize(gifstream& stream);
	shape_type get_type();
	shape_index get_index();
protected:
	static void serialize_type(base_shape* shape, gofstream& stream);
	static shape_type deserialize_type(gifstream& stream, bool reset_file_pos = true);
	void set_index(shape_index index);
	gfs_path get_filename();
private:
	shape_type m_type;
	shape_index m_index;
	linker* m_links_out;
	linker* m_links_in;
};

