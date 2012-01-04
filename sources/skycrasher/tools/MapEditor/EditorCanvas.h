#ifndef EDITORCANVAS_H_
#define EDITORCANVAS_H_

#include "wx/glcanvas.h"
#include <ToolFramework.h>


/// @brief Viewer canvas class.
class CEditorCanvas: public wxGLCanvas
{
    friend class CEditorFrame;

public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param id - window ID.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    /// @param name - window name.
    CEditorCanvas(  wxWindow *parent, 
                    wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0, 
                    const wxString& name = _T("CEditorCanvas") );

    /// @brief Destructor.
    virtual ~CEditorCanvas();

protected:

    /// @brief Paint handler.
    /// @param event - event structute.
    void OnPaint(wxPaintEvent& event);

    /// @brief Resizing handler.
    /// @param event - event structute.
    void OnSize(wxSizeEvent& event);

    /// @brief Erase background handler.
    /// @param event - event structute.
    void OnEraseBackground(wxEraseEvent& event);

    /// @brief Key down handler.
    /// @param event - event structute.
    void OnKeyDown(wxKeyEvent& event);

    /// @brief Key up handler.
    /// @param event - event structute.
    void OnKeyUp(wxKeyEvent& event);

    /// @brief Enter window handler.
    /// @param event - event structute.
    void OnEnterWindow(wxMouseEvent& event);

    /// @brief Render.
    void Render();

	/// @brief Tool command event handler
    /// @param event - event structute.
	void OnToolCmdEvent(CommonToolEvent<ToolCmdEventData>& event);

	/// @brief Level load event handler
    /// @param event - event structute.
	void OnLevelLoadEvent(CommonToolEvent<LevelLoadEventData>& event);

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

    /// @brief Resource switching event handler
    /// @param event - event structute.
    void OnResourceSwitch(CommonToolEvent<ResSwitchEventData>& event);

private:

    long    m_Key;
	int		m_ResX;
	int		m_ResY;

    wxTimer m_timer;

	bool	m_bMouseInWindow;
	bool	m_bMouseMoved;

    bool	bRmb;
    bool	bLmb;
    int		mouse_x; 
    int		mouse_y;

    SettingsMode    m_SettingsMode;
	ToolSettings*	m_pToolSettings;

    DECLARE_EVENT_TABLE()
};

#endif