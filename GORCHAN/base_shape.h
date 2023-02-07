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
	virtual gguid get_guid();
	shape_type get_type();
	shape_index get_index();
	linker* get_outs();
	linker* get_ins();
	static bool link_shapes(base_shape* from, base_shape* to, rule* rule, link_type type, bool rewrite, bool replace);// out-in
protected:
	static void serialize_type(base_shape* shape, gofstream& stream);
	static shape_type deserialize_type(gifstream& stream, bool reset_file_pos);
	void set_index(shape_index index);
	virtual gfs_path get_filename();

	shape_type m_type;
	shape_index m_index;
private:
	linker* m_links_out;
	linker* m_links_in;
};

