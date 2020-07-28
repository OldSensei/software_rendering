#pragma once
#include <string>

namespace SFWR::Sytem::Utils
{
	std::string to_utf8(const wchar_t* const source);
	std::string to_utf8(const wchar_t* const source, size_t size);
	//std::string to_utf8(const std::wstring& source);

} // namespace SFWR::Sytem::Utils
