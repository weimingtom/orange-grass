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