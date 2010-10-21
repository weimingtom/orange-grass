/*
 *  GameSystem.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "GameSystem.h"
#include "OrangeGrass.h"
#include "StartMenuScreenController.h"
#include "LoadScreenController.h"
#include "GameScreenController.h"


///	@brief Constructor.
CGameSystem::CGameSystem () :   m_pStartMenuScreen(NULL),
								m_pLoadScreen(NULL),
                                m_pGameScreen(NULL),
                                m_pCurScreen(NULL)
{
    m_State = SYSSTATE_ACTIVE;
    m_pStartMenuScreen = new CStartMenuScreenController();
    m_pLoadScreen = new CLoadScreenController();
    m_pGameScreen = new CGameScreenController();

	m_ScreenSequence.push_back(m_pStartMenuScreen);
	m_ScreenSequence.push_back(m_pLoadScreen);
	m_ScreenSequence.push_back(m_pGameScreen);

	m_CurModel = -1;

	ChangeModel(1, 0, 0);
}


///	@brief Destructor.
CGameSystem::~CGameSystem ()
{
    OG_SAFE_DELETE(m_pStartMenuScreen);
    OG_SAFE_DELETE(m_pLoadScreen);
    OG_SAFE_DELETE(m_pGameScreen);
    m_pCurScreen = NULL;
}


///	@brief Exit from the program.
void CGameSystem::Exit ()
{
	m_pGameScreen = NULL;
    m_State = SYSSTATE_EXIT;
}


///	@brief Change screen model.
/// @param _Model screen model id.
/// @param _Param screen model parameter #1.
/// @param _Param2 screen model parameter #2.
void CGameSystem::ChangeModel ( int _Model, int _Param, int _Param2 )
{
	switch (_Model)
	{
	case 1:
		{
			if (m_CurModel >= (int)m_ScreenSequence.size() - 1)
			{
				m_CurModel = -1;
			}
			++m_CurModel;
			m_pCurScreen = m_ScreenSequence[m_CurModel];
			if (m_pCurScreen->Init())
			{
				m_pCurScreen->Activate();
			}
			else
			{
				ChangeModel(-1, 0, 0);
				return;
			}
		}
		break;

	case -1:
		{
			if (m_CurModel <= 0)
			{
				Exit();
				return;
			}
			else
			{
				--m_CurModel;
				m_pCurScreen = m_ScreenSequence[m_CurModel];
				if (m_pCurScreen->Init())
				{
					m_pCurScreen->Activate();
				}
				else
				{
					ChangeModel(-1, 0, 0);
					return;
				}
			}
		}
		break;
	}
}


///	@brief Update screen model.
/// @param _ElapsedTime frame elapsed time in msec.
void CGameSystem::Update ( unsigned long _ElapsedTime )
{
    if (!m_pCurScreen)
        return;

    m_pCurScreen->Update (_ElapsedTime);
    ControllerState state = m_pCurScreen->GetState();
	switch (state)
	{
	case CSTATE_INACTIVE:
        ChangeModel(1, 0, 0);
		break;

	case CSTATE_FAILED:
        ChangeModel(-1, 0, 0);
		break;

	default:
		break;
	}
}


///	@brief Draw screen model.
void CGameSystem::Draw ()
{
    if (!m_pCurScreen)
        return;
    m_pCurScreen->RenderScene();
}


///	@brief Get state of the game controller.
/// @return return code.
SystemState CGameSystem::GetControllerState () const
{
    return m_State;
}


///	@brief Key press handler.
/// @param _KeyCode key code.
void CGameSystem::OnKeyDown ( int _KeyCode )
{
}


///	@brief Key release handler.
/// @param _KeyCode key code.
void CGameSystem::OnKeyUp ( int _KeyCode )
{
}


///	@brief Pointing device press handler.
/// @param _X x coordinate.
/// @param _Y y coordinate.
void CGameSystem::OnPointerDown ( int _X, int _Y )
{
	GetInput()->OnPointerDown(_X, _Y);
}


///	@brief Pointing device release handler.
/// @param _X x coordinate.
/// @param _Y y coordinate.
void CGameSystem::OnPointerUp ( int _X, int _Y )
{
	GetInput()->OnPointerUp(_X, _Y);
}


///	@brief Pointing device move handler.
/// @param _X x coordinate.
/// @param _Y y coordinate.
void CGameSystem::OnPointerMove ( int _X, int _Y )
{
	GetInput()->OnPointerMove(_X, _Y);
}


///	@brief Resetting game state.
void CGameSystem::ResetGameState ()
{
}


///	@brief Saving game state.
void CGameSystem::SaveGameState ()
{
}


///	@brief Loading game state.
void CGameSystem::LoadGameState ()
{
}
