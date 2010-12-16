#include <sstream>
#include <string>
#include "GraphControl.h"
#include "wx/wx.h"

using std::vector;


neLine::neLine(std::vector<neCoord> in_vec,wxString name)
{
    coords = in_vec;
    line_name = name;
}

void neLine::ClearItems(void)
{
	coords.clear();
}

BEGIN_EVENT_TABLE(neGraph, wxScrolledWindow)
    EVT_PAINT       (neGraph::OnPaint)
    EVT_INIT_DIALOG (neGraph::InitGraph)
END_EVENT_TABLE()


neGraph::neGraph( wxWindow *parent, const wxPoint& _pt, const wxSize& _sz)
: wxScrolledWindow(parent, wxID_ANY, _pt, _sz,
                   wxHSCROLL | wxVSCROLL | wxNO_FULL_REPAINT_ON_RESIZE)
{
    grid = false;
    m_owner = parent;
    g_size = _sz;
    DrawControls();
}

neGraph::~neGraph()
{
}


void neGraph::ClearGraph()
{
}


void neGraph::DrawAxes(wxDC& dc)
{
	unsigned int numPoints = 33;
	if (!graph.coords.empty())
	{
		numPoints = graph.coords.size();
	}

    double step = (double)g_size.x / (double)numPoints;

	if (grid)
    {
        wxPen pen(wxColour(180,180,180), 1); 
        dc.SetPen(pen);
        for (int i = 0; i < g_size.x; i += 10)
            dc.DrawLine(i, 0, i, g_size.y);
        for (int j = 0; j < g_size.y; j += 10)
            dc.DrawLine(0, j, g_size.x, j);
    }
    wxPen pen2(*wxBLACK, 2); 
    dc.SetPen(pen2);
    dc.DrawLine(0, 0, 0, g_size.y);
    dc.DrawLine(0, g_size.y, g_size.x, g_size.y);
    dc.SetPen(wxNullPen);
}


void neGraph::FillAxes(wxDC& dc)
{
	//step = g_size.y / 10;
	//for (int i = 0; i <= 10; i ++)
	//{
	//	dc.DrawLine(offset.x-5, offset.y+g_size.y-(i*step),offset.x,offset.y+g_size.y-(i*step));
	//	dc.DrawText(IntToString(i*10), offset.x-50, offset.y+g_size.y-(i*step)-10);
	//}   
}


void neGraph::DrawData(wxDC& dc)
{
	if (graph.coords.empty())
		return;

	unsigned int numPoints = graph.coords.size();
    double step = (double)g_size.x / (double)numPoints;

	wxPen pen(*wxBLUE, 1); 
	dc.SetBrush(*wxBLUE);
	dc.SetPen(pen);
	dc.DrawRoundedRectangle(g_size.x, 0, 30, 20,5.0);
	dc.FloodFill(g_size.x+10, 10, *wxWHITE, wxFLOOD_SURFACE);
	//dc.DrawText(graph.line_name, g_size.x+40, 0); 

	for (unsigned int point = 0; point < numPoints - 1; point++)
	{
		dc.DrawLine(
			graph.coords[point].minutes*step,
			g_size.y-(g_size.y/100)*graph.coords[point].y,
			graph.coords[point + 1].minutes*step,
			g_size.y-(g_size.y/100)*graph.coords[point + 1].y
			);
	}
}


void neGraph::DrawControls()
{
}


void neGraph::OnPaint(wxPaintEvent &WXUNUSED(event) )
{      
    wxPaintDC dc(this);
    PrepareDC(dc);
    dc.Clear();
    DrawAxes(dc);
    FillAxes(dc);
    DrawData(dc);
}


void neGraph::InitGraph(wxInitDialogEvent &WXUNUSED(event))
{
}


std::string IntToString(int Input, int add_a_zero)
{
    std::stringstream temp;
    std::string str;
	temp << Input;
	temp >> str;
    if (add_a_zero && Input < 10) str = "0" + str;
	return str;
}
