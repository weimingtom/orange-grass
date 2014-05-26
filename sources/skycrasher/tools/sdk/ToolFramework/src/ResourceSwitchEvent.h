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
#ifndef RESOURCESWITCHEVENT_H_
#define RESOURCESWITCHEVENT_H_
#include "CommonToolEvent.h"
#include "ResourceGroup.h"


struct ResSwitchEventData
{
    ResSwitchEventData () {}
    ResSwitchEventData (ResourceItem* _pItem)
    {
        m_pItem = _pItem;
    }

    ResourceItem*   m_pItem;
};


DECLARE_EVENT_TYPE( EVENTID_RESSWITCH, -1 )

typedef void (wxEvtHandler::*ResSwitchEventFunction)(CommonToolEvent<ResSwitchEventData> &);

#define ResSwitchEventHandler(func)                                 \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(ResSwitchEventFunction, &func)                    
 
#define EVT_RESSWITCH(id, fn)                                       \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_RESSWITCH, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(ResSwitchEventFunction, &fn), (wxObject*) NULL ),

#endif