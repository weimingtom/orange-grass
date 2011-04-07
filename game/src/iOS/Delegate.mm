#import "GameSystem.h"
#import "Delegate.h"
#import "Accelerometer.h"
#import "TouchScreen.h"
#include "OrangeGrass.h"


#define kFPS			33.0

static CGameSystem *shell = NULL;
static Accel *accel = NULL;
static int ScrWidth = 0;
static int ScrHeight = 0;
static bool Landscape = false;
static float AccelSensivity = 2.0f;


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
	
    glFlush();
	[_glView swapBuffers];
}


- (void) applicationDidFinishLaunching:(UIApplication*)application
{
	CGRect	rect = [[UIScreen mainScreen] bounds];
	
	// create a full-screen window
	_window = [[UIWindow alloc] initWithFrame:rect];
	
	// create the OpenGL view and add it to the window
	_glView = [[EAGLCameraView alloc] initWithFrame:rect pixelFormat:GL_RGB565_OES depthFormat:GL_DEPTH_COMPONENT16_OES preserveBackbuffer:NO];
	
	[_window addSubview:_glView];
    
	// show the window
	[_window makeKeyAndVisible];
    
    accel = [Accel alloc];
    [accel SetupAccelerometer: kFPS];
	
	StartOrangeGrass();
	
	shell = new CGameSystem();
	if(!shell)
		printf("InitApplication error\n");

	ScrWidth = GetGlobalVars()->GetIVar("view_width");
	ScrHeight = GetGlobalVars()->GetIVar("view_height");
    Landscape = (GetGlobalVars()->GetIVar("landscape") == 1) ? true : false;
	
	// create our rendering timer
	[NSTimer scheduledTimerWithTimeInterval:(1.0 / kFPS) target:self selector:@selector(update) userInfo:nil repeats:YES];
}


- (void)applicationWillTerminate:(UIApplication *)application
{
    if (shell) 
    {
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
