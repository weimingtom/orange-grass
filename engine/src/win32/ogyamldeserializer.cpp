/*
 *  ogyamldeserializer.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "ogyamldeserializer.h"
#include "IOGCoreHelpers.h"


COGYamlDeserializer::COGYamlDeserializer () :   m_pFile(NULL)
{
}


COGYamlDeserializer::~COGYamlDeserializer ()
{
}


// create deserializer.
bool COGYamlDeserializer::Open (const std::string& _FileName)
{
    m_pFile = fopen(_FileName.c_str(), "rb");
	yaml_parser_initialize(&m_Parser);
	yaml_parser_set_input_file(&m_Parser, m_pFile);

    return true;
}


// close deserializer.
void COGYamlDeserializer::Close ()
{
    if (m_pFile)
    {
        yaml_parser_delete(&m_Parser);
        fclose(m_pFile);
        m_pFile = NULL;
    }
}


// start serialization.
bool COGYamlDeserializer::StartDoc ()
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_STREAM_START_EVENT)
        return false;
    yaml_event_delete(&event);

    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_DOCUMENT_START_EVENT)
        return false;
    yaml_event_delete(&event);

    return true;
}


// finish serialization.
bool COGYamlDeserializer::FinishDoc ()
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_DOCUMENT_END_EVENT)
        return false;
    yaml_event_delete(&event);

    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_STREAM_END_EVENT)
        return false;
    yaml_event_delete(&event);

    return true;
}


// Start map.
bool COGYamlDeserializer::StartMap ()
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_MAPPING_START_EVENT)
        return false;
    yaml_event_delete(&event);

    return true;
}


// Finish map.
bool COGYamlDeserializer::FinishMap ()
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_MAPPING_END_EVENT)
        return false;
    yaml_event_delete(&event);

    return true;
}


// Start sequence.
bool COGYamlDeserializer::StartSeq ()
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SEQUENCE_START_EVENT)
        return false;
    yaml_event_delete(&event);

    return true;
}


// Finish sequence.
bool COGYamlDeserializer::FinishSeq ()
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SEQUENCE_END_EVENT)
        return false;
    yaml_event_delete(&event);

    return true;
}


// Read pair.
bool COGYamlDeserializer::ReadPair (const std::string& _Key, std::string& _pStrVal)
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SCALAR_EVENT)
        return false;
    if (_Key.compare(std::string((const char*)event.data.scalar.value)) != 0)
        return false;
    yaml_event_delete(&event);

    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SCALAR_EVENT)
        return false;
    _pStrVal.assign(std::string((const char*)event.data.scalar.value));
    yaml_event_delete(&event);

    return true;
}


// Read pair.
bool COGYamlDeserializer::ReadPair (const std::string& _Key, int& _Val)
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SCALAR_EVENT)
        return false;
    if (_Key.compare(std::string((const char*)event.data.scalar.value)) != 0)
        return false;
    yaml_event_delete(&event);

    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SCALAR_EVENT)
        return false;
    _Val = atoi((const char*)event.data.scalar.value);
    yaml_event_delete(&event);

    return true;
}


// Read pair.
bool COGYamlDeserializer::ReadPair (const std::string& _Key, float& _Val)
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SCALAR_EVENT)
        return false;
    if (_Key.compare(std::string((const char*)event.data.scalar.value)) != 0)
        return false;
    yaml_event_delete(&event);

    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SCALAR_EVENT)
        return false;
    _Val = (float)atof((const char*)event.data.scalar.value);
    yaml_event_delete(&event);

    return true;
}


// Read value.
bool COGYamlDeserializer::ReadValue (std::string& _pStrVal)
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SCALAR_EVENT)
        return false;
    _pStrVal.assign(std::string((const char*)event.data.scalar.value));
    yaml_event_delete(&event);

    return true;
}


// Read value.
bool COGYamlDeserializer::ReadValue (int& _Val)
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SCALAR_EVENT)
        return false;
    _Val = atoi((const char*)event.data.scalar.value);
    yaml_event_delete(&event);
    return true;
}


// Read value.
bool COGYamlDeserializer::ReadValue (float& _Val)
{
    yaml_event_t event;
    yaml_parser_parse(&m_Parser, &event);
    if (event.type != YAML_SCALAR_EVENT)
        return false;
    _Val = (float)atof((const char*)event.data.scalar.value);
    yaml_event_delete(&event);
    return true;
}
