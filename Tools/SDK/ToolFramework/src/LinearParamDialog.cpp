#include "GraphControl.h"
#include <string>
#include "LinearParamDialog.h"
#include "wx/wx.h"


BEGIN_EVENT_TABLE(LinearParamDialog, wxDialog)
    EVT_BUTTON(wxID_ANY, LinearParamDialog::OnButton)
END_EVENT_TABLE()


LinearParamDialog::LinearParamDialog(wxWindow *parent)
             : wxDialog(parent, wxID_ANY, wxString(_T("Linear parameter")), wxDefaultPosition, wxSize(740, 200))
{
    wxSize panelSize = GetSize();

    m_btnApply = new wxButton(this, wxID_OK, _T("&Apply"), wxPoint((panelSize.x / 2) - 30, panelSize.y - 60), wxSize(60, 20));

    TSamplingData graph;
    SamplingData crd;
    crd.value = 10; crd.msec = 0; graph.push_back(crd);
    crd.value = 17; crd.msec = 10; graph.push_back(crd);
    crd.value = 27; crd.msec = 30; graph.push_back(crd);
    crd.value = 7; crd.msec = 40; graph.push_back(crd);
    crd.value = 2; crd.msec = 80; graph.push_back(crd);
    m_pGraph = new GraphControl(this, wxPoint(20, 20), wxSize(700, 120));
    m_pGraph->AddData(graph);

    m_btnApply->SetFocus();
    m_btnApply->SetDefault();
}


void LinearParamDialog::OnButton(wxCommandEvent& event)
{
    if ( event.GetEventObject() == m_btnApply )
    {
    }
    else
    {
        event.Skip();
    }
}
