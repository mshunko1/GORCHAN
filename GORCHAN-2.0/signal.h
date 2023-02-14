#pragma once
#include "framework.h"


class signal
{
public:
	signal(g2string name, g2int value);
	virtual signal* add(signal* signal);
	virtual void add_to(signal* signal);
	static signal* greatest(signal* l, signal* r);
	static bool is_neutral(signal* signal);
protected:
	g2string m_name;
	g2int m_value;
};

