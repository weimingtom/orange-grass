#ifndef IOGRESOURCEFILE_H_
#define IOGRESOURCEFILE_H_

#include <stdlib.h>
#include <string>


/*!***************************************************************************
 @Class IOGResourceFile
 @Brief Resource file wrapper
 ****************************************************************************/
class IOGResourceFile
{
public:
	/*!***************************************************************************
	@Function			~COGResourceFile
	@Description		Destructor
	*****************************************************************************/
    virtual ~IOGResourceFile() {}

    /*!***************************************************************************
	@Function			OpenForRead
	@Input				Filename Name of the file you would like to open
	@Returns			true if the file is open
	@Description		Opens file for reading
	*****************************************************************************/
    virtual bool OpenForRead(const std::string& Filename) = 0;

	/*!***************************************************************************
	@Function			IsOpenForRead
	@Returns			true if the file is open for read
	@Description		Is the file open for read
	*****************************************************************************/
    virtual bool IsOpenForRead() const = 0;

	/*!***************************************************************************
	@Function			Size
	@Returns			The size of the opened file
	@Description		Returns the size of the opened file
	*****************************************************************************/
    virtual size_t Size() const = 0;

	/*!***************************************************************************
	@Function			DataPtr
	@Returns			A pointer to the file data
	@Description		Returns a pointer to the file data
	*****************************************************************************/
	virtual const void* DataPtr() const = 0;
	
	/*!***************************************************************************
	@Function			StringPtr
	@Returns			The file data as a string
	@Description		Returns the file as a null-terminated string
	*****************************************************************************/
    virtual const char* StringPtr() const = 0;

	/*!***************************************************************************
	@Function			Read
	@Output				lpBuffer output buffer
	@Input				dwNumberOfBytesToRead number of bytes to read
	@Returns			true if succeeded
	@Description		Reads number of bytes from file
	*****************************************************************************/
    virtual bool Read(void* lpBuffer, unsigned int dwNumberOfBytesToRead) = 0;

    /*!***************************************************************************
	@Function			Skip
	@Input				nBytes number of bytes to skip
	@Returns			true if succeeded
	@Description		Skips reading number of bytes from file
	*****************************************************************************/
	virtual bool Skip(unsigned int nBytes) = 0;

	/*!***************************************************************************
	@Function			ReadMarker
	@Output				nName output name
	@Output				nLen output length
	@Returns			true if succeeded
	@Description		Reads marker from file
	*****************************************************************************/
	virtual bool ReadMarker(unsigned int &nName, unsigned int &nLen) = 0;

	/*!***************************************************************************
	@Function			Close
	@Description		Closes the file
	*****************************************************************************/
	virtual void Close() = 0;
};


#endif
