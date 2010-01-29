#ifndef OGLEVELMANAGER_H_
#define OGLEVELMANAGER_H_

#include "IOGLevelManager.h"
#include "ogterrain.h"
#include "tinyxml.h"
#include <string>
#include <map>


class COGLevelManager : public IOGLevelManager
{
public:

	// constructor.
	COGLevelManager ();

	// destructor.
	virtual ~COGLevelManager ();
		
	// load from config file.
	virtual bool Init (const char* _pLevelCfgFile);

    // get level path
    virtual const char* GetLevelPath () const;
	
	// get terrain.
	virtual IOGTerrain* GetEditableTerrain (int _level);
	
	// save terrain.
	virtual bool SaveEditableTerrain (int _level);

private:

	COGTerrain*	m_LevelList[16];
	char		m_LevelsRootPath[2048];
};


#endif
