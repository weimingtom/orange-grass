/*
 *  oggraphicshelpers.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "..\\include\\IOGGraphicsHelpers.h"
#include "IOGMesh.h"
#include <vector>


// Draw AABB
void DrawAABB (const IOGAabb& _aabb)
{
#ifdef WIN32
	const Vec3& min = _aabb.GetMin();
	const Vec3& max = _aabb.GetMax();

    glBegin(GL_LINE_STRIP);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(min.x, min.y, min.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(min.x, min.y, max.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(min.x, max.y, max.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(min.x, max.y, min.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(min.x, min.y, min.z);

        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(max.x, min.y, min.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(max.x, min.y, max.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(max.x, max.y, max.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(max.x, max.y, min.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(max.x, min.y, min.z);

        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(max.x, min.y, max.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(min.x, min.y, max.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(min.x, min.y, min.z);

        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(min.x, max.y, min.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(max.x, max.y, min.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(max.x, max.y, max.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(min.x, max.y, max.z);
	glEnd();
#endif
}


// Draw OBB
void DrawOBB (const IOGObb& _obb)
{
    Vec3 vMin = _obb.m_vMin;
    Vec3 vMax = _obb.m_vMax;

    Vec3 vA = _obb.VectorConvertToWorld ( Vec3 ( vMin.x, vMin.y, vMin.z) );
	Vec3 vB = _obb.VectorConvertToWorld ( Vec3 ( vMin.x, vMin.y, vMax.z) );
	Vec3 vC = _obb.VectorConvertToWorld ( Vec3 ( vMax.x, vMin.y, vMax.z) );
	Vec3 vD = _obb.VectorConvertToWorld ( Vec3 ( vMax.x, vMin.y, vMin.z) );
	Vec3 vE = _obb.VectorConvertToWorld ( Vec3 ( vMin.x, vMax.y, vMin.z) );
	Vec3 vF = _obb.VectorConvertToWorld ( Vec3 ( vMin.x, vMax.y, vMax.z) );
	Vec3 vG = _obb.VectorConvertToWorld ( Vec3 ( vMax.x, vMax.y, vMax.z) );
	Vec3 vH = _obb.VectorConvertToWorld ( Vec3 ( vMax.x, vMax.y, vMin.z) );

	DrawLine ( vA, vB );
	DrawLine ( vB, vC );
	DrawLine ( vC, vD );
	DrawLine ( vD, vA );

	DrawLine ( vE, vF );
	DrawLine ( vF, vG );
	DrawLine ( vG, vH );
	DrawLine ( vH, vE );

	DrawLine ( vA, vE );
	DrawLine ( vB, vF );
	DrawLine ( vC, vG );
	DrawLine ( vD, vH );
}


// Draw line
void DrawLine (const Vec3& _vStart, const Vec3& _vEnd)
{
#ifdef WIN32
    glBegin(GL_LINES);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(_vStart.x, _vStart.y, _vStart.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(_vEnd.x, _vEnd.y, _vEnd.z);
	glEnd();
#endif
}


// Draw coordiantes grid
void DrawCoordGrid (int _Bounds, int _Step, int _MajorStep)
{
#ifdef WIN32
    glBegin(GL_LINES);
        for (int i = -_Bounds; i <= _Bounds; i+=_Step)
        {
            float fColor = 0.5f;
            if (!(i%_MajorStep))
                fColor = 1.0f;

            glColor3f(fColor, fColor, fColor);
            glVertex3i(-_Bounds, 0, i);
            glColor3f(fColor, fColor, fColor);
            glVertex3i(_Bounds, 0, i);

            glColor3f(fColor, fColor, fColor);
            glVertex3i(i, 0, -_Bounds);
            glColor3f(fColor, fColor, fColor);
            glVertex3i(i, 0, _Bounds);
        }
    glEnd();
#endif
}


// Draw point patch grid
void DrawPatchGrid (int _NumPatchVerts, const Vec3* _pGridData)
{
#ifdef WIN32
	float fPointSize = 3.0f;
	glPointSize(fPointSize);
	glEnable(GL_POINT_SMOOTH);

	glBegin(GL_POINTS);
		for (int i = 0; i < _NumPatchVerts; ++i)
		{
			glColor3f(1.0f, 0.1f, 0.1f);
			glVertex3f(_pGridData[i].x, _pGridData[i].y + fPointSize, _pGridData[i].z);
		}
	glEnd();

	glPointSize(1.0f);
	glDisable(GL_POINT_SMOOTH);
#endif
}


// Draw geometry grid
void DrawGeometryGrid (const std::vector<OGFace>& _GridData)
{
#ifdef WIN32
    unsigned int numFaces = _GridData.size();
    for (unsigned int i = 0; i < numFaces; ++i)
    {
        glBegin(GL_LINE_LOOP);
            glColor3f(0.9f, 0.4f, 0.4f);
            glVertex3f(_GridData[i].vertices[0].x, _GridData[i].vertices[0].y, _GridData[i].vertices[0].z);
            glColor3f(0.9f, 0.4f, 0.4f);
            glVertex3f(_GridData[i].vertices[1].x, _GridData[i].vertices[1].y, _GridData[i].vertices[1].z);
            glColor3f(0.9f, 0.4f, 0.4f);
            glVertex3f(_GridData[i].vertices[2].x, _GridData[i].vertices[2].y, _GridData[i].vertices[2].z);
        glEnd();
    }
#endif
}


// Draw level ranges
void DrawLevelRanges (const Vec3& _StartPoint, const Vec3& _FinishPoint, float _fWidth, float _fHeight)
{
#ifdef WIN32
	glPointSize(6.0f);

	Vec3 min = _StartPoint; min.x = _StartPoint.x - _fWidth/2.0f; min.y = 0.0f;
	Vec3 max = _FinishPoint; max.x = _FinishPoint.x + _fWidth/2.0f; max.y = _fHeight;
	
    glBegin(GL_LINE_STRIP);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(min.x, min.y, min.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(min.x, min.y, max.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(min.x, max.y, max.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(min.x, max.y, min.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(min.x, min.y, min.z);

        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(max.x, min.y, min.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(max.x, min.y, max.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(max.x, max.y, max.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(max.x, max.y, min.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(max.x, min.y, min.z);

        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(max.x, min.y, max.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(min.x, min.y, max.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(min.x, min.y, min.z);

        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(min.x, max.y, min.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(max.x, max.y, min.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(max.x, max.y, max.z);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex3f(min.x, max.y, max.z);
	glEnd();

	glBegin(GL_LINES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(_StartPoint.x, -_fHeight, _StartPoint.z);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(_StartPoint.x, _fHeight, _StartPoint.z);
	glEnd();

	glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(_FinishPoint.x, -_fHeight, _FinishPoint.z);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(_FinishPoint.x, _fHeight, _FinishPoint.z);
	glEnd();

	glPointSize(1.0f);
#endif
}
