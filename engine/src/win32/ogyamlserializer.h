/*
 *  OGYamlSerializer.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGYAMLSERIALIZER_H_
#define OGYAMLSERIALIZER_H_

#include "IOGSerializer.h"
#include <yaml.h>
#include <stdio.h>


class COGYamlSerializer : public IOGSerializer
{
public:
	COGYamlSerializer ();
	virtual ~COGYamlSerializer ();

	// create serializer to file.
	virtual bool Open (const std::string& _pFileName);

	// close serializer to file.
	virtual void Close ();

	// start serialization.
	virtual bool StartDoc ();

	// finish serialization.
	virtual bool FinishDoc ();

	// Serialize pair.
	virtual bool WritePair (const std::string& _Key, const std::string& _StrVal);

	// Serialize pair.
	virtual bool WritePair (const std::string& _Key, int _Val);

	// Serialize pair.
	virtual bool WritePair (const std::string& _Key, float _Val);

	// Serialize map.
	virtual bool StartMap ();

	// Serialize map.
	virtual bool FinishMap ();

	// Serialize sequence.
	virtual bool StartSeq ();

	// Serialize sequence.
	virtual bool FinishSeq ();

	// Serialize value.
	virtual bool WriteValue (const std::string& _StrVal);

	// Serialize value.
	virtual bool WriteValue (int _Val);

	// Serialize value.
	virtual bool WriteValue (float _Val);

private:

    yaml_emitter_t  m_Emitter;
    FILE*           m_pFile;
};

#endif
