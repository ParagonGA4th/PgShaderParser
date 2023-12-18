#pragma once

namespace Pg
{
	struct float2
	{
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

	struct color4
	{
		union
		{
			float _v[4];
			struct
			{
				float r;
				float g;
				float b;
				float a;
			};
		};
	};
}
