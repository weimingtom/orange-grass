/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef MATERIALLOADINGEVENT_H_
#define MATERIALLOADINGEVENT_H_
#include "CommonToolEvent.h"


struct MtlLoadEventData
{
    MtlLoadEventData () {}
    MtlLoadEventData (float _dif, float _amb, float _spc, int _blend)
    {
        m_dif = _dif;
        m_amb = _amb;
        m_spc = _spc;
        m_blend = _blend;
    }

    float m_dif;
    float m_amb;
    float m_spc;
    int m_blend;
};


DECLARE_EVENT_TYPE( EVENTID_MTLLOAD, -1 )

typedef void (wxEvtHandler::*MtlLoadEventFunction)(CommonToolEvent<MtlLoadEventData> &);

#define MtlLoadEventHandler(func)                                   \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(MtlLoadEventFunction, &func)                    
 
#define EVT_MTLLOAD(id, fn)                                         \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_MTLLOAD, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(MtlLoadEventFunction, &fn), (wxObject*) NULL ),


#endif