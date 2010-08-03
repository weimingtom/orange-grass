/*
 *  OGYamlDeserializer.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGYAMLDESERIALIZER_H_
#define OGYAMLDESERIALIZER_H_

#include "IOGDeserializer.h"
#include <yaml.h>
#include <stdio.h>


class COGYamlDeserializer : public IOGDeserializer
{
public:
    COGYamlDeserializer ();
	virtual ~COGYamlDeserializer ();

	// create deserializer.
	virtual bool Open (const std::string& _FileName);

	// close deserializer.
	virtual void Close ();

	// start serialization.
	virtual bool StartDoc ();

	// finish serialization.
	virtual bool FinishDoc ();

	// Read pair.
	virtual bool ReadPair (const std::string& _Key, std::string& _pStrVal);

	// Read pair.
	virtual bool ReadPair (const std::string& _Key, int& _Val);

	// Read pair.
	virtual bool ReadPair (const std::string& _Key, float& _Val);

	// Start map.
	virtual bool StartMap ();

    // Finish map.
	virtual bool FinishMap ();

	// Start sequence.
	virtual bool StartSeq ();

	// Finish sequence.
	virtual bool FinishSeq ();

	// Read value.
	virtual bool ReadValue (std::string& _pStrVal);

	// Read value.
	virtual bool ReadValue (int& _Val);

	// Read value.
	virtual bool ReadValue (float& _Val);

private:

    yaml_parser_t   m_Parser;
    FILE*           m_pFile;
};


#endif
