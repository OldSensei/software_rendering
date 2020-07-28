#include <Windows.h>
#include <string>
#include <exception>

#include "string_conversion.hpp"

namespace SFWR::Sytem::Utils
{
	std::string to_utf8(const wchar_t* const source)
	{
		int requestedSize = WideCharToMultiByte(CP_UTF8, 0, source, -1, nullptr, 0, nullptr, nullptr);

		if (requestedSize == 0)
		{
			throw std::exception(u8"Error during calculation of conversioned utf8 string");
		}

		std::string convertedString(requestedSize, 0);

		int result = WideCharToMultiByte(CP_UTF8, 0, source, -1, convertedString.data(), requestedSize, nullptr, nullptr);

		if (requestedSize == 0)
		{
			throw std::exception(u8"Error during conversion to utf8");
		}

		return convertedString;
	}

	std::string to_utf8(const wchar_t* const source, size_t size)
	{
		int requestedSize = WideCharToMultiByte(CP_UTF8, 0, source, size, nullptr, 0, nullptr, nullptr);

		if (requestedSize == 0)
		{
			throw std::exception(u8"Error during calculation of conversioned utf8 string");
		}

		std::string convertedString(static_cast<size_t>(requestedSize) + 1, 0);

		int result = WideCharToMultiByte(CP_UTF8, 0, source, size, convertedString.data(), requestedSize, nullptr, nullptr);

		if (requestedSize == 0)
		{
			throw std::exception(u8"Error during conversion to utf8");
		}

		return convertedString;
	}

	//std::string to_utf8(const std::wstring& source)
	//{
	//
	//}

} // namespace SFWR::Sytem::Utils