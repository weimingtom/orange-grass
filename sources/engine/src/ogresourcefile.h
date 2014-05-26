/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef OGRESOURCEFILE_H_
#define OGRESOURCEFILE_H_

#include "IOGResourceFile.h"


/*!***************************************************************************
 @Class COGResourceFile
 @Brief Resource file wrapper
*****************************************************************************/
class COGResourceFile : public IOGResourceFile
{
public:
	/*!***************************************************************************
	@Function			COGResourceFile
	@Description		Constructor
	*****************************************************************************/
	COGResourceFile();

	/*!***************************************************************************
	@Function			~COGResourceFile
	@Description		Destructor
	*****************************************************************************/
	virtual ~COGResourceFile();

    /*!***************************************************************************
	@Function			OpenForRead
	@Input				Filename Name of the file you would like to open
	@Returns			true if the file is open
	@Description		Opens file for reading
	*****************************************************************************/
    virtual bool OpenForRead(const std::string& Filename);

	/*!***************************************************************************
	@Function			IsOpenForRead
	@Returns			true if the file is open for read
	@Description		Is the file open for read
	*****************************************************************************/
    virtual bool IsOpenForRead() const { return m_bOpenForRead; }

	/*!***************************************************************************
	@Function			Size
	@Returns			The size of the opened file
	@Description		Returns the size of the opened file
	*****************************************************************************/
    virtual size_t Size() const { return m_Size; }

	/*!***************************************************************************
	@Function			DataPtr
	@Returns			A pointer to the file data
	@Description		Returns a pointer to the file data
	*****************************************************************************/
	virtual const void* DataPtr() const { return m_pData; }
	
	/*!***************************************************************************
	@Function			StringPtr
	@Returns			The file data as a string
	@Description		Returns the file as a null-terminated string
	*****************************************************************************/
    virtual const char* StringPtr() const { return m_pData; }

	/*!***************************************************************************
	@Function			Read
	@Output				lpBuffer output buffer
	@Input				dwNumberOfBytesToRead number of bytes to read
	@Returns			true if succeeded
	@Description		Reads number of bytes from file
	*****************************************************************************/
    virtual bool Read(void* lpBuffer, unsigned int dwNumberOfBytesToRead);

    /*!***************************************************************************
	@Function			Skip
	@Input				nBytes number of bytes to skip
	@Returns			true if succeeded
	@Description		Skips reading number of bytes from file
	*****************************************************************************/
	virtual bool Skip(unsigned int nBytes);

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
	virtual bool ReadMarker(unsigned int &nName, unsigned int &nLen);

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
	virtual void Close();

protected:
	bool m_bOpenForRead;
	size_t m_Size;
	size_t m_BytesReadCount;
	const char* m_pData;
};


/*!***************************************************************************
 @Function			InitializeResourceSystem
 @Input				_ResourcePath   storage path
 @Input				_bSingleStorage is a single storage flag
 @Description		Initializes resource system
 ****************************************************************************/
void InitializeResourceSystem (const std::string& _ResourcePath, bool _bSingleStorage);


/*!***************************************************************************
 @Function			ShutdownResourceSystem
 @Description		Shutdown resource system
 ****************************************************************************/
void ShutdownResourceSystem ();


#endif
