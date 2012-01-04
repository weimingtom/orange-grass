#include "OrangeGrass.h"
#include "ogresourcefile.h"
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif
#include "unzip/unzip.h"


// static string represents full path to resource file or folder
static std::string  g_strResourcePath = std::string("");

// resource storage file (ex.: Android .APK)
static void*        g_pResourceStorage = NULL;

// single resource storage file flag
static bool         g_bSingleResourceData = false;


/*!***************************************************************************
@Function			COGResourceFile
@Description		Constructor
*****************************************************************************/
COGResourceFile::COGResourceFile() :
	m_bOpenForRead(false),
	m_Size(0),
    m_BytesReadCount(0),
    m_pData(NULL)
{
}


/*!***************************************************************************
@Function			~COGResourceFile
@Description		Destructor
*****************************************************************************/
COGResourceFile::~COGResourceFile()
{
    Close();
}


/*!***************************************************************************
@Function			OpenForRead
@Input				Filename Name of the file you would like to open
@Returns			true if the file is open
@Description		Opens file for reading
*****************************************************************************/
bool COGResourceFile::OpenForRead(const std::string& Filename)
{
    if (g_bSingleResourceData)
    {
        char strCurrentFileName[2048];
        std::string strPath = std::string("assets/GameResources") + Filename;
		unz_file_info file_info;
        OG_LOG_INFO("COGResourceFile::OpenForRead: Loading %s from resource storage.", strPath.c_str());
		if ( unzLocateFile ( g_pResourceStorage, strPath.c_str(), 2 ) == UNZ_OK )
		{
			unzGetCurrentFileInfo ( g_pResourceStorage, &file_info,
									strCurrentFileName, 
									sizeof ( strCurrentFileName ) - 1,
									NULL, 0, NULL, 0 );
			m_Size = file_info.uncompressed_size;
			char* pData = new char [ m_Size + 1 ];
		    pData[m_Size] = '\0';
			unzOpenCurrentFile ( g_pResourceStorage );
			unzReadCurrentFile ( g_pResourceStorage, pData, m_Size );
			unzCloseCurrentFile ( g_pResourceStorage );
            m_pData = pData;

            m_BytesReadCount = 0;
            m_bOpenForRead = true;
		}
        else
        {
            OG_LOG_ERROR("COGResourceFile::OpenForRead: cannot find resource file %s at resource storage.", strPath.c_str());
        }
    }
    else
    {
        std::string strFilename = g_strResourcePath + std::string("/GameResources") + Filename;
        OG_LOG_INFO("COGResourceFile::OpenForRead: Loading %s from filesystem.", strFilename.c_str());
	    FILE* pFile = fopen(strFilename.c_str(), "rb");
	    if (pFile)
	    {
		    // Get the file size
		    fseek(pFile, 0, SEEK_END);
		    m_Size = ftell(pFile);
		    fseek(pFile, 0, SEEK_SET);

		    // read the data, append a 0 byte as the data might represent a string
		    char* pData = new char[m_Size + 1];
		    pData[m_Size] = '\0';
		    size_t BytesRead = fread(pData, 1, m_Size, pFile);

		    if (BytesRead != m_Size)
		    {
			    delete [] pData;
			    m_Size = 0;
		    }
		    else
		    {
			    m_pData = pData;
			    m_bOpenForRead = true;
		    }
            m_BytesReadCount = 0;
		    fclose(pFile);
	    }
        else
        {
            OG_LOG_ERROR("COGResourceFile::OpenForRead: cannot find resource file %s at filesystem.", strFilename.c_str());
        }
    }
    return m_bOpenForRead;
}


/*!***************************************************************************
@Function			Read
@Output				lpBuffer output buffer
@Input				dwNumberOfBytesToRead number of bytes to read
@Returns			true if succeeded
@Description		Reads number of bytes from file
*****************************************************************************/
bool COGResourceFile::Read(void* lpBuffer, unsigned int dwNumberOfBytesToRead)
{
	_ASSERT(lpBuffer);
	_ASSERT(m_bOpenForRead);

	if (m_BytesReadCount + dwNumberOfBytesToRead > Size()) 
        return false;

	memcpy(lpBuffer, &(StringPtr())[m_BytesReadCount], dwNumberOfBytesToRead);
	m_BytesReadCount += dwNumberOfBytesToRead;
	return true;
}


/*!***************************************************************************
@Function			Skip
@Input				nBytes number of bytes to skip
@Returns			true if succeeded
@Description		Skips reading number of bytes from file
*****************************************************************************/
bool COGResourceFile::Skip(unsigned int nBytes)
{
	_ASSERT(m_bOpenForRead);

    if (m_BytesReadCount + nBytes > Size()) 
        return false;

    m_BytesReadCount += nBytes;
    return true;
}


/*!***************************************************************************
@Function			ReadMarker
@Output				nName output name
@Output				nLen output length
@Returns			true if succeeded
@Description		Reads marker from file
*****************************************************************************/
bool COGResourceFile::ReadMarker(unsigned int &nName, unsigned int &nLen)
{
	_ASSERT(m_bOpenForRead);

    if(!Read(&nName, sizeof(nName)))
        return false;
    if(!Read(&nLen, sizeof(nLen)))
        return false;
    return true;
}


/*!***************************************************************************
@Function			Close
@Description		Closes the file
*****************************************************************************/
void COGResourceFile::Close()
{
	if (m_bOpenForRead)
	{
    	delete [] (char*)m_pData;
		m_pData = NULL;

        m_bOpenForRead = false;
		m_Size = 0;
        m_BytesReadCount = 0;
	}
}


/*!***************************************************************************
 @Function			InitializeResourceSystem
 @Input				_ResourcePath   storage path
 @Input				_bSingleStorage is a single storage flag
 @Description		Initializes resource system
 ****************************************************************************/
void InitializeResourceSystem (const std::string& _ResourcePath, bool _bSingleStorage)
{
    g_strResourcePath = _ResourcePath;
    g_bSingleResourceData = _bSingleStorage;

    if (_bSingleStorage)
    {
    	std::string resStorage = g_strResourcePath;
    	g_pResourceStorage = unzOpen (resStorage.c_str());
        if (!g_pResourceStorage)
        {
            OG_LOG_ERROR("Cannot open resource storage at %s", resStorage.c_str());
        }
        else
        {
            OG_LOG_INFO("Resource storage at %s opened SUCCESSFULLY", resStorage.c_str());
        }
    }
}


/*!***************************************************************************
 @Function			ShutdownResourceSystem
 @Description		Shutdown resource system
 ****************************************************************************/
void ShutdownResourceSystem ()
{
    if (g_pResourceStorage)
    {
        unzClose ( g_pResourceStorage );
        OG_LOG_INFO("Resource storage was closed");
        g_pResourceStorage = NULL;
    }
}
