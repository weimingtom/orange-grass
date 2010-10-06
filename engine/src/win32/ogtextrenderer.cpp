/*
 *  OGTextRenderer.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


#include "Mathematics.h"
#include "Geometry.h"

#include "ogtextrenderer.h"
#include "ogtextrenderer_data.h"

#define MAX_LETTERS				            (5120)
#define MIN_CACHED_VTX			            (0x1000)
#define MAX_CACHED_VTX			            (0x00100000)
#define DISPLAYTEXT_MAX_RENDERABLE_LETTERS	(0xFFFF >> 2)


COGTextRenderer::COGTextRenderer()
{
	// Initialise all variables
	memset(this, 0, sizeof(*this));
}


COGTextRenderer::~COGTextRenderer()
{
}


// dwScreenX		Screen resolution along X
// dwScreenY		Screen resolution along Y
// true or false
// Initialization and texture upload.
bool COGTextRenderer::SetTextures(
	const unsigned int	dwScreenX,
	const unsigned int	dwScreenY,
	bool			bRotate) 
{
	int				i;
	bool			bStatus;

    m_WindowWidth = dwScreenX;
    m_WindowHeight = dwScreenY;

	m_bScreenRotate = bRotate; 
	if( m_bScreenRotate ) 
    {
        m_WindowWidth = dwScreenY;
        m_WindowHeight = dwScreenX;
	}

    /* Set the aspect ratio, so we can change it without updating textures or anything else */
	m_fScreenScale[0] = 1.0f;
	m_fScreenScale[1] = 1.0f;

	/* Check whether textures are already set up just in case */
	if (m_bTexturesSet) return true;

	/* This is the texture with the fonts. Type 1 because there is only alpha component (RGB are white). */
	bStatus = APIUpLoad4444((unsigned char *)DisplayTextABC_Pixels, 256, 1);
	if (!bStatus) return false;

	/* INDEX BUFFERS */
	m_pwFacesFont = (unsigned short*) malloc(DISPLAYTEXT_MAX_RENDERABLE_LETTERS * 2 * 3 * sizeof(unsigned short));
	memset(m_pwFacesFont, 0, DISPLAYTEXT_MAX_RENDERABLE_LETTERS * 2 * 3 * sizeof(unsigned short));	

	/* Vertex indices for letters */
	for (i=0; i < DISPLAYTEXT_MAX_RENDERABLE_LETTERS; i++)
	{
		m_pwFacesFont[i*6+0] = 0+i*4;
		m_pwFacesFont[i*6+1] = 3+i*4;
		m_pwFacesFont[i*6+2] = 1+i*4;

		m_pwFacesFont[i*6+3] = 3+i*4;
		m_pwFacesFont[i*6+4] = 0+i*4;
		m_pwFacesFont[i*6+5] = 2+i*4;
	}

	m_nVtxCacheMax = MIN_CACHED_VTX;
	m_pVtxCache = (SDisplayTextAPIVertex*)malloc(m_nVtxCacheMax * sizeof(*m_pVtxCache));
	memset(m_pVtxCache, 0, m_nVtxCacheMax * sizeof(*m_pVtxCache));	
	m_nVtxCache = 0;

	/* Everything is OK */
	m_bTexturesSet = true;

	/* Return OK */
	return true;
}


