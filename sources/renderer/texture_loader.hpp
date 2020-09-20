#pragma once
#include <filesystem>
#include <memory>

#include "texture_data.hpp"

namespace SFWR::Renderer
{
	enum class LoaderType
	{
		UNKNOWN = 0,
		BMP = 1
	};

	class ITextureLoader
	{
	public:
		virtual LoaderType getLoaderType() const = 0;
		virtual std::unique_ptr<ITextureData> load(const std::filesystem::path& texturePath) noexcept = 0;

	protected:
		virtual ~ITextureLoader() = default;
	};
} // namespace SFWR::Renderer
