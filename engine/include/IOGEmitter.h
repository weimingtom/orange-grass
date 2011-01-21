/*
 *  IOGEmitter.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGEMITTER_H_
#define IOGEMITTER_H_

#include "Mathematics.h"
#include "IOGRenderer.h"
#include "IOGRenderable.h"
#include "IOGSettingsReader.h"
#include <vector>
#include <string>
#include <map>


enum OGEffectStatus
{
	OG_EFFECTSTATUS_INACTIVE,
	OG_EFFECTSTATUS_STARTED,
	OG_EFFECTSTATUS_STOPPED
};

enum OGEmitterType
{
	OG_EMITTER_NO = 0,
	OG_EMITTER_ANIMATEDBB,
	OG_EMITTER_GLOW,
	OG_EMITTER_LIGHTFLASH,
	OG_EMITTER_PARTICLECHAIN,
	OG_EMITTER_PULSEGLOW,
	OG_EMITTER_RINGWAVE,
	OG_EMITTER_ROTATINGSPARKS,
	OG_EMITTER_SCROLLINGRAY,
	OG_EMITTER_TRAIL
};


typedef std::map<std::string, std::string*>		TStringParamList;
typedef std::map<std::string, unsigned int*>	TIntParamList;
typedef std::map<std::string, float*>			TFloatParamList;
typedef std::map<std::string, Vec4*>			TColorParamList;


class IOGEmitter
{
public:
    virtual ~IOGEmitter() {}

	// Initialize emitter.
	virtual void Init (IOGGroupNode* _pNode) = 0;

	// Update.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Update position.
	virtual void UpdatePosition (const Vec3& _vPosition) = 0;

	// Set start and finish positions.
    virtual void SetStartFinishPositions (const Vec3& _vStartPos, const Vec3& _vFinishPos) = 0;

	// Set direction.
    virtual void SetDirection (const Vec3& _vDir) = 0;

	// Render.
	virtual void Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight) = 0;

	// Start.
	virtual void Start () = 0;

	// Stop.
	virtual void Stop () = 0;

	// Is dynamic.
	virtual bool IsDynamic () const = 0;

	// Get effect run status.
	virtual OGEffectStatus GetStatus() const = 0;

	// get all string params.
	virtual TStringParamList& GetStringParams () = 0;

	// get all int params.
	virtual TIntParamList& GetIntParams () = 0;

	// get all float params.
	virtual TFloatParamList& GetFloatParams () = 0;

	// get all color params.
	virtual TColorParamList& GetColorParams () = 0;

	// set string parameter.
	virtual void SetStringParam (const std::string& _Alias, std::string* _pValue) = 0;

	// set int parameter.
	virtual void SetIntParam (const std::string& _Alias, unsigned int* _pValue) = 0;

	// set float parameter.
	virtual void SetFloatParam (const std::string& _Alias, float* _pValue) = 0;

	// set color parameter.
	virtual void SetColorParam (const std::string& _Alias, Vec4* _pValue) = 0;

	// get string parameter.
	virtual std::string* GetStringParam (const std::string& _Alias) = 0;

	// get int parameter.
	virtual unsigned int* GetIntParam (const std::string& _Alias) = 0;

	// get float parameter.
	virtual float* GetFloatParam (const std::string& _Alias) = 0;

	// get color parameter.
	virtual Vec4* GetColorParam (const std::string& _Alias) = 0;

	// Get effect type.
	virtual OGEmitterType GetType() const = 0;

	// Get effect type.
    virtual const std::string& GetAlias() const = 0;
};

#endif
