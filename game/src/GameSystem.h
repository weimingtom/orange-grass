/*
 *  GameSystem.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef GAMESYSTEM_H_
#define GAMESYSTEM_H_

#include "IScreenController.h"
#include <vector>
#include "IOGResourceMgr.h"
#include "IOGGlobalVarsTable.h"


enum SystemState
{
    SYSSTATE_ACTIVE,
    SYSSTATE_EXIT
};


class CGameSystem
{
public:
    ///	@brief Constructor.
	CGameSystem ();

	///	@brief Destructor.
	virtual ~CGameSystem ();

	///	@brief Exit from the program.
	virtual void Exit ();

	///	@brief Change screen model.
    /// @param _Model screen model id.
    /// @param _Param screen model parameter #1.
    /// @param _Param2 screen model parameter #2.
	virtual void ChangeModel ( int _Model, int _Param, int _Param2 = -1 );

	///	@brief Update screen model.
    /// @param _ElapsedTime frame elapsed time in msec.
	virtual void Update ( unsigned long _ElapsedTime );

	///	@brief Draw screen model.
	virtual void Draw ();

	///	@brief Get state of the game controller.
    /// @return return code.
	virtual SystemState GetControllerState () const;

	///	@brief Key press handler.
    /// @param _KeyCode key code.
	virtual void OnKeyDown ( int _KeyCode );

	///	@brief Key release handler.
    /// @param _KeyCode key code.
	virtual void OnKeyUp ( int _KeyCode );

	///	@brief Pointing device press handler.
    /// @param _X x coordinate.
    /// @param _Y y coordinate.
	virtual void OnPointerDown ( int _X, int _Y );

	///	@brief Pointing device release handler.
    /// @param _X x coordinate.
    /// @param _Y y coordinate.
	virtual void OnPointerUp ( int _X, int _Y );

	///	@brief Pointing device move handler.
    /// @param _X x coordinate.
    /// @param _Y y coordinate.
	virtual void OnPointerMove ( int _X, int _Y );
    
	///	@brief Accelerometer handler.
    /// @param _X x coordinate.
    /// @param _Y y coordinate.
    /// @param _Z z coordinate
	virtual void OnAccelerometer ( float _X, float _Y, float _Z );
    
	///	@brief Resetting game state.
	virtual void ResetGameState ();

	///	@brief Saving game state.
	virtual void SaveGameState ();

	///	@brief Loading game state.
	virtual void LoadGameState ();

private:

    SystemState         m_State;
    IScreenController*  m_pStartMenuScreen;
    IScreenController*  m_pLoadScreen;
    IScreenController*  m_pGameScreen;
    IScreenController*  m_pCurScreen;

	std::vector<IScreenController*>	m_ScreenSequence;
	int								m_CurModel;

	IOGGlobalVarsTable* m_pGlobalVars;
	IOGResourceMgr*	    m_pResourceMgr;
	float			    m_fFOV;
	float			    m_fZNear;
	float			    m_fZFar;
	int				    m_ScrWidth;
	int				    m_ScrHeight;
};


#endif