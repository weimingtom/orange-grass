#include <Opengl2.h>
#include <wx/wx.h>
#include "EffectViewerCanvas.h"
#include <OrangeGrass.h>
#include <IOGGraphicsHelpers.h>
#include <IOGMath.h>
#include "EffectViewerScene.h"


#define TIMER_ID    1000

BEGIN_EVENT_TABLE(CEffectViewerCanvas, wxGLCanvas)
    EVT_TIMER(TIMER_ID, CEffectViewerCanvas::OnTimer)
    EVT_SIZE(CEffectViewerCanvas::OnSize)
    EVT_PAINT(CEffectViewerCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(CEffectViewerCanvas::OnEraseBackground)
    EVT_KEY_DOWN( CEffectViewerCanvas::OnKeyDown )
    EVT_KEY_UP( CEffectViewerCanvas::OnKeyUp )
	EVT_RESSWITCH( wxID_ANY, CEffectViewerCanvas::OnResourceSwitch )
	EVT_TOOLCMD( wxID_ANY, CEffectViewerCanvas::OnToolCmdEvent )
	EVT_ENTER_WINDOW( CEffectViewerCanvas::OnMouseEnter )
	EVT_LEAVE_WINDOW( CEffectViewerCanvas::OnMouseLeave )
	EVT_MOTION( CEffectViewerCanvas::OnMouseMove )
	EVT_LEFT_DOWN( CEffectViewerCanvas::OnLMBDown )
	EVT_LEFT_UP( CEffectViewerCanvas::OnLMBUp )
	EVT_RIGHT_DOWN( CEffectViewerCanvas::OnRMBDown )
	EVT_RIGHT_UP( CEffectViewerCanvas::OnRMBUp )
	EVT_MOUSEWHEEL( CEffectViewerCanvas::OnMouseWheel )
END_EVENT_TABLE()


CEffectViewerScene*  g_pScene = NULL;

bool bRmb = false;
bool bLmb = false;
int  mouse_x = 0, mouse_y = 0;

/// @brief Constructor.
/// @param parent - parent window.
/// @param id - window ID.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
/// @param name - window name.
CEffectViewerCanvas::CEffectViewerCanvas (  wxWindow *parent, 
                                wxWindowID id,
                                const wxPoint& pos, 
                                const wxSize& size, 
                                long style, 
                                const wxString& name) : wxGLCanvas(parent, (wxGLCanvas*)NULL, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name),
                                                        m_timer(this, TIMER_ID)
{
	g_pScene = new CEffectViewerScene();
    m_init = false;
	m_bLoaded = false;
	GetEventHandlersTable()->AddEventHandler(EVENTID_RESSWITCH, this);
	GetEventHandlersTable()->AddEventHandler(EVENTID_TOOLCMD, this);
    m_timer.Start(33);
}


/// @brief Destructor.
CEffectViewerCanvas::~CEffectViewerCanvas()
{
    OG_SAFE_DELETE(g_pScene);
}


/// @brief Render.
void CEffectViewerCanvas::Render()
{
    wxPaintDC dc(this);
    dc.GetWindow()->GetHandle();
    if (!GetContext()) 
        return;
    SetCurrent();
}


/// @brief Timer handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnTimer(wxTimerEvent& event)
{
    g_pScene->Init();
    g_pScene->Update(10);
    g_pScene->RenderScene();
	SwapBuffers();
}


/// @brief Paint handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    Render();
}


/// @brief Resizing handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnSize(wxSizeEvent& event)
{
    wxGLCanvas::OnSize(event);
    GetClientSize(&m_ResX, &m_ResY);
    if (GetContext())
    {
		g_pScene->SetViewport(m_ResX, m_ResY);
    }
}


/// @brief Key down handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnKeyDown( wxKeyEvent& event )
{
    switch (event.GetKeyCode())
    {
	case WXK_UP:
		break;

	case WXK_DOWN:
		break;

	case WXK_LEFT:
		break;

	case WXK_RIGHT:
		break;
    }
    event.Skip();
}


/// @brief Key up handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnKeyUp( wxKeyEvent& event )
{
    event.Skip();
}


/// @brief Resource switching event handler
/// @param event - event structute.
void CEffectViewerCanvas::OnResourceSwitch ( CommonToolEvent<ResSwitchEventData>& event )
{
	const ResSwitchEventData& evtData = event.GetEventCustomData();
    g_pScene->SetupEffect(evtData.m_pItem->name);
	Refresh();
}


/// @brief Tool command event handler
/// @param event - event structute.
void CEffectViewerCanvas::OnToolCmdEvent ( CommonToolEvent<ToolCmdEventData>& event )
{
	const ToolCmdEventData& evtData = event.GetEventCustomData();
	switch (evtData.m_CmdType)
	{
	case CMD_COORDGRID:
		g_pScene->SetGridMode(evtData.m_bSwitcher);
		break;

	case CMD_AABB:
		g_pScene->SetAABBMode(evtData.m_bSwitcher);
		break;
	}
	Refresh ();
}


/// @brief Mouse enter handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnMouseEnter(wxMouseEvent& event)
{
	 SetFocus();
}


/// @brief Mouse leave handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnMouseLeave(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bLmb = false;
	bRmb = false;
}


/// @brief Mouse move handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnMouseMove(wxMouseEvent& event)
{
	if (bLmb)
	{
		mouse_x = event.GetX();
		mouse_y = event.GetY();
	}

	mouse_x = event.GetX();
	mouse_y = event.GetY();
}


/// @brief Mouse Left button up handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnLMBUp(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bLmb = false;
}


/// @brief Mouse Left button up handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnLMBDown(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bLmb = true;
}


/// @brief Mouse Right button up handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnRMBUp(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bRmb = false;
}


/// @brief Mouse Right button up handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnRMBDown(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bRmb = true;
}


/// @brief Mouse wheel handler.
/// @param event - event structute.
void CEffectViewerCanvas::OnMouseWheel(wxMouseEvent& event)
{
	int delta = event.GetWheelRotation();
	g_pScene->CameraZoom((float)delta / 10.0f);
	Refresh ();
}
