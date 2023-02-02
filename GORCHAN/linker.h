#pragma once

class linker
{
public:
	linker();
	void serialize(gofstream& stream);
	void deserialize(gifstream& stream);

private:
	rule** m_links;
};

