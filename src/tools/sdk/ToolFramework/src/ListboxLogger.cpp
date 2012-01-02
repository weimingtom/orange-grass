#include "ListboxLogger.h"


/// @brief Constructor.
ListBoxLogger::ListBoxLogger(wxListBox *lbox, wxLog *logOld)
{
	m_lbox = lbox;
	m_logOld = logOld;
}


/// @brief Destructor.
ListBoxLogger::~ListBoxLogger()
{
	wxLog::SetActiveTarget(m_logOld);
}


/// @brief Implementation of logging function.
void ListBoxLogger::DoLog(wxLogLevel level, const wxChar *szString, time_t t)
{
	// don't put trace messages into listbox or we can get into infinite
	// recursion
	if ( level == wxLOG_Trace )
	{
		if ( m_logOld )
		{
			// cast is needed to call protected method
			((ListBoxLogger *)m_logOld)->DoLog(level, szString, t);
		}
	}
	else
	{
		wxLog::DoLog(level, szString, t);
	}
}


/// @brief Implementation of logging function.
void ListBoxLogger::DoLogString(const wxChar *szString, time_t WXUNUSED(t))
{
	wxString msg;
	TimeStamp(&msg);
	msg += szString;

	m_lbox->Append(msg);
	m_lbox->SetFirstItem(m_lbox->GetCount() - 1);
}
