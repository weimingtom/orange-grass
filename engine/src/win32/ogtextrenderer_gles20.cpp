/*
 *  OGTextRenderer_GLES20.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "GraphicsDevice.h"

#include "ogtextrenderer_gles20.h"
#include "ogtextrenderer_data.h"


COGTextRenderer_GLES20::COGTextRenderer_GLES20()
{
}


COGTextRenderer_GLES20::~COGTextRenderer_GLES20()
{
}


// Flushes all the print text commands
int COGTextRenderer_GLES20::Flush()
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

        // Bind the VBO so we can fill it with data
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, VERTTYPEENUM, GL_FALSE, sizeof(SDisplayTextAPIVertex), &m_pVtxCache[nVtxBase].sx);	

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, VERTTYPEENUM, GL_FALSE, sizeof(SDisplayTextAPIVertex), &m_pVtxCache[nVtxBase].r);	

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, VERTTYPEENUM, GL_FALSE, sizeof(SDisplayTextAPIVertex), &m_pVtxCache[nVtxBase].tu);

        glDrawElements(GL_TRIANGLES, nTris * 3, GL_UNSIGNED_SHORT, m_pwFacesFont);
		
		nVtxBase += nVtx;
		m_nVtxCache -= nVtx;
	}

	/* Restore render states */
	APIRenderStates(1);
	return nTrisTot;
}


// Stores, writes and restores Render States
void COGTextRenderer_GLES20::APIRenderStates(int nAction)
{
	static GLint iFrontFace, iCullFaceMode, iDestBlend, iSrcBlend;
	static GLboolean bCullFace, bDepthTest, bBlend;

	/* Saving or restoring states ? */
	switch (nAction)
	{
	case 0:
		bCullFace = glIsEnabled(GL_CULL_FACE);
		bDepthTest = glIsEnabled(GL_DEPTH_TEST);
		bBlend = glIsEnabled(GL_BLEND);
		glGetIntegerv(GL_FRONT_FACE, &iFrontFace);
		glGetIntegerv(GL_CULL_FACE_MODE, &iCullFaceMode);
		glGetIntegerv(GL_BLEND_DST, &iDestBlend);
		glGetIntegerv(GL_BLEND_SRC, &iSrcBlend);
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

        /* Culling */
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
		glCullFace(GL_FRONT);
        glActiveTexture(GL_TEXTURE0);

		/* Blending mode */
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		/* Set Z compare properties */
		glDisable(GL_DEPTH_TEST);
		break;

	case 1:
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
