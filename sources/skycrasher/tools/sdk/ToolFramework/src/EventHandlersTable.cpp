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
