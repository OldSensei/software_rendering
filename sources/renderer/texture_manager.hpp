#pragma once
#include <unordered_map>
#include "texture_loader.hpp"

namespace SFWR::Renderer
{
	class TextureManager
	{
	public:
		bool addTextureLoader(ITextureLoader&& loader);


	private:
		std::unordered_map<std::uint64_t, ITextureData> m_textures;
	};

} // namespace SFWR::Renderer
