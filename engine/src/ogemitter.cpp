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


// Set direction.
void COGEmitter::SetDirection (const Vec3& _vDir)
{
	m_Direction = _vDir;
}


// Get effect run status.
OGEffectStatus COGEmitter::GetStatus() const 
{ 
	return m_Status; 
}


// get string parameter.
std::string* COGEmitter::GetStringParam (const std::string& _Alias)
{
	TStringParamList::const_iterator iter = m_StringParams.find(_Alias);
	if (iter != m_StringParams.end())
	{
		return iter->second;
	}
	return NULL;
}


// set string parameter.
void COGEmitter::SetStringParam (const std::string& _Alias, std::string* _pValue)
{
	TStringParamList::iterator iter = m_StringParams.find(_Alias);
	if (iter != m_StringParams.end())
	{
		iter->second = _pValue;
	}
}


// get int parameter.
unsigned int* COGEmitter::GetIntParam (const std::string& _Alias)
{
	TIntParamList::const_iterator iter = m_IntParams.find(_Alias);
	if (iter != m_IntParams.end())
	{
		return iter->second;
	}
	return NULL;
}


// set int parameter.
void COGEmitter::SetIntParam (const std::string& _Alias, unsigned int* _pValue)
{
	TIntParamList::iterator iter = m_IntParams.find(_Alias);
	if (iter != m_IntParams.end())
	{
		iter->second = _pValue;
	}
}


// get float parameter.
float* COGEmitter::GetFloatParam (const std::string& _Alias)
{
	TFloatParamList::const_iterator iter = m_FloatParams.find(_Alias);
	if (iter != m_FloatParams.end())
	{
		return iter->second;
	}
	return NULL;
}


// set float parameter.
void COGEmitter::SetFloatParam (const std::string& _Alias, float* _pValue)
{
	TFloatParamList::iterator iter = m_FloatParams.find(_Alias);
	if (iter != m_FloatParams.end())
	{
		iter->second = _pValue;
	}
}


// get color parameter.
Vec4* COGEmitter::GetColorParam (const std::string& _Alias)
{
	TColorParamList::const_iterator iter = m_ColorParams.find(_Alias);
	if (iter != m_ColorParams.end())
	{
		return iter->second;
	}
	return NULL;
}


// set color parameter.
void COGEmitter::SetColorParam (const std::string& _Alias, Vec4* _pValue)
{
	TColorParamList::iterator iter = m_ColorParams.find(_Alias);
	if (iter != m_ColorParams.end())
	{
		iter->second = _pValue;
	}
}


// add string param.
void COGEmitter::AddStringParam (const std::string& _Alias, std::string* _pValue)
{
	m_StringParams[_Alias] = _pValue;
}


// add int param.
void COGEmitter::AddIntParam (const std::string& _Alias, unsigned int* _pValue)
{
	m_IntParams[_Alias] = _pValue;
}


// add float param.
void COGEmitter::AddFloatParam (const std::string& _Alias, float* _pValue)
{
	m_FloatParams[_Alias] = _pValue;
}


// add color param.
void COGEmitter::AddColorParam (const std::string& _Alias, Vec4* _pValue)
{
	m_ColorParams[_Alias] = _pValue;
}


// Load parameters of the emitter.
void COGEmitter::LoadParams (IOGGroupNode* _pNode)
{
	IOGSettingsReader* pReader = GetSettingsReader();

	if (_pNode)
	{
		TStringParamList::iterator str_iter = m_StringParams.begin();
		for (; str_iter != m_StringParams.end(); ++str_iter)
		{
			*(str_iter->second) = pReader->ReadStringParam(_pNode, str_iter->first);
		}

		TIntParamList::iterator int_iter = m_IntParams.begin();
		for (; int_iter != m_IntParams.end(); ++int_iter)
		{
			*(int_iter->second) = (unsigned int)pReader->ReadIntParam(_pNode, int_iter->first);
		}

		TFloatParamList::iterator flt_iter = m_FloatParams.begin();
		for (; flt_iter != m_FloatParams.end(); ++flt_iter)
		{
			*(flt_iter->second) = pReader->ReadFloatParam(_pNode, flt_iter->first);
		}

		TColorParamList::iterator clr_iter = m_ColorParams.begin();
		for (; clr_iter != m_ColorParams.end(); ++clr_iter)
		{
			*(clr_iter->second) = pReader->ReadVec4Param(_pNode, 
				clr_iter->first + std::string("_r"),
				clr_iter->first + std::string("_g"),
				clr_iter->first + std::string("_b"),
				clr_iter->first + std::string("_a"));
		}
	}
}


// Save parameters of the emitter.
void COGEmitter::SaveParams (IOGGroupNode* _pNode)
{
	IOGSettingsReader* pReader = GetSettingsReader();

	if (_pNode)
	{
		TStringParamList::iterator str_iter = m_StringParams.begin();
		for (; str_iter != m_StringParams.end(); ++str_iter)
		{
			pReader->WriteStringParam(_pNode, str_iter->first, *str_iter->second);
		}

		TIntParamList::iterator int_iter = m_IntParams.begin();
		for (; int_iter != m_IntParams.end(); ++int_iter)
		{
			pReader->WriteIntParam(_pNode, int_iter->first, *int_iter->second);
		}

		TFloatParamList::iterator flt_iter = m_FloatParams.begin();
		for (; flt_iter != m_FloatParams.end(); ++flt_iter)
		{
			pReader->WriteFloatParam(_pNode, flt_iter->first, *flt_iter->second);
		}

		TColorParamList::iterator clr_iter = m_ColorParams.begin();
		for (; clr_iter != m_ColorParams.end(); ++clr_iter)
		{
			pReader->WriteVec4Param(_pNode, 
				clr_iter->first + std::string("_r"),
				clr_iter->first + std::string("_g"),
				clr_iter->first + std::string("_b"),
				clr_iter->first + std::string("_a"),
				*clr_iter->second);
		}
	}
}
