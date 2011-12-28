/*
 *  ogfinishlevelworker.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogfinishlevelworker.h"


COGFinishLevelWorker::COGFinishLevelWorker()
{
    m_WrkState = FINISHWRK_STATE_MOVING;
}


COGFinishLevelWorker::~COGFinishLevelWorker()
{
}


// Create worker.
bool COGFinishLevelWorker::Create(IOGActor* _pActor)
{
    if (COGWorker::Create(_pActor))
    {
        m_OrientWorker.Create(_pActor);
        return true;
    }
    return false;
}


// Update worker.
void COGFinishLevelWorker::Update (unsigned long _ElapsedTime)
{
	if (!m_bActive)
		return;

    const OGVec3& vActorPos = m_pActor->GetPhysicalObject()->GetPosition();

    switch (m_WrkState)
    {
    case FINISHWRK_STATE_MOVING:
        if (Dist2DSq(vActorPos, m_vTarget) >= 1000.0f)
        {
            OGVec3 vMoveDir = OGVec3(m_vTarget.x, vActorPos.y, m_vTarget.z) - vActorPos;
            vMoveDir.normalize();
            m_pActor->GetPhysicalObject()->Move(vMoveDir);
        }
        else
        {
            m_WrkState = FINISHWRK_STATE_LANDING;
        }
        break;

    case FINISHWRK_STATE_LANDING:
        if (vActorPos.y > 10.0f)
        {
            m_pActor->GetPhysicalObject()->Move(OGVec3(0, -1.0f, 0));
        }
        else
        {
		    Activate(false);
		    m_bFinished = true;
        }
        break;
    }
}


// Set active state.
void COGFinishLevelWorker::Activate (bool _bActive)
{
    COGWorker::Activate(_bActive);
    m_OrientWorker.Activate(_bActive);
    m_WrkState = FINISHWRK_STATE_MOVING;
}


// Reset worker.
void COGFinishLevelWorker::Reset ()
{
    COGWorker::Reset();
    m_WrkState = FINISHWRK_STATE_MOVING;
}


// Set target.
void COGFinishLevelWorker::SetTarget(const OGVec3& _vTarget) 
{
    m_vTarget = _vTarget;
    m_OrientWorker.SetTarget(_vTarget);
}
