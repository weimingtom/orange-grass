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
#include "EventHandlersTable.h"


static EventHandlersTable* g_pEventHandlersTable = NULL;


EventHandlersTable* GetEventHandlersTable ()
{
	if (g_pEventHandlersTable == NULL)
	{
		g_pEventHandlersTable = new EventHandlersTable ();
	}
	return g_pEventHandlersTable;
}


/// @brief Add event handler
/// @param _EvtType event type
/// @param _pHandler event handler
void EventHandlersTable::AddEventHandler (int _EvtType, wxEvtHandler* _pHandler)
{
	std::vector<wxEvtHandler*>& evtHandlersList = m_EventHandlers[_EvtType];
	evtHandlersList.push_back (_pHandler);
}


/// @brief Fire event
/// @param _EvtType event type
/// @param _event event
void EventHandlersTable::FireEvent (int _EvtType, wxCommandEvent* _event)
{
	std::vector<wxEvtHandler*>& evtHandlersList = m_EventHandlers[_EvtType];
	std::vector<wxEvtHandler*>::iterator iter = evtHandlersList.begin();
	for (; iter != evtHandlersList.end(); ++iter)
	{
		wxPostEvent( *iter, *_event );
	}
}
