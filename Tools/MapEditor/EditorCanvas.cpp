#include <Opengl2.h>
#include <wx/wx.h>
#include "EditorCanvas.h"
#include <OrangeGrass.h>
#include <IOGGraphicsHelpers.h>
#include <IOGMath.h>
#include "EditorLevelScene.h"


#define TIMER_ID    1000

BEGIN_EVENT_TABLE(CEditorCanvas, wxGLCanvas)
    EVT_TIMER(TIMER_ID, CEditorCanvas::OnTimer)
    EVT_SIZE(CEditorCanvas::OnSize)
    EVT_PAINT(CEditorCanvas::OnPaint)
    EVT_ERASE_BACKGROUND(CEditorCanvas::OnEraseBackground)
    EVT_KEY_DOWN( CEditorCanvas::OnKeyDown )
    EVT_KEY_UP( CEditorCanvas::OnKeyUp )
    EVT_ENTER_WINDOW( CEditorCanvas::OnEnterWindow )
	EVT_TOOLCMD( wxID_ANY, CEditorCanvas::OnToolCmdEvent )
	EVT_LEVELLOAD( wxID_ANY, CEditorCanvas::OnLevelLoadEvent )
	EVT_RESSWITCH( wxID_ANY, CEditorCanvas::OnResourceSwitch )
	EVT_ENTER_WINDOW( CEditorCanvas::OnMouseEnter )
	EVT_LEAVE_WINDOW( CEditorCanvas::OnMouseLeave )
	EVT_MOTION( CEditorCanvas::OnMouseMove )
	EVT_LEFT_DOWN( CEditorCanvas::OnLMBDown )
	EVT_LEFT_UP( CEditorCanvas::OnLMBUp )
	EVT_RIGHT_DOWN( CEditorCanvas::OnRMBDown )
	EVT_RIGHT_UP( CEditorCanvas::OnRMBUp )
	EVT_MOUSEWHEEL( CEditorCanvas::OnMouseWheel )
END_EVENT_TABLE()


bool		m_bIntersectionFound = false;
Vec3		m_vIntersection;
CEditorLevelScene*  g_pScene = NULL;


/// @brief Constructor.
/// @param parent - parent window.
/// @param id - window ID.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
/// @param name - window name.
CEditorCanvas::CEditorCanvas (  wxWindow *parent, 
                                wxWindowID id,
                                const wxPoint& pos, 
                                const wxSize& size, 
                                long style, 
                                const wxString& name) : wxGLCanvas(parent, (wxGLCanvas*)NULL, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name),
                                                        m_timer(this, TIMER_ID)
{
    g_pScene = new CEditorLevelScene();
	GetEventHandlersTable()->AddEventHandler(EVENTID_RESSWITCH, this);
	GetEventHandlersTable()->AddEventHandler(EVENTID_TOOLCMD, this);
	GetEventHandlersTable()->AddEventHandler(EVENTID_LEVELLOAD, this);
    m_timer.Start(100);

    bRmb = bLmb = false;
    mouse_x = mouse_y = 0;

    m_fFineAngleStep = TO_RADIAN(2.0f);
    m_fCoarseAngleStep = TO_RADIAN(45.0f);

	m_bMouseInWindow = true;
	m_bMouseMoved = false;
	m_bIntersectionFound = false;
    
    m_SettingsMode = SETMODE_NONE;
}


/// @brief Destructor.
CEditorCanvas::~CEditorCanvas()
{
    OG_SAFE_DELETE(g_pScene);
}


/// @brief Render.
void CEditorCanvas::Render()
{
    wxPaintDC dc(this);
    dc.GetWindow()->GetHandle();
    if (!GetContext()) 
        return;
    SetCurrent();

    if (!g_pScene->m_bInited)
    {
        g_pScene->Init();
    }
    g_pScene->Update(10);
    g_pScene->RenderScene();

	SwapBuffers();
}


/// @brief Timer handler.
/// @param event - event structute.
void CEditorCanvas::OnTimer(wxTimerEvent& event)
{
	if (m_bMouseMoved)
	{
		m_bIntersectionFound = g_pScene->GetTerrainIntersection(m_vIntersection, mouse_x, mouse_y);

		ToolSettings* pTool = GetToolSettings();
		switch (pTool->GetEditMode())
		{
		case EDITMODE_OBJECTS:
			{
				if (m_bIntersectionFound)
					g_pScene->UpdateCurrentNodePosition(m_vIntersection);
			}
			break;

		case EDITMODE_ADJUST:
			{
			}
			break;

		case EDITMODE_SETTINGS:
			{
				if (bLmb && m_bIntersectionFound)
				{
					switch (m_SettingsMode)
					{
					case SETMODE_LEVEL_START:
						g_pScene->UpdateLevelStartPosition(m_vIntersection);
						break;

					case SETMODE_LEVEL_FINISH:
						g_pScene->UpdateLevelFinishPosition(m_vIntersection);
						break;
					}
				}
			}
			break;
		}

		m_bMouseMoved = false;
		Refresh();
	}
}


