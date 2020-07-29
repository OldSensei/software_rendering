#pragma once
#include <cstddef>
#include <memory>

namespace SFWR::Renderer
{
	class FrameBuffer
	{
	public:
		FrameBuffer(std::uint32_t width, std::uint32_t height, std::uint32_t bitsPerPixel);

		void clear(std::uint32_t r, std::uint32_t g, std::uint32_t b);
		void putPixel(std::uint32_t x, std::uint32_t y, std::uint32_t r, std::uint32_t g, std::uint32_t b);

		const std::byte* const getBuffer() const;
		std::uint32_t getWidth() const { return m_width; };
		std::uint32_t getHeight() const { return m_height; };

	private:
		std::uint32_t m_width;
		std::uint32_t m_height;
		std::uint32_t m_rowSize;
		std::uint32_t m_pixelDepth;
		std::uint64_t m_sizeInBytes;
		std::unique_ptr<std::byte[]> m_buffer;
	};
} // namespace SFWR::Renderer
