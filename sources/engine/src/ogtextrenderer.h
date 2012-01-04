/*
 *  OGTextRenderer.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGTEXTRENDERER_H_
#define OGTEXTRENDERER_H_


class COGTextRenderer
{
public:
	COGTextRenderer();
	virtual ~COGTextRenderer();

    // dwScreenX		Screen resolution along X
    // dwScreenY		Screen resolution along Y
    // true or false
    // Initialization and texture upload. Should be called only once
    // for a given context.
    bool SetTextures(
	    unsigned int	dwScreenX,
	    unsigned int	dwScreenY,
	    bool			bRotate = true); 

    // fPosX		Position of the text along X
    // fPosY		Position of the text along Y
    // fScale		Scale of the text
    // Colour		Colour of the text
    // pszFormat	Format string for the text
    // Display text on screen.
    void DisplayText(float fPosX, float fPosY, float fScale, unsigned int Colour, const char * const pszFormat, ...);

    // Deallocate the memory allocated in SetTextures
    void ReleaseTextures();

    // Flushes all the print text commands
    int Flush();

private:

    // A structure for our vertex type
    struct SDisplayTextAPIVertex
    {
	    float sx, sy, sz;
	    float r, g, b, a;
	    float tu, tv;
    };

private:

    unsigned int UpdateLine(
        float XPos, 
        float YPos, 
        float fScale, 
        unsigned int Colour, 
        const char * const Text, 
        SDisplayTextAPIVertex * const pVertices);


    void DrawLineUP(SDisplayTextAPIVertex *pVtx, unsigned int nVertices);

    void Rotate(SDisplayTextAPIVertex * const pv, const unsigned int nCnt);

    // true if succesful, false otherwise.
    // Reads texture data from *.dat and loads it in video memory.
    bool APIUpLoad4444(unsigned char *pSource, unsigned int nSize, unsigned int nMode);

    // Stores, writes and restores Render States
    void APIRenderStates(int nAction);

private:

    bool                    m_bScreenRotate;
    GLuint					m_uTexture;
	unsigned short			*m_pwFacesFont;
	SDisplayTextAPIVertex	*m_pPrint3dVtx;
	bool					m_bTexturesSet;
	SDisplayTextAPIVertex	*m_pVtxCache;
	int						m_nVtxCache;
	int						m_nVtxCacheMax;
    float                   m_WindowWidth;
    float                   m_WindowHeight;
};

#endif