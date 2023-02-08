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
    m_context = new bg_context();
    m_shape_iterator = new shape_iterator(m_memory, m_context);
    m_ear = new ear();
    m_mind_preservation_service = new mind_preservation_service(m_memory, m_context);

    m_shape_iterator->init();
    m_memory->load();

    m_mind_proc = gthread(&GORCHAN::mind_proc, this);
    m_react_proc =  gthread(&GORCHAN::react_proc, this);

    m_mind_status = mind_status_ready_to_new_signal;
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

    gvector<base_shape*> shaped_signal = m_ear->parse_shapes(wide);
    gvector<base_shape*> shape_signal;

    for(base_shape* shape:shaped_signal)
    {
        base_shape* exist_shape = m_memory->get_shape(shape->get_guid());
        if(exist_shape == nullptr)
        {
            exist_shape = shape;
            m_memory->add_shape(shape);
        }
        shape_signal.push_back(exist_shape);
    }
 
    if(whois == nullptr)
    {
        whois  = new whois_shape(L"mshunko");
        m_memory->add_shape(whois);
    }
    if(howis == nullptr)
    { 
        howis = new howis_shape(L"normal");
        m_memory->add_shape(howis);
    }

    shape_signal.insert(shape_signal.begin(), howis);
    shape_signal.insert(shape_signal.begin(), whois);

    base_shape* eos = m_memory->get_shape(eos_shape_index);
    shape_signal.push_back(eos);
    
    m_input_q.push(shape_signal);
}

void GORCHAN::add_callback(mind_callback* callback)
{

}

void GORCHAN::react_proc()
{
    while(true)
    {
        if(m_mind_status == mind_status_ready_to_new_signal)
        {
            if(m_input_q.empty())
            {
                continue;
            }
            gvector<base_shape*> signals = m_input_q.front();
            m_input_q.pop();
            m_memory->reset_raycast();
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
        if(m_mind_status != mind_status_in_proc)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(1000));
            continue;
        }

        shape_iterator_state status = m_shape_iterator->build_down();
        if(status == shape_iterator_state_synced)
        {
            m_memory->reset_raycast();
            m_mind_preservation_service->mind_preserve_operation();
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        }

        status = m_shape_iterator->build_up();
        if(status == shape_iterator_state_synced)
        {
            m_memory->reset_raycast();
            m_mind_preservation_service->mind_preserve_operation();
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        }

        status = m_shape_iterator->build_rules();
        if(status == shape_iterator_state_synced)
        {
            m_memory->reset_raycast();
            m_mind_preservation_service->mind_preserve_operation();
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        } 
    }
}

