/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#include <wx/wx.h>
#include "EditorCanvas.h"
#include "EditorLevelScene.h"
#include <OrangeGrass.h>


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
OGVec3		m_vIntersection;
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
	m_timer.Start(33);

	bRmb = bLmb = false;
	mouse_x = mouse_y = 0;

	m_bMouseInWindow = true;
	m_bMouseMoved = false;
	m_bIntersectionFound = false;

	m_SettingsMode = SETMODE_NONE;
	m_pToolSettings = GetToolSettings();
	g_pScene->SetViewport(size.x, size.y);
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
}


/// @brief Timer handler.
/// @param event - event structute.
void CEditorCanvas::OnTimer(wxTimerEvent& event)
{
	if (m_bMouseMoved)
	{
		m_bIntersectionFound = g_pScene->GetTerrainIntersection(m_vIntersection, mouse_x, mouse_y);

		switch (m_pToolSettings->GetEditMode())
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
	}

    g_pScene->Init();
    g_pScene->Update(33);
    g_pScene->RenderScene();

	SwapBuffers();
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
        //SetCurrent();
		g_pScene->SetViewport(m_ResX, m_ResY);
    }
}


/// @brief Erase background handler.
/// @param event - event structute.
void CEditorCanvas::OnEraseBackground(wxEraseEvent& event) 
{
}


/// @brief Level load event handler
/// @param event - event structute.
void CEditorCanvas::OnLevelLoadEvent ( CommonToolEvent<LevelLoadEventData>& event )
{
	g_pScene->LoadLevel(std::string(event.GetEventCustomData().m_Path));
	m_pToolSettings->SetLevel((void*)g_pScene->GetLevel());
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
			g_pScene->UpdatePickedActorPosition(OGVec3(0.0f,0.0f,-1.0f));
        }
        else
			g_pScene->CameraMove(0.0f, -1.0f);
		m_bMouseMoved = true;
        break;

	case WXK_DOWN:
        if (event.ControlDown())
        {
			g_pScene->UpdatePickedActorPosition(OGVec3(0.0f,0.0f,1.0f));
        }
        else
    		g_pScene->CameraMove(0.0f, 1.0f);
		m_bMouseMoved = true;
        break;

	case WXK_LEFT:
        if (event.ControlDown())
        {
			if (m_pToolSettings->GetEditMode() == EDITMODE_SETTINGS)
			{
				g_pScene->UpdateLevelActiveWidth(-1.0f);
			}
			else
			{
				g_pScene->UpdatePickedActorPosition(OGVec3(-1.0f,0.0f,0.0f));
			}
        }
        else
    		g_pScene->CameraMove(-1.0f, 0.0f);
		m_bMouseMoved = true;
        break;

	case WXK_RIGHT:
        if (event.ControlDown())
        {
			if (m_pToolSettings->GetEditMode() == EDITMODE_SETTINGS)
			{
				g_pScene->UpdateLevelActiveWidth(1.0f);
			}
			else
			{
				g_pScene->UpdatePickedActorPosition(OGVec3(1.0f,0.0f,0.0f));
			}
        }
        else
    		g_pScene->CameraMove(1.0f, 0.0f);
		m_bMouseMoved = true;
        break;

    case WXK_PAGEUP:
		if (event.ControlDown())
		{
			g_pScene->UpdatePickedActorPosition(OGVec3(0.0f,1.0f,0.0f));
		}
        break;

    case WXK_PAGEDOWN:
		if (event.ControlDown())
		{
			g_pScene->UpdatePickedActorPosition(OGVec3(0.0f,-1.0f,0.0f));
		}
        break;

    case WXK_DELETE:
		g_pScene->DeletePickedActor();
        break;

    case WXK_ESCAPE:
        m_SettingsMode = SETMODE_NONE;
		GetToolSettings()->SetEditMode(EDITMODE_ADJUST);
		g_pScene->SetEditMode(EDITMODE_ADJUST);
        break;

    case 'D':
		g_pScene->UpdateSelectedActorRotation(OGVec3(0.0f,1.0f,0.0f), event.ControlDown());
        break;

    case 'A':
		g_pScene->UpdateSelectedActorRotation(OGVec3(0.0f,-1.0f,0.0f), event.ControlDown());
        break;

    case 'W':
		g_pScene->UpdateSelectedActorRotation(OGVec3(1.0f,0.0f,0.0f), event.ControlDown());
        break;

    case 'S':
		g_pScene->UpdateSelectedActorRotation(OGVec3(-1.0f,0.0f,0.0f), event.ControlDown());
        break;

    case 'E':
		g_pScene->UpdateSelectedActorRotation(OGVec3(0.0f,0.0f,1.0f), event.ControlDown());
        break;

    case 'Q':
		g_pScene->UpdateSelectedActorRotation(OGVec3(0.0f,0.0f,-1.0f), event.ControlDown());
        break;

    case 'Z':
		g_pScene->UpdateSelectedActorScaling(-1.0f, event.ControlDown());
        break;

    case 'X':
		g_pScene->UpdateSelectedActorScaling(1.0f, event.ControlDown());
        break;

    case 'C':
		g_pScene->ResetSelectedActorTansform();
        break;
    }

	mouse_x = event.GetX();
	mouse_y = event.GetY();
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
		g_pScene->SetAABBMode(evtData.m_bSwitcher);
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
        break;

	case CMD_VIEW_EDITOR:
        g_pScene->CameraMode(CAMMODE_EDITOR);
        break;

	case CMD_VIEW_GAME:
        g_pScene->CameraMode(CAMMODE_GAME);
        break;
	}
}


/// @brief Mouse enter handler.
/// @param event - event structute.
void CEditorCanvas::OnMouseEnter(wxMouseEvent& event)
{
    SetFocus();
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

    switch (m_pToolSettings->GetEditMode())
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
}


/// @brief Resource switching event handler
/// @param event - event structute.
void CEditorCanvas::OnResourceSwitch ( CommonToolEvent<ResSwitchEventData>& event )
{
	const ResSwitchEventData& evtData = event.GetEventCustomData();
    switch (evtData.m_pItem->type)
	{
	case RESTYPE_MODEL:
        {
            g_pScene->SetNewCurrentNodeForPlacement(evtData.m_pItem->name);
        }
		break;
	}
}
