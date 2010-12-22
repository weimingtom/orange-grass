/*
 *  OGLuaVM.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogluavm.h"


// LUA function to run script
static int LUA_RunScript ( lua_State* _L );


COGLuaVM::COGLuaVM() : m_pVM(NULL)
{
	if (m_pVM == NULL)
		m_pVM = lua_open ();

	RegisterFunction ("RunScript", LUA_RunScript );
}


COGLuaVM::~COGLuaVM()
{
	if (m_pVM != NULL)
	{
		lua_close ( m_pVM );
		m_pVM = NULL;
	}
}


// run the script
void COGLuaVM::Run ( const std::string& _ScriptFile )
{
	luaL_loadfile(m_pVM, GetResourceMgr()->GetFullPath(_ScriptFile).c_str());
}


// set global variable value
void COGLuaVM::SetGlobalVar ( const double& Value, const std::string& VarName )
{
	lua_pushnumber ( m_pVM, Value );
	lua_setglobal ( m_pVM, VarName.c_str() );
}


// set global string variable value
void COGLuaVM::SetGlobalSVar ( const std::string& Value, const std::string& VarName )
{
	lua_pushstring ( m_pVM, Value.c_str() );
	lua_setglobal ( m_pVM, VarName.c_str () );
}


// get global variable value
long COGLuaVM::GetGlobalIVar ( const std::string& VarName )
{
	long retval;
	lua_getglobal ( m_pVM, VarName.c_str() );
	double doubleresult = lua_tonumber ( m_pVM, 1 );
	retval = static_cast<long> (lua_tonumber ( m_pVM, 1 ));	
	lua_remove ( m_pVM, 1 );
	return retval;
}


// get global variable value
float COGLuaVM::GetGlobalFVar ( const std::string& VarName )
{
	float retval;
	lua_getglobal ( m_pVM, VarName.c_str() );
	retval = static_cast<float> (lua_tonumber ( m_pVM, 1 ));	
	lua_remove ( m_pVM, 1 );
	return retval;
}


// get global variable value
std::string COGLuaVM::GetGlobalSVar ( const std::string& VarName )
{
	std::string RetVal;
	lua_getglobal ( m_pVM, VarName.c_str() );
	RetVal = lua_tostring ( m_pVM, 1 );	
	lua_remove ( m_pVM, 1 );
	return RetVal;
}


// register LUA function
void COGLuaVM::RegisterFunction ( const std::string& _FunctionName, void* _pFunction )
{
	lua_register ( m_pVM, _FunctionName.c_str (), (lua_CFunction)_pFunction	);
}


// LUA function to run script
int LUA_RunScript ( lua_State* _L )
{
	std::string _ScriptName = lua_tostring ( _L, 1 );
	GetLuaVM ()->Run ( _ScriptName );
	return 0;
}
