/*
 *  IOGGlobalVarsTable.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGGLOBALVARSTABLE_H_
#define IOGGLOBALVARSTABLE_H_

#include <string>
#include "Mathematics.h"


class IOGGlobalVarsTable
{
public:
	virtual ~IOGGlobalVarsTable() {}

	// set integer variable.
	virtual void SetIVar (
		const std::string& _VarAlias, 
		int _Var) = 0;

	// set floating point variable.
	virtual void SetFVar (
		const std::string& _VarAlias, 
		float _fVar) = 0;

	// set string variable.
	virtual void SetSVar (
		const std::string& _VarAlias, 
		const std::string& _SVar) = 0;

	// set Vec2 variable.
	virtual void SetVec2Var (
		const std::string& _VarAlias, 
		const Vec2& _vVar) = 0;

	// set Vec3 variable.
	virtual void SetVec3Var (
		const std::string& _VarAlias, 
		const Vec3& _vVar) = 0;

	// set Vec4 variable.
	virtual void SetVec4Var (
		const std::string& _VarAlias, 
		const Vec4& _vVar) = 0;

	// get integer variable.
	virtual int GetIVar (const std::string& _VarAlias) = 0;

	// get floating point variable.
	virtual float GetFVar (const std::string& _VarAlias) = 0;

	// get string variable.
	virtual const std::string& GetSVar (const std::string& _VarAlias) = 0;

	// get Vec2 variable.
	virtual const Vec2& GetVec2Var (const std::string& _VarAlias) = 0;

	// get Vec3 variable.
	virtual const Vec3& GetVec3Var (const std::string& _VarAlias) = 0;

	// get Vec4 variable.
	virtual const Vec4& GetVec4Var (const std::string& _VarAlias) = 0;
};


#endif
