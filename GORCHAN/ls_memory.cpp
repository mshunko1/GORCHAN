#include "pch.h"
#include "ls_memory.h"


ls_memory::ls_memory()
:m_shape_indexator(nullptr)
{
    m_shape_indexator = new indexator(gfs_path(L"shape_indexator.txt"));
    m_base_path /= BASE_PATH / L"ls_memory";
    gfs::create_directories(m_base_path);
}

void ls_memory::add_shape(base_shape* shape)
{
    shape_index index = m_shape_indexator->get_next_shape_index();
    shape->set_index(index);
    m_gguid_to_shape[shape->get_guid()] = shape;
    m_index_to_shape[index] = shape;
}

void ls_memory::reset_raycast()
{
    for(auto item:m_index_to_shape)
    {
        item.second->reset_daycaster();
    }
}

void ls_memory::load()
{
    using recursive_directory_iterator = gfs::recursive_directory_iterator;
 
    for (const auto& dirEntry : recursive_directory_iterator(m_base_path))
    {
        gfs_path path = dirEntry.path();
        if(gfs::is_directory(path) == false)
        { 
            gifstream stream(path.c_str(), std::ios::binary);
            glocale utf16(glocale(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>);
            stream.imbue(utf16);

            base_shape* shape;
            shape_type shape_type = base_shape::deserialize_type(stream, true);
            switch (shape_type)
            {
                case shape_type_fona:
                    shape = new fona_shape();
                    break;
                case shape_type_eos:
                    shape = new eos_shape();
                    break;
                case shape_type_soul_matter:
                    shape = new soul_matter_shape();
                default:
                    throw new gexception((char*)"undefined shape type when try to load shapes in ls_memory");
                    break;
            }
            shape->deserialize(stream);
            stream.close();
        }
    }

    add_static_shapes();
}


gmap<shape_index, base_shape*>* ls_memory::get_index_to_shape_map()
{
    return &m_index_to_shape;
}


base_shape* ls_memory::get_shape(shape_index index)
{
    return m_index_to_shape[index];
}

base_shape* ls_memory::get_shape(gguid guid)
{
    return m_gguid_to_shape[guid];
}

void ls_memory::add_static_shapes()
{
    auto shape_eos = m_index_to_shape.find(eos_shape_index);
    if(shape_eos == m_index_to_shape.end())
    {
        base_shape* oes = eos_shape::get_instance();
        m_gguid_to_shape[oes->get_guid()] = oes;
        m_index_to_shape[oes->get_index()] = oes;
    }

    auto shape_sm = m_index_to_shape.find(soul_matter_shape_index);
    if(shape_sm == m_index_to_shape.end())
    {
        base_shape* sm = soul_matter_shape::get_instance();
        m_gguid_to_shape[sm->get_guid()] = sm;
        m_index_to_shape[sm->get_index()] = sm;
    }
}

void ls_memory::save()
{
    for(gpair<shape_index, base_shape*> shape:m_index_to_shape)
    {
        gfs_path file_name = shape.second->get_filename();
        shape_type shape_type = shape.second->get_type();
        gfs_path path_to_shape_file = m_base_path / gto_gstring(shape_type);
        gfs::create_directories(path_to_shape_file);
        path_to_shape_file /= file_name;
        gofstream stream(path_to_shape_file.c_str(), std::ios::trunc|std::ios::binary);

        shape.second->serialize(stream);
        stream.flush();
        stream.close();
    }

    m_index_to_shape.clear();
    m_gguid_to_shape.clear();
}