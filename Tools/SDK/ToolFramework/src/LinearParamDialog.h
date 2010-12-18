#ifndef LINEARPARAMDIALOG_H_
#define LINEARPARAMDIALOG_H_

#include <vector>
#include "wx/wx.h"


class LinearParamDialog : public wxDialog
{
public:

    LinearParamDialog(wxWindow *parent);

    void OnButton(wxCommandEvent& event);

private:

    wxButton*       m_btnApply;
    wxButton*       m_btnCancel;
    GraphControl*   m_pGraph;

    DECLARE_EVENT_TABLE()
};

#endif