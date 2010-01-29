#define _CRT_SECURE_NO_WARNINGS
#include "OrangeGrass.h"
#include "oglevelmanager.h"
#include "Pathes.h"


// constructor.
COGLevelManager::COGLevelManager ()
{
	GetResourcePathASCII(m_LevelsRootPath, 2048);
	sprintf(m_LevelsRootPath, "%sLevels", m_LevelsRootPath);
	memset(m_LevelList, 0, sizeof(m_LevelList));
}


// destructor.
COGLevelManager::~COGLevelManager ()
{
	for (int i = 0; i < 16; ++i)
	{
		OG_SAFE_DELETE (m_LevelList[i]);
	}
}


// load from config file.
bool COGLevelManager::Init (const char* _pLevelCfgFile)
{
	char file_path[2048];
	TiXmlDocument* pXmlSettings = new TiXmlDocument("levels.xml");
	sprintf(file_path, "%s\\%s", m_LevelsRootPath, _pLevelCfgFile);
	if (!pXmlSettings->LoadFile (file_path))
		return false;
	TiXmlHandle* hDoc = new TiXmlHandle (pXmlSettings);

	int index = 0;
	TiXmlHandle hTerrainsRoot = hDoc->FirstChild ( "Terrains" );
	TiXmlHandle TerrainHandle = hTerrainsRoot.Child ( "Terrain", index );
	while (TerrainHandle.Node ())
	{
		TiXmlElement* pElement = TerrainHandle.Element();
		const char* terrain_alias = pElement->Attribute ("alias");
		const char* terrain_file = pElement->Attribute ("map");
		sprintf(file_path, "%s/Level_%d/%s", m_LevelsRootPath, index, terrain_file);
		COGTerrain* pTerrain = new COGTerrain ();
		pTerrain->Init (terrain_alias, file_path);
		m_LevelList[index] = pTerrain;
		TerrainHandle = hTerrainsRoot.Child ( "Terrain", ++index );
	}

	return true;
}


// get level path
const char* COGLevelManager::GetLevelPath () const
{
	return m_LevelsRootPath;
}


// get terrain.
IOGTerrain* COGLevelManager::GetEditableTerrain (int _level)
{
	COGTerrain* pLevel = (COGTerrain*)(m_LevelList[_level]);
	if (pLevel)
	{
		if (pLevel->GetLoadState() == OG_RESSTATE_DEFINED)
		{
			pLevel->SetWorldPosition (Vec3(0, 0, 0));
			pLevel->Load ();
			pLevel->SetTexture(GetResourceMgr()->GetTexture("land"));
		}
	}
	return pLevel;
}

	
// save terrain.
bool COGLevelManager::SaveEditableTerrain (int _level)
{
	COGTerrain* pLevel = (COGTerrain*)(m_LevelList[_level]);
	if (pLevel)
	{
		if (pLevel->GetLoadState() == OG_RESSTATE_LOADED)
		{
			char file_path[2048];
			sprintf(file_path, "%s/Level_%d", m_LevelsRootPath, _level);
			pLevel->Save (file_path);
		}
	}
	return true;
}
