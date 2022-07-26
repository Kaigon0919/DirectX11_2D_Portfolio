#pragma once

template<typename RETURN, typename MAP, typename KEY>
RETURN MapFindHelper(MAP& _Map, const KEY& _Key)
{
	MAP::iterator FindIter = _Map.find(_Key);

	if (FindIter != _Map.end())
	{
		return FindIter->second;
	}

	return nullptr;
}