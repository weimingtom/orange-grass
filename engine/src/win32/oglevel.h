/*
 *  OGLevel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGLEVEL_H_
#define OGLEVEL_H_

#include "IOGModel.h"
#include "IOGTerrain.h"
#include "ogresource.h"


class COGLevel : public IOGLevel, public COGResource
{
public:
	COGLevel ();
	virtual ~COGLevel ();

	// load scene from file.
	virtual bool Load ();

	// Unload resource.
	virtual void Unload ();

	// get associated terrain.
	virtual IOGTerrain* GetTerrain ();

	// get level start position.
	virtual const Vec3& GetStartPosition () const;

	// get level start finish.
	virtual const Vec3& GetFinishPosition () const;

	// set level start position.
	virtual void SetStartPosition (const Vec3& _Pos);

	// set level start finish.
	virtual void SetFinishPosition (const Vec3& _Pos);

	// save level.
	virtual bool Save ();

private:

    IOGTerrain* m_pTerrain;
	Vec3		m_vStartPos;
	Vec3		m_vFinishPos;
	Vec3		m_vLightDir;
	Vec3		m_vLightColor;
};

#endif
