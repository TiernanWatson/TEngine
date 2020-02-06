#include "Resource.h"

namespace TEngine
{
	Resource::Resource()
		: r_id_(0), path_("")
	{
	}
	
	Resource::Resource(U32 rId, std::string path)
		: r_id_(rId), path_(path)
	{
	}

	U32 Resource::GetId() const
	{
		return r_id_;
	}

	std::string Resource::GetPath() const
	{
		return path_;
	}
}
