#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <windows.h>
#include <strstream>
#include <fstream>
using namespace std;

typedef struct _SETTINGS
{
	DWORD m_PosX;
	DWORD m_PosY;

	DWORD m_dwCreationHeight;
	DWORD m_dwCreationWidth;

 	DWORD m_dwCreationFlags;
} SETTINGS;

class CSettings
{
private:
	SETTINGS settings; 
	string filename;
public:
	CSettings( string );
	~CSettings( void );

	bool load( void );
	bool save( void );
	SETTINGS get( void );
	void set( SETTINGS );
};

#endif
