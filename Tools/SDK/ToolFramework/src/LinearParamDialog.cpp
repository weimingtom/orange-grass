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
    //wxBoxSizer *sizerTop = new wxBoxSizer(wxBOTH);

    wxSize panelSize = GetSize();

    m_btnApply = new wxButton(this, wxID_OK, _T("&Apply"), wxPoint((panelSize.x / 2) - 30, panelSize.y - 60), wxSize(60, 20));
    //m_btnCancel = new wxButton(this, wxID_CANCEL, _T("&Cancel"));

    TSamplingData graph;
    for (int i = 0; i < 33; ++i)
    {
        SamplingData crd;
        crd.value = 27;
        crd.msec = i;
        graph.push_back(crd);
    }
    m_pGraph = new GraphControl(this, wxPoint(20, 20), wxSize(700, 50));
    m_pGraph->AddData(graph);

    //sizerTop->Add(m_pGraph, 0, wxALIGN_CENTER | wxTOP, 5);
    //sizerTop->Add(m_btnApply, 0, wxALIGN_CENTER | wxALL, 5);
    //sizerTop->Add(m_btnCancel, 0, wxALIGN_CENTER | wxALL, 5);

    //SetSizer(sizerTop);

    //sizerTop->SetSizeHints(this);
    //sizerTop->Fit(this);

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
