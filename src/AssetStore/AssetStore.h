#ifndef ASSETSTORE_H  // Use underscore instead of period
#define ASSETSTORE_H

#include <SDL.h>
#include <map>
#include <string>

class AssetStore {
	private:
		std::map<std::string, SDL_Texture*> textures;
	public:
		AssetStore();
		~AssetStore();

		void ClearAssets();
		void AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filepath);
		SDL_Texture* GetTexture(const std::string& assetId);
};

#endif //ASSETSTORE_H