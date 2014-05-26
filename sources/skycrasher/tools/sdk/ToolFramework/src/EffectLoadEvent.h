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
#ifndef EFFECTLOADINGEVENT_H_
#define EFFECTLOADINGEVENT_H_
#include "CommonToolEvent.h"


struct EffectLoadEventData
{
    EffectLoadEventData () {}
    EffectLoadEventData (void* _pData)
    {
        m_pData = _pData;
    }

    void* m_pData;
};


DECLARE_EVENT_TYPE( EVENTID_EFFECTLOAD, -1 )

typedef void (wxEvtHandler::*EffectLoadEventFunction)(CommonToolEvent<EffectLoadEventData> &);

#define EffectLoadEventHandler(func)                                   \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(EffectLoadEventFunction, &func)                    
 
#define EVT_EFFECTLOAD(id, fn)                                         \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_EFFECTLOAD, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(EffectLoadEventFunction, &fn), (wxObject*) NULL ),


#endif