#include <stdio.h>
#include <stdlib.h>
#include <yaml.h>


void parse_data(yaml_parser_t *parser);
void emit_data(yaml_emitter_t *emitter);

bool EmitBeginStream(yaml_emitter_t *emitter);
bool EmitEndStream(yaml_emitter_t *emitter);
bool EmitBeginDoc(yaml_emitter_t *emitter);
bool EmitEndDoc(yaml_emitter_t *emitter);
bool EmitBeginMap(yaml_emitter_t *emitter);
bool EmitEndMap(yaml_emitter_t *emitter);
bool EmitMapKeyVal(yaml_emitter_t *emitter, const char* pKey, const char* pVal);
bool EmitBeginSeq(yaml_emitter_t *emitter);
bool EmitEndSeq(yaml_emitter_t *emitter);


int main (int argc, char **argv) 
{
	yaml_parser_t parser;
	FILE *source = fopen("test.yaml", "rb");
	yaml_parser_initialize(&parser);
	yaml_parser_set_input_file(&parser, source);
	parse_data(&parser);
	yaml_parser_delete(&parser);
	fclose(source);

	yaml_emitter_t emitter;
	FILE *dest = fopen("test_out.yaml", "wb");
	yaml_emitter_initialize(&emitter);
	yaml_emitter_set_output_file(&emitter, dest);
	emit_data(&emitter);
	yaml_emitter_delete(&emitter);
	fclose(dest);

	return(0);
}


void parse_data(yaml_parser_t *parser) 
{
    yaml_event_t event;

	bool bDone = false;
    while (1) 
	{
        yaml_parser_parse(parser, &event);

        switch (event.type)
		{
		case YAML_SCALAR_EVENT:
			{
				yaml_char_t* pVal = event.data.scalar.value;
				printf ("VAL = %s\n", pVal);
			}
			break;

		case YAML_MAPPING_START_EVENT:
			{
				yaml_char_t* pVal = event.data.mapping_start.anchor;
				printf ("MAP TAG = %s\n", pVal);
			}
			break;

		case YAML_SEQUENCE_START_EVENT:
			{
				yaml_char_t* pVal = event.data.sequence_start.anchor;
				printf ("SEQ TAG = %s\n", pVal);
			}
			break;

		case YAML_STREAM_END_EVENT:
			bDone = true;
			break;
        }

        yaml_event_delete(&event);

		if (bDone)
			break;
    }
}


void emit_data(yaml_emitter_t *emitter)
{
	EmitBeginStream(emitter);
		EmitBeginDoc(emitter);
			EmitBeginMap(emitter);
				EmitMapKeyVal(emitter, "levels", NULL);
				EmitBeginSeq(emitter);
					EmitBeginMap(emitter);
						EmitMapKeyVal(emitter, "terrain", "level_0");
						EmitMapKeyVal(emitter, "scene_file", "Levels\\Level_0\\level_0.scn");
					EmitEndMap(emitter);
					EmitBeginMap(emitter);
						EmitMapKeyVal(emitter, "terrain", "level_1");
						EmitMapKeyVal(emitter, "scene_file", "Levels\\Level_1\\level_1.scn");
					EmitEndMap(emitter);
				EmitEndSeq(emitter);
			EmitEndMap(emitter);
		EmitEndDoc(emitter);
	EmitEndStream(emitter);
}
