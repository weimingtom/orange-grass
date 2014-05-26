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
#ifndef OGANIMATIONSET_H_
#define OGANIMATIONSET_H_

#include "IOGModelSkeleton.h"
#include "IOGAnimation.h"
#include "IOGRenderable.h"
#include "IOGMesh.h"


class COGModelSkeleton : public IOGModelSkeleton
{
public:
    COGModelSkeleton();
    virtual ~COGModelSkeleton();

    // Get node transofrmation matrix
    virtual void GetWorldMatrix(OGMatrix& _mOut, unsigned int _NodeId, unsigned int _Frame) const;

    // Get number of skeleton nodes
    virtual unsigned int GetNumNodes () const;

    // Get specified skeleton node
    virtual const OGModelNode* GetNode (unsigned int _NodeId) const;

public:
    void Clear();
    void SetNumFrames(unsigned int _NumFrames);
    OGModelNode* AddNode(int _Idx, int _IdxParent, const float* _pfAnimMatrix);
    OGModelNode* BuildSG ();

private:
    void AttachChild(OGModelNode* _pParent, OGModelNode* _pChild);

public:
    unsigned int                m_NumFrames;
    std::vector<OGModelNode*>   m_Nodes;
};

#endif
