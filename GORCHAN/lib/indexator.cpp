#include "../pch.h"
#include "indexator.h"


indexator::indexator(gfs_path filename)
{
	gfs_path base_path = BASE_PATH / L"indexes";
	gfs::create_directories(base_path);
	m_filename /= base_path;
	m_filename /= filename;
	glocale utf16(glocale(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>);

	if(gfs::exists(m_filename) == true)
	{
		gifstream stream(m_filename.generic_string(), std::ios::app);
		stream.imbue(utf16);
		stream >> m_index;
	}
	else
	{
		m_index = 0;
	}
}

shape_index indexator::get_next_shape_index()
{
	m_index++;

	glocale utf16(glocale(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>);
	gofstream stream(m_filename.c_str(), std::ios::trunc);
	stream.imbue(utf16);
	stream << m_index;

	return m_index;
}

gint indexator::get_next_index()
{
	m_index++;

	glocale utf16(glocale(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>);
	gofstream stream(m_filename.c_str(), std::ios::trunc);
	stream.imbue(utf16);
	stream << m_index;

	return m_index;
}