// fPosX		Position of the text along X
// fPosY		Position of the text along Y
// fScale		Scale of the text
// Colour		Colour of the text
// pszFormat	Format string for the text
// Display text on screen.
void COGTextRenderer::DisplayText(float fPosX, float fPosY, const float fScale, unsigned int Colour, const char * const pszFormat, ...)
{
	va_list				args;
	static char			Text[MAX_LETTERS+1], sPreviousString[MAX_LETTERS+1];
	static float		XPosPrev, YPosPrev, fScalePrev;
	static unsigned int	ColourPrev;
	static unsigned int	nVertices;

	/* No textures! so... no window */
	if (!m_bTexturesSet)
		return;

	/* Reading the arguments to create our Text string */
	va_start(args, pszFormat);
	vsprintf(Text, pszFormat, args);		// Could use _vsnprintf but e.g. LinuxVP does not support it
	va_end(args);

	/* nothing to be drawn */
	if(*Text == 0)
		return;

	/* Adjust input parameters */
	fPosX *= WindowWidth/100.0f;
	fPosY *= WindowHeight/100.0f;

	/* We check if the string has been changed since last time */
	if(
		strcmp (sPreviousString, Text) != 0 ||
		fPosX != XPosPrev ||
		fPosY != YPosPrev ||
		fScale != fScalePrev ||
		Colour != ColourPrev ||
		m_pPrint3dVtx == NULL)
	{
		/* copy strings */
		strcpy (sPreviousString, Text);
		XPosPrev = fPosX;
		YPosPrev = fPosY;
		fScalePrev = fScale;
		ColourPrev = Colour;

		/* Create Vertex Buffer (only if it doesn't exist) */
		if(m_pPrint3dVtx==0)
		{
			m_pPrint3dVtx = (SDisplayTextAPIVertex*) malloc(MAX_LETTERS*4*sizeof(SDisplayTextAPIVertex));
			memset(m_pPrint3dVtx, 0, MAX_LETTERS*4*sizeof(SDisplayTextAPIVertex));
		}

		/* Fill up our buffer */
		nVertices = UpdateLine(fPosX, fPosY, fScale, Colour, Text, m_pPrint3dVtx);
	}

	// Draw the text
	DrawLineUP(m_pPrint3dVtx, nVertices);
}


// Deallocate the memory allocated in SetTextures
void COGTextRenderer::ReleaseTextures()
{
	/* Only release textures if they've been allocated */
	if (!m_bTexturesSet) return;

	/* Release IndexBuffer */
	free(m_pwFacesFont);
	free(m_pPrint3dVtx);

	/* Delete textures */
	glDeleteTextures(1, &m_uTexture);

	m_bTexturesSet = false;

	free(m_pVtxCache);
}


// true if succesful, false otherwise.
// Reads texture data from *.dat and loads it in video memory.
bool COGTextRenderer::APIUpLoad4444(unsigned char *pSource, unsigned int nSize, unsigned int nMode)
{
	int				i, j;
	int				x=256, y=256;
	unsigned short	R, G, B, A;
	unsigned short	*p8888,  *pDestByte;
	unsigned char   *pSrcByte;

	/* Only square textures */
	x = nSize;
	y = nSize;

	glGenTextures(1, &m_uTexture);

	/* Load texture from data */

	/* Format is 4444-packed, expand it into 8888 */
	if (nMode==0)
	{
		/* Allocate temporary memory */
		p8888 = (unsigned short *) malloc(nSize * nSize * sizeof(unsigned short));
		memset(p8888, 0, nSize * nSize * sizeof(unsigned short));
		pDestByte = p8888;

		/* Set source pointer (after offset of 16) */
		pSrcByte = &pSource[16];

		/* Transfer data */
		for (i=0; i<y; i++)
		{
			for (j=0; j<x; j++)
			{
				/* Get all 4 colour channels (invert A) */
				G =   (*pSrcByte) & 0xF0;
				R = ( (*pSrcByte++) & 0x0F ) << 4;
				A =   (*pSrcByte) ^ 0xF0;
				B = ( (*pSrcByte++) & 0x0F ) << 4;

				/* Set them in 8888 data */
				*pDestByte++ = ((R&0xF0)<<8) | ((G&0xF0)<<4) | (B&0xF0) | (A&0xF0)>>4;
			}
		}
	}
	else
	{
		/* Set source pointer */
		pSrcByte = pSource;

		/* Allocate temporary memory */
		p8888 = (unsigned short *) malloc (nSize*nSize*sizeof(unsigned short));
		memset(p8888, 0, nSize*nSize*sizeof(unsigned short));

		if (!p8888)
		{
			//_RPT0(_CRT_WARN,"Not enough memory!\n");
			return false;
		}

		/* Set destination pointer */
		pDestByte = p8888;

		/* Transfer data */
		for (i=0; i<y; i++)
		{
			for (j=0; j<x; j++)
			{
				/* Get alpha channel */
				A = *pSrcByte++;

				/* Set them in 8888 data */
				R = 255;
				G = 255;
				B = 255;

				/* Set them in 8888 data */
				*pDestByte++ = ((R&0xF0)<<8) | ((G&0xF0)<<4) | (B&0xF0) | (A&0xF0)>>4;
			}
		}
	}

	/* Bind texture */
	glBindTexture(GL_TEXTURE_2D, m_uTexture);

	/* Default settings: bilinear */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* Now load texture */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, p8888);

	if (glGetError())
	{
		free(p8888);
		return false;
	}

	/* Destroy temporary data */
	free(p8888);

	/* Return status : OK */
	return true;
}


