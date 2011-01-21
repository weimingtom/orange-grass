#include "main.h"
#include "..\GameSystem.h"
#include "common.h"
#include "Timing.h"
#include "OrangeGrass.h"

#define TIMER_ID	1
#define TIMER_RATE	30


CGameSystem*    pGameSystem = NULL;
int				ScrWidth, ScrHeight;
std::vector<std::string> CmdParams;


/// Application initialization.
void Initialize ()
{
    GLuint PixelFormat;
    PIXELFORMATDESCRIPTOR pfd;
    memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion   = 1;
    pfd.dwFlags    = PFD_DRAW_TO_WINDOW |PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 16;
    pfd.cDepthBits = 16;
    shDC = GetDC( shWnd );
    PixelFormat = ChoosePixelFormat( shDC, &pfd );
    SetPixelFormat( shDC, PixelFormat, &pfd);
    shRC = wglCreateContext( shDC );
    wglMakeCurrent( shDC, shRC );
    glewInit();

    glViewport(0, 0, ScrWidth, ScrHeight);
    glDisable(GL_CULL_FACE);

    pGameSystem = new CGameSystem();
}


/// Application shutdown.
void Shutdown()
{
	OG_SAFE_DELETE(pGameSystem);
    PostQuitMessage(0);
}


/// Application window procedure.
LRESULT CALLBACK WndProc ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )
	{
		case WM_DESTROY:
			Shutdown();
     		break;

		case WM_KEYDOWN:
            if (wParam == VK_LEFT)
            {
                sMouseX -= 3;
            }
            else if (wParam == VK_RIGHT)
            {
                sMouseX += 3;
            }
            pGameSystem->OnPointerMove(sMouseX, sMouseY);
            //pGameSystem->OnKeyDown(0);
			break;

		case WM_KEYUP:
            //pGameSystem->OnKeyUp(0);
			break;

		case WM_LBUTTONUP:
        {
            bTouch = false;
            sTouchX = (SHORT)LOWORD(lParam);
            sTouchY = (SHORT)HIWORD(lParam);
            pGameSystem->OnPointerUp(sTouchX, sTouchY);
        }
        break;

		case WM_LBUTTONDOWN:
        {
            bTouch = true;
            sTouchX = (SHORT)LOWORD(lParam);
            sTouchY = (SHORT)HIWORD(lParam);
            pGameSystem->OnPointerDown(sTouchX, sTouchY);
            //int X = (SHORT)LOWORD(lParam);
            //int Y = (SHORT)HIWORD(lParam);
            //pGameSystem->OnPointerDown(X, Y);
        }
        break;

		case WM_MOUSEMOVE:
		{
            //sMouseX = (SHORT)LOWORD(lParam);
            //sMouseY = (SHORT)HIWORD(lParam);
            //pGameSystem->OnPointerMove(sMouseX, sMouseY);
		}
		break;

		default:
			return DefWindowProc ( hWnd, message, wParam, lParam );
   }
   return 0;
}


/// timer callback function
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if (idEvent == TIMER_ID)
	{
        if (pGameSystem->GetControllerState() != SYSSTATE_EXIT)
        {
            //pGameSystem->OnPointerMove(sMouseX, sMouseY);
            //if (bTouch)
            //{
            //    pGameSystem->OnPointerDown(sTouchX, sTouchY);
            //}
            pGameSystem->Update(33);
            pGameSystem->Draw();

            glFlush();
            SwapBuffers(shDC);
        }
        else
        {
            Shutdown();
        }
	}
}


/// Application window initialization.
BOOL InitInstance ( HINSTANCE hInstance, int nCmdShow )
{
	shInstance = hInstance;
	shWnd = FindWindow ( L"AirAssault.MainWindow", L"AirAssault" );

	if ( shWnd )
	{
		SetForegroundWindow ((HWND)(((__int64)shWnd) | 0x01));    
		return FALSE;
	} 

	GetAppSettings()->Init("settings.xml");

	if (CmdParams.size() == 2)
	{
		GetGlobalVars()->SetSVar("profile", CmdParams[0]);
		if (CmdParams[1].compare("l") == 0)
		{
			GetGlobalVars()->SetIVar("landscape", 1);
		}
		else
		{
			GetGlobalVars()->SetIVar("landscape", 0);
		}
	}

	GetAppSettings()->InitScreenMode();

	ScrWidth = GetGlobalVars()->GetIVar("view_width");
	ScrHeight = GetGlobalVars()->GetIVar("view_height");

	WNDCLASS	wc;
    wc.style			= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC) WndProc;
    wc.cbClsExtra		= 0;
    wc.cbWndExtra		= 0;
    wc.hInstance		= hInstance;
    wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
    wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName		= 0;
    wc.lpszClassName	= L"AirAssault.MainWindow";
	RegisterClass ( &wc );
	
    int wndSizeX = ScrWidth + (GetSystemMetrics(SM_CXBORDER) * 2);
    int wndSizeY = ScrHeight + GetSystemMetrics(SM_CYSIZE) + GetSystemMetrics(SM_CYBORDER);

	shWnd = CreateWindow (	L"AirAssault.MainWindow", L"AirAssault", WS_SYSMENU|WS_OVERLAPPED,
							(GetSystemMetrics(SM_CXSCREEN)-wndSizeX)/2, 
							(GetSystemMetrics(SM_CYSCREEN)-wndSizeY)/2, 
							wndSizeX, wndSizeY, NULL, NULL, hInstance, NULL);
	if ( !shWnd )
		return FALSE;

    if (SetTimer(shWnd, TIMER_ID,  TIMER_RATE,  (TIMERPROC)TimerProc)!=TIMER_ID ) 
        return FALSE;

	ShowWindow(shWnd, nCmdShow);	
	UpdateWindow(shWnd);

	Initialize ();

	return TRUE;
}


/// main function
int WINAPI WinMain( HINSTANCE hInstance, 
					HINSTANCE hPrevInstance, 
					LPSTR lpszCmdLine,
					int nCmdShow )
{
	char* pch;
	pch = strtok (lpszCmdLine, " -");
	while (pch != NULL)
	{
		CmdParams.push_back(std::string(pch));
		pch = strtok (NULL, " -");
	}

	if ( !InitInstance ( hInstance, nCmdShow ) ) 
		return FALSE;

	MSG msg;
    while( 1 )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            WaitMessage();
        }
    }

	return (int)msg.wParam;
}
