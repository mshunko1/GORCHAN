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

    whois = nullptr;

    howis = nullptr;

    whois_gorchan = nullptr;

    howis_mindprocess = nullptr;
}

void GORCHAN::deinit()
{
    m_shape_iterator->deinit();
    m_memory->save();
    m_mind_proc.join();
}

void GORCHAN::percive(std::string signal, bool debug)
{

    while (m_mind_status != mind_status_ready_to_new_signal)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(signal);
    gvector<base_shape*> shape_signal;

    whois = m_memory->get_shape(L"mshunko");
    if (whois == nullptr)
    {
        whois = new whois_shape(L"mshunko");
        m_memory->add_shape(whois);
    }
    howis = m_memory->get_shape(L"normal");
    if (howis == nullptr)
    {
        howis = new howis_shape(L"normal");
        m_memory->add_shape(howis);
    }
    whois_gorchan = m_memory->get_shape(L"gorchan");
    if (whois_gorchan == nullptr)
    {
        whois_gorchan = new whois_shape(L"gorchan");
        m_memory->add_shape(whois_gorchan);
    }
    howis_mindprocess = m_memory->get_shape(L"mindprocess");
    if (howis_mindprocess == nullptr)
    {
        howis_mindprocess = new howis_shape(L"mindprocess");
        m_memory->add_shape(howis_mindprocess);
    }
    base_shape* eos = m_memory->get_shape(eos_shape_index);
    if (eos == nullptr)
    {
        eos = eos_shape::get_instance();
        m_memory->add_shape(eos);
    }

    if (debug == false)
    {
        gvector<base_shape*> shaped_signal = m_ear->parse_shapes(wide);

        for (base_shape* shape : shaped_signal)
        {
            base_shape* exist_shape = m_memory->get_shape(shape->get_guid());
            if (exist_shape == nullptr)
            {
                exist_shape = shape;
                m_memory->add_shape(shape);
            }
            shape_signal.push_back(exist_shape);
        }


        shape_signal.insert(shape_signal.begin(), howis);
        shape_signal.insert(shape_signal.begin(), whois);

        base_shape* eos = m_memory->get_shape(eos_shape_index);
        shape_signal.push_back(eos);

        m_input_q.push(shape_signal);
    }
    else
    { 
        base_shape* exist_shape = m_memory->get_shape(wide);
        base_shape* shape = nullptr;
        if (exist_shape == nullptr)
        {
            shape = new fona_shape(wide);
            m_memory->add_shape(shape);
            exist_shape = shape;
        }


        shape_signal.push_back(whois_gorchan);
        shape_signal.push_back(howis_mindprocess);
        shape_signal.push_back(shape);
        shape_signal.push_back(eos);

        m_input_q.push(shape_signal);
    }
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
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }
            gvector<base_shape*> signals = m_input_q.front();
            m_input_q.pop();
            m_memory->reset_raycast();
            //m_memory->reset_just_added();
            m_shape_iterator->set_initial_shapes(signals);
            m_mind_status = mind_status_in_proc;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void GORCHAN::mind_proc()
{
    while(true)
    {    
        if(m_mind_status != mind_status_in_proc)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }

        shape_iterator_state status = m_shape_iterator->build_down();
        if(status == shape_iterator_state_synced)
        {
            m_mind_preservation_service->mind_preserve_operation();
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        }

        status = m_shape_iterator->build_up();
        if(status == shape_iterator_state_synced)
        {
            m_mind_preservation_service->mind_preserve_operation();
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        }

        status = m_shape_iterator->build_rules();
        if(status == shape_iterator_state_synced)
        {
            m_mind_preservation_service->mind_preserve_operation();
            m_mind_status = mind_status_ready_to_new_signal;
            continue;
        } 
    }
}

