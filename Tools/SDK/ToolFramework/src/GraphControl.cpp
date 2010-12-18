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
    m_GraphOffset = wxPoint(20, 20);
	m_size = wxSize(_sz.x - m_GraphOffset.x, _sz.y - m_GraphOffset.y);
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
	if (!m_Data.empty())
	{
        wxPen pen(wxColour(180,180,180), 1); 
        dc.SetPen(pen);

        unsigned int numPoints = m_Data.size();
    	float hor_step = (float)m_size.x / (float)(numPoints-1);

        for (unsigned int i = 0; i < numPoints; ++i)
	    {
            SamplingData& p = m_Data[i];
            int v = p.msec * hor_step;
            dc.DrawLine(v, 0, v, m_size.y);
        }
        for (int j = 0; j < m_size.y; j += 10)
            dc.DrawLine(0, j, m_size.x, j);
	}

	wxPen pen2(*wxBLACK, 2); 
	dc.SetPen(pen2);
	dc.DrawLine(m_GraphOffset.x, m_GraphOffset.y, m_GraphOffset.x, m_size.y);
	dc.DrawLine(m_GraphOffset.x, m_size.y, m_GraphOffset.x + m_size.x, m_size.y);
	dc.SetPen(wxNullPen);
}


void GraphControl::DrawData(wxDC& dc)
{
	if (m_Data.empty())
		return;

	unsigned int numPoints = m_Data.size() - 1;
	float hor_step = (float)m_size.x / (float)numPoints;
	float ver_step = (float)m_size.y / (float)m_fScale;

    int TipWidth = wxMin((hor_step / 2), 6);
    int HalfTipWidth = TipWidth / 2;

	wxPen pen(*wxBLUE, 1); 
	dc.SetBrush(*wxBLUE);
	dc.SetPen(pen);

	for (unsigned int point = 0; point < numPoints; ++point)
	{
        SamplingData& p_start = m_Data[point];
        SamplingData& p_end = m_Data[point + 1];

		dc.DrawLine(
			p_start.msec * hor_step,
			m_size.y - ver_step * p_start.value,
			p_end.msec * hor_step,
			m_size.y - ver_step * p_end.value
			);
		dc.DrawRectangle(p_start.msec * hor_step - HalfTipWidth,
			m_size.y - ver_step * p_start.value - HalfTipWidth,
			TipWidth, TipWidth
			);
	}

	dc.DrawRectangle(m_Data[numPoints].msec * hor_step - HalfTipWidth,
		m_size.y - ver_step * m_Data[numPoints].value - HalfTipWidth, TipWidth, TipWidth );
}


void GraphControl::OnPaint(wxPaintEvent &WXUNUSED(event) )
{      
	wxPaintDC dc(this);
	PrepareDC(dc);
	dc.Clear();
	DrawAxes(dc);
	DrawData(dc);
}
