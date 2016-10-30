#pragma once
#include <vector>
using namespace std;

/* Stores an assets information */
template<typename Asset, typename ID> struct AssetInfo
{
	AssetInfo(Asset* asset, ID name) : asset(asset), name(name) {}
	~AssetInfo() { delete asset; }
	Asset* asset;
	ID name;
};

/* Stores and distributes assets */
template<typename Asset, typename ID> class AssetManeger
{
public:
	AssetManeger() {}
	/* Adds an asset to the vector */
	void loadAsset(Asset* asset, ID id) { assets.push_back(new AssetInfo<Asset, ID>(asset, id)); }

	/* Gets an asset by it ID */
	Asset* getAsset(ID id);

	/* Returns the assets as an array */
	vector<Asset*> getAssets() { vector<Asset*> aa; for (AssetInfo<Asset, ID>* info : assets) aa.push_back(info->asset); return aa; }

	/* Deletes the asset */
	~AssetManeger() {}
private:
	/* Vector of asset pointers */
	vector<AssetInfo<Asset, ID>*> assets;
};