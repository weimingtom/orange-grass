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
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogmaterial.h"


COGMaterial::COGMaterial ()
{
	m_Specular = OGVec4(0.0f, 0.0f, 0.0f, 0.0f);
	m_Ambient = OGVec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Diffuse = OGVec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_Blend = OG_BLEND_NO;
}


COGMaterial::~COGMaterial ()
{
}


// load material from config
void COGMaterial::LoadConfig (const OGMaterialCfg* _pCfg)
{
    if (!_pCfg)
    {
        OG_LOG_WARNING("Trying to load NULL config to material.");
        return;
    }

    m_Ambient = _pCfg->material_ambient;
    m_Diffuse = _pCfg->material_diffuse;
    m_Specular = _pCfg->material_specular;
    m_Blend = _pCfg->blend_type;
}


// save material config
OGMaterialCfg COGMaterial::SaveConfig ()
{
    OGMaterialCfg cfg;
    cfg.material_ambient = m_Ambient;
    cfg.material_diffuse = m_Diffuse;
    cfg.material_specular = m_Specular;
    cfg.blend_type = m_Blend;
    return cfg;
}


// get material ambient.
const OGVec4& COGMaterial::GetAmbient () const
{
	return m_Ambient;
}


// get material diffuse.
const OGVec4& COGMaterial::GetDiffuse () const
{
	return m_Diffuse;
}


// get material specular.
const OGVec4& COGMaterial::GetSpecular () const
{
	return m_Specular;
}


// get material blend.
OGBlendType COGMaterial::GetBlend () const
{
    return m_Blend;
}


// set material ambient.
void COGMaterial::SetAmbient (const OGVec4& _Value)
{
	m_Ambient = _Value;
}


// set material diffuse.
void COGMaterial::SetDiffuse (const OGVec4& _Value)
{
	m_Diffuse = _Value;
}


// set material specular.
void COGMaterial::SetSpecular (const OGVec4& _Value)
{
	m_Specular = _Value;
}


// set material blend.
void COGMaterial::SetBlend (OGBlendType _Value)
{
    m_Blend = _Value;
}
