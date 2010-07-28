#include "OpenGL2.h"
#include "IOGGraphicsHelpers.h"
#include "IOGMesh.h"
#include <vector>


// Draw AABB
void DrawAABB (const IOGAabb& _aabb)
{
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
void DrawPatchGrid (int _NumPatchVerts, const Vec3* _pGridData)
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
