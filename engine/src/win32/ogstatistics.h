/*
 *  OGStatistics.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSTATISTICS_H_
#define OGSTATISTICS_H_

#include "IOGStatistics.h"


class COGStatistics : public IOGStatistics
{
public:
	COGStatistics();
	virtual ~COGStatistics();

	// add vertex / face count.
	virtual void AddVertexCount (
		unsigned long _Vert, 
		unsigned long _Faces);

	// add texture switch.
	virtual void AddTextureSwitch ();

	// add vertex buffer switch.
	virtual void AddVBOSwitch ();

	// add draw call.
	virtual void AddDrawCall ();

	// reset counters.
	virtual void Reset ();

	// get frame statistics.
	virtual void GetStatistics (
		unsigned long& _Verts, 
		unsigned long& _Faces,
		unsigned long& _TextureSwitches,
		unsigned long& _VBOSwitches,
		unsigned long& _DrawCalls ) const;

private:

	unsigned long m_Verts; 
	unsigned long m_Faces;
	unsigned long m_TextureSwitches;
	unsigned long m_VBOSwitches;
	unsigned long m_DrawCalls;
};


#endif
