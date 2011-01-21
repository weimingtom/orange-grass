/*
 *  OGTextRenderer_GLES11.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGTEXTRENDERER_GLES11_H_
#define OGTEXTRENDERER_GLES11_H_

#include "ogtextrenderer.h"


class COGTextRenderer_GLES11 : public COGTextRenderer
{
public:
	COGTextRenderer_GLES11();
	virtual ~COGTextRenderer_GLES11();

    // Flushes all the print text commands
    virtual int Flush();

protected:

    // Stores, writes and restores Render States
    virtual void APIRenderStates(int nAction);
};

#endif