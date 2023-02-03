#include "pch.h"
#include "indexator.h"


indexator::indexator(gfs_path filename)
{
	gfs_path base_path = BASE_PATH / L"indexes";
	gfs::create_directories(base_path);
	m_filename = base_path / filename;
	glocale utf16(glocale(""), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>);
	gifstream stream(m_filename.c_str());
	stream.imbue(utf16);
	stream >> m_index;
}

shape_index indexator::get_next_shape_index()
{
	m_index++;

	glocale utf16(glocale(""), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>);
	gofstream stream(m_filename.c_str(), std::ios::trunc);
	stream.imbue(utf16);
	stream << m_index;

	return m_index;
}

gint indexator::get_next_index()
{
	m_index++;

	glocale utf16(glocale(""), new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>);
	gofstream stream(m_filename.c_str(), std::ios::trunc);
	stream.imbue(utf16);
	stream << m_index;

	return m_index;
}