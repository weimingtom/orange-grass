#ifndef VIEWER_H_
#define VIEWER_H_

class CViewerFrame;

/// @brief Application class.
class CViewerApp: public wxApp
{
public:

    /// @brief Initializing handler.
    /// @return true if success
    bool OnInit();

    /// @brief Destroying handler.
    /// @return code
    int OnExit();

private:

    CViewerFrame* m_pFrame;
};


#endif

