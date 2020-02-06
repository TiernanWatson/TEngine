#pragma once
#include "../../Core/PortableTypes.h"
#include <string>
#include <unordered_map>

namespace TEngine
{
	class Matrix4;
	class Vector4;
	class Vector3;
	class Vector2;

	/**
	* Class consisting of only static members for the management of shaders
	**/
	class Shaders
	{
	public:
		Shaders() = delete;

		static U32 CreateShader(
			const std::string& name, 
			const char* vertSource, 
			const char* fragSource
		);

		static U32 GetShader(const std::string& name);

		static U32 GetDefault();

		static void SetMat4(U32 id, const std::string& name, const Matrix4& mat);
		static void SetVec4(U32 id, const std::string& name, const Vector4& vec);
		static void SetVec3(U32 id, const std::string& name, const Vector3& vec);
		static void SetVec2(U32 id, const std::string& name, const Vector2& vec);
		static void SetFloat32(U32 id, const std::string& name, const F32& val);

	private:
		static std::unordered_map<std::string, U32> nameToShader;
	};
}
