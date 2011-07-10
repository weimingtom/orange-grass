#ifndef LISTBOXLOGGER_H_
#define LISTBOXLOGGER_H_

#include <wx/wx.h>


/// @brief A log target which just redirects the messages to a listbox.
class ListBoxLogger : public wxLog
{
public:

	/// @brief Constructor.
	ListBoxLogger(wxListBox *lbox, wxLog *logOld);

	/// @brief Destructor.
    virtual ~ListBoxLogger();

private:

	/// @brief Implementation of logging function.
    virtual void DoLog(wxLogLevel level, const wxChar *szString, time_t t);

	/// @brief Implementation of logging function.
    virtual void DoLogString(const wxChar *szString, time_t WXUNUSED(t));

private:

    /// the control we use
    wxListBox *m_lbox;

    /// the old log target
    wxLog *m_logOld;
};


#endif