#include <Opengl2.h>
#include <wx/wx.h>
#include "ViewerCanvas.h"
#include <OrangeGrass.h>
#include <IOGGraphicsHelpers.h>
#include <IOGMath.h>
#include "ViewerScene.h"


#define TIMER_ID    1000

BEGIN_EVENT_TABLE(CViewerCanvas, wxGLCanvas)
    EVT_TIMER(TIMER_ID, CViewerCanvas::OnTimer)
    EVT_SIZE(CViewerCanvas::OnSize)
    EVT_PAINT(CViewerCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(CViewerCanvas::OnEraseBackground)
    EVT_KEY_DOWN( CViewerCanvas::OnKeyDown )
    EVT_KEY_UP( CViewerCanvas::OnKeyUp )
	EVT_RESSWITCH( wxID_ANY, CViewerCanvas::OnResourceSwitch )
	EVT_TOOLCMD( wxID_ANY, CViewerCanvas::OnToolCmdEvent )
	EVT_ENTER_WINDOW( CViewerCanvas::OnMouseEnter )
	EVT_LEAVE_WINDOW( CViewerCanvas::OnMouseLeave )
	EVT_MOTION( CViewerCanvas::OnMouseMove )
	EVT_LEFT_DOWN( CViewerCanvas::OnLMBDown )
	EVT_LEFT_UP( CViewerCanvas::OnLMBUp )
	EVT_RIGHT_DOWN( CViewerCanvas::OnRMBDown )
	EVT_RIGHT_UP( CViewerCanvas::OnRMBUp )
	EVT_MOUSEWHEEL( CViewerCanvas::OnMouseWheel )
END_EVENT_TABLE()


CViewerScene*  g_pScene = NULL;

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
CViewerCanvas::CViewerCanvas (  wxWindow *parent, 
                                wxWindowID id,
                                const wxPoint& pos, 
                                const wxSize& size, 
                                long style, 
                                const wxString& name) : wxGLCanvas(parent, (wxGLCanvas*)NULL, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name),
                                                        m_timer(this, TIMER_ID)
{
	g_pScene = new CViewerScene();
    m_init = false;
	m_bLoaded = false;
	GetEventHandlersTable()->AddEventHandler(EVENTID_RESSWITCH, this);
	GetEventHandlersTable()->AddEventHandler(EVENTID_TOOLCMD, this);
    m_timer.Start(33);
}


/// @brief Destructor.
CViewerCanvas::~CViewerCanvas()
{
    OG_SAFE_DELETE(g_pScene);
}


/// @brief Render.
void CViewerCanvas::Render()
{
    wxPaintDC dc(this);
    dc.GetWindow()->GetHandle();
    if (!GetContext()) 
        return;
    SetCurrent();

 //   g_pScene->Init();
 //   g_pScene->Update(10);
 //   g_pScene->RenderScene();

	//SwapBuffers();
}


/// @brief Timer handler.
/// @param event - event structute.
void CViewerCanvas::OnTimer(wxTimerEvent& event)
{
    g_pScene->Init();
    g_pScene->Update(10);
    g_pScene->RenderScene();
	SwapBuffers();
}


/// @brief Paint handler.
/// @param event - event structute.
void CViewerCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    Render();
}


/// @brief Resizing handler.
/// @param event - event structute.
void CViewerCanvas::OnSize(wxSizeEvent& event)
{
    wxGLCanvas::OnSize(event);
    GetClientSize(&m_ResX, &m_ResY);
    if (GetContext())
    {
        //SetCurrent();
		g_pScene->SetViewport(m_ResX, m_ResY);
    }
}


/// @brief Key down handler.
/// @param event - event structute.
void CViewerCanvas::OnKeyDown( wxKeyEvent& event )
{
    switch (event.GetKeyCode())
    {
	case WXK_UP:
		g_pScene->CameraMove(0.0f, -1.0f);
		Refresh();
		break;

	case WXK_DOWN:
		g_pScene->CameraMove(0.0f, 1.0f);
		Refresh();
		break;

	case WXK_LEFT:
		g_pScene->CameraMove(-1.0f, 0.0f);
		Refresh();
		break;

	case WXK_RIGHT:
		g_pScene->CameraMove(1.0f, 0.0f);
		Refresh();
		break;
    }
    event.Skip();
}


/// @brief Key up handler.
/// @param event - event structute.
void CViewerCanvas::OnKeyUp( wxKeyEvent& event )
{
    event.Skip();
}


/// @brief Resource switching event handler
/// @param event - event structute.
void CViewerCanvas::OnResourceSwitch ( CommonToolEvent<ResSwitchEventData>& event )
{
	const ResSwitchEventData& evtData = event.GetEventCustomData();
	switch (evtData.m_ResourceType)
	{
	case RESTYPE_MODEL:
		g_pScene->SetupModel(evtData.m_Resource);
		break;
	}
	Refresh();
}


/// @brief Tool command event handler
/// @param event - event structute.
void CViewerCanvas::OnToolCmdEvent ( CommonToolEvent<ToolCmdEventData>& event )
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
void CViewerCanvas::OnMouseEnter(wxMouseEvent& event)
{
	 SetFocus();
}


/// @brief Mouse leave handler.
/// @param event - event structute.
void CViewerCanvas::OnMouseLeave(wxMouseEvent& event)
{
}


/// @brief Mouse move handler.
/// @param event - event structute.
void CViewerCanvas::OnMouseMove(wxMouseEvent& event)
{
}


/// @brief Mouse Left button up handler.
/// @param event - event structute.
void CViewerCanvas::OnLMBUp(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bLmb = false;
}


/// @brief Mouse Left button up handler.
/// @param event - event structute.
void CViewerCanvas::OnLMBDown(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bLmb = true;
}


/// @brief Mouse Right button up handler.
/// @param event - event structute.
void CViewerCanvas::OnRMBUp(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bRmb = false;
}


/// @brief Mouse Right button up handler.
/// @param event - event structute.
void CViewerCanvas::OnRMBDown(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bRmb = true;
}


/// @brief Mouse wheel handler.
/// @param event - event structute.
void CViewerCanvas::OnMouseWheel(wxMouseEvent& event)
{
	int delta = event.GetWheelRotation();
	g_pScene->CameraZoom((float)delta / 10.0f);
	Refresh ();
}
