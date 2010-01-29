#ifndef IOGLEVELMGR_H_
#define IOGLEVELMGR_H_

#include "IOGTerrain.h"


class IOGLevelManager
{
public:
	virtual ~IOGLevelManager () {}
		
	// load from config file.
	virtual bool Init (const char* _pLevelCfgFile) = 0;

    // get level path
    virtual const char* GetLevelPath () const = 0;
	
	// get terrain.
	virtual IOGTerrain* GetEditableTerrain (int _level) = 0;
	
	// save terrain.
	virtual bool SaveEditableTerrain (int _level) = 0;
};

#endif
