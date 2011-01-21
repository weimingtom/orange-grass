/*
 *  OGTextRenderer_GLES11.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogtextrenderer_gles11.h"
#include "ogtextrenderer_data.h"


COGTextRenderer_GLES11::COGTextRenderer_GLES11()
{
}


COGTextRenderer_GLES11::~COGTextRenderer_GLES11()
{
}


// Flushes all the print text commands
int COGTextRenderer_GLES11::Flush()
{
	int	nTris, nVtx, nVtxBase, nTrisTot;
	
	/* Save render states */
	APIRenderStates(0);

	/* Set font texture */
	glBindTexture(GL_TEXTURE_2D, m_uTexture);	

	nTrisTot = m_nVtxCache >> 1;

	/* Render the text then. Might need several submissions. */
	nVtxBase = 0;
	while(m_nVtxCache)
	{
		nVtx = OG_MIN(m_nVtxCache, 0xFFFC);
		nTris = nVtx >> 1;

        /* Draw triangles */
        glVertexPointer(3, VERTTYPEENUM, sizeof(SDisplayTextAPIVertex), &m_pVtxCache[nVtxBase].sx);
        glColorPointer(4, VERTTYPEENUM, sizeof(SDisplayTextAPIVertex), &m_pVtxCache[nVtxBase].r);
        glTexCoordPointer(2, VERTTYPEENUM, sizeof(SDisplayTextAPIVertex), &m_pVtxCache[nVtxBase].tu);

        glDrawElements(GL_TRIANGLES, nTris * 3, GL_UNSIGNED_SHORT, m_pwFacesFont);
		
		nVtxBase += nVtx;
		m_nVtxCache -= nVtx;
	}

	/* Restore render states */
	APIRenderStates(1);
	return nTrisTot;
}


// Stores, writes and restores Render States
void COGTextRenderer_GLES11::APIRenderStates(int nAction)
{
	static GLint iMatrixMode, iFrontFace, iCullFaceMode, iDestBlend, iSrcBlend;
	static GLboolean bLighting, bCullFace, bFog, bDepthTest, bBlend, bVertexPointerEnabled, bColorPointerEnabled, bTexCoorPointerEnabled;
    static GLboolean bTextureEnabled0, bTextureEnabled1;
	MATRIX Matrix;
	int i;

	/* Saving or restoring states ? */
	switch (nAction)
	{
	case 0:
        bVertexPointerEnabled = glIsEnabled(GL_VERTEX_ARRAY);
        bColorPointerEnabled = glIsEnabled(GL_COLOR_ARRAY);
        bTexCoorPointerEnabled = glIsEnabled(GL_TEXTURE_COORD_ARRAY);
        bLighting = glIsEnabled(GL_LIGHTING);
        bFog = glIsEnabled(GL_FOG);
        // save texture unit state
        glActiveTexture(GL_TEXTURE0);
        bTextureEnabled0 = glIsEnabled(GL_TEXTURE_2D);

        glActiveTexture(GL_TEXTURE1);
        bTextureEnabled1 = glIsEnabled(GL_TEXTURE_2D);

        bCullFace = glIsEnabled(GL_CULL_FACE);
		bDepthTest = glIsEnabled(GL_DEPTH_TEST);
		bBlend = glIsEnabled(GL_BLEND);
		glGetIntegerv(GL_FRONT_FACE, &iFrontFace);
		glGetIntegerv(GL_CULL_FACE_MODE, &iCullFaceMode);
		glGetIntegerv(GL_BLEND_DST, &iDestBlend);
		glGetIntegerv(GL_BLEND_SRC, &iSrcBlend);

        /* Save matrices */
        glGetIntegerv(GL_MATRIX_MODE, &iMatrixMode);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        /* Set matrix with viewport dimensions */
		for(i=0; i<16; i++)
		{
			Matrix.f[i]=0;
		}
		Matrix.f[0] = f2vt(2.0f/m_WindowWidth);
		Matrix.f[5] = f2vt(-2.0f/m_WindowHeight);
		Matrix.f[10] = f2vt(1.0f);
		Matrix.f[12] = f2vt(-1.0f);
		Matrix.f[13] = f2vt(1.0f);
		Matrix.f[15] = f2vt(1.0f);

        /* Set matrix mode so that screen coordinates can be specified */
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(Matrix.f);
        glDisable(GL_LIGHTING);

        /* Culling */
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_FRONT);

        /* Set client states */
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glClientActiveTexture(GL_TEXTURE0);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        /* texture 	*/
        glActiveTexture(GL_TEXTURE1);
        glDisable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);

        glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        /* Disable fog */
        glDisable(GL_FOG);

        /* Blending mode */
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		/* Set Z compare properties */
		glDisable(GL_DEPTH_TEST);
		break;

	case 1:
        /* Restore render states */
        if (!bVertexPointerEnabled)		
            glDisableClientState(GL_VERTEX_ARRAY);
        else 
            glEnableClientState(GL_VERTEX_ARRAY);
        if (!bColorPointerEnabled)		
            glDisableClientState(GL_COLOR_ARRAY);
        else
            glEnableClientState(GL_COLOR_ARRAY);
        if (!bTexCoorPointerEnabled)		
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        else
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        /* Restore matrix mode & matrix */
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glMatrixMode(iMatrixMode);
        if(bLighting)
            glEnable(GL_LIGHTING);
        if(bFog)
            glEnable(GL_FOG);

        // restore texture states
        glActiveTexture(GL_TEXTURE1);
        bTextureEnabled1 ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        bTextureEnabled0 ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);

        // Restore some values
		if(!bCullFace) 
            glDisable(GL_CULL_FACE);
		if(bDepthTest) 
            glEnable(GL_DEPTH_TEST);

		glFrontFace(iFrontFace);
		glCullFace(iCullFaceMode);

		glBlendFunc(iSrcBlend, iDestBlend);
		if(bBlend == 0) 
            glDisable(GL_BLEND);
		break;
	}
}
