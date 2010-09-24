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
void COGGlobalVarsTable::SetFVar (
					  const std::string& _VarAlias, 
					  const std::string& _SVar)
{
	m_SVarsList[_VarAlias] = _SVar;
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