unsigned int COGTextRenderer::UpdateLine(
                                      float XPos, 
                                      float YPos, 
                                      const float fScale, 
                                      const unsigned int Colour, 
                                      const char * const Text, 
                                      SDisplayTextAPIVertex * const pVertices)
{
	unsigned	i=0, VertexCount=0;
	unsigned	Val;
	float		XSize = 0.0f, YSize = 0;
	float		UPos,	VPos;
	float		USize,	VSize;
	float		fScaleX, fScaleY, fPreXPos;

	/* Nothing to update */
	if (Text==NULL) return 0;

	if (fScale>0)
	{
		fScaleX = m_fScreenScale[0] * fScale * 255.0f;
		fScaleY = m_fScreenScale[1] * fScale * 27.0f;
	}
	else
	{
		fScaleX = m_fScreenScale[0] * 255.0f;
		fScaleY = m_fScreenScale[1] * 12.0f;
	}

	XPos *= m_fScreenScale[0];
	YPos *= m_fScreenScale[1];

	fPreXPos = XPos;

	while (true)
	{
		Val = (int)Text[i++];

		/* End of the string */
		if (Val==0 || i>MAX_LETTERS) break;

		/* It is SPACE so don't draw and carry on... */
		if (Val==' ')
		{
			if (fScale>0)	XPos += 10.0f/255.0f * fScaleX;
			else			XPos += 5.0f * m_fScreenScale[0];
			continue;
		}

		/* It is SPACE so don't draw and carry on... */
		if (Val=='#')
		{
			if (fScale>0)	XPos += 1.0f/255.0f * fScaleX;
			else			XPos += 5.0f * m_fScreenScale[0];
			continue;
		}

		/* It is RETURN so jump a line */
		if (Val==0x0A)
		{
			XPos = fPreXPos - XSize;
			YPos += YSize;
			continue;
		}

		/* If fScale is negative then select the small set of letters (System) */
		if (fScale < 0.0f)
		{
			XPos    += XSize;
			UPos    =  DisplayTextU_System[Val];
			VPos    =  DisplayTextV_System[Val] - 0.0001f; /* Some cards need this little bit */
			YSize   =  fScaleY;
			XSize   =  DisplayTextSize_System[Val] * fScaleX;
			USize	=  DisplayTextSize_System[Val];
			VSize	=  12.0f/255.0f;
		}
		else /* Big set of letters (Bold) */
		{
			XPos    += XSize;
			UPos    =  DisplayTextU_Bold[Val];
			VPos    =  DisplayTextV_Bold[Val] - 1.0f/230.0f;
			YSize   =  fScaleY;
			XSize   =  DisplayTextSize_Bold[Val] * fScaleX;
			USize	=  DisplayTextSize_Bold[Val];
			VSize	=  29.0f/255.0f;
		}

		/* CLIPPING */
		/* Filling vertex data */
		pVertices[VertexCount+0].sx		= f2vt(XPos);
		pVertices[VertexCount+0].sy		= f2vt(YPos);
		pVertices[VertexCount+0].sz		= 0;
		pVertices[VertexCount+0].tu		= f2vt(UPos);
		pVertices[VertexCount+0].tv		= f2vt(VPos);

		pVertices[VertexCount+1].sx		= f2vt(XPos+XSize);
		pVertices[VertexCount+1].sy		= f2vt(YPos);
		pVertices[VertexCount+1].sz		= 0;
		pVertices[VertexCount+1].tu		= f2vt(UPos+USize);
		pVertices[VertexCount+1].tv		= f2vt(VPos);

		pVertices[VertexCount+2].sx		= f2vt(XPos);
		pVertices[VertexCount+2].sy		= f2vt(YPos+YSize);
		pVertices[VertexCount+2].sz		= 0;
		pVertices[VertexCount+2].tu		= f2vt(UPos);
		pVertices[VertexCount+2].tv		= f2vt(VPos-VSize);

		pVertices[VertexCount+3].sx		= f2vt(XPos+XSize);
		pVertices[VertexCount+3].sy		= f2vt(YPos+YSize);
		pVertices[VertexCount+3].sz		= 0;
		pVertices[VertexCount+3].tu		= f2vt(UPos+USize);
		pVertices[VertexCount+3].tv		= f2vt(VPos-VSize);

		float r = ((float)((Colour & 0xFF)>>0)) / 255.0f;
		float g = ((float)((Colour & 0xFF00)>>8)) / 255.0f;
		float b = ((float)((Colour & 0xFF0000)>>16)) / 255.0f;
		float a = ((float)((Colour & 0xFF000000)>>24)) / 255.0f;
		
		pVertices[VertexCount+0].r = r;
		pVertices[VertexCount+0].g = g;
		pVertices[VertexCount+0].b = b;
		pVertices[VertexCount+0].a = a;
		
		pVertices[VertexCount+1].r = r;
		pVertices[VertexCount+1].g = g;
		pVertices[VertexCount+1].b = b;
		pVertices[VertexCount+1].a = a;
		
		pVertices[VertexCount+2].r = r;
		pVertices[VertexCount+2].g = g;
		pVertices[VertexCount+2].b = b;
		pVertices[VertexCount+2].a = a;
		
		pVertices[VertexCount+3].r = r;
		pVertices[VertexCount+3].g = g;
		pVertices[VertexCount+3].b = b;
		pVertices[VertexCount+3].a = a;
		
		VertexCount += 4;

		/* Fix number width */
		if (Val >='0' && Val <='9')
		{
			if (fScale < 0.0f)
				XSize = DisplayTextSize_System[(int)'0'] * fScaleX;
			else
				XSize = DisplayTextSize_Bold[(int)'0'] * fScaleX;
		}
	}

	if(m_bScreenRotate)
	{
		Rotate(pVertices, VertexCount);
	}

	return VertexCount;
}


