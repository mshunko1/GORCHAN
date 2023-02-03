#include "ear.h"

ear::ear()
{

}

ear::~ear()
{

}


gvector<base_shape*> ear::parse_shapes(gstring s)
{
    gvector<base_shape*> ret;

    const std::wregex &sep_regex = std::wregex{L"\\s+"};
    std::wsregex_token_iterator iter(s.begin(), s.end(), sep_regex, -1);
    std::wsregex_token_iterator end;
    for(;iter!=end; ++iter)
    {
        ret.push_back(new fona_shape(*iter));
    } 
    return ret;
}