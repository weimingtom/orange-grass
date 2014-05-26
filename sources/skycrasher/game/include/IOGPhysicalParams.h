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
#ifndef IOGPHYSICALPARAMS_H_
#define IOGPHYSICALPARAMS_H_

#include "IOGMath.h"
#include "IOGObb.h"


enum OGPhysicsType
{
	OG_PHYSICS_NONE = -1,
	OG_PHYSICS_STATIC,
	OG_PHYSICS_LANDBOT,
	OG_PHYSICS_AIRBOT,
	OG_PHYSICS_PLAYER,
	OG_PHYSICS_MISSILE,
	OG_PHYSICS_BONUS
};


struct IOGPhysicalParams
{
    IOGPhysicalParams()
    {
		type = OG_PHYSICS_STATIC;
        fMaxSpeed = 0.0f;
        fAcceleration = 0.0f;
        fStrafeMaxSpeed = 0.0f;
	    fRollSpeed = 0.0f;
	    fMaxRollAngle = 0.0f;
	    fPitchSpeed = 0.0f;
	    fMaxPitchAngle = 0.0f;
	    fTorque = 0.0f;
    }

    OGPhysicsType type;
	float fMaxSpeed;
	float fAcceleration;
	float fStrafeMaxSpeed;
	float fRollSpeed;
	float fMaxRollAngle;
	float fPitchSpeed;
	float fMaxPitchAngle;
	float fTorque;
};

#endif