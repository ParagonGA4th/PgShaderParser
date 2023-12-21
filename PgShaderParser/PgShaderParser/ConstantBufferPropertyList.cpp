#include "ConstantBufferPropertyList.h"

namespace Pg
{

	ConstantBufferPropertyList::ConstantBufferPropertyList()
	{

	}

	ConstantBufferPropertyList::~ConstantBufferPropertyList()
	{

	}

	void ConstantBufferPropertyList::Reset()
	{
		_boolPropList.clear();
		_uintPropList.clear();
		_intPropList.clear();
		_floatPropList.clear();
		_vec2PropList.clear();
		_vec3PropList.clear();
		_vec4PropList.clear();
	}

	void ConstantBufferPropertyList::SetByteCount(unsigned int byteCount)
	{
		_byteCount = byteCount;
	}

	unsigned int ConstantBufferPropertyList::GetByteCount()
	{
		return _byteCount;
	}

	void ConstantBufferPropertyList::SetConstantBufferName(const std::string& cBufName)
	{
		_constantBufferName = cBufName;
	}

	std::string ConstantBufferPropertyList::GetConstantBufferName()
	{
		return _constantBufferName;
	}
}