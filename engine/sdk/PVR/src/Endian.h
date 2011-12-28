#ifndef ENDIAN_H_
#define ENDIAN_H_


/*!***************************************************************************
 @Function		PVRTIsLittleEndian
 @Returns		True if the platform the code is ran on is little endian
 @Description	Returns true if the platform the code is ran on is little endian
 *****************************************************************************/
inline bool PVRTIsLittleEndian()
{
	static bool bLittleEndian;
	static bool bIsInit = false;
	
	if(!bIsInit)
	{
		short int word = 0x0001;
		char *byte = (char*) &word;
		bLittleEndian = byte[0] ? true : false;
		bIsInit = true;
	}
	
	return bLittleEndian;
}


#endif // ENDIAN_H_

