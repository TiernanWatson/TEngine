#pragma once
#include "../PortableTypes.h"

namespace TEngine
{
	/**
	* Configuration variable holding atomic types, 4-byte aligned
	**/
	class ConfigVar
	{
	public:
		ConfigVar() {}
		ConfigVar(bool b) : b(b) {}
		ConfigVar(int32 i32) : i32(i32) {}
		ConfigVar(float32 f32) : f32(f32) {}
		ConfigVar(char* str) : str(str) {}

	private:
		union {
			bool b;
			int32 i32;
			float32 f32;
			char* str;
		};

	public:
		bool GetBool() { return b; }
		int32 GetInt32() { return i32; }
		float32 GetFloat32() { return f32; }

		void SetBool(bool b) { this->b = b; }
		void SetInt32(int32 i32) { this->i32 = i32; }
		void SetFloat32(float32 f32) { this->f32 = f32; }
	};
}
