#ifndef EVENTHANDLERSTABLE_H_
#define EVENTHANDLERSTABLE_H_

#include <wx/wx.h>
#include "ResourceLoadingEvent.h"
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