/// @brief Enter window handler.
/// @param event - event structute.
void CEditorCanvas::OnEnterWindow( wxMouseEvent& WXUNUSED(event) )
{
    SetFocus();
}


/// @brief Paint handler.
/// @param event - event structute.
void CEditorCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
    Render();
}


/// @brief Resizing handler.
/// @param event - event structute.
void CEditorCanvas::OnSize(wxSizeEvent& event)
{
    wxGLCanvas::OnSize(event);
    GetClientSize(&m_ResX, &m_ResY);
    if (GetContext())
    {
        SetCurrent();
		g_pScene->SetViewport(m_ResX, m_ResY);
    }
}


/// @brief Level load event handler
/// @param event - event structute.
void CEditorCanvas::OnLevelLoadEvent ( CommonToolEvent<LevelLoadEventData>& event )
{
	g_pScene->LoadLevel(std::string(event.GetEventCustomData().m_Path));
	GetToolSettings()->SetLevel((void*)g_pScene->m_pCurLevel);
	this->Refresh();
}


/// @brief Key down handler.
/// @param event - event structute.
void CEditorCanvas::OnKeyDown( wxKeyEvent& event )
{
    /*switch (event.GetKeyCode())
    {
    case WXK_UP:
        if (event.ControlDown())
        {
            if (m_pPickedActor)
            {
                Vec3 vPos = m_pPickedActor->GetPhysicalObject()->GetPosition(); vPos.z -= 1.0f;
                m_pPickedActor->GetPhysicalObject()->SetPosition(vPos);
            }
        }
        else
		    GetRenderer()->GetCamera()->Strafe(5.5f, Vec3(0, 0, -1));
		mouse_x = event.GetX();
		mouse_y = event.GetY();
		m_bMouseMoved = true;
		this->Refresh();
        break;

	case WXK_DOWN:
        if (event.ControlDown())
        {
            if (m_pPickedActor)
            {
                Vec3 vPos = m_pPickedActor->GetPhysicalObject()->GetPosition(); vPos.z += 1.0f;
                m_pPickedActor->GetPhysicalObject()->SetPosition(vPos);
            }
        }
        else
    		GetRenderer()->GetCamera()->Strafe(5.5f, Vec3(0, 0, 1));
		mouse_x = event.GetX();
		mouse_y = event.GetY();
		m_bMouseMoved = true;
		this->Refresh();
        break;

	case WXK_LEFT:
        if (event.ControlDown())
        {
			if (GetToolSettings()->GetEditMode() == EDITMODE_SETTINGS)
			{
				if (m_pCurLevel)
				{
					float fW = m_pCurLevel->GetActiveWidth();
					if (fW > 30.0f)
						fW -= 1.0f;
					m_pCurLevel->SetActiveWidth(fW);
				}
			}
			else
			{
				if (m_pPickedActor)
				{
					Vec3 vPos = m_pPickedActor->GetPhysicalObject()->GetPosition(); vPos.x -= 1.0f;
					m_pPickedActor->GetPhysicalObject()->SetPosition(vPos);
				}
			}
        }
        else
    		GetRenderer()->GetCamera()->Strafe(5.5f, Vec3(-1, 0, 0));
		mouse_x = event.GetX();
		mouse_y = event.GetY();
		m_bMouseMoved = true;
		this->Refresh();
        break;

	case WXK_RIGHT:
        if (event.ControlDown())
        {
			if (GetToolSettings()->GetEditMode() == EDITMODE_SETTINGS)
			{
				if (m_pCurLevel)
				{
					float fW = m_pCurLevel->GetActiveWidth();
					if (fW < 400.0f)
						fW += 1.0f;
					m_pCurLevel->SetActiveWidth(fW);
				}
			}
			else
			{
				if (m_pPickedActor)
				{
					Vec3 vPos = m_pPickedActor->GetPhysicalObject()->GetPosition(); vPos.x += 1.0f;
					m_pPickedActor->GetPhysicalObject()->SetPosition(vPos);
				}
			}
        }
        else
    		GetRenderer()->GetCamera()->Strafe(5.5f, Vec3(1, 0, 0));
		mouse_x = event.GetX();
		mouse_y = event.GetY();
		m_bMouseMoved = true;
		this->Refresh();
        break;

    case WXK_PAGEUP:
        if (event.ControlDown())
        {
            if (m_pPickedActor)
            {
                Vec3 vPos = m_pPickedActor->GetPhysicalObject()->GetPosition(); vPos.y += 1.0f;
                m_pPickedActor->GetPhysicalObject()->SetPosition(vPos);
            }
        }
		this->Refresh();
        break;

    case WXK_PAGEDOWN:
        if (event.ControlDown())
        {
            if (m_pPickedActor)
            {
                Vec3 vPos = m_pPickedActor->GetPhysicalObject()->GetPosition(); vPos.y -= 1.0f;
                m_pPickedActor->GetPhysicalObject()->SetPosition(vPos);
            }
        }
		this->Refresh();
        break;

    case WXK_DELETE:
        if (m_pPickedActor)
        {
            GetActorManager()->DestroyActor(m_pPickedActor);
            m_pPickedActor = NULL;
        }
		this->Refresh();
        break;

    case 'D':
        if (m_pCurActor)
        {
            m_vCurRotation.y += event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pCurActor->GetPhysicalObject()->SetRotation(m_vCurRotation);
        }
        if (m_pPickedActor)
        {
            Vec3 vRot = m_pPickedActor->GetPhysicalObject()->GetRotation();
            vRot.y += event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pPickedActor->GetPhysicalObject()->SetRotation(vRot);
        }
		this->Refresh();
        break;

    case 'A':
        if (m_pCurActor)
        {
            m_vCurRotation.y -= event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pCurActor->GetPhysicalObject()->SetRotation(m_vCurRotation);
        }
        if (m_pPickedActor)
        {
            Vec3 vRot = m_pPickedActor->GetPhysicalObject()->GetRotation();
            vRot.y -= event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pPickedActor->GetPhysicalObject()->SetRotation(vRot);
        }
		this->Refresh();
        break;

    case 'W':
        if (m_pCurActor)
        {
            m_vCurRotation.x += event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pCurActor->GetPhysicalObject()->SetRotation(m_vCurRotation);
        }
        if (m_pPickedActor)
        {
            Vec3 vRot = m_pPickedActor->GetPhysicalObject()->GetRotation();
            vRot.x += event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pPickedActor->GetPhysicalObject()->SetRotation(vRot);
        }
		this->Refresh();
        break;

    case 'S':
        if (m_pCurActor)
        {
            m_vCurRotation.x -= event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pCurActor->GetPhysicalObject()->SetRotation(m_vCurRotation);
        }
        if (m_pPickedActor)
        {
            Vec3 vRot = m_pPickedActor->GetPhysicalObject()->GetRotation();
            vRot.x -= event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pPickedActor->GetPhysicalObject()->SetRotation(vRot);
        }
		this->Refresh();
        break;

    case 'E':
        if (m_pCurActor)
        {
            m_vCurRotation.z += event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pCurActor->GetPhysicalObject()->SetRotation(m_vCurRotation);
        }
        if (m_pPickedActor)
        {
            Vec3 vRot = m_pPickedActor->GetPhysicalObject()->GetRotation();
            vRot.z += event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pPickedActor->GetPhysicalObject()->SetRotation(vRot);
        }
		this->Refresh();
        break;

    case 'Q':
        if (m_pCurActor)
        {
            m_vCurRotation.z -= event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pCurActor->GetPhysicalObject()->SetRotation(m_vCurRotation);
        }
        if (m_pPickedActor)
        {
            Vec3 vRot = m_pPickedActor->GetPhysicalObject()->GetRotation();
            vRot.z -= event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pPickedActor->GetPhysicalObject()->SetRotation(vRot);
        }
		this->Refresh();
        break;

    case 'Z':
        if (m_pCurActor)
        {
            m_vCurScaling -= event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pCurActor->GetPhysicalObject()->SetScaling(m_vCurScaling);
        }
        if (m_pPickedActor)
        {
            Vec3 vScale = m_pPickedActor->GetPhysicalObject()->GetScaling();
            vScale -= 0.02f;
            m_pPickedActor->GetPhysicalObject()->SetScaling(vScale);
        }
		this->Refresh();
        break;

    case 'X':
        if (m_pCurActor)
        {
            m_vCurScaling += event.ControlDown() ? m_fCoarseAngleStep : m_fFineAngleStep;
            m_pCurActor->GetPhysicalObject()->SetScaling(m_vCurScaling);
        }
        if (m_pPickedActor)
        {
            Vec3 vScale = m_pPickedActor->GetPhysicalObject()->GetScaling();
            vScale += 0.02f;
            m_pPickedActor->GetPhysicalObject()->SetScaling(vScale);
        }
		this->Refresh();
        break;

    case 'C':
        if (m_pCurActor)
        {
            m_vCurScaling.x = m_vCurScaling.y = m_vCurScaling.z = 1;
            m_vCurRotation.x = m_vCurRotation.y = m_vCurRotation.z = 0;
            m_pCurActor->GetPhysicalObject()->SetWorldTransform(m_vIntersection, m_vCurRotation, m_vCurScaling);
        }
        if (m_pPickedActor)
        {
            Vec3 vPos = m_pPickedActor->GetPhysicalObject()->GetPosition();
            m_pPickedActor->GetPhysicalObject()->SetWorldTransform(vPos, Vec3(0, 0, 0), Vec3(1, 1, 1));
        }
		this->Refresh();
        break;
    }*/

    event.Skip();
}


