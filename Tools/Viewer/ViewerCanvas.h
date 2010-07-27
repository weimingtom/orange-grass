#ifndef VIEWERCANVAS_H_
#define VIEWERCANVAS_H_

#include "wx/glcanvas.h"
#include "wx/progdlg.h"
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

    /// @brief Initialize renderer.
    void InitGL();

    /// @brief Load next resource bulk.
    /// @return false if finished loading.
    bool LoadNextResource();

	/// @brief Resource switching event handler
    /// @param event - event structute.
	void OnResourceSwitch ( CommonToolEvent<ResSwitchEventData>& event );

	/// @brief Tool command event handler
    /// @param event - event structute.
	void OnToolCmdEvent ( CommonToolEvent<ToolCmdEventData>& event );

    /// @brief Timer handler.
    /// @param event - event structute.
    void OnTimer(wxTimerEvent& event);

    /// @brief Setup camera.
    void SetupCamera();

    /// @brief Render scene helpers.
    void RenderHelpers();

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

private:

    bool	m_init;
	bool	m_bLoaded;
    long    m_Key;
	int		m_ResX;
	int		m_ResY;

	//wxProgressDialog*	m_pLoadProgressDlg;
    wxTimer             m_timer;

	bool	m_bShowGrid;
	bool	m_bShowAABB;

    DECLARE_EVENT_TABLE()
};

#endif