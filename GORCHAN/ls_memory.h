#pragma once


class ls_memory
{
    public:
    ls_memory();
    void add_shape(base_shape* shape);
    void load();
    void save();
    bool exist(shape_index index);
    bool exist(base_shape* shape);
protected:
    void add_static_shapes();
    private:
    gmap<shape_index, base_shape*> m_index_to_shape;
    gmap<base_shape*, shape_index> m_shape_to_index;
    indexator* m_shape_indexator;
    gfs_path m_base_path; 
};

