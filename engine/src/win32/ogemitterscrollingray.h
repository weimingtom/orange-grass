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
	virtual void Init(IOGGroupNode* _pNode);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Set start and finish positions.
	virtual void SetStartFinishPositions (const Vec3& _vStartPos, const Vec3& _vFinishPos);

	// Set direction.
    virtual void SetDirection (const Vec3& _vDir) {}

	// Render.
	virtual void Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

	// Get effect type.
    virtual OGEmitterType GetType() const { return s_Type; }

	// Get effect type.
    virtual const std::string& GetAlias() const { return s_Alias; }

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

    Vec3                        m_vStartPos;
    Vec3                        m_vFinishPos;
    bool                        m_bPosReady;
    float                       m_fRayLength;

    std::string     m_Texture;
    unsigned int    m_MappingStartId;
    unsigned int    m_MappingFinishId;
    float           m_fSegment;
    float           m_fScale;
    float           m_fSpeed;
	Vec4			m_color;

public:

    static std::string     s_Alias;
    static OGEmitterType   s_Type;
};


#endif