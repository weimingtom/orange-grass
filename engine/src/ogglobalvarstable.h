/*
 *  OGGlobalVarsTable.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGGLOBALVARSTABLE_H_
#define OGGLOBALVARSTABLE_H_

#include "IOGGlobalVarsTable.h"
#include <hash_map>


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

	// set Vec2 variable.
	virtual void SetVec2Var (
		const std::string& _VarAlias, 
		const Vec2& _vVar);

	// set Vec3 variable.
	virtual void SetVec3Var (
		const std::string& _VarAlias, 
		const Vec3& _vVar);

	// set Vec4 variable.
	virtual void SetVec4Var (
		const std::string& _VarAlias, 
		const Vec4& _vVar);

	// get integer variable.
	virtual int GetIVar (const std::string& _VarAlias);

	// get floating point variable.
	virtual float GetFVar (const std::string& _VarAlias);

	// get string variable.
	virtual const std::string& GetSVar (const std::string& _VarAlias);

	// get Vec2 variable.
	virtual const Vec2& GetVec2Var (const std::string& _VarAlias);

	// get Vec3 variable.
	virtual const Vec3& GetVec3Var (const std::string& _VarAlias);

	// get Vec4 variable.
	virtual const Vec4& GetVec4Var (const std::string& _VarAlias);

private:

	std::hash_map<std::string, int>			m_IVarsList;
	std::hash_map<std::string, float>		m_FVarsList;
	std::hash_map<std::string, std::string>	m_SVarsList;
	std::hash_map<std::string, Vec2>		m_Vec2VarsList;
	std::hash_map<std::string, Vec3>		m_Vec3VarsList;
	std::hash_map<std::string, Vec4>		m_Vec4VarsList;
};


#endif
