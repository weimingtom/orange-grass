#include "ResourceFile.h"
#include "Macros.h"
#include <stdio.h>
#include <string.h>


/*!***************************************************************************
@Function			CResourceFile
@Description		Constructor
*****************************************************************************/
CResourceFile::CResourceFile() :
	m_bOpen(false),
	m_Size(0),
    m_BytesReadCount(0),
    m_pData(NULL)
{
}


/*!***************************************************************************
@Function			~CResourceFile
@Description		Destructor
*****************************************************************************/
CResourceFile::~CResourceFile()
{
    Close();
}


/*!***************************************************************************
@Function			Open
@Input				pszFilename Name of the file you would like to open
@Returns			true if the file is open
@Description		Opens file
*****************************************************************************/
bool CResourceFile::Open(const char* pszFilename)
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
			m_bOpen = true;
		}
        m_BytesReadCount = 0;
		fclose(pFile);
	}
    return m_bOpen;
}


/*!***************************************************************************
@Function			Read
@Output				lpBuffer output buffer
@Input				dwNumberOfBytesToRead number of bytes to read
@Returns			true if succeeded
@Description		Reads number of bytes from file
*****************************************************************************/
bool CResourceFile::Read(void* lpBuffer, unsigned int dwNumberOfBytesToRead)
{
	_ASSERT(lpBuffer);
	_ASSERT(m_bOpen);

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
bool CResourceFile::Skip(unsigned int nBytes)
{
	_ASSERT(m_bOpen);

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
bool CResourceFile::ReadMarker(unsigned int &nName, unsigned int &nLen)
{
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
void CResourceFile::Close()
{
	if (m_bOpen)
	{
    	delete [] (char*)m_pData;
		m_bOpen = false;
		m_pData = NULL;
		m_Size = 0;
        m_BytesReadCount = 0;
	}
}
