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
