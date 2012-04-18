#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <string>
#include "Game.h"


IOGGameSystem* pGameSystem = NULL;


void finishGame()
{
	OG_LOG_INFO("Finishing game core.");
	FinishGameCore();
	OG_LOG_INFO("Finishing engine.");
	FinishOrangeGrass();
	pGameSystem = NULL;
	OG_LOG_INFO("Game finished, all subsystems are stopped.");
}


bool setupGraphics(int w, int h, const char* assetsPath)
{
	if (pGameSystem)
	{
		finishGame();
	}

	OG_LOG_INFO("Starting game with: Width = [%d], Height = [%d], asset path = [%s]", w, h, assetsPath);

	StartOrangeGrass(assetsPath, true);
	StartGameCore();

	IOGGlobalVarsTable* pGlobalVars = GetGlobalVars();
	if (pGlobalVars)
	{
	    pGlobalVars->SetIVar("view_width", w);
	    pGlobalVars->SetIVar("view_height", h);
	}
	else
	{
		OG_LOG_ERROR("Cannot start game - global vars table was not created.");
		return false;
	}

	pGameSystem = GetGame();
	if (pGameSystem == NULL)
	{
		OG_LOG_ERROR("Cannot start game - game system was not created.");
		return false;
	}

    glViewport(0, 0, w, h);
    glDisable(GL_CULL_FACE);
    return true;
}


void renderFrame()
{
	if (pGameSystem)
	{
		if (pGameSystem->GetControllerState() != SYSSTATE_EXIT)
		{
			pGameSystem->Update(33);
			pGameSystem->Draw();
		}
		else
		{
			finishGame();
		}
	}
}


void onTouchDown(float x, float y)
{
	if (pGameSystem)
	{
		pGameSystem->OnPointerDown((int)x, (int)y);
	}
}


void onTouchUp(float x, float y)
{
	if (pGameSystem)
	{
		pGameSystem->OnPointerUp((int)x, (int)y);
	}
}


void onAccelerometer(float x, float y)
{
	if (pGameSystem)
	{
		float fAccelSensivity = 2.0f;
		pGameSystem->OnAccelerometer(-x*fAccelSensivity, y*fAccelSensivity, 0);
	}
}


extern "C"
{
    JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_init(JNIEnv * env, jobject obj, jint width, jint height, jstring assetsPath);
    JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_ontouchdown(JNIEnv * env, jobject obj, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_ontouchup(JNIEnv * env, jobject obj, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_onaccel(JNIEnv * env, jobject obj, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_destroy(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_init(JNIEnv * env, jobject obj, jint width, jint height, jstring assetsPath)
{
	const char* str;
	jboolean isCopy;
	str = env->GetStringUTFChars(assetsPath, &isCopy);
    setupGraphics(width, height, str);
}

JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}

JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_ontouchdown(JNIEnv * env, jobject obj, jfloat x, jfloat y)
{
    onTouchDown(x, y);
}

JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_ontouchup(JNIEnv * env, jobject obj, jfloat x, jfloat y)
{
    onTouchUp(x, y);
}

JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_onaccel(JNIEnv * env, jobject obj, jfloat x, jfloat y)
{
    onAccelerometer(x, y);
}

JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_destroy(JNIEnv * env, jobject obj)
{
	OG_LOG_INFO("Destroying activity.");
	finishGame();
}
