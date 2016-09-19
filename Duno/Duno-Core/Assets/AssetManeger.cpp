#include "AssetManeger.h"

template<typename Asset, typename ID> Asset* AssetManeger<Asset, ID>::getAsset(ID id)
{
	for (AssetInfo* info : assets)
		if (info->id == id)
			return info->asset;
	/* Call exception here */
	return NULL;
}