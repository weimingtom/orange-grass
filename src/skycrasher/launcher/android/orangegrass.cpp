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


bool setupGraphics(int w, int h, const char* assetsPath)
{
	StartOrangeGrass(assetsPath, true);
	StartGameCore();
	pGameSystem = GetGame();

    glViewport(0, 0, w, h);
    glDisable(GL_CULL_FACE);
    return true;
}


void renderFrame()
{
	if (pGameSystem && pGameSystem->GetControllerState() != SYSSTATE_EXIT)
	{
		pGameSystem->Update(33);
		pGameSystem->Draw();
	}
	else
	{
		OG_SAFE_DELETE(pGameSystem);
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


extern "C"
{
    JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_init(JNIEnv * env, jobject obj, jint width, jint height, jstring assetsPath);
    JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_ontouchdown(JNIEnv * env, jobject obj, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_skycrasher_launcher_android_OrangeGrassLib_ontouchup(JNIEnv * env, jobject obj, jfloat x, jfloat y);
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
