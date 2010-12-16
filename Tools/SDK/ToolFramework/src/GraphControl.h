#ifndef GRAPHCONTROL_H_
#define GRAPHCONTROL_H_

#include <vector>
#include "wx/wx.h"


struct neCoord
{
    long minutes;
    double y;
};


class neLine
{
public:
    std::vector<neCoord> coords;
    neLine() {line_name = "<empty>";}
    neLine(std::vector<neCoord>,wxString name = "<empty>");
    ~neLine(){};
    void ClearItems(void);
    wxString line_name;
    void Add(neCoord in_coord){coords.push_back(in_coord);}
};


// define a scrollable canvas for drawing onto
class neGraph: public wxScrolledWindow
{
public:
    neGraph( wxWindow*, const wxPoint& _pt, const wxSize& _sz);
    ~neGraph();
    void AddData(const neLine& in_data) {graph = in_data;}
    void ClearGraph(void);
    void DrawGrid(bool in ) { grid = in; }
private:
    void InitGraph(wxInitDialogEvent &event);
    void OnPaint(wxPaintEvent &event);
    void DrawAxes(wxDC& dc);
    void DrawControls(void);
    void FillAxes(wxDC& dc);
    void DrawData(wxDC& dc);
private:
    bool grid;
    wxWindow *m_owner;
    wxSize g_size;
    neLine graph;
    DECLARE_EVENT_TABLE();
};


std::string IntToString(int Input, int add_a_zero = 0);


#endif