/// @brief Key up handler.
/// @param event - event structute.
void CEditorCanvas::OnKeyUp( wxKeyEvent& event )
{
    event.Skip();
}


/// @brief Tool command event handler
/// @param event - event structute.
void CEditorCanvas::OnToolCmdEvent ( CommonToolEvent<ToolCmdEventData>& event )
{
	const ToolCmdEventData& evtData = event.GetEventCustomData();
	switch (evtData.m_CmdType)
	{
	case CMD_AABB:
		g_pScene->m_bShowAABB = evtData.m_bSwitcher;
		break;

	case CMD_EDITMODE_OBJECTS:
        m_SettingsMode = SETMODE_NONE;
		g_pScene->SetEditMode(EDITMODE_OBJECTS);
		break;

	case CMD_EDITMODE_ADJUST:
        m_SettingsMode = SETMODE_NONE;
		g_pScene->SetEditMode(EDITMODE_ADJUST);
		break;

	case CMD_EDITMODE_SETTINGS:
        m_SettingsMode = SETMODE_NONE;
		g_pScene->SetEditMode(EDITMODE_SETTINGS);
		break;

    case CMD_LEVEL_SAVE:
		g_pScene->SaveLevel();
        break;

	case CMD_SETTINGSMODE_LEVSTART:
        m_SettingsMode = SETMODE_LEVEL_START;
        break;

	case CMD_SETTINGSMODE_LEVFINISH:
        m_SettingsMode = SETMODE_LEVEL_FINISH;
        break;

	case CMD_UPDATE:
        Refresh();
        break;
	}
	Refresh ();
}


