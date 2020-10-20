#pragma once
#include <unordered_map>
#include <string>

namespace Libero
{
	template <typename Data>
	class ILoader
	{
	public:
		virtual Data* Load(const std::string& filepath) = 0;

	protected:
		using DataMap = std::unordered_map<std::string, Data*>;
		DataMap m_pDataMap;
	};

	class Loader_SDL_Textures : public ILoader<SDL_Texture>
	{
	public:
		SDL_Texture* Load(const std::string& filepath) override;
	};
}
