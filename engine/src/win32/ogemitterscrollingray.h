/*
 *  OGEmitterScrollingRay.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTERSCROLLINGRAY_H_
#define OGEMITTERSCROLLINGRAY_H_

#include "ogemitter.h"
#include <vector>
#include <list>


class COGEmitterScrollingRay : public COGEmitter
{
public:
	COGEmitterScrollingRay();
	virtual ~COGEmitterScrollingRay();

	// Initialize emitter.
	virtual void Init();

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Set start and finish positions.
	virtual void SetStartFinishPositions (const Vec3& _vStartPos, const Vec3& _vFinishPos);

	// Render.
	virtual void Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

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
    Vec3                        m_Direction;
    bool                        m_bPosReady;
    float                       m_fRayLength;

public:

    std::string     m_Texture;
    unsigned int    m_MappingStartId;
    unsigned int    m_MappingFinishId;
    float           m_fSegment;
    float           m_fScale;
    float           m_fSpeed;
};


#endif