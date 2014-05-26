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
#ifndef EVENTHANDLERSTABLE_H_
#define EVENTHANDLERSTABLE_H_

#include <wx/wx.h>
#include "ResourceLoadingEvent.h"
#include "MaterialLoadEvent.h"
#include "MaterialAdjustEvent.h"
#include "MeshLoadEvent.h"
#include "EffectLoadEvent.h"
#include "EffectAdjustEvent.h"
#include "ResourceSwitchEvent.h"
#include "ToolCommandEvent.h"
#include "LevelLoadingEvent.h"
#include "CommonToolEvent.h"
#include <vector>
#include <map>


class EventHandlersTable
{
public:
	/// @brief Add event handler
	/// @param _EvtType event type
	/// @param _pHandler event handler
	void AddEventHandler (int _EvtType, wxEvtHandler* _pHandler);

	/// @brief Fire event
	/// @param _EvtType event type
	/// @param _event event
	void FireEvent (int _EvtType, wxCommandEvent* _event);

private:

	std::map<int, std::vector<wxEvtHandler*> >	m_EventHandlers;
};

EventHandlersTable* GetEventHandlersTable ();


#endif