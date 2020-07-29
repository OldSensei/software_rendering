#include <cassert>
#include "frame_buffer.hpp"

namespace SFWR::Renderer
{
	FrameBuffer::FrameBuffer(std::uint32_t width, std::uint32_t height, std::uint32_t bitsPerPixel) : 
		m_width{ width },
		m_height{ height },
		m_rowSize{ width * (bitsPerPixel / 8) },
		m_pixelDepth{ bitsPerPixel / 8 },
		m_sizeInBytes{ width * static_cast<std::uint64_t>(height) * static_cast<std::uint64_t>(bitsPerPixel / 8) },
		m_buffer{ std::make_unique<std::byte[]>(m_sizeInBytes) }
	{
		// for now only 32 bits per pixel mode is allowed
		assert(bitsPerPixel == 32);
	}

	void FrameBuffer::clear(std::uint32_t r, std::uint32_t g, std::uint32_t b)
	{
		std::uint32_t value = 
								(static_cast<std::uint32_t>(b) & 0xff) + 
								(static_cast<std::uint32_t>(g) << 8) + 
								(static_cast<std::uint32_t>(r) << 16);

		auto* start = reinterpret_cast<std::uint32_t*>(m_buffer.get());
		auto size = m_sizeInBytes / sizeof(std::uint32_t);

		for (std::uint32_t pixelIndex = 0; pixelIndex < size; ++pixelIndex)
		{
			*(start + pixelIndex) = value;
		}
	}

	void FrameBuffer::putPixel(std::uint32_t x, std::uint32_t y, std::uint32_t r, std::uint32_t g, std::uint32_t b)
	{
		std::uint64_t pixelStartByte = static_cast<std::uint64_t>(y) * m_rowSize + static_cast<std::uint64_t>(x) * m_pixelDepth;
		m_buffer[pixelStartByte] = static_cast<std::byte>(b & 0xff);
		m_buffer[pixelStartByte + 1] = static_cast<std::byte>(g & 0xff);
		m_buffer[pixelStartByte + 2] = static_cast<std::byte>(r & 0xff);
		m_buffer[pixelStartByte + 3] = static_cast<std::byte>(0);
	}

	const std::byte* const FrameBuffer::getBuffer() const
	{
		return m_buffer.get();
	}
} // namespace SFWR::Renderer
