/*
 *  OGEmitterLightFlash.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTERLIGHTFLASH_H_
#define OGEMITTERLIGHTFLASH_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterLightFlash : public COGEmitter
{
public:
    COGEmitterLightFlash();
    virtual ~COGEmitterLightFlash();

    // Initialize emitter.
    virtual void Init(IOGGroupNode* _pNode);

    // Update.
    virtual void Update (unsigned long _ElapsedTime);

    // Render.
    virtual void Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight, OGRenderPass _Pass);

    // Start.
    virtual void Start ();

    // Stop.
    virtual void Stop ();

    // Get effect type.
    virtual OGEmitterType GetType() const { return s_Type; }

    // Get effect type.
    virtual const std::string& GetAlias() const { return s_Alias; }

protected:

    IOGLight*       m_pLight;

    float           m_fFadeFactor;
    float           m_fInitialIntensity;
    OGVec4          m_color;

public:

    static std::string     s_Alias;
    static OGEmitterType   s_Type;
};


#endif
