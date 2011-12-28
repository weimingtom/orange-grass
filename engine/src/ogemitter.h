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
#include "IOGEmitter.h"


class COGEmitter : public IOGEmitter
{
public:
	COGEmitter();
	virtual ~COGEmitter();

	// Initialize emitter.
	virtual void Init (IOGGroupNode* _pNode) = 0;

	// Update.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Update position.
	virtual void UpdatePosition (const OGVec3& _vPosition);

	// Set start and finish positions.
    virtual void SetStartFinishPositions (const OGVec3& _vStartPos, const OGVec3& _vFinishPos) {}

	// Set direction.
    virtual void SetDirection (const OGVec3& _vDir);

	// Render.
	virtual void Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight) = 0;

	// Start.
	virtual void Start () = 0;

	// Stop.
	virtual void Stop () = 0;

	// Is dynamic.
	virtual bool IsDynamic () const {return false;}

	// Get effect run status.
	virtual OGEffectStatus GetStatus() const;

	// Get effect type.
	virtual OGEmitterType GetType() const = 0;

	// Get effect type.
    virtual const std::string& GetAlias() const = 0;

	// get all string params.
	virtual TStringParamList& GetStringParams () { return m_StringParams; }

	// get all int params.
	virtual TIntParamList& GetIntParams () { return m_IntParams; }

	// get all float params.
	virtual TFloatParamList& GetFloatParams () { return m_FloatParams; }

	// get all color params.
	virtual TColorParamList& GetColorParams () { return m_ColorParams; }

	// set string parameter.
	virtual void SetStringParam (const std::string& _Alias, std::string* _pValue);

	// set int parameter.
	virtual void SetIntParam (const std::string& _Alias, unsigned int* _pValue);

	// set float parameter.
	virtual void SetFloatParam (const std::string& _Alias, float* _pValue);

	// set color parameter.
	virtual void SetColorParam (const std::string& _Alias, OGVec4* _pValue);

	// get string parameter.
	virtual std::string* GetStringParam (const std::string& _Alias);

	// get int parameter.
	virtual unsigned int* GetIntParam (const std::string& _Alias);

	// get float parameter.
	virtual float* GetFloatParam (const std::string& _Alias);

	// get color parameter.
	virtual OGVec4* GetColorParam (const std::string& _Alias);

protected:

	// add string param.
	void AddStringParam (const std::string& _Alias, std::string* _pValue);

	// add int param.
	void AddIntParam (const std::string& _Alias, unsigned int* _pValue);

	// add float param.
	void AddFloatParam (const std::string& _Alias, float* _pValue);

	// add color param.
	void AddColorParam (const std::string& _Alias, OGVec4* _pValue);

	// Load parameters of the emitter.
	void LoadParams (IOGGroupNode* _pNode);

	// Save parameters of the emitter.
	void SaveParams (IOGGroupNode* _pNode);

protected:

	OGVec3						m_vPrevPosition;
	OGVec3						m_vCurPosition;
	OGVec3			            m_Direction;
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