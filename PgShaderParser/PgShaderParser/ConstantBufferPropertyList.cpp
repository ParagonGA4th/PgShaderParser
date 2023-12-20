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
		for (int i = 0; i < _boolPropList.size(); i++) { _boolPropList.pop(); }
		for (int i = 0; i < _uintPropList.size(); i++) { _uintPropList.pop(); }
		for (int i = 0; i < _intPropList.size(); i++) { _intPropList.pop(); }
		for (int i = 0; i < _floatPropList.size(); i++) { _floatPropList.pop(); }
		for (int i = 0; i < _vec2PropList.size(); i++) { _vec2PropList.pop(); }
		for (int i = 0; i < _vec3PropList.size(); i++) { _vec3PropList.pop(); }
		for (int i = 0; i < _vec4PropList.size(); i++) { _vec4PropList.pop(); }
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

	bool ConstantBufferPropertyList::RetrieveSingleBoolProp(std::string& varName, bool& value)
	{
		if (_boolPropList.empty()) { return false; }

		auto tRes = _boolPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_boolPropList.pop();
	}

	bool ConstantBufferPropertyList::RetrieveSingleUnsignedIntProp(std::string& varName, unsigned int& value)
	{
		if (_uintPropList.empty()) { return false; }

		auto tRes = _uintPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_uintPropList.pop();
	}

	bool ConstantBufferPropertyList::RetrieveSingleIntProp(std::string& varName, int& value)
	{
		if (_intPropList.empty()) { return false; }

		auto tRes = _intPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_intPropList.pop();
	}

	bool ConstantBufferPropertyList::RetrieveSingleFloatProp(std::string& varName, float& value)
	{
		if (_floatPropList.empty()) { return false; }

		auto tRes = _floatPropList.top();
		varName = tRes.first;
		value = tRes.second;

		_floatPropList.pop();
	}

	bool ConstantBufferPropertyList::RetrieveSingleVector2Prop(std::string& varName, float2& value)
	{
		if (_vec2PropList.empty()) { return false; }

		auto tRes = _vec2PropList.top();
		varName = tRes.first;
		value = tRes.second;

		_vec2PropList.pop();
	}

	bool ConstantBufferPropertyList::RetrieveSingleVector3Prop(std::string& varName, float3& value)
	{
		if (_vec3PropList.empty()) { return false; }

		auto tRes = _vec3PropList.top();
		varName = tRes.first;
		value = tRes.second;

		_vec3PropList.pop();
	}

	bool ConstantBufferPropertyList::RetrieveSingleVector4Prop(std::string& varName, float4& value)
	{
		if (_vec4PropList.empty()) { return false; }

		auto tRes = _vec4PropList.top();
		varName = tRes.first;
		value = tRes.second;

		_vec4PropList.pop();
	}
}