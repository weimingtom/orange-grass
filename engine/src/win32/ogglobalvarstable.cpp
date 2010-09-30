/*
 *  OGGlobalVarsTable.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogglobalvarstable.h"


COGGlobalVarsTable::COGGlobalVarsTable()
{
}


COGGlobalVarsTable::~COGGlobalVarsTable()
{
}


// set integer variable.
void COGGlobalVarsTable::SetIVar (
					  const std::string& _VarAlias, 
					  int _Var)
{
	m_IVarsList[_VarAlias] = _Var;
}


// set floating point variable.
void COGGlobalVarsTable::SetFVar (
					  const std::string& _VarAlias, 
					  float _fVar)
{
	m_FVarsList[_VarAlias] = _fVar;
}


// set string variable.
void COGGlobalVarsTable::SetSVar (
					  const std::string& _VarAlias, 
					  const std::string& _SVar)
{
	m_SVarsList[_VarAlias] = _SVar;
}


// set Vec2 variable.
void COGGlobalVarsTable::SetVec2Var (
						 const std::string& _VarAlias, 
						 const Vec2& _vVar)
{
	m_Vec2VarsList[_VarAlias] = _vVar;
}


// set Vec3 variable.
void COGGlobalVarsTable::SetVec3Var (
						 const std::string& _VarAlias, 
						 const Vec3& _vVar)
{
	m_Vec3VarsList[_VarAlias] = _vVar;
}


// set Vec4 variable.
void COGGlobalVarsTable::SetVec4Var (
						 const std::string& _VarAlias, 
						 const Vec4& _vVar)
{
	m_Vec4VarsList[_VarAlias] = _vVar;
}


// get integer variable.
int COGGlobalVarsTable::GetIVar (const std::string& _VarAlias)
{
	return m_IVarsList[_VarAlias];
}


// get floating point variable.
float COGGlobalVarsTable::GetFVar (const std::string& _VarAlias)
{
	return m_FVarsList[_VarAlias];
}


// get string variable.
const std::string& COGGlobalVarsTable::GetSVar (const std::string& _VarAlias)
{
	return m_SVarsList[_VarAlias];
}


// get Vec2 variable.
const Vec2& COGGlobalVarsTable::GetVec2Var (const std::string& _VarAlias)
{
	return m_Vec2VarsList[_VarAlias];
}


// get Vec3 variable.
const Vec3& COGGlobalVarsTable::GetVec3Var (const std::string& _VarAlias)
{
	return m_Vec3VarsList[_VarAlias];
}


// get Vec4 variable.
const Vec4& COGGlobalVarsTable::GetVec4Var (const std::string& _VarAlias)
{
	return m_Vec4VarsList[_VarAlias];
}
