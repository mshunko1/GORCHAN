#include "GORCHAN.h"

GORCHAN::GORCHAN()
{
    
}

GORCHAN::~GORCHAN()
{

}
void asd()
{

}
void GORCHAN::init()
{
    m_memory = new ls_memory();
    m_shape_iterator = new shape_iterator(m_memory);
    m_ear = new ear();

    m_shape_iterator->init();
    m_memory->load();

    std::thread  m_mind_proc1 (&asd);
}

void GORCHAN::deinit()
{
    m_shape_iterator->deinit();
    m_memory->save();
}

void GORCHAN::percive(std::string signal)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter; 
    std::wstring wide = converter.from_bytes(signal);

    gvector<base_shape*> shape_signal = m_ear->parse_shapes(wide);

    for(base_shape* shape:shape_signal)
    {
        m_memory->add_shape(shape);
    }

    m_shape_iterator->set_initial_shapes(shape_signal);
}

void GORCHAN::add_callback(mind_callback* callback)
{

}

void GORCHAN::mind_proc()
{

}

void GORCHAN::react_proc()
{

}