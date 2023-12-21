#pragma once
#include <string>
#include "PgDefineEnums.h"

namespace Pg
{
	//Vector의 오버로드를 피하기 위해. (vector<bool>)
	struct BoolWrapper
	{
		BoolWrapper(bool val) { _value = val; }
		bool _value = false;
	};

	struct ConstantBufferVariableProp
	{
		ConstantBufferVariableProp() = default;

		std::string _name;
		unsigned int _size = 0;
		unsigned int _startOffset = 0;
	};

	struct TexturesVariableProp
	{
		TexturesVariableProp() = default;

		std::string _name;
		eResourceReturnType _resReturnType; //타입자체만, 개수 기록 D3D상 X (하지만 대부분 4개짜리일것)
		unsigned int _registerCnt = 0;
	};

	struct float2
	{
		float2() = default;
		float2(float tX, float tY) : x(tX), y(tY) {}

		union
		{
			float _v[2];
			struct
			{
				float x;
				float y;
			};
		};
	};

	struct float3
	{
		float3() = default;
		float3(float tX, float tY, float tZ) : x(tX), y(tY), z(tZ) {}

		union
		{
			float _v[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};
	};

	struct float4
	{
		float4() = default;
		float4(float tX, float tY, float tZ, float tW) : x(tX), y(tY), z(tZ), w(tW) {}

		union
		{
			float _v[4];
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};
	};
}
