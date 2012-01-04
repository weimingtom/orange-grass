/*
 *  OGActorBonus.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORBONUS_H_
#define OGACTORBONUS_H_

#include "ogactor.h"


class COGActorBonus : public COGActor
{
public:
	COGActorBonus();
	virtual ~COGActorBonus();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const OGVec3& _vPos,
		const OGVec3& _vRot,
        const OGVec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Set active state
	virtual void Activate (bool _bActive);

    // collision event handler
	virtual bool OnCollision (const IOGCollision& _Collision);

	// Set bonus parameters.
    virtual void SetBonusParams (IOGBonusParams* _pBonusParams) {m_pBonusParams = _pBonusParams;}

	// Get bonus params
    virtual IOGBonusParams* GetBonusParams () {return m_pBonusParams;}

protected:

	// Update alive actor.
	virtual void UpdateAlive (unsigned long _ElapsedTime);

	// Update falling actor.
	virtual void UpdateFalling (unsigned long _ElapsedTime);

protected:

	IOGEffect*      m_pPickEffect;
    IOGSgNode*      m_pPickNode;
    IOGBonusParams* m_pBonusParams;
};


#endif
