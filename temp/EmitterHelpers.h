#ifndef EMITTERHELPERS_H_
#define EMITTERHELPERS_H_

#include <yaml.h>


bool EmitBeginStream(yaml_emitter_t *emitter);
bool EmitEndStream(yaml_emitter_t *emitter);
bool EmitBeginDoc(yaml_emitter_t *emitter);
bool EmitEndDoc(yaml_emitter_t *emitter);
bool EmitBeginMap(yaml_emitter_t *emitter);
bool EmitEndMap(yaml_emitter_t *emitter);
bool EmitMapKeyVal(yaml_emitter_t *emitter, const char* pKey, const char* pVal);
bool EmitBeginSeq(yaml_emitter_t *emitter);
bool EmitEndSeq(yaml_emitter_t *emitter);

#endif