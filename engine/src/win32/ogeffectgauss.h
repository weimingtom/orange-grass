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

#include "ogeffect.h"
#include <vector>
#include <list>


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

	// Set direction.
    virtual void SetDirection (const Vec3& _vDir) {}

protected:

    struct ParticleFormat
    {
        unsigned int    frame;
	    float	        start;
        float           end;
        float           scale;
        float           pos;
	    BBVert	        pVertices[4];
    };

	// Add segment. Returns true if last segment on ray.
	bool AddSegment (float _fPos, float _fScale);

    // Scroll segment. Returns true if needs to be removed.
    bool ScrollSegment (ParticleFormat& _Segment, float _fScrollValue);

    // Update segment.
    void UpdateSegment (ParticleFormat& _Segment);
	
protected:

    std::vector<IOGMapping*>    m_Frames;
    std::list<ParticleFormat>	m_BBList;

	Vec4						m_color;
    Vec3                        m_vStartPos;
    Vec3                        m_vFinishPos;
    bool                        m_bPosReady;
    float                       m_fRayLength;
    float                       m_fSegment;
    float                       m_fScale;
    float                       m_fSpeed;

    static std::string          m_Texture;
    static unsigned int         m_MappingStartId;
    static unsigned int         m_MappingFinishId;
};


#endif