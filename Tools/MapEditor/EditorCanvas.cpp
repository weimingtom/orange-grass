#include <Opengl2.h>
#include <wx/wx.h>
#include "EditorCanvas.h"
#include <OrangeGrass.h>
#include <IOGGraphicsHelpers.h>
#include <IOGMath.h>


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


MATRIX		m_mProjection;
MATRIX		m_mView;
IOGLevel*	m_pCurLevel = NULL;
IOGActor*   m_pCurActor = NULL;
IOGActor*   m_pPickedActor = NULL;
bool		m_bIntersectionFound = false;
Vec3		m_vIntersection;
Vec3		m_vCurRotation;
Vec3		m_vCurScaling(1);
OGActorType	m_CurActorType = OG_ACTOR_NONE;
std::string m_CurModelAlias;
float       m_fAirBotHeight = 80.0f;


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
    m_init = false;
	m_bLoaded = false;
	GetEventHandlersTable()->AddEventHandler(EVENTID_RESSWITCH, this);
	GetEventHandlersTable()->AddEventHandler(EVENTID_TOOLCMD, this);
	GetEventHandlersTable()->AddEventHandler(EVENTID_LEVELLOAD, this);
    m_timer.Start(100);
	m_fCameraDistance = 400.0f;

    bRmb = bLmb = false;
    mouse_x = mouse_y = 0;

    m_fFineAngleStep = TO_RADIAN(2.0f);
    m_fCoarseAngleStep = TO_RADIAN(45.0f);

	m_bShowAABB = false;
	m_bMouseInWindow = true;
	m_bMouseMoved = false;
	m_bRedrawPatch = false;

	m_bIntersectionFound = false;
    
    m_SettingsMode = SETMODE_NONE;
}


/// @brief Destructor.
CEditorCanvas::~CEditorCanvas()
{
    OG_SAFE_DELETE(m_pCurActor);
}


/// @brief Render.
void CEditorCanvas::Render()
{
    wxPaintDC dc(this);
    dc.GetWindow()->GetHandle();

    if (!GetContext()) 
        return;

    SetCurrent();

    // Init OpenGL once, but after SetCurrent
    if (!m_init)
    {
        InitGL();
		GetResourceMgr()->Init();
		GetLevelManager()->Init();
		m_init = true;
    }

	if (!m_bLoaded)
	{
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glFlush();
		SwapBuffers();
		LoadNextResource();
	}

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_mProjection.f);
	
	glMatrixMode(GL_MODELVIEW);
	m_mView = GetSceneGraph()->GetCamera()->Update();
	glLoadMatrixf(m_mView.f);

    GetSceneGraph()->GetLight()->Apply();

    GetPhysics()->Update(0);
    GetActorManager()->Update(10);

	if (m_pCurLevel)
        m_pCurLevel->GetTerrain()->Render(m_mView);

    GetSceneGraph()->Render(m_mView);

    switch (GetToolSettings()->GetEditMode())
    {
    case EDITMODE_OBJECTS:
        {
            if (m_pCurActor)
            {
                m_pCurActor->GetPhysicalObject()->Update(10);
                m_pCurActor->Update(10);

                MATRIX mModelView = m_pCurActor->GetSgNode()->GetWorldTransform();
                MatrixMultiply(mModelView, mModelView, m_mView);
                m_pCurActor->GetSgNode()->GetRenderable()->Render(mModelView);
            }
        }
        break;
    }

    RenderHelpers();

    glFlush();
    SwapBuffers();
}


