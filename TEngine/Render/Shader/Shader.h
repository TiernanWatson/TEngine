#pragma once
#include "../../Core/PortableTypes.h"
#include <string>

namespace TEngine
{
	class Vector4;
	class Matrix4;

	class Shader
	{
	public:
		Shader();
		Shader(const char* vertexSource, const char* fragSource);

		void Use();

		void SetVec4(const std::string& name, const Vector4& value);
		void SetMat4(const std::string& name, const Matrix4& value);

		uint32 shaderProgram;
	};
}
