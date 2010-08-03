/*
 *  IOGSerializer.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGSERIALIZER_H_
#define IOGSERIALIZER_H_

#include <string>


class IOGSerializer
{
public:
	virtual ~IOGSerializer () {}

	// create serializer to file.
    virtual bool Open (const std::string& _FileName) = 0;

	// close serializer to file.
	virtual void Close () = 0;

	// start serialization.
	virtual bool StartDoc () = 0;

	// finish serialization.
	virtual bool FinishDoc () = 0;

	// Serialize pair.
	virtual bool WritePair (const std::string& _Key, const std::string& _StrVal) = 0;

	// Serialize pair.
	virtual bool WritePair (const std::string& _Key, int _Val) = 0;

	// Serialize pair.
	virtual bool WritePair (const std::string& _Key, float _Val) = 0;

	// Serialize map.
	virtual bool StartMap () = 0;

	// Serialize map.
	virtual bool FinishMap () = 0;

	// Serialize sequence.
	virtual bool StartSeq () = 0;

	// Serialize sequence.
	virtual bool FinishSeq () = 0;

	// Serialize value.
	virtual bool WriteValue (const std::string& _StrVal) = 0;

	// Serialize value.
	virtual bool WriteValue (int _Val) = 0;

	// Serialize value.
	virtual bool WriteValue (float _Val) = 0;
};


#endif
