/*
 *  ogyamlserializer.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "ogyamlserializer.h"
#include "IOGCoreHelpers.h"


COGYamlSerializer::COGYamlSerializer () :   m_pFile(NULL)
{
}


COGYamlSerializer::~COGYamlSerializer ()
{
    Close();
}


// create serializer to file.
bool COGYamlSerializer::Open (const std::string& _FileName)
{
    m_pFile = fopen(_FileName.c_str(), "wb");
    if (!m_pFile)
        return false;

	yaml_emitter_initialize(&m_Emitter);
	yaml_emitter_set_output_file(&m_Emitter, m_pFile);
    return true;
}


// close serializer to file.
void COGYamlSerializer::Close ()
{
    if (m_pFile)
    {
        yaml_emitter_delete(&m_Emitter);
        fclose(m_pFile);
        m_pFile = NULL;
    }
}


// start serialization.
bool COGYamlSerializer::StartDoc ()
{
	yaml_event_t event;
	yaml_stream_start_event_initialize(&event, YAML_UTF8_ENCODING);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;

	yaml_document_start_event_initialize(&event, NULL, NULL, NULL, 0);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;
	return true;
}


// finish serialization.
bool COGYamlSerializer::FinishDoc ()
{
	yaml_event_t event;
	yaml_document_end_event_initialize(&event, 0);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;

    yaml_stream_end_event_initialize(&event);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;
	return true;
}


// Serialize pair.
bool COGYamlSerializer::WritePair (const std::string& _Key, const std::string& _StrVal)
{
	yaml_event_t event;
    yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)_Key.c_str(), -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;
    yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)_StrVal.c_str(), -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
    if (!yaml_emitter_emit(&m_Emitter, &event))
        return false;
	return true;
}


// Serialize pair.
bool COGYamlSerializer::WritePair (const std::string& _Key, int _Val)
{
	yaml_event_t event;
    yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)_Key.c_str(), -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;
    char StrVal[32];
    sprintf(StrVal, "%d", _Val);
    yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)StrVal, -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
    if (!yaml_emitter_emit(&m_Emitter, &event))
        return false;
	return true;
}


// Serialize pair.
bool COGYamlSerializer::WritePair (const std::string& _Key, float _Val)
{
	yaml_event_t event;
    yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)_Key.c_str(), -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;
    char StrVal[32];
    sprintf(StrVal, "%f", _Val);
    yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)StrVal, -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
    if (!yaml_emitter_emit(&m_Emitter, &event))
        return false;
	return true;
}


// Serialize map.
bool COGYamlSerializer::StartMap ()
{
	yaml_event_t event;
	yaml_mapping_start_event_initialize(&event, NULL, NULL, 0, YAML_BLOCK_MAPPING_STYLE);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;
	return true;
}


// Serialize map.
bool COGYamlSerializer::FinishMap ()
{
	yaml_event_t event;
	yaml_mapping_end_event_initialize(&event);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;
	return true;
}


// Serialize sequence.
bool COGYamlSerializer::StartSeq ()
{
	yaml_event_t event;
	yaml_sequence_start_event_initialize(&event, NULL, NULL, 0, YAML_BLOCK_SEQUENCE_STYLE);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;
	return true;
}


// Serialize sequence.
bool COGYamlSerializer::FinishSeq ()
{
	yaml_event_t event;
	yaml_sequence_end_event_initialize(&event);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;
	return true;
}


// Serialize value.
bool COGYamlSerializer::WriteValue (const std::string& _StrVal)
{
	yaml_event_t event;
    yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)_StrVal.c_str(), -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
	if (!yaml_emitter_emit(&m_Emitter, &event))
		return false;
	return true;
}


// Serialize value.
bool COGYamlSerializer::WriteValue (int _Val)
{
	yaml_event_t event;
    char StrVal[32];
    sprintf(StrVal, "%d", _Val);
    yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)StrVal, -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
    if (!yaml_emitter_emit(&m_Emitter, &event))
        return false;
	return true;
}


// Serialize value.
bool COGYamlSerializer::WriteValue (float _Val)
{
	yaml_event_t event;
    char StrVal[32];
    sprintf(StrVal, "%f", _Val);
    yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)StrVal, -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
    if (!yaml_emitter_emit(&m_Emitter, &event))
        return false;
	return true;
}
