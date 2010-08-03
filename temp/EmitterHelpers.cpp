#include "EmitterHelpers.h"


bool EmitBeginStream(yaml_emitter_t *emitter)
{
	yaml_event_t event;
	yaml_stream_start_event_initialize(&event, YAML_UTF8_ENCODING);
	if (!yaml_emitter_emit(emitter, &event))
		return false;
	return true;
}


bool EmitEndStream(yaml_emitter_t *emitter)
{
	yaml_event_t event;
	yaml_stream_end_event_initialize(&event);
	if (!yaml_emitter_emit(emitter, &event))
		return false;
	return true;
}


bool EmitBeginDoc(yaml_emitter_t *emitter)
{
	yaml_event_t event;
	yaml_document_start_event_initialize(&event, NULL, NULL, NULL, 0);
	if (!yaml_emitter_emit(emitter, &event))
		return false;
	return true;
}


bool EmitEndDoc(yaml_emitter_t *emitter)
{
	yaml_event_t event;
	yaml_document_end_event_initialize(&event, 0);
	if (!yaml_emitter_emit(emitter, &event))
		return false;
	return true;
}


bool EmitBeginMap(yaml_emitter_t *emitter)
{
	yaml_event_t event;
	yaml_mapping_start_event_initialize(&event, NULL, NULL, 0, YAML_BLOCK_MAPPING_STYLE);
	if (!yaml_emitter_emit(emitter, &event))
		return false;
	return true;
}


bool EmitEndMap(yaml_emitter_t *emitter)
{
	yaml_event_t event;
	yaml_mapping_end_event_initialize(&event);
	if (!yaml_emitter_emit(emitter, &event))
		return false;
	return true;
}


bool EmitMapKeyVal(yaml_emitter_t *emitter, const char* pKey, const char* pVal)
{
	yaml_event_t event;
	yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)pKey, -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
	if (!yaml_emitter_emit(emitter, &event))
		return false;
	if (pVal != NULL)
	{
		yaml_scalar_event_initialize(&event, NULL, NULL, (unsigned char*)pVal, -1, 1, 0, YAML_PLAIN_SCALAR_STYLE);
		if (!yaml_emitter_emit(emitter, &event))
			return false;
	}
	return true;
}


bool EmitBeginSeq(yaml_emitter_t *emitter)
{
	yaml_event_t event;
	yaml_sequence_start_event_initialize(&event, NULL, NULL, 0, YAML_BLOCK_SEQUENCE_STYLE);
	if (!yaml_emitter_emit(emitter, &event))
		return false;
	return true;
}


bool EmitEndSeq(yaml_emitter_t *emitter)
{
	yaml_event_t event;
	yaml_sequence_end_event_initialize(&event);
	if (!yaml_emitter_emit(emitter, &event))
		return false;
	return true;
}
