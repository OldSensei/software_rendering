#pragma once
#include <cstdint>
#include <chrono>

namespace SFWR::System::Utils
{
	using FloatSeconds = std::chrono::duration<float>;

	class ScopedTimer
	{
	public:
		explicit ScopedTimer(std::uint64_t& timeStore) noexcept;
		~ScopedTimer();

	private:
		std::chrono::high_resolution_clock::time_point m_start;
		std::uint64_t& m_timeStorage;
	};
} // namespace SFWR::Sytem::Utils
