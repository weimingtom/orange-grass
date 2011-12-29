#include "OrangeGrass.h"
#include "ogresourcefile.h"
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif


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
@Input				pszFilename Name of the file you would like to open
@Returns			true if the file is open
@Description		Opens file for reading
*****************************************************************************/
bool COGResourceFile::OpenForRead(const char* pszFilename)
{
	FILE* pFile = fopen(pszFilename, "rb");
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
 @Function			GetResourcePathASCII
 @Output            _pOutPath output path string
 @Input				_PathLength max. path length
 @Description		Returns the full path to resources
 ****************************************************************************/
void GetResourcePathASCII(char* _pOutPath, int _PathLength)
{
#ifdef WIN32
    {
        wchar_t* pPath = new wchar_t [ _PathLength ];
        GetModuleFileName ( NULL, pPath, _PathLength );
        WideCharToMultiByte( CP_ACP, 0, pPath, -1, _pOutPath, _PathLength, "", false );
    }
    int pos = (int)strlen( _pOutPath );
    while ( --pos )
    {
        if ( _pOutPath [ pos ] == '\\') 
        {
            _pOutPath [ pos ] = '\0';
            break;
        }
        else
            _pOutPath [ pos + 1 ] = ' ';
    }
#else
	NSString* readPath = [[NSBundle mainBundle] resourcePath];
	[readPath getCString:_pOutPath maxLength:_PathLength encoding:NSASCIIStringEncoding];
#endif
}
