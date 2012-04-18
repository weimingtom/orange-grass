/*
 *  IOGGameSystem.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGGAMESYSTEM_H_
#define IOGGAMESYSTEM_H_

#include "IOGScreenController.h"
#include <vector>


enum SystemState
{
    SYSSTATE_ACTIVE,
    SYSSTATE_EXIT
};


class IOGGameSystem
{
public:
    ///	@brief Destructor.
    virtual ~IOGGameSystem () {}

    ///	@brief Change screen model.
    /// @param _Model screen model id.
    /// @param _Param screen model parameter #1.
    /// @param _Param2 screen model parameter #2.
    virtual void ChangeModel ( int _Model, int _Param, int _Param2 = -1 ) = 0;

    ///	@brief Update screen model.
    /// @param _ElapsedTime frame elapsed time in msec.
    virtual void Update ( unsigned long _ElapsedTime ) = 0;

    ///	@brief Draw screen model.
    virtual void Draw () = 0;

    ///	@brief Get state of the game controller.
    /// @return return code.
    virtual SystemState GetControllerState () const = 0;

    ///	@brief Key press handler.
    /// @param _KeyCode key code.
    virtual void OnKeyDown ( int _KeyCode ) = 0;

    ///	@brief Key release handler.
    /// @param _KeyCode key code.
    virtual void OnKeyUp ( int _KeyCode ) = 0;

    ///	@brief Pointing device press handler.
    /// @param _X x coordinate.
    /// @param _Y y coordinate.
    virtual void OnPointerDown ( int _X, int _Y ) = 0;

    ///	@brief Pointing device release handler.
    /// @param _X x coordinate.
    /// @param _Y y coordinate.
    virtual void OnPointerUp ( int _X, int _Y ) = 0;

    ///	@brief Pointing device move handler.
    /// @param _X x coordinate.
    /// @param _Y y coordinate.
    virtual void OnPointerMove ( int _X, int _Y ) = 0;

    ///	@brief Accelerometer handler.
    /// @param _X x coordinate.
    /// @param _Y y coordinate.
    /// @param _Z z coordinate
    virtual void OnAccelerometer ( float _X, float _Y, float _Z ) = 0;

    ///	@brief Resetting game state.
    virtual void ResetGameState () = 0;

    ///	@brief Saving game state.
    virtual void SaveGameState () = 0;

    ///	@brief Loading game state.
    virtual void LoadGameState () = 0;
};


#endif
