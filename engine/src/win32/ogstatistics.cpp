/*
 *  OGStatistics.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogstatistics.h"


COGStatistics::COGStatistics()
{
	Reset();
}


COGStatistics::~COGStatistics()
{
}


// add vertex / face count.
void COGStatistics::AddVertexCount (
					 unsigned long _Vert, 
					 unsigned long _Faces)
{
	m_Verts += _Vert; 
	m_Faces += _Faces;
}


// add texture switch.
void COGStatistics::AddTextureSwitch ()
{
	++m_TextureSwitches;
}


// add vertex buffer switch.
void COGStatistics::AddVBOSwitch ()
{
	++m_VBOSwitches;
}


// add draw call.
void COGStatistics::AddDrawCall ()
{
	++m_DrawCalls;
}


// reset counters.
void COGStatistics::Reset ()
{
	m_Verts = 0; 
	m_Faces = 0;
	m_TextureSwitches = 0;
	m_VBOSwitches = 0;
	m_DrawCalls = 0;
}


// get frame statistics.
void COGStatistics::GetStatistics (
					unsigned long& _Verts, 
					unsigned long& _Faces,
					unsigned long& _TextureSwitches,
					unsigned long& _VBOSwitches,
					unsigned long& _DrawCalls ) const
{
	_Verts = m_Verts;
	_Faces = m_Faces;
	_TextureSwitches = m_TextureSwitches;
	_VBOSwitches = m_VBOSwitches;
	_DrawCalls = m_DrawCalls;
}
