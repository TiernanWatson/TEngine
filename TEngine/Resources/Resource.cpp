#include "Resource.h"

namespace TEngine
{
	Resource::Resource()
		: rId(0), path("")
	{
	}
	
	Resource::Resource(uint32 rId, std::string path)
		: rId(rId), path(path)
	{
	}

	uint32 Resource::GetId() const
	{
		return rId;
	}

	std::string Resource::GetPath() const
	{
		return path;
	}
}