/// @brief Mouse enter handler.
/// @param event - event structute.
void CEditorCanvas::OnMouseEnter(wxMouseEvent& event)
{
	m_bMouseInWindow = true;
}


/// @brief Mouse leave handler.
/// @param event - event structute.
void CEditorCanvas::OnMouseLeave(wxMouseEvent& event)
{
	m_bMouseInWindow = false;
}


/// @brief Mouse move handler.
/// @param event - event structute.
void CEditorCanvas::OnMouseMove(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	m_bMouseMoved = true;
}


/// @brief Mouse Left button up handler.
/// @param event - event structute.
void CEditorCanvas::OnLMBUp(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();

    ToolSettings* pTool = GetToolSettings();
    switch (pTool->GetEditMode())
    {
    case EDITMODE_OBJECTS:
        {
			m_bIntersectionFound = g_pScene->GetTerrainIntersection(m_vIntersection, mouse_x, mouse_y);
			if (m_bIntersectionFound)
			{
				g_pScene->PlaceCurrentNode(m_vIntersection);
			}
        }
        break;

    case EDITMODE_ADJUST:
        {
			g_pScene->PickActor(mouse_x, mouse_y);
        }
        break;

    case EDITMODE_SETTINGS:
        {
        }
        break;
    }

    Refresh();

	bLmb = false;
}


/// @brief Mouse Left button up handler.
/// @param event - event structute.
void CEditorCanvas::OnLMBDown(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bLmb = true;
}


/// @brief Mouse Right button up handler.
/// @param event - event structute.
void CEditorCanvas::OnRMBUp(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bRmb = false;
}


/// @brief Mouse Right button up handler.
/// @param event - event structute.
void CEditorCanvas::OnRMBDown(wxMouseEvent& event)
{
	mouse_x = event.GetX();
	mouse_y = event.GetY();
	bRmb = true;
}


/// @brief Mouse wheel handler.
/// @param event - event structute.
void CEditorCanvas::OnMouseWheel(wxMouseEvent& event)
{
	int delta = event.GetWheelRotation();
	g_pScene->CameraZoom((float)delta / 10.0f);
	Refresh ();
}


/// @brief Resource switching event handler
/// @param event - event structute.
void CEditorCanvas::OnResourceSwitch ( CommonToolEvent<ResSwitchEventData>& event )
{
	const ResSwitchEventData& evtData = event.GetEventCustomData();
	switch (evtData.m_ResourceType)
	{
	case RESTYPE_MODEL:
        {
			OGActorType actor_type = GetActorManager()->ParseActorType(std::string(evtData.m_ResourceActorType));
			if (actor_type != OG_ACTOR_NONE)
			{
				g_pScene->SetNewCurrentNodeForPlacement(evtData.m_Resource, (int)actor_type);
			}
			else
			{
				g_pScene->SetNewCurrentNodeForPlacement(NULL, (int)OG_ACTOR_NONE);
			}
        }
		break;
	}

	Refresh();
}
