#pragma once


class ls_memory
{
    public:
    friend class mind_preservation_service;
    ls_memory();
    void add_shape(base_shape* shape);
    void load();
    void save();
    bool exist(shape_index index);
    bool exist(base_shape* shape);
    base_shape* get_shape(shape_index index);
    base_shape* get_shape(gguid guid);
    void reset_raycast();
    void reset_just_added();
    gint remove_shape(base_shape* shape);
protected:
    void add_static_shapes();
    gmap<shape_index, base_shape*> m_index_to_shape;
    private:
    gmap<gguid, base_shape*> m_gguid_to_shape;
    indexator* m_shape_indexator;
    gfs_path m_base_path; 
};