void COGTextRenderer::DrawLineUP(SDisplayTextAPIVertex *pVtx, unsigned int nVertices)
{
	if(!nVertices)
		return;

	while(m_nVtxCache + (int)nVertices > m_nVtxCacheMax) 
	{
		if(m_nVtxCache + nVertices > MAX_CACHED_VTX) 
		{
			return;
		}

		m_nVtxCacheMax	= _MIN(m_nVtxCacheMax * 2, MAX_CACHED_VTX);
		m_pVtxCache		= (SDisplayTextAPIVertex*) reallocEM(m_pVtxCache, sizeof(*m_pVtxCache), m_nVtxCacheMax * sizeof(*m_pVtxCache));
	}

	memcpy(&m_pVtxCache[m_nVtxCache], pVtx, nVertices * sizeof(*pVtx));
	m_nVtxCache += nVertices;
}


void COGTextRenderer::Rotate(SDisplayTextAPIVertex * const pv, const unsigned int nCnt)
{
	unsigned int	i;
	VERTTYPE		x, y;

	for(i = 0; i < nCnt; ++i)
	{
		x = VERTTYPEDIV((VERTTYPE&)pv[i].sx, f2vt(WindowWidth * m_fScreenScale[0]));
		y = VERTTYPEDIV((VERTTYPE&)pv[i].sy, f2vt(WindowHeight * m_fScreenScale[1]));
		
		(VERTTYPE&)pv[i].sx = VERTTYPEMUL(-y+f2vt(1.0f), f2vt(WindowWidth * m_fScreenScale[0]));
		(VERTTYPE&)pv[i].sy = VERTTYPEMUL(x, f2vt(WindowHeight * m_fScreenScale[1]));
	}
}
