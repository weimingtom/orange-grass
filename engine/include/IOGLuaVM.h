/*
 *  IOGLuaVM.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGLUAVM_H_
#define IOGLUAVM_H_

#include <string>


class IOGLuaVM
{
public:
	virtual ~IOGLuaVM() {}

	// run the script
	virtual void Run ( const std::string& _ScriptFile ) = 0;

	// set global variable value
	virtual void SetGlobalVar ( const double& Value, const std::string& VarName ) = 0;

	// set global string variable value
	virtual void SetGlobalSVar ( const std::string& Value, const std::string& VarName ) = 0;

	// get global variable value
	virtual long GetGlobalIVar ( const std::string& VarName ) = 0;

	// get global variable value
	virtual float GetGlobalFVar ( const std::string& VarName ) = 0;

	// get global variable value
	virtual std::string GetGlobalSVar ( const std::string& VarName ) = 0;

	// register LUA function
	virtual void RegisterFunction ( const std::string&	_FunctionName, void* _pFunction ) = 0;

	// get VM state
	virtual void* GetLuaState () = 0;
};

#endif