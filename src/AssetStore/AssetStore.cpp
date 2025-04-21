#include "AssetStore.h"
#include "../Logger/Logger.h"
#include <SDL_image.h>


AssetStore::AssetStore() {
	Logger::Log("AssetStore constructor called!");
}

AssetStore::~AssetStore() {
	Logger::Log("AssetStore destructor called!");
}

void AssetStore::ClearAssets() {
	for (auto const& asset : textures) {
		SDL_DestroyTexture(asset.second);
	}
	textures.clear();
}

void AssetStore::AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filepath) {
	SDL_Surface* surfase = IMG_Load(filepath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfase);
	SDL_FreeSurface(surfase);


	textures.emplace(assetId, texture);

	Logger::Log("Texture added to AssetStore with id = " + assetId);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) {
	return textures[assetId];
}