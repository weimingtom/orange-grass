#import "GameSystem.h"
#import "Delegate.h"
#import "Accelerometer.h"
#import "TouchScreen.h"
#include "OrangeGrass.h"
#include "Game.h"


#define kFPS			33.0

static CGameSystem *shell = NULL;
static Accel *accel = NULL;
static int ScrWidth = 0;
static int ScrHeight = 0;
static bool Landscape = false;
static float AccelSensivity = 2.0f;


void GetResourcePathASCII(char* _pOutPath, int _PathLength)
{
    NSString* readPath = [[NSBundle mainBundle] resourcePath];
    [readPath getCString:_pOutPath maxLength:_PathLength encoding:NSASCIIStringEncoding];
}


@implementation AppController

- (void) update
{
    if (Landscape)
    {
        double vec[3];
        [accel GetAccelerometerVector: (double*)vec];
        shell->OnAccelerometer(
            (float)vec[1]*AccelSensivity, 
            (float)vec[0]*AccelSensivity, 
            (float)vec[2]*AccelSensivity);
        
        TouchScreenValues* pVals = GetValuesTouchScreen();
        if (pVals->CountTouchesBegan > 0)
        {
            float x = ScrWidth - pVals->LocationYTouchesBegan;
            float y = pVals->LocationXTouchesBegan;
            shell->OnPointerDown(x,y);
        }
        if (pVals->TouchesEnd)
        {
            float x = ScrWidth - pVals->LocationYTouchesEnded;
            float y = pVals->LocationXTouchesEnded;
            shell->OnPointerUp(x,y);
        }
    }
    else 
    {
        double vec[3];
        [accel GetAccelerometerVector: (double*)vec];
        shell->OnAccelerometer(
            (float)vec[0]*AccelSensivity, 
            (float)vec[1]*AccelSensivity, 
            (float)vec[2]*AccelSensivity);
        
        TouchScreenValues* pVals = GetValuesTouchScreen();
        if (pVals->CountTouchesBegan > 0)
        {
            float x = pVals->LocationXTouchesBegan;
            float y = pVals->LocationYTouchesBegan;
            shell->OnPointerDown(x,y);
        }
        if (pVals->TouchesEnd)
        {
            float x = pVals->LocationXTouchesEnded;
            float y = pVals->LocationYTouchesEnded;
            shell->OnPointerUp(x,y);
        }
    }
    
	shell->Update(33);
    shell->Draw();

	[_glView swapBuffers];
}


- (void) applicationDidFinishLaunching:(UIApplication*)application
{
	CGRect	rect = [[UIScreen mainScreen] bounds];
	
	// create a full-screen window
	_window = [[UIWindow alloc] initWithFrame:rect];
	
	// create the OpenGL view and add it to the window
	_glView = [[EAGLCameraView alloc] initWithFrame:rect pixelFormat:GL_RGB565 depthFormat:GL_DEPTH_COMPONENT16 preserveBackbuffer:NO];
	
	[_window addSubview:_glView];
    
	// show the window
	[_window makeKeyAndVisible];
    
    accel = [Accel alloc];
    [accel SetupAccelerometer: kFPS];
	
    char path[OG_MAX_PATH];
    GetResourcePathASCII(path, OG_MAX_PATH);
    StartOrangeGrass(path, false);
    StartGameCore();
	
	shell = new CGameSystem();
	if(!shell)
		printf("InitApplication error\n");

    GetGlobalVars()->SetIVar("view_width", (int)rect.size.width);
    GetGlobalVars()->SetIVar("view_height", (int)rect.size.height);
    GetGlobalVars()->SetIVar("landscape", 0);
    GetAppSettings()->Init("settings.xml");
    
    GetAppSettings()->InitScreenMode();
	ScrWidth = GetGlobalVars()->GetIVar("view_width");
	ScrHeight = GetGlobalVars()->GetIVar("view_height");
    Landscape = (GetGlobalVars()->GetIVar("landscape") == 1) ? true : false;
	
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, (int)rect.size.width, (int)rect.size.height);
    
	// create our rendering timer
	[NSTimer scheduledTimerWithTimeInterval:(1.0 / kFPS) target:self selector:@selector(update) userInfo:nil repeats:YES];
}


- (void)applicationWillTerminate:(UIApplication *)application
{
    if (shell) 
    {
        FinishGameCore();
		FinishOrangeGrass();
		
        delete shell;
        shell = NULL;
    }
}


- (void) dealloc
{
    [accel release];
	delete shell;
    shell = NULL;
    
	[_glView release];
	[_window release];
	
	[super dealloc];
}

@end
