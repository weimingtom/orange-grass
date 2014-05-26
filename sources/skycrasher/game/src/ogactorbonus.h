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
