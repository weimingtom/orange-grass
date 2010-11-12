/*
 *  OGEffectGauss.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECTGAUSS_H_
#define OGEFFECTGAUSS_H_

#include "OGEffect.h"
#include <vector>


class COGEffectGauss : public COGEffect
{
public:
	virtual ~COGEffectGauss();

	// Initialize effect.
	virtual void Init(OGEffectType _Type);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Render.
	virtual void Render (const MATRIX& _mWorld);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

	// Set start and finish positions.
	virtual void SetStartFinishPositions (const Vec3& _vStartPos, const Vec3& _vFinishPos);

protected:

    struct ParticleFormat
    {
        float   frame;
	    float	scale;
        float   angle;
	    Vec3	offset;
	    BBVert	pVertices[4];
    };
	
protected:

    std::vector<IOGMapping*>    m_Frames;
    std::vector<ParticleFormat>	m_BBList;

	Vec4						m_color;
    Vec3                        m_vStartPos;
    Vec3                        m_vFinishPos;
    bool                        m_bPosReady;

    static std::string          m_Texture;
    static unsigned int         m_MappingStartId;
    static unsigned int         m_MappingFinishId;
};


#endif