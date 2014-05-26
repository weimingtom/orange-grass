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
#ifndef EFFECTADJUSTEVENT_H_
#define EFFECTADJUSTEVENT_H_
#include "CommonToolEvent.h"


enum ParamType
{
    PRMTYPE_STR,
    PRMTYPE_INT,
    PRMTYPE_FLT,
    PRMTYPE_CLR,
};


struct EffectAdjustEventData
{
    EffectAdjustEventData () {}
    EffectAdjustEventData (ParamType _type, void* _pData)
    {
        m_type = _type;
        m_pData = _pData;
    }

    ParamType   m_type;
    void*       m_pData;
};


DECLARE_EVENT_TYPE( EVENTID_EFFECTADJUST, -1 )

typedef void (wxEvtHandler::*EffectAdjustEventFunction)(CommonToolEvent<EffectAdjustEventData> &);

#define EffectAdjustEventHandler(func)                                 \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(EffectAdjustEventFunction, &func)                    
 
#define EVT_EFFECTADJUST(id, fn)                                       \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_EFFECTADJUST, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(EffectAdjustEventFunction, &fn), (wxObject*) NULL ),


#endif