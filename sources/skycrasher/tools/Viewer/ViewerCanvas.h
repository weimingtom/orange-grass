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
#ifndef VIEWERCANVAS_H_
#define VIEWERCANVAS_H_

#include "wx/glcanvas.h"
#include <ToolFramework.h>


/// @brief Viewer canvas class.
class CViewerCanvas: public wxGLCanvas
{
    friend class CViewerFrame;

public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param id - window ID.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    /// @param name - window name.
    CViewerCanvas(  wxWindow *parent, 
                    wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0, 
                    const wxString& name = _T("CViewerCanvas") );

    /// @brief Destructor.
    virtual ~CViewerCanvas();

private:

    /// @brief Paint handler.
    /// @param event - event structute.
    void OnPaint(wxPaintEvent& event);

    /// @brief Resizing handler.
    /// @param event - event structute.
    void OnSize(wxSizeEvent& event);

    /// @brief Erase background handler.
    /// @param event - event structute.
    void OnEraseBackground(wxEraseEvent& event) {}

    /// @brief Key down handler.
    /// @param event - event structute.
    void OnKeyDown(wxKeyEvent& event);

    /// @brief Key up handler.
    /// @param event - event structute.
    void OnKeyUp(wxKeyEvent& event);

    /// @brief Render.
    void Render();

	/// @brief Resource switching event handler
    /// @param event - event structute.
	void OnResourceSwitch ( CommonToolEvent<ResSwitchEventData>& event );

	/// @brief Tool command event handler
    /// @param event - event structute.
	void OnToolCmdEvent ( CommonToolEvent<ToolCmdEventData>& event );

	/// @brief Material adjust event handler
    /// @param event - event structute.
	void OnMaterialAdjust ( CommonToolEvent<MtlAdjustEventData>& event );

    /// @brief Timer handler.
    /// @param event - event structute.
    void OnTimer(wxTimerEvent& event);

    /// @brief Mouse enter handler.
    /// @param event - event structute.
    void OnMouseEnter(wxMouseEvent& event);

    /// @brief Mouse leave handler.
    /// @param event - event structute.
    void OnMouseLeave(wxMouseEvent& event);

    /// @brief Mouse move handler.
    /// @param event - event structute.
    void OnMouseMove(wxMouseEvent& event);

    /// @brief Mouse Left button up handler.
    /// @param event - event structute.
    void OnLMBUp(wxMouseEvent& event);

    /// @brief Mouse Left button up handler.
    /// @param event - event structute.
    void OnLMBDown(wxMouseEvent& event);

    /// @brief Mouse Right button up handler.
    /// @param event - event structute.
    void OnRMBUp(wxMouseEvent& event);

    /// @brief Mouse Right button up handler.
    /// @param event - event structute.
    void OnRMBDown(wxMouseEvent& event);

	/// @brief Mouse wheel handler.
	/// @param event - event structute.
	void OnMouseWheel(wxMouseEvent& event);

private:

    bool	m_init;
	bool	m_bLoaded;
    long    m_Key;
	int		m_ResX;
	int		m_ResY;

    wxTimer m_timer;

    DECLARE_EVENT_TABLE()
};

#endif