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
#include "OpenGL2.h"
#include "..\\include\\IOGGraphicsHelpers.h"
#include <vector>


// Draw AABB
void DrawAABB (const IOGAabb& _aabb)
{
	const OGVec3& min = _aabb.GetMin();
	const OGVec3& max = _aabb.GetMax();

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
}


// Draw OBB
void DrawOBB (const IOGObb& _obb)
{
    OGVec3 vMin = _obb.m_vMin;
    OGVec3 vMax = _obb.m_vMax;

    OGVec3 vA = _obb.VectorConvertToWorld ( OGVec3 ( vMin.x, vMin.y, vMin.z) );
	OGVec3 vB = _obb.VectorConvertToWorld ( OGVec3 ( vMin.x, vMin.y, vMax.z) );
	OGVec3 vC = _obb.VectorConvertToWorld ( OGVec3 ( vMax.x, vMin.y, vMax.z) );
	OGVec3 vD = _obb.VectorConvertToWorld ( OGVec3 ( vMax.x, vMin.y, vMin.z) );
	OGVec3 vE = _obb.VectorConvertToWorld ( OGVec3 ( vMin.x, vMax.y, vMin.z) );
	OGVec3 vF = _obb.VectorConvertToWorld ( OGVec3 ( vMin.x, vMax.y, vMax.z) );
	OGVec3 vG = _obb.VectorConvertToWorld ( OGVec3 ( vMax.x, vMax.y, vMax.z) );
	OGVec3 vH = _obb.VectorConvertToWorld ( OGVec3 ( vMax.x, vMax.y, vMin.z) );

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
void DrawLine (const OGVec3& _vStart, const OGVec3& _vEnd)
{
    glBegin(GL_LINES);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(_vStart.x, _vStart.y, _vStart.z);
        glColor3f(0.9f, 0.4f, 0.4f);
        glVertex3f(_vEnd.x, _vEnd.y, _vEnd.z);
	glEnd();
}


// Draw coordiantes grid
void DrawCoordGrid (int _Bounds, int _Step, int _MajorStep)
{
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
}


// Draw point patch grid
void DrawPatchGrid (int _NumPatchVerts, const OGVec3* _pGridData)
{
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
}


// Draw geometry grid
void DrawGeometryGrid (const std::vector<OGFace>& _GridData)
{
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
}


// Draw level ranges
void DrawLevelRanges (const OGVec3& _StartPoint, const OGVec3& _FinishPoint, float _fWidth, float _fHeight)
{
	glPointSize(6.0f);

	OGVec3 min = _StartPoint; min.x = _StartPoint.x - _fWidth/2.0f; min.y = 0.0f;
	OGVec3 max = _FinishPoint; max.x = _FinishPoint.x + _fWidth/2.0f; max.y = _fHeight;
	
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
}
