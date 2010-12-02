/*
 *  OGEmitter.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTER_H_
#define OGEMITTER_H_

#include "IOGEffect.h"
#include "IOGTexture.h"
#include "IOGRenderer.h"
#include <vector>
#include <string>
#include <map>


struct EmitterIntParam
{
	unsigned int value;
	unsigned int min_value;
	unsigned int max_value;
};

struct EmitterFloatParam
{
	float value;
	float min_value;
	float max_value;
};


typedef std::map<std::string, std::string>			TStringParamList;
typedef std::map<std::string, EmitterIntParam>		TIntParamList;
typedef std::map<std::string, EmitterFloatParam>	TFloatParamList;
typedef std::map<std::string, Vec4>					TColorParamList;


class COGEmitter
{
public:
	COGEmitter();
	virtual ~COGEmitter();

	// Initialize emitter.
	virtual void Init() = 0;

	// Update.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Update position.
	virtual void UpdatePosition (const Vec3& _vPosition);

	// Render.
	virtual void Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight) = 0;

	// Start.
	virtual void Start () = 0;

	// Stop.
	virtual void Stop () = 0;

	// Get effect run status.
	virtual OGEffectStatus GetStatus() const;

	// get all string params.
	virtual const TStringParamList& GetStringParams () const { return m_StringParams; }

	// get all int params.
	virtual const TIntParamList& GetIntParams () const { return m_IntParams; }

	// get all float params.
	virtual const TFloatParamList& GetFloatParams () const { return m_FloatParams; }

	// get all color params.
	virtual const TColorParamList& GetColorParams () const { return m_ColorParams; }

	// get string parameter.
	virtual std::string GetStringParam (const std::string& _Alias) const;

	// set string parameter.
	virtual void SetStringParam (const std::string& _Alias, const std::string& _Value);

	// get int parameter.
	virtual unsigned int GetIntParam (const std::string& _Alias) const;

	// set int parameter.
	virtual void SetIntParam (const std::string& _Alias, unsigned int _Value);

	// get float parameter.
	virtual float GetFloatParam (const std::string& _Alias) const;

	// set float parameter.
	virtual void SetFloatParam (const std::string& _Alias, float _Value);

	// get color parameter.
	virtual Vec4 GetColorParam (const std::string& _Alias) const;

	// set color parameter.
	virtual void SetColorParam (const std::string& _Alias, const Vec4& _Value);

protected:

	// add string param.
	void AddStringParam (const std::string& _Alias, const std::string& _Value);

	// add int param.
	void AddIntParam (const std::string& _Alias, unsigned int _Value, unsigned int _Min, unsigned int _Max);

	// add float param.
	void AddFloatParam (const std::string& _Alias, float _Value, float _Min, float _Max);

	// add color param.
	void AddColorParam (const std::string& _Alias, const Vec4& _Value);

protected:

	Vec3						m_vPrevPosition;
	Vec3						m_vCurPosition;
	bool						m_bPositionUpdated;
	IOGMapping*					m_pMapping;
	OGEffectStatus				m_Status;
	IOGTexture*					m_pTexture;
	OGBlendType					m_Blend;
	IOGRenderer*				m_pRenderer;

	TStringParamList			m_StringParams;
	TIntParamList				m_IntParams;
	TFloatParamList				m_FloatParams;
	TColorParamList				m_ColorParams;
};


#endif