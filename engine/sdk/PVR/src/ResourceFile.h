#ifndef RESOURCEFILE_H_
#define RESOURCEFILE_H_

#include <stdlib.h>


/*!***************************************************************************
 @Class CResourceFile
 @Brief Simple resource file wrapper
*****************************************************************************/
class CResourceFile
{
public:
	/*!***************************************************************************
	@Function			CResourceFile
	@Description		Constructor
	*****************************************************************************/
	CResourceFile();

	/*!***************************************************************************
	@Function			~CResourceFile
	@Description		Destructor
	*****************************************************************************/
	virtual ~CResourceFile();

    /*!***************************************************************************
	@Function			Open
	@Input				pszFilename Name of the file you would like to open
	@Returns			true if the file is open
	@Description		Opens file
	*****************************************************************************/
	bool Open(const char* pszFilename);

	/*!***************************************************************************
	@Function			IsOpen
	@Returns			true if the file is open
	@Description		Is the file open
	*****************************************************************************/
    bool IsOpen() const { return m_bOpen; }

	/*!***************************************************************************
	@Function			Size
	@Returns			The size of the opened file
	@Description		Returns the size of the opened file
	*****************************************************************************/
    size_t Size() const { return m_Size; }

	/*!***************************************************************************
	@Function			DataPtr
	@Returns			A pointer to the file data
	@Description		Returns a pointer to the file data
	*****************************************************************************/
	const void* DataPtr() const { return m_pData; }
	
	/*!***************************************************************************
	@Function			StringPtr
	@Returns			The file data as a string
	@Description		Returns the file as a null-terminated string
	*****************************************************************************/
    const char* StringPtr() const { return m_pData; }

	/*!***************************************************************************
	@Function			Read
	@Output				lpBuffer output buffer
	@Input				dwNumberOfBytesToRead number of bytes to read
	@Returns			true if succeeded
	@Description		Reads number of bytes from file
	*****************************************************************************/
    bool Read(void* lpBuffer, unsigned int dwNumberOfBytesToRead);

    /*!***************************************************************************
	@Function			Skip
	@Input				nBytes number of bytes to skip
	@Returns			true if succeeded
	@Description		Skips reading number of bytes from file
	*****************************************************************************/
	bool Skip(unsigned int nBytes);

	/*!***************************************************************************
	@Function			Read
	@Output				n data
	@Returns			true if succeeded
	@Description		Reads data from file
	*****************************************************************************/
	template <typename T> bool Read(T &n) { return Read(&n, sizeof(T)); }

	/*!***************************************************************************
	@Function			ReadMarker
	@Output				nName output name
	@Output				nLen output length
	@Returns			true if succeeded
	@Description		Reads marker from file
	*****************************************************************************/
	bool ReadMarker(unsigned int &nName, unsigned int &nLen);

	/*!***************************************************************************
	@Function			ReadAfterAlloc
	@Output				lpBuffer output buffer
	@Input				dwNumberOfBytesToRead number of bytes to read
	@Returns			true if succeeded
	@Description		Allocates memory and reads number of bytes from file
	*****************************************************************************/
	template <typename T> bool ReadAfterAlloc(
        T* &lpBuffer, 
        unsigned int dwNumberOfBytesToRead)
    {
        if(!SafeAlloc(lpBuffer, dwNumberOfBytesToRead))
            return false;
        return Read(lpBuffer, dwNumberOfBytesToRead);
    }

	/*!***************************************************************************
	@Function			Close
	@Description		Closes the file
	*****************************************************************************/
	void Close();

protected:
	bool m_bOpen;
	size_t m_Size;
	size_t m_BytesReadCount;
	const char* m_pData;
};


#endif
