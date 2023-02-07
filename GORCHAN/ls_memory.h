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
    gmap<shape_index, base_shape*>* get_index_to_shape_map();
    base_shape* get_shape(shape_index index);
    base_shape* get_shape(gguid guid);
    void reset_raycast();
protected:
    void add_static_shapes();
    private:
    gmap<shape_index, base_shape*> m_index_to_shape;
    gmap<gguid, base_shape*> m_gguid_to_shape;
    indexator* m_shape_indexator;
    gfs_path m_base_path; 
};

