#include "stdafx.h"
#include "audio_capture.h"




bool audio_capture::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
	OutputDebugString(std::to_wstring((int)sampleCount).c_str());
	OutputDebugString(L"\r\n");
	return true;
}