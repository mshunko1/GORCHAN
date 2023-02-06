#include "GORCHAN.h"

GORCHAN::GORCHAN()
{
    
}

GORCHAN::~GORCHAN()
{

}

void GORCHAN::init()
{
    m_memory = new ls_memory();
    m_shape_iterator = new shape_iterator(m_memory);
    m_ear = new ear();

    m_shape_iterator->init();
    m_memory->load();

    m_mind_proc = gthread(&GORCHAN::mind_proc, this);
}

void GORCHAN::deinit()
{
    m_shape_iterator->deinit();
    m_memory->save();
    m_mind_proc.join();
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
    
    m_input_q.push(shape_signal);
}

void GORCHAN::add_callback(mind_callback* callback)
{

}

void GORCHAN::react_proc()
{
    while(true)
    {
        if(m_shape_iterator->get_state() == shape_iterator_state_synced)
        {
            gvector<base_shape*> signals = m_input_q.front();
            m_input_q.pop();
            m_shape_iterator->set_initial_shapes(signals);
            m_mind_status = mind_status_in_proc;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

void GORCHAN::mind_proc()
{
    while(true)
    {    
        if(m_mind_status > mind_status_ready_to_new_signal)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(100));
            continue;
        }

        shape_iterator_state status = m_shape_iterator->build_up();
        if(status == shape_iterator_state_synced)
        {
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        }

        status = m_shape_iterator->build_down();
        if(status == shape_iterator_state_synced)
        {
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        }

        status = m_shape_iterator->build_up();
        if(status == shape_iterator_state_synced)
        {
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        }

        status = m_shape_iterator->build_rules();
        if(status == shape_iterator_state_synced)
        {
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        }

        status = m_shape_iterator->build_down();
        if(status == shape_iterator_state_synced)
        {
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        }
    }
}

