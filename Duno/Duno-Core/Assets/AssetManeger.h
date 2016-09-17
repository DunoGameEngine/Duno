#pragma once
#include <vector>
using namespace std;

/* Stores and distributes assets */
template<typename Asset> class AssetManeger
{
public:
	AssetManeger() {}
	/* Adds an asset to the vector */
	void loadAsset(Asset* asset) { assets.push_back(asset); }
	/* Delets the asset */
	~AssetManeger() {}
private:
	/* Vector of asset pointers */
	vector<Asset*> assets;
};