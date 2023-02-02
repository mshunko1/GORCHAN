#pragma once
class ls_memory
{
    public:
    ls_memory();
    void add_shape(base_shape* shape);
    void load();
    void save();
    private:
    gmap<shape_index, base_shape*> m_index_to_shape;
    gmap<base_shape*, shape_index> m_shape_to_index;
};

