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
#ifndef COMMONTOOLEVENT_H_
#define COMMONTOOLEVENT_H_
#include <wx/wx.h>

static const int EVENTID_TOOLCMD	    = 32000;
static const int EVENTID_RESLOAD	    = 32001;
static const int EVENTID_RESSWITCH	    = 32002;
static const int EVENTID_LEVELLOAD	    = 32003;
static const int EVENTID_MTLLOAD	    = 32004;
static const int EVENTID_MTLADJUST	    = 32005;
static const int EVENTID_EFFECTLOAD	    = 32006;
static const int EVENTID_EFFECTADJUST	= 32007;
static const int EVENTID_MESHLOAD	    = 32008;


template <typename T>
class CommonToolEvent : public wxCommandEvent
{
public:
    CommonToolEvent( wxEventType commandType ) : wxCommandEvent(commandType, 0)
    {
    }
 
	CommonToolEvent( const CommonToolEvent& event ) : wxCommandEvent(event)
    {
        SetEventCustomData ( event.GetEventCustomData() );
    }
 
	wxEvent* Clone() const
    {
        return new CommonToolEvent<T>(*this);
    }
 
	const T& GetEventCustomData() const { return m_CustomData; }
	void SetEventCustomData( const T& _customData ) { m_CustomData = _customData; }

private:

    T   m_CustomData;
};

#endif