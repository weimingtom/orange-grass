/*
 *  ogscenemesh.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSCENEMESH_H_
#define OGSCENEMESH_H_

#include "ogbasemesh.h"


class COGSceneMesh : public COGBaseMesh
{
public:
	COGSceneMesh ();
	virtual ~COGSceneMesh();

	// Render parts of the mesh.
	void RenderParts (const IOGFrustum& _frustum);

protected:

    // load sub-meshes
    virtual void LoadSubMeshes ();

    // unload sub-meshes
    virtual void UnloadSubMeshes ();

protected:

	typedef std::vector<unsigned int> PartsList;
	PartsList m_TerraParts;

    IOGRenderer* m_pRenderer;
};


#endif
