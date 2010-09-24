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
	virtual void SetFVar (
		const std::string& _VarAlias, 
		const std::string& _SVar) = 0;

	// get integer variable.
	virtual int GetIVar (const std::string& _VarAlias) = 0;

	// get floating point variable.
	virtual float GetFVar (const std::string& _VarAlias) = 0;

	// get string variable.
	virtual const std::string& GetSVar (const std::string& _VarAlias) = 0;
};


#endif
