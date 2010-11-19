#ifndef EFFECTVIEWERCANVAS_H_
#define EFFECTVIEWERCANVAS_H_

#include "wx/glcanvas.h"
#include <ToolFramework.h>


/// @brief EffectViewer canvas class.
class CEffectViewerCanvas: public wxGLCanvas
{
    friend class CEffectViewerFrame;

public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param id - window ID.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    /// @param name - window name.
    CEffectViewerCanvas(  wxWindow *parent, 
                    wxWindowID id = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0, 
                    const wxString& name = _T("CEffectViewerCanvas") );

    /// @brief Destructor.
    virtual ~CEffectViewerCanvas();

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