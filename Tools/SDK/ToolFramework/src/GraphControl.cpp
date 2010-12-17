#include <string>
#include "GraphControl.h"
#include "wx/wx.h"


BEGIN_EVENT_TABLE(GraphControl, wxScrolledWindow)
EVT_PAINT(GraphControl::OnPaint)
END_EVENT_TABLE()


GraphControl::GraphControl( wxWindow *parent, 
						   const wxPoint& _pt, 
						   const wxSize& _sz) : wxScrolledWindow(parent, 
											   wxID_ANY, _pt, _sz, 
											   wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
	m_fScale = 100.0f;
	m_size = _sz;
}

GraphControl::~GraphControl()
{
	ClearGraph();
}


void GraphControl::ClearGraph()
{
	m_Data.clear();
}


void GraphControl::DrawAxes(wxDC& dc)
{
	unsigned int numPoints = 33;
	if (!m_Data.empty())
	{
		numPoints = m_Data.size() - 1;
	}

	float hor_step = (float)m_size.x / (float)numPoints;
	float ver_step = 10;//(float)m_size.y / (float)m_fScale;

	wxPen pen(wxColour(180,180,180), 1); 
	dc.SetPen(pen);
	for (int i = 0; i < m_size.x; i += hor_step)
		dc.DrawLine(i, 0, i, m_size.y);
	for (int j = 0; j < m_size.y; j += ver_step)
		dc.DrawLine(0, j, m_size.x, j);

	wxPen pen2(*wxBLACK, 2); 
	dc.SetPen(pen2);
	dc.DrawLine(0, 0, 0, m_size.y);
	dc.DrawLine(0, m_size.y, m_size.x, m_size.y);
	dc.SetPen(wxNullPen);
}


void GraphControl::DrawData(wxDC& dc)
{
	if (m_Data.empty())
		return;

	unsigned int numPoints = m_Data.size() - 1;
	float hor_step = (float)m_size.x / (float)numPoints;
	float ver_step = (float)m_size.y / (float)m_fScale;

	wxPen pen(*wxBLUE, 1); 
	dc.SetBrush(*wxBLUE);
	dc.SetPen(pen);

	for (unsigned int point = 0; point < numPoints; ++point)
	{
		dc.DrawLine(
			m_Data[point].msec * hor_step,
			m_size.y - ver_step * m_Data[point].value,
			m_Data[point + 1].msec * hor_step,
			m_size.y - ver_step * m_Data[point + 1].value
			);
		dc.DrawRectangle(m_Data[point].msec * hor_step - 3,
			m_size.y - ver_step * m_Data[point].value - 3,
			6, 6
			);
	}

	dc.DrawRectangle(m_Data[numPoints].msec * hor_step - 3,
		m_size.y - ver_step * m_Data[numPoints].value - 3, 6, 6 );
}


void GraphControl::OnPaint(wxPaintEvent &WXUNUSED(event) )
{      
	wxPaintDC dc(this);
	PrepareDC(dc);
	dc.Clear();
	DrawAxes(dc);
	DrawData(dc);
}