/// @brief Timer handler.
/// @param event - event structute.
void CEditorCanvas::OnTimer(wxTimerEvent& event)
{
	if (m_bMouseMoved)
	{
		Vec3 vPick = GetPickRay (mouse_x, mouse_y);
		Vec3 vPos = GetSceneGraph()->GetCamera()->GetPosition();
		Vec3 vVec = vPick - vPos;
		vVec.normalize();

		ToolSettings* pTool = GetToolSettings();
		switch (pTool->GetEditMode())
		{
		case EDITMODE_OBJECTS:
			{
                if (m_pCurLevel)
				{
					m_bIntersectionFound = m_pCurLevel->GetTerrain()->GetRayIntersection(vPos, vVec, &m_vIntersection);
					if (m_bIntersectionFound)
					{
						if (m_pCurActor)
						{
                            if (m_CurActorType == OG_ACTOR_AIRBOT || m_CurActorType == OG_ACTOR_PLAYER)
                            {
                                m_vIntersection.y = m_fAirBotHeight;
                            }
                            m_pCurActor->GetPhysicalObject()->SetPosition(m_vIntersection);
						}
						m_bRedrawPatch = true;
					}
				}
			}
			break;

		case EDITMODE_ADJUST:
			{
			}
			break;

		case EDITMODE_SETTINGS:
			{
                if (m_pCurLevel)
				{
                    if (bLmb)
                    {
                        m_bIntersectionFound = m_pCurLevel->GetTerrain()->GetRayIntersection(vPos, vVec, &m_vIntersection);
                        if (m_bIntersectionFound)
                        {
                            switch (m_SettingsMode)
                            {
                            case SETMODE_LEVEL_START:
                                m_pCurLevel->SetStartPosition(m_vIntersection);
                                break;

                            case SETMODE_LEVEL_FINISH:
                                m_pCurLevel->SetFinishPosition(m_vIntersection);
                                break;
                            }
                            m_bRedrawPatch = true;
                        }
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
        glViewport(0, 0, m_ResX, m_ResY);
		MatrixPerspectiveFovRH(m_mProjection, 1.0f, float(m_ResX)/float(m_ResY), 4.0f, 4500.0f, true);
    }
}


/// @brief Initialize renderer.
void CEditorCanvas::InitGL()
{
	glewInit();

    SetupCamera ();

	glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
}


/// @brief Load next resource bulk.
/// @return false if finished loading.
bool CEditorCanvas::LoadNextResource()
{
	std::vector<IOGResourceInfo> resInfo;
	if (GetResourceMgr()->Load(resInfo))
	{
		std::vector<IOGResourceInfo>::const_iterator iter = resInfo.begin();
		for (; iter != resInfo.end(); ++iter)
		{
			CommonToolEvent<ResLoadEventData> cmd(EVENTID_RESLOAD);
			cmd.SetEventCustomData(ResLoadEventData(wxT((*iter).m_Resource), 
				wxT((*iter).m_ResourceGroup), 
				wxT((*iter).m_ResourceIcon),
				wxT((*iter).m_ResourceActorType)));
			GetEventHandlersTable()->FireEvent(EVENTID_RESLOAD, &cmd);
		}
	}

	m_bLoaded = true;
	SetNewCurrentNodeForPlacement(NULL, OG_ACTOR_NONE);

	return true;
}


/// @brief Level load event handler
/// @param event - event structute.
void CEditorCanvas::OnLevelLoadEvent ( CommonToolEvent<LevelLoadEventData>& event )
{
	if (m_pCurLevel)
	{
		GetLevelManager()->UnloadLevel(m_pCurLevel);
	}
	m_pCurLevel = GetLevelManager()->LoadLevel(std::string(event.GetEventCustomData().m_Path));
	GetToolSettings()->SetLevel((void*)m_pCurLevel);
	this->Refresh();
}


/// @brief Key down handler.
/// @param event - event structute.
void CEditorCanvas::OnKeyDown( wxKeyEvent& event )
{
    switch (event.GetKeyCode())
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
		    GetSceneGraph()->GetCamera()->Strafe(5.5f, Vec3(0, 0, -1));
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
    		GetSceneGraph()->GetCamera()->Strafe(5.5f, Vec3(0, 0, 1));
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
    		GetSceneGraph()->GetCamera()->Strafe(5.5f, Vec3(-1, 0, 0));
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
    		GetSceneGraph()->GetCamera()->Strafe(5.5f, Vec3(1, 0, 0));
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
    }

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
		m_bShowAABB = evtData.m_bSwitcher;
		break;

	case CMD_EDITMODE_OBJECTS:
        m_SettingsMode = SETMODE_NONE;
        m_pPickedActor = NULL;
        m_vCurRotation = Vec3(0, 0, 0);
        m_vCurScaling = Vec3(1, 1, 1);
		if (m_CurModelAlias.empty())
			SetNewCurrentNodeForPlacement(NULL, OG_ACTOR_NONE);
		else
			SetNewCurrentNodeForPlacement(m_CurModelAlias.c_str(), m_CurActorType);
		break;

	case CMD_EDITMODE_ADJUST:
        m_SettingsMode = SETMODE_NONE;
        m_vCurRotation = Vec3(0, 0, 0);
        m_vCurScaling = Vec3(1, 1, 1);
        m_pPickedActor = NULL;
		SetNewCurrentNodeForPlacement(NULL, OG_ACTOR_NONE);
		break;

	case CMD_EDITMODE_SETTINGS:
        m_SettingsMode = SETMODE_NONE;
        m_vCurRotation = Vec3(0, 0, 0);
        m_vCurScaling = Vec3(1, 1, 1);
        m_pPickedActor = NULL;
		SetNewCurrentNodeForPlacement(NULL, OG_ACTOR_NONE);
		break;

    case CMD_LEVEL_SAVE:
        GetLevelManager()->SaveLevel(m_pCurLevel);
        break;

	case CMD_SETTINGSMODE_LEVSTART:
        m_SettingsMode = SETMODE_LEVEL_START;
        break;

	case CMD_SETTINGSMODE_LEVFINISH:
        m_SettingsMode = SETMODE_LEVEL_FINISH;
        break;
	}
	Refresh ();
}


/// @brief Setup camera.
void CEditorCanvas::SetupCamera()
{
    Vec3 vTarget (200, 0, -100);
	Vec3 vDir (0, 1.0f, 0.4f);
	vDir = vDir.normalize();
	Vec3 vUp = vDir.cross (Vec3(0, 1, 0));
	GetSceneGraph()->GetCamera()->Setup (vTarget + (vDir* m_fCameraDistance), vTarget, vUp);
}


/// @brief Render scene helpers.
void CEditorCanvas::RenderHelpers()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_mView.f);
    glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	if (m_bShowAABB)
	{
        if (m_pCurActor)
        {
            DrawOBB(m_pCurActor->GetPhysicalObject()->GetOBB());
        }
	}

    if (m_pPickedActor)
    {
        DrawOBB(m_pPickedActor->GetPhysicalObject()->GetOBB());
    }

	if (m_bIntersectionFound && m_bRedrawPatch)
	{
		DrawPatchGrid (1, &m_vIntersection);
		m_bRedrawPatch = false;
	}

    if (m_pCurLevel)
    {
		DrawLevelRanges(m_pCurLevel->GetStartPosition(),
			m_pCurLevel->GetFinishPosition(),
            m_pCurLevel->GetActiveWidth(),
			m_fAirBotHeight);
    }

    glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
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

    Vec3 vPick = GetPickRay (mouse_x, mouse_y);
    Vec3 vPos = GetSceneGraph()->GetCamera()->GetPosition();
    Vec3 vVec = vPick - vPos;
    vVec.normalize();

    ToolSettings* pTool = GetToolSettings();
    switch (pTool->GetEditMode())
    {
    case EDITMODE_OBJECTS:
        {
            if (m_pCurLevel)
            {
                m_bIntersectionFound = m_pCurLevel->GetTerrain()->GetRayIntersection(vPos, vVec, &m_vIntersection);
                if (m_bIntersectionFound && m_pCurActor)
                {
                    if (m_CurActorType == OG_ACTOR_AIRBOT || m_CurActorType == OG_ACTOR_PLAYER)
                    {
                        m_vIntersection.y = m_fAirBotHeight;
                    }
                    GetActorManager()->AddActor (m_pCurActor);
                    m_pCurActor = GetActorManager()->CreateActor(
                        OG_ACTOR_STATIC, 
                        m_CurModelAlias.c_str(), 
                        m_vIntersection, 
                        m_vCurRotation, 
                        m_vCurScaling);
                }
            }
        }
        break;

    case EDITMODE_ADJUST:
        {
            m_pPickedActor = GetActorManager()->GetNearestIntersectedActor(vPos, vVec);
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
	GetSceneGraph()->GetCamera()->Move ((float)delta / 10.0f);
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
				SetNewCurrentNodeForPlacement(evtData.m_Resource, (int)actor_type);
			}
			else
			{
				SetNewCurrentNodeForPlacement(NULL, (int)OG_ACTOR_NONE);
			}
        }
		break;
	}

	Refresh();
}


/// @brief Setup new current node for placement.
void CEditorCanvas::SetNewCurrentNodeForPlacement(const char* _pModelAlias, int _ActorType)
{
	OG_SAFE_DELETE(m_pCurActor);
	m_CurActorType = OG_ACTOR_NONE;

	if (_pModelAlias != NULL && _ActorType != (int)OG_ACTOR_NONE)
	{
        m_vCurScaling.x = m_vCurScaling.y = m_vCurScaling.z = 1;
        m_vCurRotation.x = m_vCurRotation.y = m_vCurRotation.z = 0;
		m_CurActorType = (OGActorType)_ActorType;
		m_CurModelAlias = std::string(_pModelAlias);

		m_pCurActor = GetActorManager()->CreateActor(
            m_CurActorType, 
            m_CurModelAlias,
            Vec3(0,0,0), 
            Vec3(0,0,0), 
            Vec3(1,1,1));
	}
}
