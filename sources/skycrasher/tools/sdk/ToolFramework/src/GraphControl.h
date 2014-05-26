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
#ifndef GRAPHCONTROL_H_
#define GRAPHCONTROL_H_

#include <vector>
#include "wx/wx.h"


struct SamplingData
{
    unsigned long msec;
    float value;
};


typedef std::vector<SamplingData>	TSamplingData;

class GraphControl : public wxScrolledWindow
{
public:
    GraphControl( wxWindow*, const wxPoint& _pt, const wxSize& _sz);
    virtual ~GraphControl();
    void AddData(const TSamplingData& _Data);
	void SetScale(float _fScale) {m_fScale = _fScale;}
    void ClearGraph(void);

private:

    void OnPaint(wxPaintEvent &event);
    void DrawAxes(wxDC& dc);
    void DrawData(wxDC& dc);

private:
    
	float			m_fScale;
    wxSize			m_size;
    wxPoint         m_GraphOffset;
    TSamplingData	m_Data;
    unsigned long   m_MaxSample;

    DECLARE_EVENT_TABLE();
};


#endif
