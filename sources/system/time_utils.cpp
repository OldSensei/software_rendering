#include "time_utils.hpp"

namespace SFWR::System::Utils
{
	ScopedTimer::ScopedTimer(std::uint64_t& timeStore) noexcept :
		m_timeStorage{ timeStore },
		m_start{ std::chrono::high_resolution_clock::now() }
	{

	}

	ScopedTimer::~ScopedTimer()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto result = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_start);
		m_timeStorage = result.count();
	}

} // namespace SFWR::Sytem::Utils
