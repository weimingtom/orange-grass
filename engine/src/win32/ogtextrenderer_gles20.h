/*
 *  OGTextRenderer_GLES20.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGTEXTRENDERER_GLES20_H_
#define OGTEXTRENDERER_GLES20_H_

#include "ogtextrenderer.h"


class COGTextRenderer_GLES20 : public COGTextRenderer
{
public:
	COGTextRenderer_GLES20();
	virtual ~COGTextRenderer_GLES20();

    // Flushes all the print text commands
    virtual int Flush();

protected:

    // Stores, writes and restores Render States
    virtual void APIRenderStates(int nAction);

protected:

    // Declare the fragment and vertex shaders.
	GLuint uiFragShader, uiVertShader;
	GLuint uiProgramObject;

    // Handles for the uniform variables.
	int PMVMatrixHandle;
	int TextureHandle;
};

#endif