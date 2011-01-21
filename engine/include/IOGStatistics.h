/*
 *  IOGStatistics.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGSTATISTICS_H_
#define IOGSTATISTICS_H_


class IOGStatistics
{
public:
	virtual ~IOGStatistics() {}

	// add vertex / face count.
	virtual void AddVertexCount (
		unsigned long _Vert, 
		unsigned long _Faces) = 0;

	// add texture switch.
	virtual void AddTextureSwitch () = 0;

	// add vertex buffer switch.
	virtual void AddVBOSwitch () = 0;

	// add draw call.
	virtual void AddDrawCall () = 0;

	// reset counters.
	virtual void Reset () = 0;

	// get frame statistics.
	virtual void GetStatistics (
		unsigned long& _Verts, 
		unsigned long& _Faces,
		unsigned long& _TextureSwitches,
		unsigned long& _VBOSwitches,
		unsigned long& _DrawCalls ) const = 0;
};


#endif
