/*
 *  ogemitter.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitter.h"
#include "OrangeGrass.h"
#include <algorithm>


COGEmitter::COGEmitter()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_pRenderer = GetRenderer();
}


COGEmitter::~COGEmitter()
{
}


// Update position.
void COGEmitter::UpdatePosition (const Vec3& _vPosition)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	if (!m_bPositionUpdated)
	{
		m_vCurPosition = _vPosition;
		m_vPrevPosition = _vPosition;
		m_bPositionUpdated = true;
	}
	else
	{
		m_vPrevPosition = m_vCurPosition;
		m_vCurPosition = _vPosition;
	}
}


// Get effect run status.
OGEffectStatus COGEmitter::GetStatus() const 
{ 
	return m_Status; 
}


// get string parameter.
std::string COGEmitter::GetStringParam (const std::string& _Alias) const
{
	TStringParamList::const_iterator iter = m_StringParams.find(_Alias);
	if (iter != m_StringParams.end())
	{
		return iter->second;
	}
	return std::string("");
}


// set string parameter.
void COGEmitter::SetStringParam (const std::string& _Alias, const std::string& _Value)
{
	TStringParamList::iterator iter = m_StringParams.find(_Alias);
	if (iter != m_StringParams.end())
	{
		iter->second = _Value;
	}
}


// get int parameter.
unsigned int COGEmitter::GetIntParam (const std::string& _Alias) const
{
	TIntParamList::const_iterator iter = m_IntParams.find(_Alias);
	if (iter != m_IntParams.end())
	{
		return iter->second.value;
	}
	return 0;
}


// set int parameter.
void COGEmitter::SetIntParam (const std::string& _Alias, unsigned int _Value)
{
	TIntParamList::iterator iter = m_IntParams.find(_Alias);
	if (iter != m_IntParams.end())
	{
		if (_Value >= iter->second.min_value && _Value <= iter->second.max_value)
		{
			iter->second.value = _Value;
		}
	}
}


// get float parameter.
float COGEmitter::GetFloatParam (const std::string& _Alias) const
{
	TFloatParamList::const_iterator iter = m_FloatParams.find(_Alias);
	if (iter != m_FloatParams.end())
	{
		return iter->second.value;
	}
	return 0.0f;
}


// set float parameter.
void COGEmitter::SetFloatParam (const std::string& _Alias, float _Value)
{
	TFloatParamList::iterator iter = m_FloatParams.find(_Alias);
	if (iter != m_FloatParams.end())
	{
		if (_Value >= iter->second.min_value && _Value <= iter->second.max_value)
		{
			iter->second.value = _Value;
		}
	}
}


// get color parameter.
Vec4 COGEmitter::GetColorParam (const std::string& _Alias) const
{
	TColorParamList::const_iterator iter = m_ColorParams.find(_Alias);
	if (iter != m_ColorParams.end())
	{
		return iter->second;
	}
	return Vec4(0.0f, 0.0f, 0.0f, 0.0f);
}


// set color parameter.
void COGEmitter::SetColorParam (const std::string& _Alias, const Vec4& _Value)
{
	TColorParamList::iterator iter = m_ColorParams.find(_Alias);
	if (iter != m_ColorParams.end())
	{
		iter->second = _Value;
	}
}


// add string param.
void COGEmitter::AddStringParam (const std::string& _Alias, const std::string& _Value)
{
	m_StringParams[_Alias] = _Value;
}


// add int param.
void COGEmitter::AddIntParam (const std::string& _Alias, unsigned int _Value, unsigned int _Min, unsigned int _Max)
{
	EmitterIntParam param;
	param.value = _Value;
	param.min_value = _Min;
	param.max_value = _Max;
	m_IntParams[_Alias] = param;
}


// add float param.
void COGEmitter::AddFloatParam (const std::string& _Alias, float _Value, float _Min, float _Max)
{
	EmitterFloatParam param;
	param.value = _Value;
	param.min_value = _Min;
	param.max_value = _Max;
	m_FloatParams[_Alias] = param;
}


// add color param.
void COGEmitter::AddColorParam (const std::string& _Alias, const Vec4& _Value)
{
	m_ColorParams[_Alias] = _Value;
}
