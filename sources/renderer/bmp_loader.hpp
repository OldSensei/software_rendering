#pragma once
#include "texture_loader.hpp"

namespace SFWR::Renderer
{
	class BMPTextureLoader : public ITextureLoader
	{
	public:
		LoaderType getLoaderType() const override { return LoaderType::BMP; };

		std::unique_ptr<ITextureData> load(const std::filesystem::path& texturePath) noexcept override;
	};
} // namespace SFWR::Renderer
