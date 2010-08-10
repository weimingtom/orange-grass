#include "main.h"
#include <OrangeGrass.h>
#include <IOGGraphicsHelpers.h>
#include <IOGMath.h>


MATRIX		m_mProjection;
MATRIX		m_mView;
IOGLevel*	m_pCurLevel = NULL;


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

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    MatrixPerspectiveFovRH(m_mProjection, 1.0f, float(SCR_WIDTH)/float(SCR_HEIGHT), 4.0f, 4500.0f, true);

    Vec3 vTarget (150, 0, -100);
	Vec3 vDir (0, 0.4f, 0.6f);
	vDir = vDir.normalize();
	Vec3 vUp = vDir.cross (Vec3(0, 1, 0));
	GetSceneGraph()->GetCamera()->Setup (vTarget + (vDir* 200.0f), vTarget, vUp);

    glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	GetSceneGraph()->GetLight()->SetDirection(Vec4(0.0f, 0.0f, 1.0f, 0.0f));
	GetSceneGraph()->GetLight()->SetColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	GetSceneGraph()->GetLight()->Apply();

    GetResourceMgr()->Init();
    GetLevelManager()->Init();

	std::vector<IOGResourceInfo> resInfo;
	if (GetResourceMgr()->Load(resInfo))
	{
	}

    m_pCurLevel = GetLevelManager()->LoadLevel(std::string("level_0"));
}


/// Application shutdown.
void Shutdown()
{
}


/// Application main cycle.
void Run ()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_mProjection.f);
	
	glMatrixMode(GL_MODELVIEW);
	m_mView = GetSceneGraph()->GetCamera()->Update();
	glLoadMatrixf(m_mView.f);

    GetPhysics()->Update(10);
    GetActorManager()->Update(10);

	if (m_pCurLevel)
        m_pCurLevel->GetTerrain()->Render(m_mView);

    GetSceneGraph()->Render(m_mView);

    glFlush();
    SwapBuffers(shDC);
}


/// Application window procedure.
LRESULT CALLBACK WndProc ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )
	{
		case WM_DESTROY:
			PostQuitMessage ( 0 );
     		break;

		case WM_KEYDOWN:
			break;

		case WM_KEYUP:
			break;

		case WM_LBUTTONUP:
        {
			sMouseX = (SHORT)LOWORD(lParam);
			sMouseX = (SHORT)HIWORD(lParam);
        }
        break;

		case WM_LBUTTONDOWN:
        {
			sMouseX = (SHORT)LOWORD(lParam);
			sMouseX = (SHORT)HIWORD(lParam);
        }
        break;

		case WM_MOUSEMOVE:
		{
			if ( wParam & MK_LBUTTON )
			{
                sMouseX = (SHORT)LOWORD(lParam);
                sMouseX = (SHORT)HIWORD(lParam);
			}
			else
				return DefWindowProc ( hWnd, message, wParam, lParam );
		}
		break;

		default:
			return DefWindowProc ( hWnd, message, wParam, lParam );
   }
   return 0;
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
	
	shWnd = CreateWindow (	L"AirAssault.MainWindow", L"AirAssault", WS_SYSMENU|WS_OVERLAPPED,
							(GetSystemMetrics(SM_CXSCREEN)-SCR_WIDTH)/2, 
							(GetSystemMetrics(SM_CYSCREEN)-SCR_HEIGHT)/2, 
							SCR_WIDTH, SCR_HEIGHT, NULL, NULL, hInstance, NULL);
	if ( !shWnd )
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
            Run ();
    }

	return (int)msg.wParam;
}
