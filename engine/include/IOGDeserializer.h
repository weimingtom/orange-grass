/*
 *  IOGDeserializer.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGDESERIALIZER_H_
#define IOGDESERIALIZER_H_

#include <string>

enum OGParserMarkers
{
    OG_PARSER_MAP_START,
    OG_PARSER_MAP_END,
    OG_PARSER_SEQ_START,
    OG_PARSER_SEQ_END,
};

class IOGDeserializer
{
public:
	virtual ~IOGDeserializer () {}

	// create deserializer.
	virtual bool Open (const std::string& _FileName) = 0;

	// close deserializer.
	virtual void Close () = 0;

	// start serialization.
	virtual bool StartDoc () = 0;

	// finish serialization.
	virtual bool FinishDoc () = 0;

	// Read pair.
	virtual bool ReadPair (const std::string& _Key, std::string& _pStrVal) = 0;

	// Read pair.
	virtual bool ReadPair (const std::string& _Key, int& _Val) = 0;

	// Read pair.
	virtual bool ReadPair (const std::string& _Key, float& _Val) = 0;

	// Start map.
	virtual bool StartMap () = 0;

	// Finish map.
	virtual bool FinishMap () = 0;

	// Start sequence.
	virtual bool StartSeq () = 0;

	// Finish sequence.
	virtual bool FinishSeq () = 0;

	// Read value.
	virtual bool ReadValue (std::string& _pStrVal) = 0;

	// Read value.
	virtual bool ReadValue (int& _Val) = 0;

	// Read value.
	virtual bool ReadValue (float& _Val) = 0;
};


#endif
