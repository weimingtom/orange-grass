/*
 *  ogmodel.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "OrangeGrass.h"
#include "ogmodel.h"


COGModel::COGModel() :	m_pMesh(NULL),
						m_pTexture(NULL),
                        m_pMaterial(NULL),
						m_pTransparentMaterial(NULL)
{
    m_pRenderer = GetRenderer();
	m_pReader = GetSettingsReader();
}


COGModel::~COGModel()
{
	m_pMesh = NULL;
	m_pTexture = NULL;	
}


// Load model.
bool COGModel::Load ()
{
	switch (m_LoadState)
	{
	case OG_RESSTATE_UNKNOWN:
		return false;

	case OG_RESSTATE_LOADED:
        return true;    
	}

	Cfg modelcfg;
	if (!LoadConfig(modelcfg))
	{
        OG_LOG_ERROR("Failed to load model from config");
		return false;
	}

	m_pMesh = GetResourceMgr()->GetMesh(modelcfg.mesh_alias);
	m_pTexture = GetResourceMgr()->GetTexture(modelcfg.texture_alias);
	m_pMaterial = GetMaterialManager()->GetMaterial(modelcfg.material_type);

	if (m_pMesh->HasSubmeshesOfType(OG_SUBMESH_PROPELLER))
	{
		m_pTransparentMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);
	}

	std::list<Cfg::Anim>::const_iterator anim_iter = modelcfg.anim_list.begin();
	for (; anim_iter != modelcfg.anim_list.end(); ++anim_iter)
    {
		const COGModel::Cfg::Anim& anim = (*anim_iter);
        IOGAnimation* pAnim = new IOGAnimation();
        pAnim->name = anim.anim_alias;
        pAnim->start_frame = (unsigned int)anim.anim_start;
        pAnim->end_frame = (unsigned int)anim.anim_end;
        pAnim->speed = (unsigned int)anim.speed;
        pAnim->looped = (anim.looped == 0) ? false : true;
        m_pAnimations[pAnim->name] = pAnim;
    }

	m_LoadState = OG_RESSTATE_LOADED;
    return true;
}


// Load model configuration
bool COGModel::LoadConfig (COGModel::Cfg& _cfg)
{
	IOGSettingsSource* pSource = m_pReader->OpenSource(m_ResourceFile);
	if (!pSource)
	{
		OG_LOG_ERROR("Failed to load model config file %s", m_ResourceFile.c_str());
		return false;
	}

	IOGGroupNode* pMeshNode = m_pReader->OpenGroupNode(pSource, NULL, "Mesh");
	if (pMeshNode != NULL)
	{
		_cfg.mesh_alias = m_pReader->ReadStringParam(pMeshNode, "alias");
		m_pReader->CloseGroupNode(pMeshNode);
	}

	IOGGroupNode* pMaterialNode = m_pReader->OpenGroupNode(pSource, NULL, "Material");
	if (pMaterialNode != NULL)
	{
		_cfg.texture_alias = m_pReader->ReadStringParam(pMaterialNode, "texture");
		_cfg.material_type = m_pReader->ReadStringParam(pMaterialNode, "type");
		m_pReader->CloseGroupNode(pMaterialNode);
	}

	IOGGroupNode* pAnimationsNode = m_pReader->OpenGroupNode(pSource, NULL, "Animations");
    if (pAnimationsNode)
    {
        IOGGroupNode* pAnimationNode = m_pReader->OpenGroupNode(pSource, pAnimationsNode, "Animation");
        while (pAnimationNode != NULL)
        {
            COGModel::Cfg::Anim anim;
            anim.anim_alias = m_pReader->ReadStringParam(pAnimationNode, "name");
            anim.anim_start = m_pReader->ReadIntParam(pAnimationNode, "start_frame");
            anim.anim_end = m_pReader->ReadIntParam(pAnimationNode, "end_frame");
            anim.speed = m_pReader->ReadIntParam(pAnimationNode, "speed");
            anim.looped = m_pReader->ReadIntParam(pAnimationNode, "looped");
            _cfg.anim_list.push_back(anim);
            pAnimationNode = m_pReader->ReadNextNode(pAnimationNode);
        }
        m_pReader->CloseGroupNode(pAnimationsNode);
    }

	m_pReader->CloseSource(pSource);
	return true;
}


// Unload resource.
void COGModel::Unload ()
{
	if (m_LoadState != OG_RESSTATE_LOADED)
	{
		return;
	}

	OG_SAFE_DELETE(m_pMaterial);
	OG_SAFE_DELETE(m_pTransparentMaterial);

    std::map<std::string, IOGAnimation*>::iterator iter= m_pAnimations.begin();
	for (; iter != m_pAnimations.end(); ++iter)
	{
		OG_SAFE_DELETE(iter->second);
	}
    m_pAnimations.clear();

	m_LoadState = OG_RESSTATE_DEFINED;
}


// Render mesh.
void COGModel::Render (const MATRIX& _mWorld, unsigned int _Frame)
{
    m_pRenderer->SetMaterial(m_pMaterial);
    m_pRenderer->SetTexture(m_pTexture);
	m_pMesh->Render (_mWorld, _Frame);
}


// Render solid parts of the mesh.
void COGModel::RenderSolidParts (const MATRIX& _mWorld, unsigned int _Frame)
{
    m_pRenderer->SetMaterial(m_pMaterial);
    m_pRenderer->SetTexture(m_pTexture);
	m_pMesh->RenderSolidParts(_mWorld, _Frame);
}


// Render transparent parts of the mesh.
void COGModel::RenderTransparentParts (const MATRIX& _mWorld, unsigned int _Frame)
{
    m_pRenderer->SetMaterial(m_pTransparentMaterial);
    m_pRenderer->SetTexture(m_pTexture);
	m_pMesh->RenderTransparentParts(_mWorld, _Frame);
}


// Check if has submeshes of the following type
bool COGModel::HasSubmeshesOfType(SubMeshType _Type) const
{
	return m_pMesh->HasSubmeshesOfType(_Type);
}


// Get num renderable parts.
unsigned int COGModel::GetNumRenderables () const
{
    return m_pMesh->GetNumRenderables();
}


// Get combined AABB
const IOGAabb& COGModel::GetAABB () const
{
	return m_pMesh->GetAABB();
}


// Get model alias
const std::string& COGModel::GetAlias () const
{
    return m_ResourceAlias;
}


// Get animation
IOGAnimation* COGModel::GetAnimation (const std::string& _Alias)
{
    return m_pAnimations[_Alias];
}


// Get active point
bool COGModel::GetActivePoint (IOGActivePoint& _point, const std::string& _Alias, unsigned int _Frame)
{
    if (!m_pMesh->GetActivePoint(_point.pos, _Alias, _Frame))
        return false;

    _point.alias = _Alias;
    return true;
}
