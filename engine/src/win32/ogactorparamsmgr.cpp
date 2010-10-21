/*
 *  OGActorParamsMgr.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorparamsmgr.h"


COGActorParamsMgr::COGActorParamsMgr ()
{
	m_pReader = GetSettingsReader();
}


COGActorParamsMgr::~COGActorParamsMgr ()
{
	std::map<std::string, IOGActorParams*>::iterator iter = m_ParamsList.begin();
	for( ; iter != m_ParamsList.end(); ++iter )
	{
		OG_SAFE_DELETE (iter->second);
	}	
}


// load from config file.
bool COGActorParamsMgr::Init ()
{
	IOGSettingsSource* pSource = m_pReader->OpenSource(GetResourceMgr()->GetFullPath("actors.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = m_pReader->OpenGroupNode(pSource, NULL, "Actors");
	IOGGroupNode* pActorNode = m_pReader->OpenGroupNode(pSource, pRoot, "Actor");
	for (; pActorNode != NULL; )
	{
		std::string alias = m_pReader->ReadStringParam(pActorNode, "alias");
		std::string file = m_pReader->ReadStringParam(pActorNode, "file");
		file = GetResourceMgr()->GetFullPath(file);
		LoadParamsConfig(alias, file);

		pActorNode = m_pReader->ReadNextNode(pActorNode);
	}
	m_pReader->CloseGroupNode(pRoot);
	m_pReader->CloseSource(pSource);
	return true;
}


// get params by alias.
IOGActorParams* COGActorParamsMgr::GetParams (const std::string& _Alias)
{
	IOGActorParams* pParam = m_ParamsList[_Alias];
	if (pParam)
	{
		return pParam;
	}
    return NULL;
}


// Load actor params configuration
bool COGActorParamsMgr::LoadParamsConfig (const std::string& _Alias, const std::string& _Path)
{
	IOGSettingsSource* pSource = m_pReader->OpenSource(_Path);
	if (!pSource)
		return false;

	IOGActorParams* pParam = new IOGActorParams;
	pParam->alias = _Alias;

	IOGGroupNode* pRoot = m_pReader->OpenGroupNode(pSource, NULL, "Params");
	IOGGroupNode* pPhysicsNode = m_pReader->OpenGroupNode(pSource, pRoot, "Physics");
	if (pPhysicsNode != NULL)
	{
		pParam->physics.fMaxSpeed = m_pReader->ReadFloatParam(pPhysicsNode, "max_speed");
		pParam->physics.fAcceleration = m_pReader->ReadFloatParam(pPhysicsNode, "acceleration");
        pParam->physics.fStrafeMaxSpeed = m_pReader->ReadFloatParam(pPhysicsNode, "max_strafe_speed");
        pParam->physics.fRollSpeed = m_pReader->ReadFloatParam(pPhysicsNode, "roll_speed");
        pParam->physics.fMaxRollAngle = m_pReader->ReadFloatParam(pPhysicsNode, "max_roll_angle");
		pParam->physics.fTorque = m_pReader->ReadFloatParam(pPhysicsNode, "torque");
        pParam->physics.type = ParsePhysicsType(m_pReader->ReadStringParam(pPhysicsNode, "type"));
		m_pReader->CloseGroupNode(pPhysicsNode);
	}

	IOGGroupNode* pActorNode = m_pReader->OpenGroupNode(pSource, pRoot, "Actor");
	if (pActorNode != NULL)
	{
		pParam->model_alias = m_pReader->ReadStringParam(pActorNode, "model");
		pParam->model_propeller_alias = m_pReader->ReadStringParam(pActorNode, "model_propeller");
		pParam->model_destruction = m_pReader->ReadStringParam(pActorNode, "model_destruction");
		pParam->type = ParseActorType(m_pReader->ReadStringParam(pActorNode, "type"));
		pParam->icon = m_pReader->ReadStringParam(pActorNode, "icon");
		m_pReader->CloseGroupNode(pActorNode);
	}

	IOGGroupNode* pLogicNode = m_pReader->OpenGroupNode(pSource, pRoot, "Logic");
	if (pLogicNode != NULL)
	{
		pParam->gameplay.team = (OGTeam)m_pReader->ReadIntParam(pLogicNode, "team");
		pParam->gameplay.max_hitpoints = m_pReader->ReadIntParam(pLogicNode, "max_hitpoints");
		pParam->gameplay.hitpoints = pParam->gameplay.max_hitpoints;
		m_pReader->CloseGroupNode(pLogicNode);
	}

	m_ParamsList[_Alias] = pParam;

	m_pReader->CloseGroupNode(pRoot);
	m_pReader->CloseSource(pSource);

	return true;
}


// get params list.
void COGActorParamsMgr::GetParamsList (std::list<IOGActorParams*>& _List)
{
	_List.clear();
	std::map<std::string, IOGActorParams*>::iterator iter = m_ParamsList.begin();
	for( ; iter != m_ParamsList.end(); ++iter )
	{
		_List.push_back(iter->second);
	}	
}
