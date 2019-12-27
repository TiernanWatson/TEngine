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

		static uint32 CreateShader(
			const std::string& name, 
			const char* vertSource, 
			const char* fragSource
		);

		static uint32 GetShader(const std::string& name);

		static void SetMat4(uint32 id, const std::string& name, const Matrix4& mat);
		static void SetVec4(uint32 id, const std::string& name, const Vector4& vec);
		static void SetVec3(uint32 id, const std::string& name, const Vector3& vec);
		static void SetVec2(uint32 id, const std::string& name, const Vector2& vec);
		static void SetFloat32(uint32 id, const std::string& name, const float32& val);

	private:
		static std::unordered_map<std::string, uint32> nameToShader;
	};
}
