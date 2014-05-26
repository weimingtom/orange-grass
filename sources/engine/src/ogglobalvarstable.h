/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef OGGLOBALVARSTABLE_H_
#define OGGLOBALVARSTABLE_H_

#include "IOGGlobalVarsTable.h"
#include <map>


class COGGlobalVarsTable : public IOGGlobalVarsTable
{
public:
	COGGlobalVarsTable();
	virtual ~COGGlobalVarsTable();

	// set integer variable.
	virtual void SetIVar (
		const std::string& _VarAlias, 
		int _Var);

	// set floating point variable.
	virtual void SetFVar (
		const std::string& _VarAlias, 
		float _fVar);

	// set string variable.
	virtual void SetSVar (
		const std::string& _VarAlias, 
		const std::string& _SVar);

	// set OGVec2 variable.
	virtual void SetVec2Var (
		const std::string& _VarAlias, 
		const OGVec2& _vVar);

	// set OGVec3 variable.
	virtual void SetVec3Var (
		const std::string& _VarAlias, 
		const OGVec3& _vVar);

	// set OGVec4 variable.
	virtual void SetVec4Var (
		const std::string& _VarAlias, 
		const OGVec4& _vVar);

	// get integer variable.
	virtual int GetIVar (const std::string& _VarAlias);

	// get floating point variable.
	virtual float GetFVar (const std::string& _VarAlias);

	// get string variable.
	virtual const std::string& GetSVar (const std::string& _VarAlias);

	// get OGVec2 variable.
	virtual const OGVec2& GetVec2Var (const std::string& _VarAlias);

	// get OGVec3 variable.
	virtual const OGVec3& GetVec3Var (const std::string& _VarAlias);

	// get OGVec4 variable.
	virtual const OGVec4& GetVec4Var (const std::string& _VarAlias);

private:

    std::map<std::string, int>			m_IVarsList;
    std::map<std::string, float>		m_FVarsList;
    std::map<std::string, std::string>  m_SVarsList;
    std::map<std::string, OGVec2>		    m_Vec2VarsList;
    std::map<std::string, OGVec3>		    m_Vec3VarsList;
    std::map<std::string, OGVec4>		    m_Vec4VarsList;
};


#endif
