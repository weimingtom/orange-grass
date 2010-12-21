/*
 *  OGLuaVM.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGLUAVM_H_
#define OGLUAVM_H_

#include "lua.hpp"
#include "IOGLuaVM.h"


class COGLuaVM  : public IOGLuaVM
{
public:
	COGLuaVM();
	virtual ~COGLuaVM();

	// run the script
	virtual void Run ( const std::string& _ScriptFile );

	// set global variable value
	virtual void SetGlobalVar ( const double& Value, const std::string& VarName );

	// set global string variable value
	virtual void SetGlobalSVar ( const std::string& Value, const std::string& VarName );

	// get global variable value
	virtual long GetGlobalIVar ( const std::string& VarName );

	// get global variable value
	virtual float GetGlobalFVar ( const std::string& VarName );

	// get global variable value
	virtual std::string GetGlobalSVar ( const std::string& VarName );

	// register LUA function
	virtual void RegisterFunction ( const std::string& _FunctionName, void* _pFunction );

	// get VM state
	virtual void* GetLuaState () { return m_pVM; }

private:

	lua_State*	m_pVM;
};

#endif