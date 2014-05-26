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
#ifndef MATERIALADJUSTEVENT_H_
#define MATERIALADJUSTEVENT_H_
#include "CommonToolEvent.h"


enum MtlType
{
    MTLTYPE_DIF,
    MTLTYPE_AMB,
    MTLTYPE_SPC,
};


struct MtlAdjustEventData
{
    MtlAdjustEventData () {}
    MtlAdjustEventData (MtlType _type, float _val)
    {
        m_type = _type;
        m_val = _val;
    }

    MtlType m_type;
    float m_val;
};


DECLARE_EVENT_TYPE( EVENTID_MTLADJUST, -1 )

typedef void (wxEvtHandler::*MtlAdjustEventFunction)(CommonToolEvent<MtlAdjustEventData> &);

#define MtlAdjustEventHandler(func)                                 \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(MtlAdjustEventFunction, &func)                    
 
#define EVT_MTLADJUST(id, fn)                                       \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_MTLADJUST, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(MtlAdjustEventFunction, &fn), (wxObject*) NULL ),


#endif