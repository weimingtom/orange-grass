/*
 *  ogplasmaeffect.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogplasmaeffect.h"
#include "OrangeGrass.h"


COGPlasmaEffect::~COGPlasmaEffect()
{
}


// Initialize effect.
void COGPlasmaEffect::Init(OGEffectType _Type)
{
	m_pTexture = GetResourceMgr()->GetTexture("plasma_01");
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHAMULT);

	Vec4 color = Vec4(1.0f, 0.0f, 0.0f, 0.5f);

	for (int i = 0; i < 4; ++i)
	{
		COGBillboard& particle = m_Particles[i];
		particle.scale = (4.0f - i) / 2.0f;
		particle.pVertices = &m_Vertices[i * 4];
		particle.pVertices[0].t = Vec2(1.0f, 0.0f);
		particle.pVertices[0].c = color;
		particle.pVertices[1].t = Vec2(0.0f, 0.0f);
		particle.pVertices[1].c = color;
		particle.pVertices[2].t = Vec2(1.0f, 1.0f);
		particle.pVertices[2].c = color;
		particle.pVertices[3].t = Vec2(0.0f, 1.0f);
		particle.pVertices[3].c = color;
	}
}


// Update.
void COGPlasmaEffect::Update (unsigned long _ElapsedTime)
{
    MatrixTranslation(m_World, m_Position.x, m_Position.y, m_Position.z);

	for (int i = 0; i < 4; ++i)
	{
		m_Particles[i].offset = m_Direction * (float)i;
	}
}


// Render.
void COGPlasmaEffect::Render (
							  const MATRIX& _mView,
							  const Vec3& _vRight, 
							  const Vec3& _vUp)
{
	MATRIX mModelView;
	MatrixMultiply(mModelView, m_World, _mView);
	glLoadMatrixf(mModelView.f);

	glDisable(GL_DEPTH_TEST);

	glVertexPointer(3, GL_FLOAT, 36, m_Vertices);
	glTexCoordPointer(2, GL_FLOAT, 36, (void*)((char *)m_Vertices + 12));
	glColorPointer(4, GL_FLOAT, 36, (void*)((char *)m_Vertices + 20));

	GetRenderer()->SetMaterial(m_pMaterial);
	GetRenderer()->SetTexture(m_pTexture);

	for (int i = 0; i < 4; ++i)
	{
		COGBillboard& particle = m_Particles[i];
		Vec3 vUp = _vUp * particle.scale;
		Vec3 vRight = _vRight * particle.scale;
		particle.pVertices[0].p = vRight + vUp + particle.offset;
		particle.pVertices[1].p = -vRight + vUp + particle.offset;
		particle.pVertices[2].p = vRight - vUp + particle.offset;
		particle.pVertices[3].p = -vRight - vUp + particle.offset;
		glDrawArrays(GL_TRIANGLE_STRIP, 4 * i, 4);
	}

	glEnable(GL_DEPTH_TEST);
}
