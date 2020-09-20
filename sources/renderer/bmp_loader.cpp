#include <Windows.h>
#include <wingdi.h>
#include <exception>

#include "bmp_loader.hpp"

namespace SFWR::Renderer
{
	class BMPTextureData : public ITextureData
	{
	public:
		BMPTextureData(const std::filesystem::path& texturePath);
		~BMPTextureData();

		SFWR::Renderer::TextureInfo getInfo() override;
		SFWR::Math::Colour getColor(float u, float v) override;
		SFWR::Math::Colour getColor(std::uint32_t x, std::uint32_t y) override;

		BMPTextureData(const BMPTextureData&) = delete;
		BMPTextureData& operator=(const BMPTextureData&) = delete;

	private:
		HANDLE m_imageHandle;
		BITMAP m_bitmap;
	};

	BMPTextureData::BMPTextureData(const std::filesystem::path& texturePath)
	{
		m_imageHandle = ::LoadImage(NULL, texturePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (m_imageHandle == NULL)
		{
			throw std::invalid_argument("Can't load image");
		}
		if (::GetObject(m_imageHandle, sizeof(BITMAP), reinterpret_cast<LPVOID>(&m_bitmap)) == 0)
		{
			throw std::invalid_argument("Can't get image object");
		}
	}

	SFWR::Renderer::TextureInfo BMPTextureData::getInfo()
	{
		return TextureInfo{static_cast<std::uint32_t>(m_bitmap.bmWidth), static_cast<std::uint32_t>(m_bitmap.bmHeight), m_bitmap.bmBitsPixel};
	}

	SFWR::Math::Colour BMPTextureData::getColor(float u, float v)
	{
		return SFWR::Math::Colour{ 1.0f, 1.0f, 1.0f, 0.f };
	}

	SFWR::Math::Colour BMPTextureData::getColor(std::uint32_t x, std::uint32_t y)
	{
		std::uint32_t pixelIndex = (y * m_bitmap.bmWidth * 3) + (x * 3);
		std::uint8_t* buffer = reinterpret_cast<std::uint8_t*>(m_bitmap.bmBits) + pixelIndex;
		float r = *buffer;
		float g = *(buffer + 1);
		float b = *(buffer + 2);

		return SFWR::Math::Colour{ b, g, r, 0.f };
	}

	BMPTextureData::~BMPTextureData()
	{
		::DeleteObject(m_imageHandle);
	}

	std::unique_ptr<ITextureData> BMPTextureLoader::load(const std::filesystem::path& texturePath) noexcept
	{
		if (texturePath.empty() || !std::filesystem::exists(texturePath))
		{
			return nullptr;
		}
		
		try
		{
			return std::make_unique<BMPTextureData>(texturePath);
		}
		catch(const std::invalid_argument& e)
		{
			return nullptr;
		}
	}
}
