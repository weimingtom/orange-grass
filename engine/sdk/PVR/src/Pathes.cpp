#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\include\Pathes.h"


void GetResourcePathASCII(char* _pOutPath, int _PathLength)
{
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
			_pOutPath [ pos + 1 ] = '\0';
			break;
		}
		else
			_pOutPath [ pos + 1 ] = ' ';
	}
}
