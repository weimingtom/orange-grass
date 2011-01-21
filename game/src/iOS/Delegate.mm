#import "GameSystem.h"
#import "Delegate.h"
#import "Accelerometer.h"
#import "TouchScreen.h"


#define kFPS			33.0

static CGameSystem *shell = NULL;
static Accel *accel = NULL;


@implementation AppController

- (void) update
{
    double vec[3];
    [accel GetAccelerometerVector: (double*)vec];
    shell->OnPointerMove(vec[1]*50, vec[2]*50);
    
    TouchScreenValues* pVals = GetValuesTouchScreen();
    if (pVals->CountTouchesBegan > 0)
    {
        float x = 480.0f - pVals->LocationYTouchesBegan;
        float y = pVals->LocationXTouchesBegan;
        shell->OnPointerDown(x,y);
    }
    if (pVals->TouchesEnd)
    {
        float x = 480.0f - pVals->LocationYTouchesEnded;
        float y = pVals->LocationXTouchesEnded;
        shell->OnPointerUp(x,y);
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
	
	shell = new CGameSystem();
	if(!shell)
		printf("InitApplication error\n");
	
	// create our rendering timer
	[NSTimer scheduledTimerWithTimeInterval:(1.0 / kFPS) target:self selector:@selector(update) userInfo:nil repeats:YES];
}


- (void)applicationWillTerminate:(UIApplication *)application
{
    if (shell) 
    {
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
