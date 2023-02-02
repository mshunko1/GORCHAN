#pragma once

class indexator
{
public:
	indexator(gfs_path filename);
	shape_index get_next_shape_index();
	gint get_next_index();
private:
	gint m_index;
	gstring m_filename;
};

